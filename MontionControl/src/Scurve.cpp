#include <stdio.h>
#include <math.h>
#include "PinConfig.h"
#include "Scurve.h"

const double phi = pi; // Total rotation angle(rad)
const double vm = phi / (ta + tm); // Max speed

double Scurve_velocity(double t)
{
    if (t <= 0) return 0.0;
    else if (t <= ta / 2)  return v1(t);
    else if (t <= ta) return v2(t);
    else if (t <= ta + tm) return v3();
    else if (t <= ta + tm + ta / 2) return v4(t);
    else if (t <= 2 * ta + tm) return v5(t);
    else return v5(2 * ta + tm);
}

double Scurve_position(double t)
{
    if (t <= 0) return 0.0;
    else if (t <= ta / 2)  return x1(t);
    else if (t <= ta) return x2(t);
    else if (t <= ta + tm) return x3(t);
    else if (t <= ta + tm + ta / 2) return x4(t);
    else if (t <= 2 * ta + tm) return x5(t);
    else return x5(2 * ta + tm);
}

// First half of the acceleration curve
double v1(double t) {
    return 2 * vm / (ta * ta) * t * t; 
}

// Second half of the acceleration curve
double v2(double t) {
    return vm - 2 * vm / (ta * ta) * (ta - t) * (ta - t); 
}

// Constant speed
double v3() {
    return vm; 
}

// First half of the deceleration curve
double v4(double t) {
    return vm - 2 * vm / (ta * ta) * (t - ta - tm) * (t - ta - tm); 
}

// Second half of the deceleration curve
double v5(double t) {
    return 2 * vm / (ta * ta) * (2 * ta + tm - t) * (2 * ta + tm - t);
}

// First half of the acceleration curve
double x1(double t) {
    return  2 * vm / (3 * ta * ta) * t * t * t;
}

// Second half of the acceleration curve
double x2(double t) {
    return vm * t + 2 * vm * (ta - t) * (ta - t) * (ta - t) / (3 * ta * ta) - vm * ta / 2; 
}

// Constant speed
double x3(double t) {
    return vm * t - vm * ta / 2;  
}

// First half of the deceleration curve
double x4(double t) {
    return vm * t - 2 * vm * (t - ta - tm) * (t - ta - tm) * (t - ta - tm)  / (3 * ta * ta) - vm * ta / 2; 
}

// Second half of the deceleration curve
double x5(double t) {
    return - 2 * vm * (2 * ta + tm - t) * (2 * ta + tm - t) * (2 * ta + tm - t) / (3 * ta * ta) + vm * ta + vm * tm;
}