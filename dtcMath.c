/*
    under testing
*/

#include <math.h>

#include "dtcMath.h"

const int cosN = 10;

const double pCosCoe[] = { 
    1,
    -0.5,
    4.1666666667E-2,
    -1.3888888889E-3,
    2.4801587302E-5,
    -2.7557319223E-7,
    2.0876756988E-9,
    -1.1470745598E-11,
    4.7794773324E-14,
    -1.5619206969E-16,
};

double dtcCos(double x)
{
    double fact = 0;
    double midX = x >= 0 ? x : -x;
    int i = 0;
    while (midX > 2 * M_PI){
	midX = midX - 2 * M_PI;
    }
    fact += pCosCoe[0];
    for (i = 1; i < cosN; i++){
	midX = midX * midX;
	fact += midX * pCosCoe[i];
    }
    return fact;
}
