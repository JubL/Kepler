#ifndef SUN_H
#define SUN_H

#include <vector>
#include <cstdint>

#include "star.h"

using namespace std;

class Sun final : public Star
{
  public:
    Sun();

    Sun(double starMass = 1.9885e30,
        double starRadius = 6.957e8,
        vector<double> starLimbDarkeningA = {.4412},
        vector<double> starLimbDarkeningB = {.2312},
        double starPosX = 0,
        double starPosY = 0,
        double starPosZ = 0);

    Sun(const Sun& sun2);

  private:
    vector<double> limbDarkeningA; /** limb darkening coefficient a */
    vector<double> limbDarkeningB; /** limb darkening coefficient b */
    static uint32_t currentID;
    uint32_t id;
};

#endif
