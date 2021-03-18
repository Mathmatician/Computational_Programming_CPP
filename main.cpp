#include <iostream>
#include <vector>
#include <fstream>

#include "Statistics.h"

void Fast_Fourier_Transform(std::vector<double>);
void Cubic_Spline_Interpolation(std::vector<double>);

int main(int argc, char* argv[])
{	
	// Test data
	std::vector<double> data = {-2.2, -2.8, -6.1, -3.9, 0.0, 1.1, -0.6, -1.1};
	std::vector<double> x_data = { 1, 2.2, 4.6, 8, 10, 11, 11.5, 12 };

	for (int i = 1; i < argc; i++)
	{
		int val = (int)argv[i];
		switch (val)
		{
			case FAST_FOURIER_TRANSFORM:
				Fast_Fourier_Transform(data);
				break;
			case CUBIC_SPLINE_INTERPOLATION:
				Cubic_Spline_Interpolation(x_data, data); // Computationally Expensive
				break;
			default:
				break;
		}
	}

	return 0;
}