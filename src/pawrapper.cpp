#include <future>
#include <iostream>

#include "PAWrapper.h"

#define SAMPLE_RATE (44100)
#define CHANNELS (1)
#define FRAMES (512)
#define SAMPLE_SILENCE (0.0f)

typedef float SAMPLE;

PAWrapper::PAWrapper() : _frames(FRAMES), _isInit(false), _stream(nullptr) {}

PAWrapper *PAWrapper::init() {
  if (!_isInit) {
    if (Pa_Initialize() != paNoError) {
      throw std::runtime_error("Failed to initialize PortAudio.");
    }

    _isInit = true;
  }

  return this;
}

std::string PAWrapper::startStream(PaStreamCallback *cb) {
  PaError openStreamError = Pa_OpenDefaultStream(
      &_stream, CHANNELS, 0, paFloat32, SAMPLE_RATE, _frames, cb, NULL);

  if (openStreamError != paNoError)
    return Pa_GetErrorText(openStreamError);

  return Pa_GetErrorText(Pa_StartStream(_stream));
}

std::string PAWrapper::stopStream() {
  return Pa_GetErrorText(Pa_StopStream(_stream));
}

PAWrapper::PAWrapper(PAWrapper &&other) {
  this->_frames = other._frames;
  this->_isInit = other._isInit;
  this->_stream = other._stream;

  other._frames = 0;
  other._isInit = false;
  other._stream = nullptr;
}

PAWrapper &PAWrapper::operator=(PAWrapper &&other) {
  if (this != &other) {
    this->_frames = other._frames;
    this->_isInit = other._isInit;
    this->_stream = other._stream;

    other._frames = 0;
    other._isInit = false;
    other._stream = nullptr;
  }
}

PAWrapper::~PAWrapper() {
  if (Pa_Terminate() != paNoError) {
    throw std::runtime_error("Failed to terminate PortAudio.");
  }
}
