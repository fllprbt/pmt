#ifndef AUDIOIOVARIANT_H
#define AUDIOIOVARIANT_H

#include <memory>

#include "AudioIO.h"

class VariantinatorBase {
public:
  VariantinatorBase() {}
  virtual ~VariantinatorBase() {}
  virtual std::unique_ptr<AudioIO> create() = 0;
};

template <class T> class Variantinator : public VariantinatorBase {
public:
  Variantinator() {}
  virtual ~Variantinator() {}
  virtual std::unique_ptr<AudioIO> create() { return std::make_unique<T>(); }
};

#endif // AUDIOIOVARIANT_H
