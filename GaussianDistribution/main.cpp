
#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

int main()
{
	printf("\n");
	int radius = 0;
	printf("    ENTER RADIUS : ");
	scanf_s("%d", &radius);
	printf("\n");
	float variance = 1.0f;
	printf("    ENTER VARIANCE : ");
	scanf_s("%f", &variance);
	printf("\n");

	float g = 5.0f / 6.0f;
	float total = 0.0f;
	for (int i = -radius; i <= radius; i++)
	{
		for (int k = -radius; k <= radius; k++)
		{
#if 1
			float w = 
				(1.0f / (2.0f * float(M_PI) * pow(g, 2))) * 
				exp(-(pow(float(k), 2) + pow(float(i), 2)) / (2.0f * pow(g, 2)));
#else
			float a = 1.0f / (variance * sqrt(2.0f * float(M_PI)));
			float b = 0.0f;
			float c = variance;
			float w = a * exp(-(
				(a * pow(float(k), 2)) + 
				(c * pow(float(i), 2))
				) / 
				(2.0f * pow(c, 2)));
#endif
			total += w;
			printf("Gaussian Weight : [x = %3d] [y = %3d] [w = %f]\n", k, i, w);
		}
	}
	printf("Weights Total : %f\n", total);

	_getch();
	return 0;
}