#include "sun.h"

using namespace std;

Sun::Sun() : Star(1.9885e30,
                  6.957e8,
                  {.4412},
                  {.2312},
                  0, 0, 0)
{
}

Sun::Sun(double sunMass,
         double sunRadius,
         vector<double> sunLimbDarkeningA,
         vector<double> sunLimbDarkeningB,
         double sunPosX,
         double sunPosY,
         double sunPosZ) : Star(sunMass,
                                sunRadius,
                                sunLimbDarkeningA,
                                sunLimbDarkeningB,
                                sunPosX,
                                sunPosY,
                                sunPosZ)
{
}

Sun::Sun(const Sun& sun2) : Star(sun2.mass,
                                 sun2.radius,
                                 sun2.limbDarkeningA,
                                 sun2.limbDarkeningB,
                                 sun2.posX,
                                 sun2.posY,
                                 sun2.posZ)
{
}
