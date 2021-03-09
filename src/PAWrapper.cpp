#include <future>
#include <iostream>

#include "PAWrapper.h"

static int record(const void *inputBuffer, void *outBuffer,
                  unsigned long framesPerBuffer,
                  const PaStreamCallbackTimeInfo *timeInfo,
                  PaStreamCallbackFlags statusFlags, void *notifyHandle) {

  (void)outBuffer;
  (void)timeInfo;
  (void)statusFlags;

  NotifyCallbackHandle notify = (NotifyCallbackHandle)notifyHandle;
  const SAMPLE *rptr = (const SAMPLE *)inputBuffer;
  std::vector<SAMPLE> data(framesPerBuffer);

  for (unsigned long i = 0; i < framesPerBuffer; i++) {
    data[i] = *rptr++;
  }

  notify(std::move(data));

  return 0;
}

PAWrapper::PAWrapper() : _isInit(false), _stream(nullptr) { this->init(); }

PAWrapper *PAWrapper::init() {
  if (!_isInit) {
    if (Pa_Initialize() != paNoError) {
      throw std::runtime_error("Failed to initialize PortAudio.");
    }

    _isInit = true;
  }

  return this;
}

std::string PAWrapper::startStream(NotifyCallbackHandle cbPtr) {
  PaError openStreamError =
      Pa_OpenDefaultStream(&_stream, _channels, 0, paFloat32, _sampleRate,
                           _frames, record, (void *)cbPtr);

  if (openStreamError != paNoError)
    return Pa_GetErrorText(openStreamError);

  return Pa_GetErrorText(Pa_StartStream(_stream));
}

std::string PAWrapper::stopStream() {
  PaError closeStreamError = Pa_StopStream(_stream);

  return Pa_GetErrorText(closeStreamError);
}

PAWrapper::PAWrapper(PAWrapper &&other) : AudioIO(std::move(other)) {
  this->_isInit = other._isInit;
  this->_stream = other._stream;

  other._isInit = false;
  other._stream = nullptr;
}

PAWrapper &PAWrapper::operator=(PAWrapper &&other) {
  if (this != &other) {
    AudioIO::operator=(std::move(other));
    other._isInit = false;
    other._stream = nullptr;
  }

  return *this;
}

PAWrapper::~PAWrapper() {
  if (Pa_Terminate() != paNoError) {
    throw std::runtime_error("Failed to terminate PortAudio.");
  }
}
