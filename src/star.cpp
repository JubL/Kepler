#include "star.h"

using namespace std;

Star::Star(double starMass,
           double starRadius,
           vector<double> starLimbDarkeningA,
           vector<double> starLimbDarkeningB,
           double starPosX,
           double starPosY,
           double starPosZ) : CelestialObject(starMass,
                                              starRadius,
                                              starPosX,
                                              starPosY,
                                              starPosZ)
{
    // sanity check
    if(starLimbDarkeningA.size() != starLimbDarkeningB.size())
    {
        throw logic_error("The lenght of the vectors 'limbDarkeningA' and 'limbDarkeningB' are unequal.");
    }
    limbDarkeningA = starLimbDarkeningA;
    limbDarkeningB = starLimbDarkeningB;

    for(uint32_t i = 0; i < limbDarkeningA.size(); ++i)
    {
        averageStarLightValue.push_back(faceArea * calcAverageStarLight(0, radius, i));
    }

    id = currentID++;
    stars.push_back(this);
}

Star::Star(const Star& star2) : CelestialObject(star2.mass,
                                                star2.radius,
                                                star2.posX,
                                                star2.posY,
                                                star2.posZ)
{
    id = currentID++;
    stars.push_back(this);
}

double Star::calcAverageStarLight(double radius_i, double radius_o, uint32_t freq)
{
    double ri = radius_i/radius;
    double ro = radius_o/radius;

    return ((1 - limbDarkeningA[freq] - 2*limbDarkeningB[freq]) * (ro-ri)
           + (limbDarkeningA[freq] + 2*limbDarkeningB[freq]) * (ro * sqrt(1 - ro*ro) + asin(ro) - ri * sqrt(1 - ri*ri) - asin(ri)) / 2.0
           + 1.0/3.0 * limbDarkeningB[freq] * (pow(ro, 3) - pow(ri, 3)) ) / (ro -ri);
}

uint32_t Star::getID()
{
    return id;
}
