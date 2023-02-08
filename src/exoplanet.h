#ifndef EXOPLANET_H
#define EXOPLANET_H

#include <vector>
#include <cstdint>

#include "celestialObject.h"
#include "star.h"

using namespace std;

class Exoplanet : public CelestialObject
{
  public:
    Exoplanet(double exoplanetMass,
              double exoplanetRadius,
              double exoplanetPeriod,
              double exoplanetTrueAnomalyStart,
              double exoplanetInclination,
              double exoplanetEccentricity,
              double exoplanetArgumentOfPericenter,
              double exoplanetLongitudeOfAscendingNode,
              double exoplanetAlbedo = 0.306);

    Exoplanet(double exoplanetMass,
              double exoplanetRadius,
              double exoplanetPeriod,
              double exoplanetTrueAnomalyStart,
              double exoplanetInclination,
              double exoplanetEccentricity,
              double exoplanetArgumentOfPericenter,
              double exoplanetLongitudeOfAscendingNode,
              double exoplanetAlbedo,
              Star &host);

    Exoplanet(double exoplanetMass,
              double exoplanetRadius,
              double exoplanetPeriod,
              double exoplanetTrueAnomalyStart,
              Star &host);

    Exoplanet(const Exoplanet& exoplanet2);

    double getAlbedo();
    uint32_t getID();
    uint32_t getHostID();

    static vector<Exoplanet*> exoplanets;
    double albedo;
  private:
    static uint32_t currentID;
    uint32_t id;
    uint32_t hostID;
};

#endif
