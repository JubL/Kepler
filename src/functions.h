#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <chrono>

#include "exoplanet.h"
#include "star.h"

using namespace std;

/**
 * This function gets all exoplanets and their hoststars and hands over all
 * associated pairs to the blackout funktion.
 * @param star This is the vector of stars in question including all necessary parameters like position and radius.
 * @param exoplanet This is the vector of exoplanets in question including all necessary parameters like position and radius
 * @return Returns the blocked flux.
 */
double calcCurve(vector<Star*> stars, vector<Exoplanet*> exoplanets, uint32_t freq);

/**
 * The function 'blackout' calculates how much flux is blocked due to the transit
 * for a star exoplanet pair. It first checks if there exists a partial or full
 * overlapping. In these cases it calculates the relative overlapping and in other
 * case it returns 0 for no overlapping. The overlapping area is then corrected for
 * the limb darkening.
 * @param star This is the star in question including all necessary parameters like position and radius.
 * @param exoplanet This is the exoplanet in question including all necessary parameters like position and radius
 * @return Returns the blocked flux.
 */
double blackout(Star* star, Exoplanet* exoplanet, uint32_t freq);

/**
 * This function calculates the difference in magnitudes.
 * @param value This is the value (flux) to be calculated into magnitudes.
 * @return Returns magnitudes.
 */
double calcMag(double value);

/**
 * All measurements are subject to noise.
 * @param sigma The parameter sigma is the standard deviation.
 * @return Returns a value for the noise.
 */
double noise(double sigma);

/**
 * This function writes the data to a file.
 * @param filename This is the filename.
 * @param times These are the datapoints for the x-axis.
 * @param fluxes These are the datapoints for the y-axis.
 */
void writeToFile(string filename, vector<double> times, vector< vector<double> > fluxes);

#endif
