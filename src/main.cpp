#include <AubioWrapper.h>
#include <AudioIO.h>
#include <AudioIOVariantFactory.h>
#include <PAWrapper.h>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>

enum AudioBackends { PortAudio };

#define PITCH_WINDOW 4096

int main(int argc, char **argv) {
  AudioIOVariantFactory audioFactory;

  // Register and create the PortAudio Api
  audioFactory.add<AudioBackends::PortAudio, PAWrapper>();
  std::unique_ptr<AudioIO> pA = audioFactory.create(AudioBackends::PortAudio);

  // Create our Pitch Detection object
  const AubioWrapper aubio(PITCH_WINDOW, pA->getSampleRate());

  // Write callback for when PortAudio has data
  std::vector<SAMPLE> buffer(PITCH_WINDOW);
  AudioIO::RecordCBHandle callback = [&](std::vector<SAMPLE> &&v) {
    const size_t vSize = v.size();
    for (uint_t i = 0; i < PITCH_WINDOW - vSize; i++)
      buffer[i] = buffer[i + vSize];

    std::move(v.begin(), v.end(), buffer.end() - vSize);
    std::cout << aubio.detectPitch(buffer) << std::endl;
  };

  pA->startStream(callback);

  std::this_thread::sleep_for(std::chrono::seconds(30));

  pA->stopStream();

  return 0;
}
