#include "timedisc.h"

using namespace std;

Timedisc::Timedisc(double dt, size_t bodysSize, bool adaptiveStep, double transDur)
{
    time = 0;
    h = dt;
    hmax = transDur / 2.;
    k1 = 0;
    k2 = 0;
    k3 = 0;
    k4 = 0;
    k5 = 0;
    k6 = 0;
    k7 = 0;
    b = 0;
    bast = 0;
    delta = 0;
    errtol = 1e-12;
    fluxtol = 1e-4;
    adaptiveStepsize = adaptiveStep;

    stepNum = 0;

    times.reserve(262144); // 262144 = 2**18
    times.push_back(0);

    nextStep.reserve(bodysSize);
    nextStep.resize(bodysSize);

    herr.reserve(bodysSize);
    herr.resize(bodysSize);
    for (double &i : herr) i = h;
}

void Timedisc::step(vector<Exoplanet*> bodys)
{
    do
    {
        hstart = h;
        for (size_t i = 0; i < bodys.size(); i++)
        {
            updateDOPRI(bodys[i], i);
        }
    }
    while (h < .9 * hstart);

    for (size_t i = 0; i < bodys.size(); i++)
    {
        bodys[i]->trueAnomaly += nextStep[i];
        bodys[i]->updatePosition();
    }
}

void Timedisc::acceptStep()
{
    time += h;
    times.push_back(time);
    stepNum++;

    if(adaptiveStepsize)
    {
        h = hmax;
        // find the smallest item in herr
        for (double &item : herr) if (item < h) h = item;
    }
}

void Timedisc::rejectStep(vector<Exoplanet*> bodys, double deltaFlux)
{
    for (size_t i = 0; i < bodys.size(); i++)
    {
        bodys[i]->trueAnomaly -= nextStep[i];
        bodys[i]->updatePosition();
    }
    h = 0.9 * h * pow(fluxtol / deltaFlux, 0.25); // flux limited
}

double Timedisc::ode(CelestialObject* body, double k)
{
    return 2 * M_PI / body->period * (1 + body->eccentricity * cos(body->trueAnomaly + k)) / pow(1 - body->eccentricity * body->eccentricity, 1.5);
}

void Timedisc::updateExplicitEuler(CelestialObject* body, size_t i)
{
    nextStep[i] = ode(body, 0) * h;
}

void Timedisc::updateRK4(CelestialObject* body, size_t i)
{
    k1 = ode(body, 0);
    k2 = ode(body, 0.5*h*k1);
    k3 = ode(body, 0.5*h*k2);
    k4 = ode(body, h*k3);

    nextStep[i] =  h / 6 * (k1 + 2*k2 + 2*k3 + k4);
}

void Timedisc::updateDOPRI(CelestialObject* body, size_t i)
{
    k1 = h * ode(body, 0);
    k2 = h * ode(body,        1./5.*k1);
    k3 = h * ode(body,       3./40.*k1 +       9./40.*k2);
    k4 = h * ode(body,      44./45.*k1 -      56./15.*k2 +       32./9.*k3);
    k5 = h * ode(body, 19372./6561.*k1 - 25360./2187.*k2 + 64448./6561.*k3 - 212./729.*k4);
    k6 = h * ode(body,  9017./3168.*k1 -     355./33.*k2 + 46732./5247.*k3 +  49./176.*k4 -   5103./18656.*k5);
    k7 = h * ode(body,     35./384.*k1 +                     500./1113.*k3 + 125./192.*k4 -    2187./6784.*k5 +    11./84.*k6);
    b    =                 35./384.*k1 +                     500./1113.*k3 + 125./192.*k4 -    2187./6784.*k5 +    11./84.*k6;
    bast =             5179./57600.*k1 +                   7571./16695.*k3 + 393./640.*k4 - 92097./339200.*k5 + 187./2100.*k6 + 1./40.*k7;
    delta = abs(b - bast);
    if(delta == 0) delta = errtol;
    if(delta > errtol) herr[i] = 0.9 * h * pow(errtol / delta, 0.25);
    else               herr[i] = 0.9 * h * pow(errtol / delta, 0.20);
    nextStep[i] = b;
}
