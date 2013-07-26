
#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

int main()
{
	int radius = 0;
	printf("\n    ENTER RADIUS : ");
	scanf_s("%d", &radius);
	printf("\n\n");

	float g = 5.0f / 6.0f;
	for (int i = -radius; i <= radius; i++)
	{
		for (int k = -radius; k <= radius; k++)
		{
			float w = 
				(1.0f / (2.0f * float(M_PI) * pow(g, 2))) * 
				exp(-(pow(float(k), 2) + pow(float(i), 2)) / (2.0f * pow(g, 2)));
			printf("Gaussian Weight : [x = %3d] [y = %3d] [w = %f]\n", k, i, w);
		}
	}

	_getch();
	return 0;
}