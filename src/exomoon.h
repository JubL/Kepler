#ifndef EXOMOON_H
#define EXOMOON_H

#include <iostream>
#include <cstdint>

//#include "celestialObject.h"
#include "exoplanet.h"

using namespace std;

class Exomoon final : public Exoplanet
{
  public:
    Exomoon(double exomoonMass,
            double exomoonRadius,
            double exomoonPeriod,
            double exomoonTrueAnomalyStart,
            double exomoonInclination,
            double exomoonEccentricity,
            double exomoonArgumentOfPericenter,
            double exomoonLongitudeOfAscendingNode,
            double exomoonAlbedo,
            Exoplanet &host);

    Exomoon(double exomoonMass,
            double exomoonRadius,
            double exomoonPeriod,
            double exomoonTrueAnomalyStart,
            Exoplanet &host);
    Exomoon(const Exomoon& moon2);
    uint32_t getID();

    static vector<Exomoon*> exomoons;

  private:
    static uint32_t currentID;
    uint32_t id;
};

#endif
