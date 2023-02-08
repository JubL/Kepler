#ifndef STAR_H
#define STAR_H

#include <vector>
#include <cstdint>
#include <stdexcept>

#include "celestialObject.h"

using namespace std;

class Star : public CelestialObject
{
  public:
    Star(double starMass,
         double starRadius,
         vector<double> starLimbDarkeningA,
         vector<double> starLimbDarkeningB,
         double starPosX = 0,
         double starPosY = 0,
         double starPosZ = 0);

    Star(const Star& star2);

    /**
     * This method calculates the Integral of the quadratic limb darkening law.
     * The formula of the quadratic limb darkening law goes as follows:
     * (1 - limbDarkeningA * (1 - cos(alpha)) - limbDarkeningB * (1 - cos(alpha)) * (1 - cos(alpha)))
     * with  cos(alpha) = sqrt(1 - r*r)
     * @param radius_i This is the inner limit for the integral.
     * @param radius_o This is the outer limit for the integral.
     * @return Returns the mean starlight between two radii based on the limb darkening
     */
    double calcAverageStarLight(double radius_i, double radius_o, uint32_t freq);
    uint32_t getID();

    vector<double> averageStarLightValue; /** This is the integrated starlight of full radius at different frequencies multiplied with the star face area */
    static vector<Star*> stars;

  private:
    vector<double> limbDarkeningA;       /** limb darkening coefficient a */
    vector<double> limbDarkeningB;       /** limb darkening coefficient b */
    static uint32_t currentID;
    uint32_t id;
};

#endif
