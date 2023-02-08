#include "functions.h"

using namespace std;

double calcCurve(vector<Star*> stars, vector<Exoplanet*> exoplanets, uint32_t freq)
{
    double flux = 0;
    uint32_t hostID = 0;
    for (Exoplanet* exoplanet : exoplanets)
    {
        hostID = exoplanet->getHostID();
        flux += blackout(stars[hostID], exoplanet, freq);
    }
    return flux;
}

double blackout(Star* star, Exoplanet* exoplanet, uint32_t freq)
{
    // distance of the object to the parent object in 2D y-z-projection
    double distanceProjection = sqrt( pow(exoplanet->posY - star->posY, 2) + pow(exoplanet->posZ - star->posZ, 2) );

    const double phaseFactor = pow(exoplanet->radius / exoplanet->getDistance(), 2) * exoplanet->getAlbedo() / 4.0;
    double planetPhaseFunction = phaseFactor * (1 - cos(atan2(exoplanet->posY, exoplanet->posX))) / 2.0;

    // in this case we have a primary or a secondary eclipse (i.e. star and planet overlap)
    if(distanceProjection <  (star->radius - exoplanet->radius))
    {
        if(exoplanet->posX > star->posX)
        {
            // in this case the celestrial object is fully in front of the parent object, we have a primary eclipse, a transit
            return planetPhaseFunction - exoplanet->faceArea * star->calcAverageStarLight(distanceProjection - exoplanet->radius, distanceProjection + exoplanet->radius, freq) / star->averageStarLightValue[freq];
        }
        else
        {
            // in this case we have a secondary eclipse, the celestial object is in occultation
            return 0;
        }
    }
    // in this case the celestrial object is partially in front of the parent object
    else if(distanceProjection <= (star->radius + exoplanet->radius) && distanceProjection >= (star->radius - exoplanet->radius))
    {
        double u = (star->radius * star->radius + distanceProjection * distanceProjection - exoplanet->radius * exoplanet->radius)/(2 * distanceProjection);
        double hs = star->radius - u; // segment height
        double segmentAreaStar = star->radius * star->radius * acos(1 - (hs / star->radius)) - (star->radius - hs) * sqrt(2 * star->radius * hs - hs * hs);
        double hp = u - distanceProjection + exoplanet->radius;
        double segmentAreaPlanet = exoplanet->radius * exoplanet->radius * acos(1-(hp / exoplanet->radius)) - (exoplanet->radius - hp) * sqrt(2 * exoplanet->radius * hp - hp * hp);

        if(exoplanet->posX > star->posX)
        {
            // in the case of a transit
            return planetPhaseFunction - (segmentAreaStar + segmentAreaPlanet) * star->calcAverageStarLight(distanceProjection - exoplanet->radius, star->radius, freq) / star->averageStarLightValue[freq];
        }
        else
        {
            // in the case of an occultation
            return (1 - (segmentAreaStar + segmentAreaPlanet) / exoplanet->faceArea) * planetPhaseFunction;
        }
    }
    else
    {
        // when there is no eclipse, return the amount of reflected light
        return planetPhaseFunction;
    }
    return 0;
}

double calcMag(double value)
{
    return - 2.5 * log10(value);
}

double noise(double sigma)
{
    // obtain a seed from the system clock
    // and cast it to long unsigned int to prevent a sign
    // conversion warning when putting it into the generator
    long unsigned int seed = static_cast<long unsigned int>(chrono::system_clock::now().time_since_epoch().count());

    default_random_engine generator(seed);
    normal_distribution<double> distribution(0.,sigma);

    return distribution(generator);
}

[[deprecated("use the FileIO Class instead")]]
void writeToFile(string filename, vector<double> times, vector< vector<double> > fluxes)
{
    ofstream datafile;
    datafile.open(filename);
    datafile << "# time in days | normalized lightcurve | magnitude" << endl;
    for(size_t i = 0; i < times.size(); ++i)
    {
        datafile << setprecision(16) << times[i];
        for(size_t j = 0; j < fluxes[0].size(); ++j)
        {
            datafile << " " << fluxes[i][j] << " " << calcMag(fluxes[i][j]);
        }
        datafile << endl;
    }
    datafile.close();
}
