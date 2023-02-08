#ifndef JUPITER_H
#define JUPITER_H

#include <vector>
#include <cstdint>

#include "exoplanet.h"
#include "star.h"

using namespace std;

class Jupiter : public Exoplanet
{
  public:
    Jupiter(Star &host);

    Jupiter(const Jupiter& jupiter2);

  private:
    static uint32_t currentID;
    uint32_t id;
};

#endif
