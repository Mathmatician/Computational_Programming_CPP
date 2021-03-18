#pragma once

#include "Euler_Number.h";
#include "fraction.h"

#include <iostream>
#include <vector>

#define PI 3.14159265358979323846

template <typename T>
class MATRIX {

	// Number of rows : matrix.size()
	// Number of columns : matrix[0].size()

private:
	std::vector<std::vector<T>> matrix;

	T det_of_matrix(MATRIX<T>* mtx);
	T cofactor_of_position(MATRIX<T>* mtx, const int row, const int col);
	MATRIX<T>* adj_of_matrix(MATRIX<T>* mtx);
	MATRIX<T>* trans_of_matrix(MATRIX<T>* mtx);

public:
	MATRIX();
	MATRIX(int rows, int cols);
	MATRIX(int rows, int cols, const T val);
	void set_size(const int rows, const int cols);
	void set_size(const int rows, const int cols, const T val);
	const int get_row_size();
	const int get_colomn_size();
	void add_value_at(T val, const int rows, const int cols);
	T get_value_at(const int rows, const int cols);
	void display_matrix();
	MATRIX<T>& get_matrix();
	MATRIX<T>* calculate_inverse_matrix();
	T determinant_of_matrix();
	MATRIX<T>* adjoint_of_matrix();
	MATRIX<T>* transpose_of_matrix();

	MATRIX<T>* operator*(MATRIX<T>& right_matrix)
	{
		MATRIX<T>* mtx = new MATRIX<T>();

		if ((this->get_row_size() > 0 && this->get_colomn_size() > 0) && (right_matrix.get_row_size() > 0 && right_matrix.get_colomn_size() > 0))
		{
			if (this->get_colomn_size() == right_matrix.get_row_size())
			{
				for (int i = 0; i < this->get_row_size(); i++)
				{
					std::vector<T> ROW;
					for (int j = 0; j < right_matrix.get_colomn_size(); j++)
					{
						T val;
						val = 0;
						for (int k = 0; k < this->get_colomn_size(); k++)
						{
							val = val + this->get_value_at(i, k) * right_matrix.get_value_at(k, j);
						}
						ROW.push_back(val);
					}
					mtx->matrix.push_back(ROW);
				}
			}
		}

		return mtx;
	}
};


template <typename T>
MATRIX<T>* operator*(MATRIX<T>& input_matrix, double d_num)
{
	for (int i = 0; i < input_matrix.get_row_size(); i++)
	{
		for (int j = 0; j < input_matrix.get_colomn_size(); j++)
		{
			input_matrix.add_value_at(d_num * input_matrix.get_value_at(i, j), i, j);
		}
	}
	return &input_matrix;
}



template <typename T>
MATRIX<T>::MATRIX() {}


template <typename T>
MATRIX<T>::MATRIX(int rows, int cols)
{
	set_size(rows, cols);
}



template <typename T>
MATRIX<T>::MATRIX(int rows, int cols, const T val)
{
	set_size(rows, cols, val);
}


template <typename T>
void MATRIX<T>::set_size(const int rows, const int cols, const T val)
{
	for (int i = 0; i < rows; i++)
	{
		std::vector<T> ROW;
		for (int j = 0; j < cols; j++)
		{
			ROW.push_back(val);
		}

		matrix.push_back(ROW);
	}
}

template <typename T>
void MATRIX<T>::set_size(const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		std::vector<T> ROW;
		for (int j = 0; j < cols; j++)
		{
			T val;
			if (i == j)
				val = 1;
			else
				val = 0;

			ROW.push_back(val);
		}

		matrix.push_back(ROW);
	}
}



template <typename T>
const int MATRIX<T>::get_row_size()
{
	return matrix.size();
}


template <typename T>
const int MATRIX<T>::get_colomn_size()
{
	return matrix[0].size();
}



template <typename T>
void MATRIX<T>::add_value_at(T val, const int rows, const int cols)
{
	if (rows >= 0 && cols >= 0)
		if (rows < matrix.size() && cols < matrix[0].size())
			matrix[rows][cols] = val;
}



template <typename T>
T MATRIX<T>::get_value_at(const int rows, const int cols)
{
	if (rows >= 0 && cols >= 0)
		if (rows < matrix.size() && cols < matrix[0].size())
			return matrix[rows][cols];
	T a;
	a = 0;
	return a;
}



template <typename T>
void MATRIX<T>::display_matrix()
{
	for (auto& r : matrix)
	{
		for (auto& c : r)
			std::cout << c << " ";
		std::cout << std::endl;
	}
}


template <typename T>
MATRIX<T>& MATRIX<T>::get_matrix()
{
	return *this;
}


template <typename T>
MATRIX<T>* MATRIX<T>::calculate_inverse_matrix()
{
	//if (determinant_of_matrix() == 0)
		//return new MATRIX<T>(this->get_row_size(), this->get_colomn_size()); // returns empty matrix

	MATRIX<T>* adj_mtx = this->adjoint_of_matrix();
	double det_val = this->determinant_of_matrix();
	MATRIX<T>* inv_mtx =  adj_mtx->get_matrix() * (1 / det_val);

	return inv_mtx;
}

template <typename T>
T MATRIX<T>::determinant_of_matrix()
{
	if (matrix.size() != matrix[0].size())
		throw;

	return det_of_matrix(this);
}

template <typename T>
T MATRIX<T>::det_of_matrix(MATRIX<T>* mtx)
{
	T val;
	val = 0;
	if (mtx->get_row_size() > 2)
	{
		int sign = 1;
		for (int i = 0; i < mtx->get_row_size(); i++)
		{
			T factor = sign * mtx->get_value_at(0, i);
			MATRIX<T>* new_mtx = new MATRIX<T>(mtx->get_row_size() - 1, mtx->get_row_size() - 1, 0);
			for (int j = 1; j < mtx->get_row_size(); j++)
			{
				int K = 0;
				for (int k = 0; k < mtx->get_row_size(); k++)
				{
					if (k != i)
					{
						new_mtx->add_value_at(mtx->get_value_at(j, k), j - 1, K);
						K++;
					}
				}
			}
			val += factor * det_of_matrix(new_mtx);
			sign *= -1;

			delete new_mtx;
		}
	}
	else
		val = (mtx->get_value_at(0, 0) * mtx->get_value_at(1, 1) - mtx->get_value_at(0, 1) * mtx->get_value_at(1, 0));

	return val;
}




template <typename T>
T MATRIX<T>::cofactor_of_position(MATRIX<T>* mtx, const int row, const int col)
{
	MATRIX<T>* new_mtx = new MATRIX<T>(mtx->get_row_size() - 1, mtx->get_row_size() - 1);

	int I = 0;
	for (int i = 0; i < mtx->get_row_size(); i++)
	{
		if (i != row)
		{
			int J = 0;
			for (int j = 0; j < mtx->get_row_size(); j++)
			{
				if (j != col)
				{
					new_mtx->add_value_at(mtx->get_value_at(i, j), I, J);
					J++;
				}
			}
			I++;
		}
	}

	T val = pow(-1, row + col + 2) * det_of_matrix(new_mtx);

	delete new_mtx;

	return val;
}




template <typename T>
MATRIX<T>* MATRIX<T>::adjoint_of_matrix()
{
	if (this->get_colomn_size() != this->get_row_size())
		throw;

	return adj_of_matrix(this);
}

template <typename T>
MATRIX<T>* MATRIX<T>::adj_of_matrix(MATRIX<T>* mtx)
{
	MATRIX<T>* new_mtx = new MATRIX<T>(mtx->get_row_size(), mtx->get_colomn_size());

	for (int i = 0; i < new_mtx->get_row_size(); i++)
	{
		for (int j = 0; j < new_mtx->get_colomn_size(); j++)
		{
			new_mtx->add_value_at(cofactor_of_position(mtx, i, j), i, j);
		}
	}

	MATRIX<T>* final_mtx = new_mtx->transpose_of_matrix();
	delete new_mtx;
	return final_mtx;
}

template <typename T>
MATRIX<T>* MATRIX<T>::transpose_of_matrix()
{
	return trans_of_matrix(this);
}

template <typename T>
MATRIX<T>* MATRIX<T>::trans_of_matrix(MATRIX<T>* mtx)
{
	MATRIX<T>* new_mtx = new MATRIX<T>(mtx->get_colomn_size(), mtx->get_row_size());
	
	for (int i = 0; i < mtx->get_colomn_size(); i++)
	{
		for (int j = 0; j < mtx->get_row_size(); j++)
		{
			new_mtx->add_value_at(mtx->get_value_at(j, i), i, j);
		}
	}

	return new_mtx;
}
