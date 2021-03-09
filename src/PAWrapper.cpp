#include "PAWrapper.h"

PAWrapper::PAWrapper()
    : _isInit(false), _stream(nullptr), _recordUserDataPtr(nullptr) {
  this->init();
}

PAWrapper *PAWrapper::init() {
  if (!_isInit) {
    if (Pa_Initialize() != paNoError) {
      throw std::runtime_error("Failed to initialize PortAudio.");
    }

    _isInit = true;
  }

  return this;
}

/**
 * Every time PortAudio has data, it writes them to a vector and calls the
 * callback passed by the consumer with it.
 */
int PAWrapper::Record(const void *inputBuffer, void *outBuffer,
                      unsigned long framesPerBuffer,
                      const PaStreamCallbackTimeInfo *timeInfo,
                      PaStreamCallbackFlags statusFlags, void *_userData) {

  (void)outBuffer;
  (void)timeInfo;
  (void)statusFlags;

  RecordUserData *userData = (RecordUserData *)_userData;

  const SAMPLE *rptr = (const SAMPLE *)inputBuffer;
  std::vector<SAMPLE> data(framesPerBuffer * userData->channels);

  size_t rBufferIndex = 0;
  for (unsigned long i = 0; i < framesPerBuffer; i++) {
    data[rBufferIndex++] = *rptr++;
    if (userData->channels == 2) {
      data[rBufferIndex++] = *rptr++;
    }
  }

  userData->cb(std::move(data));

  return 0;
}

std::string PAWrapper::startStream(RecordCBHandle cbPtr) {
  if (_recordUserDataPtr == nullptr) {
    _recordUserDataPtr = new RecordUserData;
  }
  _recordUserDataPtr->cb = cbPtr;
  _recordUserDataPtr->channels = _inputChannels;

  PaError openStreamError = Pa_OpenDefaultStream(
      &_stream, _inputChannels, 0, paFloat32, _sampleRate, _frames,
      PAWrapper::Record, (void *)_recordUserDataPtr);

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
  this->_recordUserDataPtr = other._recordUserDataPtr;

  other._isInit = false;
  other._stream = nullptr;
  other._recordUserDataPtr = nullptr;
}

PAWrapper &PAWrapper::operator=(PAWrapper &&other) {
  if (this != &other) {
    AudioIO::operator=(std::move(other));
    this->_isInit = other._isInit;
    this->_stream = other._stream;
    this->_recordUserDataPtr = other._recordUserDataPtr;

    other._isInit = false;
    other._stream = nullptr;
    other._recordUserDataPtr = nullptr;
  }

  return *this;
}

PAWrapper::~PAWrapper() {
  if (_recordUserDataPtr != nullptr)
    delete _recordUserDataPtr;

  if (Pa_Terminate() != paNoError) {
    throw std::runtime_error("Failed to terminate PortAudio.");
  }
}
