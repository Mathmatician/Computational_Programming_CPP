#include "Matrix.h"

#include <cmath>

MATRIX<double>* get_data(std::vector<double>);
MATRIX<Euler_Number>* get_data_euler(std::vector<double>);
MATRIX<Euler_Number>* Fast_Fourier_Matrix(int);
void Fast_Fourier_Transform(std::vector<double>);

MATRIX<Euler_Number>* Calculate_Fourier_Coefficients(std::vector<double> data)
{
	MATRIX<Euler_Number>* f_matrix = Fast_Fourier_Matrix(data.size());
	MATRIX<Euler_Number>* data_vect = get_data_euler(data);

	MATRIX<Euler_Number>* result = f_matrix->get_matrix() * data_vect->get_matrix();

	delete f_matrix;
	delete data_vect;

	return result;
}

MATRIX<double>* get_data_float(std::vector<double> data)
{
	MATRIX<double>* data_vect = new MATRIX<double>(data.size(), 1);
	for (int i = 0; i < data.size(); i++)
	{
		data_vect->add_value_at(data[i], i, 0);
	}
	return data_vect;
}

MATRIX<Euler_Number>* get_data_euler(std::vector<double> data)
{
	MATRIX<Euler_Number>* data_vect = new MATRIX<Euler_Number>(data.size(), 1);
	for (int i = 0; i < data.size(); i++)
	{
		Euler_Number val;
		val.set_real_number(data[i]);
		data_vect->add_value_at(val, i, 0);
	}
	return data_vect;
}

MATRIX<Euler_Number>* Fast_Fourier_Matrix(int n)
{
	MATRIX<Euler_Number>* m = new MATRIX<Euler_Number>(n, n);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int k = i * j;
			Euler_Number num;
			num.set_real_number(cos( (2 * PI * k) / n ));
			num.set_imaginary_number(-sin( (2 * PI * k) / n ));
			m->add_value_at(num, i, j);
		}
	}
	m = m->get_matrix() * (1 / sqrt(n));
	return m;
}

double Fourier_Interpolation_Function(MATRIX<Euler_Number>* data, double begin_point, double end_point, double t)
{
	double P = 0;
	double delta = end_point - begin_point;
	double large_delta = t - begin_point;
	int n = data->get_row_size() / 2;
	for (int k = 1; k < n; k++)
	{
		double a = data->get_value_at(k, 0).get_real_number();
		double b = data->get_value_at(k, 0).get_imaginary_number();
		double theta = (2.0f * (double)k * PI * large_delta) / delta;
		P += a * cos(theta) - b * sin(theta);
	}

	P *= 2.0f / sqrt((double)data->get_row_size());
	P += data->get_value_at(0, 0).get_real_number() / sqrt((double)data->get_row_size());
	P += (data->get_value_at(n, 0).get_real_number() * cos((data->get_row_size() * PI * large_delta) / delta)) / sqrt((double)data->get_row_size());

	return P;
}


double Fourier_Interpolation_Function(MATRIX<Euler_Number>* data, double t)
{
	double P = 0;
	int n = data->get_row_size() / 2;
	for (int k = 1; k < n; k++)
	{
		double a = data->get_value_at(k, 0).get_real_number();
		double b = data->get_value_at(k, 0).get_imaginary_number();
		double theta = (2.0f * (double)k * PI * t) / data->get_row_size();
		P += a * cos(theta) - b * sin(theta);
	}

	P *= 2.0f / sqrt((double)data->get_row_size());
	P += data->get_value_at(0, 0).get_real_number() / sqrt((double)data->get_row_size());
	P += (data->get_value_at(n, 0).get_real_number() * cos(PI * t)) / sqrt((double)data->get_row_size());

	return P;
}


/*--- Stores the data in a text file ---*/
void Fast_Fourier_Transform(std::vector<double> data)
{
	MATRIX<Euler_Number>* data_vec = Calculate_Fourier_Coefficients(data);

	std::ofstream file("Fourier_Transform_Data.txt");
	float i = 0;
	float f = data.size();
	float del = 0.01f;
	while (i < f)
	{
		file << Fourier_Interpolation_Function(data_vec, i);
		file << "\n";
		i += del;
	}
	file.close();
}
