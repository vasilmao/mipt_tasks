#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <locale.h>

#define INFROOTS 3
#define EPSILON 1e-6




//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! int solve_quad_equation documentation
//! Solves square equation ax^2 + bx + c = 0
//!
//! @param [in] a a‐coefficient
//! @param [in] b b‐coefficient
//! @param [in] c c‐coefficient
//! @param [out] x1 Pointer to the 1st root
//! @param [out] x2 Pointer to the 2nd root
//!
//! @return Number of roots
//!
//! @note In case of infinite number of roots,
//! returns INFROOTS.
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int solve_quad_equation(float a, float b, float c, double *x1, double *x2);


//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! int is_equal_float documentation
//!
//! checks if two float values are approximately equal
//!
//! @param [in] a first float value
//! @param [in] b second float value
//!
//! @return 1 if two float values are approximately equal / 0 if not
//!
//! @note uses constant EPSILON that equals 1e-6
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
int is_equal_float(float a, float b);



int main() {

    printf("Square equation solver by Vasyan from IVT\n");

    float a = 0, b = 0, c = 0;

    printf("Введите 3 коэффициента квадратного уравнения\n");
    scanf("%f%f%f", &a, &b, &c);

    double x1 = 0, x2 = 0;

    int n_roots = solve_quad_equation(a, b, c, &x1, &x2);

    switch (n_roots) {
        case 0:
            printf("Корней нет!\n");
            break;

        case 1:
            printf("Один корень: %f\n", x1);
            break;

        case 2:
            printf("Два корня: %f и %f\n", x1, x2);
            break;

        case INFROOTS:
            printf("Любой корень\n");
            break;

        default:
            printf("Ошибка, количество корней = %d\n", n_roots);
            break;
    }

    return 0;
}


int solve_quad_equation(float a, float b, float c, double *x1, double *x2) {
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    if (a == 0) {
        if (b == 0) {
            if (c == 0) return INFROOTS;

            return 0;
        }

        *x1 = -c / b;
        return 1;
    }

    float discriminant = b * b - 4 * a * c;

    if (is_equal_float(discriminant, 0)) {
        *x1 = -b / 2 / a;
        return 1;
    }

    if (discriminant < 0) {
        return 0;
    }

    float discriminant_sqrt = sqrt(discriminant);

    *x1 = (-b + discriminant_sqrt) / (2 * a);
    *x2 = (-b - discriminant_sqrt) / (2 * a);
    return 2;
}


int is_equal_float(float a, float b) {
    return abs(a - b) < EPSILON;
}
