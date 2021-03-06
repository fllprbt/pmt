#include <future>
#include <iostream>

#include "pawrapper.h"

#define SAMPLE_RATE (44100)
#define CHANNELS (1)
#define FRAMES (512)
#define SAMPLE_SILENCE (0.0f)

typedef float SAMPLE;

PAWrapper::PAWrapper() : _frames(FRAMES), _isInit(false) {
  _cbDictionary = {{CBTypes::Record, &PAWrapper::record}};
}

void PAWrapper::init() {
  if (!_isInit) {
    if (Pa_Initialize() != paNoError) {
      throw std::runtime_error("Failed to initialize PortAudio.");
    }

    _isInit = true;
  }
}

void PAWrapper::configure(const CBTypes &type) {
  init();

  switch (type) {
  default:
    _callback = _cbDictionary[type];
  }
}

std::string PAWrapper::startStream() {
  PaError openStreamError = Pa_OpenDefaultStream(
      &_stream, CHANNELS, 0, paFloat32, SAMPLE_RATE, _frames, _callback, NULL);

  if (openStreamError != paNoError)
    return Pa_GetErrorText(openStreamError);

  return Pa_GetErrorText(Pa_StartStream(_stream));
}

std::string PAWrapper::stopStream() {
  return Pa_GetErrorText(Pa_StopStream(_stream));
}

int PAWrapper::record(const void *inputBuffer, void *outputBuffer,
                      unsigned long framesPerBuffer,
                      const PaStreamCallbackTimeInfo *timeInfo,
                      PaStreamCallbackFlags statusFlags, void *streamStruct) {

  // Prevent unused variable warning.
  (void)outputBuffer, (void)timeInfo, (void)statusFlags, (void)streamStruct;

  const SAMPLE *readPtr = (const SAMPLE *)inputBuffer;
  std::vector<SAMPLE> inputContainer;
  const size_t sz = framesPerBuffer * CHANNELS;

  if (inputBuffer == NULL) {
    for (unsigned int i = 0; i < sz; i++) {
      inputContainer.push_back(SAMPLE_SILENCE);
    }
  } else {
    for (unsigned int i = 0; i < sz; i++) {
      inputContainer.push_back(*readPtr++);
    }
  }

  return 0;
}

PAWrapper::~PAWrapper() {
  if (Pa_Terminate() != paNoError) {
    throw std::runtime_error("Failed to terminate PortAudio.");
  }
}
