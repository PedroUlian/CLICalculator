#ifndef NUMBER_H
#define NUMBER_H

typedef struct{
	char* number_str;
}Number;

Number create_number(const char* value);
Number nadd(Number num1, Number num2);
Number nsub(Number num1, Number num2);
Number nmult(Number num1, Number num2);
Number ndiv(Number num1, Number num2);
Number nroot(Number num1, Number num2);
Number npow(Number num1, Number num2);

#endif