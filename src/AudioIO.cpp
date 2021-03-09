#include "AudioIO.h"

AudioIO::AudioIO()
    : _sampleRate(44100), _frames(512), _inputChannels(1), _outputChannels(0),
      _silence(0.0) {}

AudioIO::AudioIO(AudioIO &&other) {
  this->_sampleRate = other._sampleRate;
  this->_frames = other._frames;
  this->_inputChannels = other._inputChannels;
  this->_outputChannels = other._outputChannels;
  this->_silence = other._silence;

  other._sampleRate = 0;
  other._frames = 0;
  other._inputChannels = 0;
  other._outputChannels = 0;
  other._silence = 0.0;
}

AudioIO &AudioIO::operator=(AudioIO &&other) {
  if (this != &other) {
    this->_sampleRate = other._sampleRate;
    this->_frames = other._frames;
    this->_inputChannels = other._inputChannels;
    this->_outputChannels = other._outputChannels;
    this->_silence = other._silence;

    other._sampleRate = 0;
    other._frames = 0;
    other._inputChannels = 0;
    other._outputChannels = 0;
    other._silence = 0.0;
  }

  return *this;
}
