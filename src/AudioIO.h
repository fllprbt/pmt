#ifndef AUDIOIO_H
#define AUDIOIO_H

#include <string>
#include <vector>

#include "stdint.h"

typedef float SAMPLE;
typedef void (*NotifyCallbackHandle)(std::vector<SAMPLE> &&);

class AudioIO {
public:
  AudioIO();
  AudioIO(AudioIO &&other);
  AudioIO &operator=(AudioIO &&other);
  virtual ~AudioIO() {}

  size_t _sampleRate;
  size_t _frames;
  size_t _channels;
  SAMPLE _silence;

  // The callback of the handle is delicate place, please avoid blocking
  virtual std::string startStream(NotifyCallbackHandle notifyHandle) = 0;
  virtual std::string stopStream() = 0;
};

#endif // AUDIOIO_H
