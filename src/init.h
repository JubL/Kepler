double tSim       = 15.25 * Constant::day; /** Simulate for this time in seconds. */
double dt         = 100; // max 200 /** timestep; this is only used when the adaptive time step control is disengaged. */
bool adaptiveStep = true; /** controls whether the adaptive time step control is active */
string filename   = "lightcurve.dat";

// ----- Star -----
//double starPositionX = 0; /** These are the cartesian coordinates of this star in meters. */
//double starPositionY = 0;
//double starPositionZ = 0;
double radiusStar             = 1.19 * Constant::radiusSun; /** Star radius in meters. */
double massStar               = 1.23 * Constant::massSun;   /** Star mass in kilograms. */
vector<double> limbDarkeningA = {0.5327};                   /** limb darkening coefficient a. */
vector<double> limbDarkeningB = {0.1683};                   /** limb darkening coefficient b. */
//double Teff                 = 5772;                       /** effective temperature of this star */

// ----- Exoplanet -----
// exoplanet1 variables:
double massExo1                     = 232 * Constant::massEarth;    /** Mass of the exoplanet in kilograms. */
double radiusExo1                   = 15.6 * Constant::radiusEarth; /** Radius of the exoplanet in meters. */
double periodExo1                   = 3.5247486 * Constant::day;    /** The exoplanets orbital period in seconds. */
double trueAnomalyStartExo1         = -0.57 * M_PI;                 /** Start position of the exoplanet in radians. */
double inclinationExo1              = 86.71;                        /** This is the inclination of the orbit of the exoplanet in degree. */
double eccentricityExo1             = 0.0;                          /** This is the eccentricity of the orbit. */
double argumentOfPericenterExo1     = 0;                            /** This is the argument of pericenter of the orbit in radians. */
double longitudeOfAscendingNodeExo1 = M_PI / 2;                     /** This is the longitude of the ascending node of the orbit in radians. */
double albedoExo1                   = 0.306;                        /** This is the exoplanets bond albedo. */

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable" // this is here to surpress warnings of unused vaiables
Star star1(massStar, radiusStar, limbDarkeningA, limbDarkeningB);//, starPositionX, starPositionY, starPositionZ);
Exoplanet exo1(massExo1, radiusExo1, periodExo1, trueAnomalyStartExo1, inclinationExo1, eccentricityExo1, argumentOfPericenterExo1, longitudeOfAscendingNodeExo1, albedoExo1, star1);

Star star2(massStar, radiusStar*.9, limbDarkeningA, limbDarkeningB, 1e15, -1e8, 1e7);
Exoplanet exo2(massExo1*8, 2*radiusExo1, 1.5*periodExo1, .9*trueAnomalyStartExo1, inclinationExo1, eccentricityExo1, argumentOfPericenterExo1, longitudeOfAscendingNodeExo1, albedoExo1, star2);

Star star3(1.03*massStar, radiusStar*.9, limbDarkeningA, limbDarkeningB, 1e15, -1e8, 1e7);
#pragma GCC diagnostic pop
