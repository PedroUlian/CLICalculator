#include "number.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

Number create_number(const char* value) {
    Number n;
    n.number_str = strdup(value); 
    
    if (n.number_str == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memória para o número.\n");
        exit(1);
    }
    
    return n;
}

double to_double(Number n) {
    return atof(n.number_str); 
}

Number from_double(double d) {
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "%.15g", d);
    return create_number(buffer);
}

Number nadd(Number num1, Number num2){
    double res = to_double(num1) + to_double(num2);
    return from_double(res);
}

Number nsub(Number num1, Number num2){
    double res = to_double(num1) - to_double(num2);
    return from_double(res);
}

Number nmult(Number num1, Number num2){
    double res = to_double(num1) * to_double(num2);
    return from_double(res);
}

Number ndiv(Number num1, Number num2){
    double v2 = to_double(num2);
    if (v2 == 0) {
        return create_number("NaN");
    }
    return from_double(to_double(num1) / v2);
}

Number nroot(Number num1, Number num2){
	double res = pow(to_double(num2), 1.0/to_double(num1));
    return from_double(res);
}

Number npow(Number num1, Number num2){
    double res = pow(to_double(num1), to_double(num2));
    return from_double(res);
}