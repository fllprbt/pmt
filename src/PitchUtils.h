#ifndef PITCHUTILS_H
#define PITCHUTILS_H

#include <string>
#include <vector>

#define OCTAVE_NOTES 12
#define C4 440.0
#define LOWEST_OCTAVE -3 // A1's octave. A4's is considered the current base (0)
#define HIGHEST_OCTAVE 5 // A9

class PitchUtils {
public:
  PitchUtils();

  // An octave's notes starting from A and ending to G
  const std::string _chromaticScale[OCTAVE_NOTES];

  // Frequency dictionary for all the notes of the supported octaves
  typedef std::vector<std::vector<double>> FrequencyTable;
  FrequencyTable _frequencyTable;

  /**
   * Struct with extensive information about a frequency's closest note.
   * The signs of distance metrics (frequency deviation/cents) are based on how
   * much the startFrequency is offset from the closest note e.g. for 438Hz as
   * starting frequency, the offset from 440 is -2Hz and -7.88 cents.
   */
  struct DistanceInfo {
    double startFrequency;
    double closestFrequency;
    double frequencyDeviation;
    double cents;
    std::string closestNoteName;
  };

  int getOctave(const double frequency) const;
  double getCentDistance(const double freq1, const double freq2) const;
  DistanceInfo getClosestNote(const double frequency, bool debug = false) const;

private:
  FrequencyTable generateFrequencyTable() const;
  void prettyPrintClosestNoteInfo(DistanceInfo info) const;
};

#endif // PITCHUTILS_H
