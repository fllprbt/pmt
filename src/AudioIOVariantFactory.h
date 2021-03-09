#ifndef AUDIOIOVARIANTFACTORY_H
#define AUDIOIOVARIANTFACTORY_H

#include <map>
#include <memory>
#include <stdint.h>

#include "AudioIO.h"
#include "AudioIOVariant.h"

class AudioIOVariantFactory {
public:
  AudioIOVariantFactory() {}

  template <uint8_t type, typename T> void add() {
    add(type, std::make_unique<Variantinator<T>>());
  }

  std::unique_ptr<AudioIO> create(uint8_t type) {
    TSwitchToVariant::iterator it = m_switchToVariant.find(type);
    if (it == m_switchToVariant.end())
      return nullptr;
    return it->second->create();
  }

private:
  void add(uint8_t type, std::unique_ptr<VariantinatorBase> &&creator) {
    m_switchToVariant[type] = std::move(creator);
  }

  typedef std::map<uint8_t, std::unique_ptr<VariantinatorBase>>
      TSwitchToVariant;
  TSwitchToVariant m_switchToVariant;
};

#endif // AUDIOIOVARIANTFACTORY_H
