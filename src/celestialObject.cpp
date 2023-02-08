#include "celestialObject.h"

using namespace std;

CelestialObject::CelestialObject(double celObjMass,
                                 double celObjRadius)
{
    mass   = celObjMass;
    radius = celObjRadius;

    faceArea = M_PI * radius * radius;
}

CelestialObject::CelestialObject(double celObjMass,
                                 double celObjRadius,
                                 double celObjPosX,
                                 double celObjPosY,
                                 double celObjPosZ)
{
    mass   = celObjMass;
    radius = celObjRadius;
    posX   = celObjPosX;
    posY   = celObjPosY;
    posZ   = celObjPosZ;

    faceArea = M_PI * radius * radius;
}

double CelestialObject::getDistance()
{
    return distance;
}

double CelestialObject::calcPeriod(double mass2)
{
    return sqrt((4 * M_PI * M_PI) / (Constant::gravitationalConstant * (mass + mass2))
                * pow(semiMajorAxis, 3));
}

double CelestialObject::calcSemiMajorAxis(double mass2)
{
    return pow((period * period * Constant::gravitationalConstant * (mass + mass2))
               / (4 * M_PI * M_PI), 1.0/3.0);
}

void CelestialObject::calcInclination(double inclinationDeg)
{
    inclination = (90 - inclinationDeg) * M_PI / 180;
}

void CelestialObject::updatePosition()
{
    distance = semiMajorAxis * (1 - eccentricity * eccentricity)
               / (1 + eccentricity * cos(trueAnomaly));

    posX = *hostX + distance * (cos(longitudeOfAscendingNode) * cos(argumentOfPericenter + trueAnomaly) -
           sin(longitudeOfAscendingNode) * sin(argumentOfPericenter + trueAnomaly) * cos(inclination));

    posY = *hostY + distance * (sin(longitudeOfAscendingNode) * cos(argumentOfPericenter + trueAnomaly) +
           cos(longitudeOfAscendingNode) * sin(argumentOfPericenter + trueAnomaly) * cos(inclination));

    posZ = *hostZ + distance * sin(argumentOfPericenter + trueAnomaly) * sin(inclination);
}
