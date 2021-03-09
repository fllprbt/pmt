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
  std::string startStream(RecordCBHandle);
  std::string stopStream();

private:
  bool _isInit;
  PaStream *_stream;

  static PaStreamCallback Record;
  // For each PortAudio implementation of this class, we use
  // PortAudio::OpenDefaultStream's last argument (void * userData) to pass all
  // the data required to perform IO
  struct RecordUserData {
    RecordCBHandle cb; // callback to update consumers of class with data
    size_t channels;
  };
  RecordUserData *_recordUserDataPtr;
};

#endif // PAWRAPPER_H
