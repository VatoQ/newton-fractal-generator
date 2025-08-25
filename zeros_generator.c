#include "zeros_generator.h"
#include "format_complex.h"
#include "polynomial.h"
#include "config.h"

#include <complex.h>
#include <stdlib.h>
#include <stdio.h>

void _print_gen_message(double complex z, int i, double complex omega)
{
    char z_buf[64], omega_buf[64], omega_exp_buf[64];
    double complex omega_exp = cexp(omega);
    cmpl_to_string(z_buf, sizeof(z_buf), &z);
    cmpl_to_string(omega_buf, sizeof(omega_buf), &omega);
    cmpl_to_string(omega_exp_buf, sizeof(omega_exp_buf), &omega_exp);

    printf("Generating root of unity: %s\n \
\ti = %d, (double)i= %f\n \
\tomega = %s\n \
\texp(omega) = %s\n\n",
            z_buf,
            i, (double)i,
            omega_buf,
            omega_exp_buf);
}

Polynomial new_polynomial(double radius, int zero_count, zero_pattern mode)
{
    double complex* zeros = malloc(zero_count * sizeof(double complex));
    printf("Mode: %d\n", mode);
    const double complex omega = 2. * PI * I / (double)zero_count;
    //double complex omega_copy = omega;
    if (mode == NORMAL)
    {
        for (int i = 0; i < zero_count; i++)
        {
            double complex z = radius * cexp((double)i * omega);
            _print_gen_message(z, i, omega);
            zeros[i] = z;
        }
    }
    else if (mode == SPIRAL)
    {
        for (int i = 0; i < zero_count; i++)
        {
            double complex z = radius / ((double)i + 1) * cexp((double)i * omega);
            _print_gen_message(z, i, omega);
            zeros[i] = z;
        }
    }
    else if (mode == SPIRAL_INV)
    {
        for (int i = 0; i < zero_count; i++)
        {
            double complex z = ((double)i + 1) / radius * cexp((double)i * omega);
            _print_gen_message(z, i, omega);
            zeros[i] = z;
        }
    }
    Polynomial polynomial = make_polynomial(zero_count, zeros);
    return polynomial;
}

void free_polynomial(Polynomial *polynomial)
{
    free(polynomial->zeros);
}
