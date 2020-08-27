#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int solve_quad_equation(float a, float b, float c, double *x1, double *x2){
    if (a == 0){
        if (b == 0){
            if (c == 0) return 3;
            return 0;
        }
        *x1 = -c / b;
        return 1;
    }
    double quad_discriminant = b * b - 4 * a * c;
    if (quad_discriminant < 0){
        return 0;
    }
    if (quad_discriminant == 0){
        *x1 = -b / 2 / a;
        return 1;
    }
    *x1 = (-b + sqrt(quad_discriminant)) / 2 / a;
    *x2 = (-b - sqrt(quad_discriminant)) / 2 / a;
    return 2;
}

int main(){
    //windows cmd не любит кириллицу (кодировка cp1251), поэтому изменяем кодировку на utf-8 (65001)
    #ifdef _WIN32
        system("chcp 65001");
    #endif

    float a, b, c;

    printf("Введите 3 коэффициента квадратного уравнения\n");
    scanf("%f%f%f", &a, &b, &c);

    double x1, x2;

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
        case 3:
            printf("Любой корень\n");
            break;
        default:
            printf("Ошибка, количество корней = %d\n", n_roots);
            break;
    }
}
