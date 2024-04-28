#include <Wire.h>
#include "PinConfig.h"
#include "TrapezoidalCurve.h"

const double phi = pi; // Total rotation angle(rad)
const double vm = phi / (ta + tm); // Max speed

double TrapezoidalCurve_position(double t)
{
    if (t <= 0) return 0.0;
    else if (t <= ta) return s1(t);
    else if (t <= ta + tm) return s2(t);
    else if (t <= 2 * ta + tm) return s3(t);
    else return phi;
}

double s1(double t) {
    return vm / (2 * ta) * t * t;
}

double s2(double t) {
    return vm * ta / 2 + vm * (t - ta);
}

double s3(double t) {
    return vm * ta / 2 + vm * tm + vm * (t - ta - tm) - vm / (2 * ta) * (t - ta - tm) * (t - ta - tm);
}