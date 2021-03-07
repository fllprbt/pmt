#ifndef IOBASE_H
#define IOBASE_H

#include <string>
#include <vector>

class IOBase {
public:
  virtual std::string startStream() = 0;
  virtual std::string stopStream() = 0;
};

#endif // IOBASE_H
