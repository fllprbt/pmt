#include "AubioWrapper.h"
#include <array>
#include <iostream>
#include <math.h>

AubioWrapper::AubioWrapper(size_t bufferSize, size_t sampleRate)
    : _bufferSize(bufferSize),
      _pitchDetector(
          new_aubio_pitch("default", bufferSize, bufferSize / 4, sampleRate),
          [](aubio_pitch_t *ptr) { del_aubio_pitch(ptr); }),
      _fVecDeleter([](fvec_t *ptr) { del_fvec(ptr); }) {}

AubioWrapper::AubioWrapper(size_t bufferSize, size_t sampleRate,
                           SAMPLE tolerance, SAMPLE silence)
    : _bufferSize(bufferSize),
      _pitchDetector(
          new_aubio_pitch("default", bufferSize, bufferSize / 4, sampleRate),
          [](aubio_pitch_t *ptr) { del_aubio_pitch(ptr); }),
      _fVecDeleter([](fvec_t *ptr) { del_fvec(ptr); }) {
  if (tolerance != 0.)
    aubio_pitch_set_tolerance(_pitchDetector.get(), tolerance);
  if (silence != -90.)
    aubio_pitch_set_silence(_pitchDetector.get(), silence);
}

float AubioWrapper::detectPitch(const std::vector<SAMPLE> audioInput) const {
  std::unique_ptr<fvec_t, FVecDeleter> inputBuffer(new_fvec(_bufferSize),
                                                   _fVecDeleter);
  for (size_t i = 0; i < _bufferSize; i++) {
    inputBuffer->data[i] = audioInput[i];
  }

  std::unique_ptr<fvec_t, FVecDeleter> pitchOutput(new_fvec(1), _fVecDeleter);

  aubio_pitch_do(_pitchDetector.get(), inputBuffer.get(), pitchOutput.get());

  return fvec_get_sample(pitchOutput.get(), 0);
}
