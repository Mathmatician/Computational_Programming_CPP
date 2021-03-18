#include "Matrix.h"

#include <vector>

// define functions
MATRIX<double>* Cubic_Spline_Matrix(std::vector<double> x_data, std::vector<double> y_data);
MATRIX<double>* Cubic_Spline_Vector(std::vector<double> x_data, std::vector<double> y_data);
void Cubic_Spline_Interpolation(std::vector<double> data);
void Cubic_Spline_Interpolation(std::vector<double> x_data, std::vector<double> y_data);


MATRIX<double>* Cubic_Spline_Matrix(std::vector<double> x_data, std::vector<double> y_data)
{
	if ((x_data.size() <= 0 || y_data.size() <= 0) && x_data.size() != y_data.size())
		return new MATRIX<double>();

	int data_size = x_data.size();
	MATRIX<double>* matrix = new MATRIX<double>(data_size, data_size, 0);

	// set first and last rows
	matrix->add_value_at(1, 0, 0);
	matrix->add_value_at(1, data_size - 1, data_size - 1);

	// set all remaining
	int current_row = 1;
	for (int i = 0; i < data_size - 2; i++)
	{
		double del_01 = x_data[i + 1] - x_data[i];
		double del_02 = x_data[i + 2] - x_data[i + 1];
		matrix->add_value_at(del_01, current_row, i);
		matrix->add_value_at(2 * del_01 + 2* del_02, current_row, i + 1);
		matrix->add_value_at(del_02, current_row, i + 2);
		current_row++;
	}

	return matrix;
}




MATRIX<double>* Cubic_Spline_Vector(std::vector<double> x_data, std::vector<double> y_data)
{
	if ((x_data.size() <= 0 || y_data.size() <= 0) && x_data.size() != y_data.size())
		return new MATRIX<double>();

	int data_size = y_data.size();
	MATRIX<double>* vec_mtx = new MATRIX<double>(data_size, 1);

	// set first and last index of vector matrix
	vec_mtx->add_value_at(0, 0, 0);
	vec_mtx->add_value_at(0, vec_mtx->get_row_size() - 1, 0);

	for (int i = 0; i < data_size - 2; i++)
	{
		double del_y_01 = y_data[i + 1] - y_data[i];
		double del_y_02 = y_data[i + 2] - y_data[i + 1];

		double del_x_01 = x_data[i + 1] - x_data[i];
		double del_x_02 = x_data[i + 2] - x_data[i + 1];

		vec_mtx->add_value_at(3 * ((del_y_02 / del_x_02) - (del_y_01 / del_x_01)), i + 1, 0);
	}

	return vec_mtx;
}




void Cubic_Spline_Interpolation(std::vector<double> data)
{
	// Assume change in x is 1
	std::vector<double> x_data;
	for (int i = 0; i < data.size(); i++) { x_data.push_back(i); }
	Cubic_Spline_Interpolation(x_data, data);
}




void Cubic_Spline_Interpolation(std::vector<double> x_data, std::vector<double> y_data)
{
	// Set data to matrix
	MATRIX<double>* data_vect = new MATRIX<double>(y_data.size(), 1);
	for (int i = 0; i < y_data.size(); i++)
	{
		data_vect->add_value_at(y_data[i], i, 0);
	}

	MATRIX<double>* inv_of_cubic_spline_mtx = Cubic_Spline_Matrix(x_data, y_data)->calculate_inverse_matrix();
	MATRIX<double>* vec_mtx = Cubic_Spline_Vector(x_data, y_data);
	MATRIX<double>* c_vals = inv_of_cubic_spline_mtx->get_matrix() * vec_mtx->get_matrix();

	delete inv_of_cubic_spline_mtx;
	delete vec_mtx;

	auto cubic_spline_function = [c_vals, x_data, y_data](double x) {
		int i = 0;
		while (i < x_data.size() && x_data[i] < x)
			i++;
		if (i != 0)
			i--;

		double del_x = x_data[i + 1] - x_data[i];
		double del_y = y_data[i + 1] - y_data[i];
		double c_1 = c_vals->get_value_at(i, 0);
		double c_2 = c_vals->get_value_at(i + 1, 0);

		double a = y_data[i];
		double d = (c_2 - c_1) / (3 * del_x);
		double b = (del_y / del_x) - ((del_x / 3) * ((2 * c_1) + c_2));

		double calc_val = a + b * (x - x_data[i]) + c_1 * pow((x - x_data[i]), 2) + d * pow((x - x_data[i]), 3);
		return calc_val;
	};

	std::ofstream file("Cublic_Spline_Data.txt");
	float del = 0.01f;
	double start = x_data[0];
	double end = x_data[x_data.size() - 1];
	while (start < end)
	{
		file << cubic_spline_function(start) << " ";
		file << start;
		file << "\n";
		start = start + del;
	}
	file.close();
}
