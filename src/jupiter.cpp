#include "jupiter.h"

using namespace std;

Jupiter::Jupiter(Star &host) : Exoplanet(1.89819e27,      // mass
                                         6.9911e7,        // radius
                                         4332.589 * 86400,// period
                                         -0.6 * M_PI,     // trueAnomalyStart
                                         90,              // inclination
                                         0.0489,          // eccentricity
                                         0,               // argumentOfPericenter
                                         M_PI/2,          // longitudeOfAscendingNode
                                         0.343,           // albedo
                                         host)            // hostObject
{
}

Jupiter::Jupiter(const Jupiter& jupiter2) : Exoplanet(jupiter2.mass,
                                                      jupiter2.radius,
                                                      jupiter2.period,
                                                      jupiter2.trueAnomaly,
                                                      jupiter2.inclination,
                                                      jupiter2.eccentricity,
                                                      jupiter2.argumentOfPericenter,
                                                      jupiter2.longitudeOfAscendingNode,
                                                      jupiter2.albedo)
{
}
