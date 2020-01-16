#include "Integrator.h"

using namespace std;

double integration(double acc,double velocity_prec, double a, double b, int n) {

    double h = (b - a) / n;
    double velocity;



    for (int i = 0 ; i < n ; i++) {
        velocity = velocity_prec + h * acc;
    }
    return velocity;

}