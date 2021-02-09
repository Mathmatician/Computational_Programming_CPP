#include "Matrix.h"

MATRIX<double>* get_data(std::vector<double>);
MATRIX<Euler_Number>* get_data_euler(std::vector<double>);

MATRIX<Euler_Number>* Calculate_Fourier_Coefficients(std::vector<double> data)
{
	Euler_Number num;
	num.set_real_number(-1);
	num.set_imaginary_number(1);

	MATRIX<Euler_Number>* f_matrix = new MATRIX<Euler_Number>(data.size(), data.size(), num);
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