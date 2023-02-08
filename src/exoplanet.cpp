#include "exoplanet.h"

using namespace std;

Exoplanet::Exoplanet(double exoplanetMass,
                     double exoplanetRadius,
                     double exoplanetPeriod,
                     double exoplanetTrueAnomalyStart,
                     double exoplanetInclination,
                     double exoplanetEccentricity,
                     double exoplanetArgumentOfPericenter,
                     double exoplanetLongitudeOfAscendingNode,
                     double exoplanetAlbedo) : CelestialObject(exoplanetMass,
                                                               exoplanetRadius)
{
    period                   = exoplanetPeriod;
    trueAnomaly              = exoplanetTrueAnomalyStart;
    calcInclination(exoplanetInclination);
    eccentricity             = exoplanetEccentricity;
    argumentOfPericenter     = exoplanetArgumentOfPericenter;
    longitudeOfAscendingNode = exoplanetLongitudeOfAscendingNode;
    albedo                   = exoplanetAlbedo;
}

Exoplanet::Exoplanet(double exoplanetMass,
                     double exoplanetRadius,
                     double exoplanetPeriod,
                     double exoplanetTrueAnomalyStart,
                     double exoplanetInclination,
                     double exoplanetEccentricity,
                     double exoplanetArgumentOfPericenter,
                     double exoplanetLongitudeOfAscendingNode,
                     double exoplanetAlbedo,
                     Star &host) : Exoplanet(exoplanetMass,
                                             exoplanetRadius,
                                             exoplanetPeriod,
                                             exoplanetTrueAnomalyStart,
                                             exoplanetInclination,
                                             exoplanetEccentricity,
                                             exoplanetArgumentOfPericenter,
                                             exoplanetLongitudeOfAscendingNode,
                                             exoplanetAlbedo)
{
    semiMajorAxis = calcSemiMajorAxis(host.mass);
    hostX         = &host.posX;
    hostY         = &host.posY;
    hostZ         = &host.posZ;
    updatePosition();

    id            = currentID++;
    hostID        = host.getID();
    exoplanets.push_back(this);
}

Exoplanet::Exoplanet(double exoplanetMass,
                     double exoplanetRadius,
                     double exoplanetPeriod,
                     double exoplanetTrueAnomalyStart,
                     Star &host) : Exoplanet(exoplanetMass,
                                             exoplanetRadius,
                                             exoplanetPeriod,
                                             exoplanetTrueAnomalyStart,
                                             0, 0, 0, 0)
{
    semiMajorAxis = calcSemiMajorAxis(host.mass);
    hostX         = &host.posX;
    hostY         = &host.posY;
    hostZ         = &host.posZ;
    updatePosition();

    id            = currentID++;
    hostID        = host.getID();
    exoplanets.push_back(this);
}

Exoplanet::Exoplanet(const Exoplanet& exoplanet2) : CelestialObject(exoplanet2.mass,
                                                                    exoplanet2.radius)
{
    id = currentID++;
    exoplanets.push_back(this);
}

double Exoplanet::getAlbedo()
{
    return albedo;
}

uint32_t Exoplanet::getID()
{
    return id;
}

uint32_t Exoplanet::getHostID()
{
    return hostID;
}
