/********************************************************************************
 *      Lightcurve - calculate the lightcurve for exoplanets                    *
 *      Copyright (C) 2017      Zhi-Yuan Deng                                   *
 *                              Sören Sander                                    *
 *                              Vanessa Vogt                                    *
 *                              Jubin Lirawi <jlirawi@astrophysik.uni-kiel.de>  *
 *                                                                              *
 *      This program is free software: you can redistribute it and/or modify    *
 *      it under the terms of the GNU General Public License as published by    *
 *      the Free Software Foundation, either version 3 of the License, or       *
 *      (at your option) any later version.                                     *
 *                                                                              *
 *      This program is distributed in the hope that it will be useful,         *
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *      GNU General Public License for more details.                            *
 *                                                                              *
 *      You should have received a copy of the GNU General Public License       *
 *      along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
 ********************************************************************************/
#include <iostream>
//#include <iomanip>
#include <fstream>
#include <vector>

#include "celestialObject.h"
#include "constant.h"
#include "earth.h"
#include "exomoon.h"
#include "exoplanet.h"
#include "fileio.h"
#include "functions.h"
#include "jupiter.h"
#include "star.h"
#include "sun.h"
#include "timedisc.h"

using namespace std;

// TODO: Proposal: New name for this software: Kiel ExoPlanetary Lightcurves for Education and Research (KEPLER)
// TODO: write all interesting parameters into the output file, e.g. number of planets and moons and the host they belong to, their parameters...
// TODO: Implementierung einer Methode zur Überprüfung der gegenseitigen Überlappung und entsprechenden Verdunkelungsberecnung. [Anm. von Duschl]
//       This could be done by using a (adaptive) sub-grid for the shaded area.
//       Or with the formalism presented in Saha & Sengupta (2022). In this case, the planet and its moon(s) should have a commom barycenter.
// TODO: Use a ray tracing method instead of blackout
// TODO: averageStarLightValue is only used in the blackout function at two points to normalise a value. That could be done in the function itself.
// TODO: the exoplanets and moons can reflect starlight but not yet emit thermal radiation. for that, at least, the stars need to have a temperature.
// TODO: add thermal emission of the exoplanet
// TODO: stars don't know anything like a host (see exoplanets). create an optional(!) barycenter as a host for binary star systems.
// TODO: make sure the timedisc class can only be instanciated once (maybe by using the singelton pattern)
// TODO: read "Roi Alonso - Characterisation of Exoplanets: Secondary Eclipses" and "Jesse Tarnas BA"

uint32_t Star::currentID = 0;
uint32_t Exoplanet::currentID = 0;
uint32_t Exomoon::currentID = 0;
vector<Star*> Star::stars = {};
vector<Exoplanet*> Exoplanet::exoplanets = {};
vector<Exomoon*> Exomoon::exomoons = {};

int main()
{
    #include "init.h"

    Timedisc solver(dt, Exoplanet::exoplanets.size(), adaptiveStep);
    FileIO file(filename);

    double flux = 0;
    double lastFlux = 0;

    file.writeHeader();
    lastFlux = 1 + calcCurve(Star::stars, Exoplanet::exoplanets, 0);
    file.data.push_back(lastFlux);
    while(solver.time < tSim)
    {
        solver.step(Exoplanet::exoplanets);
        flux = 1 + calcCurve(Star::stars, Exoplanet::exoplanets, 0);
        if(solver.adaptiveStepsize && abs(flux - lastFlux) > solver.fluxtol)
        {
            solver.rejectStep(Exoplanet::exoplanets, abs(flux - lastFlux));
        }
        else
        {
            solver.acceptStep();
            file.data.push_back(flux);// + noise(.023/6));
            lastFlux = flux;
            if(solver.stepNum % file.data.size() == 0)
            {
                file.flushData(solver.times);
                solver.times.clear();
            }
        }
    }
    file.flushData(solver.times);
    cout << "The data was written to " << filename << endl;
    return 0;
}
