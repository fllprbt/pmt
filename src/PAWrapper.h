#ifndef PAWRAPPER_H
#define PAWRAPPER_H

#include "./AudioIO.h"
#include "./portaudio.h"

class PAWrapper : public AudioIO {
public:
  PAWrapper();
  virtual ~PAWrapper();
  PAWrapper(PAWrapper &&other);
  PAWrapper &operator=(PAWrapper &&other);

  PAWrapper *init();

  // Inherited from AudioIO
  std::string startStream(NotifyCallbackHandle);
  std::string stopStream();

private:
  bool _isInit;
  PaStream *_stream;
};

#endif // PAWRAPPER_H
