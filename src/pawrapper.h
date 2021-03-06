#ifndef PAWRAPPER_H
#define PAWRAPPER_H

#include <map>
#include <string>

#include "./iobase.h"
#include "./portaudio.h"

class PAWrapper : public IOBase {
public:
  enum CBTypes {
    Record,
  };

  PAWrapper();
  ~PAWrapper();
  void configure(const CBTypes &);
  // Inherited from IOBase
  std::string startStream();
  std::string stopStream();

private:
  size_t _frames;
  bool _isInit;
  PaStream *_stream;
  std::map<CBTypes, PaStreamCallback *> _cbDictionary;
  // maps a callback type to the pAWrapper's callback implementation
  PaStreamCallback *_callback;
  static PaStreamCallback record;

  void init();
};

#endif // PAWRAPPER_H
