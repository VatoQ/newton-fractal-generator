#include "polynomial.h"
#include <complex.h>

#define EPS 1e-8

double complex _derivative(Polynomial* polynomial, double complex z)
{
    double complex f_z = polynomial->exec(polynomial, z);
    double complex f_z_h = polynomial->exec(polynomial, z + EPS);

    return (f_z_h - f_z) / EPS;
}

double complex _newton(Polynomial* polynomial, double complex z)
{
    double complex f_z = polynomial->exec(polynomial, z);

    while (cabs(f_z) > EPS)
    {
        z = z - polynomial->exec(polynomial, z) / _derivative(polynomial, z);
        f_z = polynomial->exec(polynomial, z);
    }

    return z;
}

double complex _poly_exec(Polynomial* polynomial, double complex z)
{
    double complex res = {1.0, 0.0};

    for (int i = 0; i < polynomial->zero_count; i++)
    {
        res *= z - polynomial->zeros[i];
    }

    return res;
}


Polynomial make_polynomial(int zero_count, _Complex double *zeros)
{
    Polynomial polynomial;
    polynomial.zero_count = zero_count;
    polynomial.zeros = zeros;
    polynomial.exec = &_poly_exec;
    polynomial.get_zero = &_newton;
    return polynomial;
}



