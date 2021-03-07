#ifndef PAWRAPPER_H
#define PAWRAPPER_H

#include <map>
#include <string>

#include "./IOBase.h"
#include "./portaudio.h"

/**
 * PortAudio Abstraction. Does not support copy semantics.
 **/
class PAWrapper : public IOBase {
public:
  PAWrapper();
  ~PAWrapper();

  PAWrapper *init();

  // Inherited from IOBase
  std::string startStream(PaStreamCallback *cb);
  std::string stopStream();

  PAWrapper(PAWrapper &&other);
  PAWrapper &operator=(PAWrapper &&other);

private:
  size_t _frames;
  bool _isInit;
  PaStream *_stream;
};

#endif // PAWRAPPER_H
