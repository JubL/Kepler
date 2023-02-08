#include "earth.h"

using namespace std;

Earth::Earth(Star &host) : Exoplanet(5.9723e24,      // mass
                                     6.371e6,        // radius
                                     365.256 * 86400,// period
                                     -0.55 * M_PI,    // trueAnomalyStart
                                     90,             // inclination
                                     0.0167,         // eccentricity
                                     0,              // argumentOfPericenter
                                     M_PI/2,         // longitudeOfAscendingNode
                                     0.306,          // albedo
                                     host)           // hostObject
{
}

Earth::Earth(const Earth& earth2) : Exoplanet(earth2.mass,
                                               earth2.radius,
                                               earth2.period,
                                               earth2.trueAnomaly,
                                               earth2.inclination,
                                               earth2.eccentricity,
                                               earth2.argumentOfPericenter,
                                               earth2.longitudeOfAscendingNode,
                                               earth2.albedo)
{
}
