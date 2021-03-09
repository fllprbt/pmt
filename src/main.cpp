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

  pA->startStream(
      [](std::vector<SAMPLE> &&v) { std::cout << "Called" << std::endl; });

  std::this_thread::sleep_for(std::chrono::seconds(5));

  pA->stopStream();

  return 0;
}
