#ifndef AUDIOIO_H
#define AUDIOIO_H

#include <string>
#include <vector>

#include "stdint.h"

typedef float SAMPLE;

/*
 * Audio callbacks are to be passed in different sound APIs for consumption when
 * there are blocks of sound available. Often, the handlers of these APIs which
 * will trigger the callbacks are delicate places, so please avoid blocking and
 * other time consuming operations to prevent data loss.
 */

// Record audio input callback contract
typedef void (*RecordCBHandle)(std::vector<SAMPLE> &&);

class AudioIO {
public:
  AudioIO();
  AudioIO(AudioIO &&other);
  AudioIO &operator=(AudioIO &&other);
  virtual ~AudioIO() {}

  virtual std::string startStream(RecordCBHandle recordCBHandle) = 0;
  virtual std::string stopStream() = 0;

protected:
  size_t _sampleRate;
  size_t _frames;
  size_t _inputChannels;
  size_t _outputChannels;
  SAMPLE _silence;
};

#endif // AUDIOIO_H
