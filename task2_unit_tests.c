#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <locale.h>

#define INFROOTS 3
#define EPSILON 1e-6
#define TESTERROR 1
#define MAXTESTS 20




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
int solve_quad_equation(float a, float b, float c, float *x1, float *x2);
//тестер:
void solve_quad_equation_tester();


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
//тестер:
void is_equal_float_tester();


int main() {
    solve_quad_equation_tester();
    printf("Square equation solver by Vasyan from IVT\n");

    float a = 0, b = 0, c = 0;

    printf("Введите 3 коэффициента квадратного уравнения\n");
    scanf("%f%f%f", &a, &b, &c);

    float x1 = 0, x2 = 0;

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



int solve_quad_equation(float a, float b, float c, float *x1, float *x2) {
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
    return fabs(a - b) < EPSILON;
}


//------------------------------
//!
//! тестеры
//!
//------------------------------

void solve_quad_equation_tester() {
    int n_tests = 6;
    float tests[MAXTESTS][3] = {
        {0, 0, 0},
        {1, 2, 3},
        {1, 4, 4},
        {0, 0, 3},
        {1, 1, 0},
        {0, 5, 3}
    };
    float answers[MAXTESTS][3] = {
        {INFROOTS, 0, 0},
        {0, 0, 0},
        {1, -2, 0},
        {0, 0, 0},
        {2, 0, -1},
        {1, -0.6, 0}
    };


    float a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
    int result = 0, expected_result = 0;
    float expected_x1 = 0, expected_x2 = 0;

    for(int i = 0; i < n_tests; ++i) {
        a = tests[i][0];
        b = tests[i][1];
        c = tests[i][2];
        x1 = 0;
        x2 = 0;
        expected_result = answers[i][0];
        expected_x1 = answers[i][1];
        expected_x2 = answers[i][2];
        result = solve_quad_equation(a, b, c, &x1, &x2);
        if (! (result == expected_result && x1 == expected_x1 && x2 == expected_x2)) {
            printf("Ошибка в функции solve_quad_equation\nТест номер %d\n", i );
            printf("параметры: a = %f, b = %f, c = %f\n", a, b, c);
            printf("ожидаемый  результат: функция возвращает = %d, x1 = %f, x2 = %f\n", expected_result, expected_x1, expected_x2);
            printf("полученный результат: функция возвращает = %d, x1 = %f, x2 = %f\n\n", result, x1, x2);
        }
    }
}

void is_equal_float_tester() {
    int n_tests = 4;
    float tests[MAXTESTS][2] = {
        {0, 0},
        {0, 0.000001},
        {0, 0.0000009},
        {-0, 0}
    };
    int answers[MAXTESTS] = {
        1,
        0,
        1,
        1
    };

    float a = 0, b = 0;
    int result = 0, expected_result = 0;


    for(int i = 0; i < n_tests; ++i) {
        a = tests[i][0];
        b = tests[i][1];
        expected_result = answers[i];
        int result = is_equal_float(a, b);
        if (! result == expected_result){
            printf("Ошибка в функции is_equal_float\nТест номер %d\n", i );
            printf("параметры: a = %f, b = %f\n", a, b);
            printf("ожидаемый  результат: функция возвращает = %d\n", expected_result);
            printf("полученный результат: функция возвращает = %d\n\n", result);
        }
    }
}
