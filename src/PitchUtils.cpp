#include "PitchUtils.h"
#include <iostream>
#include <math.h>

PitchUtils::DistanceInfo NULL_DISTANCE{
    0, 0, 0, 0, "UNKNOWN",
};

PitchUtils::PitchUtils()
    : _chromaticScale{"A",     "A#/Bb", "B", "C",     "C#/Db", "D",
                      "D#/Eb", "E",     "F", "F#/Gb", "G"},
      _frequencyTable(generateFrequencyTable()) {}

// Returns negative values for octaves below base (C4's octave)
int PitchUtils::getOctave(const double frequency) const {
  if (frequency == 0)
    return LOWEST_OCTAVE;

  int octave = floor(log2(frequency / C4));

  // TODO: generate extended frequency table (even if its frequencies cannot be
  // detected properly) to avoid edge case conditionals
  if (octave < LOWEST_OCTAVE)
    octave = LOWEST_OCTAVE;

  if (octave > HIGHEST_OCTAVE)
    octave = HIGHEST_OCTAVE;

  return octave;
}

// Utility which generates a table of frequencies, should be extended to receive
// custom octave bounds in the future or just use longer bounds.
PitchUtils::FrequencyTable PitchUtils::generateFrequencyTable() const {
  double distanceRatio = pow(2.0, 1.0 / 12.0);

  // Start populating the frequency table starting from c3 and going lower
  double c3 = C4 / 2;
  const size_t lowerOctavesCount = abs(LOWEST_OCTAVE);
  size_t currentOctaveIndex = lowerOctavesCount - 1; // array index

  PitchUtils::FrequencyTable tmpTable(lowerOctavesCount + HIGHEST_OCTAVE +
                                          1, // base octave
                                      std::vector<double>(OCTAVE_NOTES));

  for (size_t currOctaveCFreq = c3;
       currOctaveCFreq >= c3 / pow(2, lowerOctavesCount - 1); // -1 for self
       currOctaveCFreq /= 2, currentOctaveIndex--) {
    for (size_t j = 0; j < OCTAVE_NOTES; j++) {
      tmpTable[currentOctaveIndex][j] = currOctaveCFreq * pow(distanceRatio, j);
    }
  }

  // Continue populating now upwards, starting with C4's octave.
  currentOctaveIndex = lowerOctavesCount;
  for (size_t currOctaveCFreq = C4;
       currOctaveCFreq <= C4 * pow(2, HIGHEST_OCTAVE); // -1 for self
       currOctaveCFreq *= 2, currentOctaveIndex++) {
    for (size_t j = 0; j < OCTAVE_NOTES; j++) {
      tmpTable[currentOctaveIndex][j] = currOctaveCFreq * pow(distanceRatio, j);
    }
  }

  return tmpTable;
}

double PitchUtils::getCentDistance(const double freq1,
                                   const double freq2) const {
  if (freq1 == 0)
    return 0.0;

  return 1200 * log2(freq2 / freq1);
}

/*
 * Util to calculate the closest note of a given frequency.
 * Theoretically, it is bound to capture values from 55 to 12542 Hz.
 * In practice it captures precisely values from 90 to 5500 Hz.
 */
PitchUtils::DistanceInfo PitchUtils::getClosestNote(const double frequency,
                                                    bool debug) const {
  // Early return
  if (frequency == 0) {
    if (debug) {
      prettyPrintClosestNoteInfo(NULL_DISTANCE);
    }

    return NULL_DISTANCE;
  }

  const size_t octaveIndex = getOctave(frequency) + abs(LOWEST_OCTAVE);
  const std::vector<double> octaveNotes = _frequencyTable[octaveIndex];

  // Assume first octave note as closest
  const double firstOctaveNote = octaveNotes[0];
  DistanceInfo closest{
      frequency,
      firstOctaveNote,
      frequency - firstOctaveNote,
      getCentDistance(firstOctaveNote, frequency),
      _chromaticScale[0],
  };

  // Continue searching for closest from the second
  for (size_t n = 1; n < octaveNotes.size(); n++) {
    if (abs(octaveNotes[n] - frequency) < abs(closest.frequencyDeviation)) {
      closest.closestFrequency = octaveNotes[n];
      closest.closestNoteName = _chromaticScale[n];

      // Edge case. In cases where the last octave note ("G") seems to be the
      // best fit, an additional check for next octave's first note ("A"),
      // should take place.
      if (closest.closestNoteName == "G" &&
          abs(_frequencyTable[octaveIndex + 1][0] - frequency) <
              abs(closest.frequencyDeviation)) {
        closest.closestFrequency = _frequencyTable[octaveIndex + 1][0];
        closest.closestNoteName = _chromaticScale[0];
      }

      closest.frequencyDeviation = frequency - closest.closestFrequency;
      closest.cents = getCentDistance(closest.closestFrequency, frequency);
    }
  }

  if (debug)
    prettyPrintClosestNoteInfo(closest);

  return closest;
}

void PitchUtils::prettyPrintClosestNoteInfo(
    PitchUtils::DistanceInfo closest) const {
  std::cout << "Given frequency: " << closest.startFrequency << "Hz"
            << std::endl
            << "Closest note found: " << closest.closestNoteName
            << ", frequency: " << closest.closestFrequency << "Hz" << std::endl
            << "Distance in cents: " << closest.cents
            << ", frequency deviation: " << closest.frequencyDeviation << "Hz"
            << std::endl
            << std::endl;
}
