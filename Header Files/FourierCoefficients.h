#include <iostream>
#include <cmath>

class FourierCoefficients {
private:
	float real = 0;
	float imaginary = 0;

public:
	void set_real_number(float r) { real = r; }
	void set_imaginary_number(float i) { imaginary = i; }
	const float get_real_number() { return real; }
	const float get_imaginary_number() { return imaginary; }

	FourierCoefficients operator+(const FourierCoefficients& F_input)
	{
		FourierCoefficients F;
		F.set_imaginary_number(imaginary + F_input.imaginary);
		F.set_real_number(real + F_input.real);
		return F;
	}

	friend FourierCoefficients operator*(FourierCoefficients& F_input, double d_input);
	friend FourierCoefficients operator*(double d_input, FourierCoefficients F_input);
	friend std::ostream& operator<<(std::ostream& os, const FourierCoefficients& F_input);
};

FourierCoefficients operator*(FourierCoefficients& F_input, double d_input)
{
	FourierCoefficients F;
	F.set_imaginary_number(F_input.imaginary * d_input);
	F.set_real_number(F_input.real * d_input);
	return F;
}

FourierCoefficients operator*(double d_input, FourierCoefficients F_input)
{
	FourierCoefficients F;
	F.set_imaginary_number(F_input.imaginary * d_input);
	F.set_real_number(F_input.real * d_input);
	return F;
}

std::ostream& operator<<(std::ostream& os, const FourierCoefficients& F_input)
{
	os << "(";

	if (F_input.real != 0)
		os << F_input.real;

	if (F_input.imaginary != 0)
	{
		if (F_input.real != 0)
			os << ", ";

		if (F_input.imaginary == 1)
			os << "i";
		else
			os << F_input.imaginary << "i";
	}

	if (F_input.real == 0 && F_input.imaginary == 0)
		os << "0";

	os << ")";
	return os;
}
