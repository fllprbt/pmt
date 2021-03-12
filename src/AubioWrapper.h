#ifndef AUBIOWRAPPER_H
#define AUBIOWRAPPER_H

#include "Types.h"
#include <aubio.h>
#include <string>
#include <vector>

class AubioWrapper {
public:
  AubioWrapper(size_t bufferSize, size_t sampleRate);
  AubioWrapper(size_t bufferSize, size_t sampleRate, SAMPLE tolerance,
               SAMPLE silence);

  float detectPitch(const std::vector<SAMPLE>) const;

private:
  size_t _bufferSize;

  typedef const std::function<void(aubio_pitch_t *ptr)> PitchDetectorDeleter;
  std::unique_ptr<aubio_pitch_t, PitchDetectorDeleter> _pitchDetector;

  typedef const std::function<void(fvec_t *ptr)> FVecDeleter;
  FVecDeleter _fVecDeleter;
};

#endif // AUBIOWRAPPER_H
