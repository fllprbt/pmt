#include <AubioWrapper.h>
#include <AudioIO.h>
#include <AudioIOVariantFactory.h>
#include <PAWrapper.h>
#include <chrono>
#include <iostream>
#include <thread>

enum AudioBackends { PortAudio };

int main(int argc, char **argv) {
  AudioIOVariantFactory audioFactory;

  // Register and create the PortAudio Api
  audioFactory.add<AudioBackends::PortAudio, PAWrapper>();
  std::unique_ptr<AudioIO> pA = audioFactory.create(AudioBackends::PortAudio);

  // Create our Pitch Detection object
  const AubioWrapper aubio(pA->getFrames(), pA->getSampleRate());

  // Write callback for when PortAudio has data
  AudioIO::RecordCBHandle callback = [&](std::vector<SAMPLE> &&v) {
    std::cout << aubio.detectPitch(v) << std::endl;
  };

  pA->startStream(callback);

  std::this_thread::sleep_for(std::chrono::seconds(30));

  pA->stopStream();

  return 0;
}
