#ifndef TIMEDISC_H
#define TIMEDIST_H

#include <vector>
#include <iostream>
#include <iomanip>

#include "celestialObject.h"
#include "exoplanet.h"

using namespace std;

class Timedisc final
{
  public:
    Timedisc(double dt, size_t bodysSize, bool adaptiveStep = true, double transDur = 3600);

    /**
     * This mehod performs the integration and thus updates the positions of the celestial objects.
     * @param bodys These are the objects on which the operation is performed.
     */
    void step(vector<Exoplanet*> bodys);

    /**
     * If it turns out, the last done step was acceptable, this method sets the new timestep.
     */
    void acceptStep();

    /**
     * If it turns out, the last done step was unacceptable, this method undoes it.
     * @param bodys These are the objects on which the operation is performed.
     * @param delta This is the error computed in the calculation of the last step.
     */
    void rejectStep(vector<Exoplanet*> bodys, double delta);

    size_t stepNum;
    double time, errtol, fluxtol;
    bool adaptiveStepsize;
    vector<double> times;

  private:
    /**
     * This function contains the ordinary differential equation we need to solve.
     * @param k This is the input value.
     * @return The derivative is returned.
     */
    double ode(CelestialObject* body, double k = 0);

    /**
     * This method updates the true anomaly of an celestial object as a function of the timestep.
     * The ode solver is explicit euler.
     * @param dt This is the timestep used for the numerical integration.
     * @param i The integer i indicates the i-th object.
     */
    void updateExplicitEuler(CelestialObject* body, size_t i);

    /**
     * This method updates the true anomaly of an celestial object as a function of the timestep.
     * The ode solver is Runge-Kutta of 4th order.
     * @param dt This is the timestep used for the numerical integration.
     * @param i The integer i indicates the i-th object.
     */
    void updateRK4(CelestialObject* body, size_t i);

    /**
     * This method updates the true anomaly of an celestial object as a function of the timestep.
     * The ode solver is Dormand-Prince of 4th/5th order.
     * @param dt This is the timestep used for the numerical integration.
     * @param i The integer i indicates the i-th object.
     */
    void updateDOPRI(CelestialObject* body, size_t i);

    double h, hstart, hmax, hflux, k1, k2, k3, k4, k5, k6, k7, b, bast, delta;
    vector<double> nextStep, herr;
};

#endif
