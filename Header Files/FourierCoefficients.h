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
};

FourierCoefficients operator*(FourierCoefficients& F_input, double d_input)
{
	FourierCoefficients F;
	F.set_imaginary_number(F_input.get_imaginary_number() * d_input);
	F.set_real_number(F_input.get_real_number() * d_input);
	return F;
}

FourierCoefficients operator*(double d_input, FourierCoefficients F_input)
{
	FourierCoefficients F;
	F.set_imaginary_number(F_input.get_imaginary_number() * d_input);
	F.set_real_number(F_input.get_real_number() * d_input);
	return F;
}
