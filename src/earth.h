#ifndef EARTH_H
#define EARTH_H

#include <vector>
#include <cstdint>

#include "exoplanet.h"
#include "star.h"

using namespace std;

class Earth : public Exoplanet
{
  public:
    Earth(Star &host);

    Earth(const Earth& earth2);

  private:
    static uint32_t currentID;
    uint32_t id;
};

#endif
