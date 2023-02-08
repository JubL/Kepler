#include "exomoon.h"

using namespace std;

Exomoon::Exomoon(double exomoonMass,
                 double exomoonRadius,
                 double exomoonPeriod,
                 double exomoonTrueAnomalyStart,
                 double exomoonInclination,
                 double exomoonEccentricity,
                 double exomoonArgumentOfPericenter,
                 double exomoonLongitudeOfAscendingNode,
                 double exomoonAlbedo,
                 Exoplanet &host) : Exoplanet(exomoonMass,
                                              exomoonRadius,
                                              exomoonPeriod,
                                              exomoonTrueAnomalyStart,
                                              exomoonInclination,
                                              exomoonEccentricity,
                                              exomoonArgumentOfPericenter,
                                              exomoonLongitudeOfAscendingNode,
                                              exomoonAlbedo)
{
    semiMajorAxis = calcSemiMajorAxis(host.mass);
    hostX = &host.posX;
    hostY = &host.posY;
    hostZ = &host.posZ;
    updatePosition();

    id = currentID++;
    exomoons.push_back(this);
}

Exomoon::Exomoon(double exomoonMass,
                 double exomoonRadius,
                 double exomoonPeriod,
                 double exomoonTrueAnomalyStart,
                 Exoplanet &host) : Exoplanet(exomoonMass,
                                              exomoonRadius,
                                              exomoonPeriod,
                                              exomoonTrueAnomalyStart,
                                              0, 0, 0, 0)
{
    semiMajorAxis = calcSemiMajorAxis(host.mass);
    hostX = &host.posX;
    hostY = &host.posY;
    hostZ = &host.posZ;
    updatePosition();

    id = currentID++;
    exomoons.push_back(this);
}

Exomoon::Exomoon(const Exomoon& exomoon2) : Exoplanet(exomoon2.mass,
                                                      exomoon2.radius,
                                                      exomoon2.period,
                                                      exomoon2.trueAnomaly,
                                                      exomoon2.inclination,
                                                      exomoon2.eccentricity,
                                                      exomoon2.argumentOfPericenter,
                                                      exomoon2.longitudeOfAscendingNode)
{
    id = currentID++;
    exomoons.push_back(this);
}

uint32_t Exomoon::getID()
{
    return id;
}

