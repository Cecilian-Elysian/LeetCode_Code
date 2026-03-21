#include<stdio.h>
#include<stdlib.h>

double* convertTemperature(double celsius, int *returnSize);//ÉùÃ÷º¯Êý

int main()
{
	double celsius;
	scanf("%lf", &celsius); 
	int Size;
	double* result = convertTemperature(celsius, &Size);
	printf("%lf %lf", result[0] ,result[1]);
	free(result);
	return 0;
}

double* convertTemperature(double celsius, int* returnSize)
{
	*returnSize = 2;
	double* ans = (double*)malloc(sizeof(double) * 2);
	double fahrenheit = celsius * 1.80 + 32.00;
	double kelvin = celsius + 273.15;
	ans[1] = fahrenheit;
	ans[0] = kelvin;
	return ans;
}
