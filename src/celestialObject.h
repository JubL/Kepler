#ifndef CELESTIALOBJECT_H
#define CELESTIALOBJECT_H

#include "constant.h"

using namespace std;

class CelestialObject
{
  friend class Timedisc;
  public:
    // The constructors are protected and therefore to be found further down in this file.

    double posX;
    double posY;
    double posZ;
    double radius;
    double mass;
    double faceArea; /** This is the visible 2D projection area. */
    double nextStep;

    /**
     * This method returns the distance between a celestial object and the barycenter it is orbiting around.
     * @return Returns the distance between a celestial body and its host.
     */
    double getDistance();

    /**
     * This method calculates the orbital period with Keplers third law.
     * @param mass2 This is the mass of the second object needed for Keplers third law.
     * @return The orbital period is returned in seconds.
     */
    double calcPeriod(double mass2);

    /**
     * This method calculates the semi-major axis with Keplers third law.
     * @param mass2 This is the mass of the second object needed for Keplers third law.
     * @return The semi-major axis in returned in meters.
     */
    double calcSemiMajorAxis(double mass2);

    /**
     * This method calculates the inclination in radians.
     * The inclination is given so that a transit would occure with i = 90°.
     * It is changed so that a transit will occure at i = 0 rad.
     * @param inclinationDeg This is the inclination in its definition with a transit at 90° in degree.
     */
    void calcInclination(double inclinationDeg);

    /**
     * This method calculates the cartesian coordinates and the distance to the barycenter with the formulas from the following paper:
     * Dimitri, Veras 2018 'Explicit relations and criteria for eclipses, transits and occultations' [formula (3), (4), (5), (6)]
     * @see {@link https://arxiv.org/pdf/1811.05484.pdf}
     */
    void updatePosition();

  protected:
    CelestialObject(double celObjMass,
                    double celObjRadius);

    CelestialObject(double celObjMass,
                    double celObjRadius,
                    double celObjPosX,
                    double celObjPosY,
                    double celObjPosZ);

    double trueAnomaly;
    double period;
    double inclination;
    double longitudeOfAscendingNode; /** When the longitude of the ascending node equals 0, it is in between the observer and the orbits focus point (i.e. the star). */
    double distance; /** This is the distance to the center of gravity. */
    double semiMajorAxis;
    double eccentricity;
    double argumentOfPericenter;
    double *hostX;  /** These are the carthesian coordinates of the host object around this celestial object is floating. */
    double *hostY;
    double *hostZ;
};

#endif
