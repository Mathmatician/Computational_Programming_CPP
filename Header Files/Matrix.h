#include "Euler_Number.h";

#include <iostream>
#include <vector>

template <typename T>
class MATRIX {

	// Number of rows : matrix.size()
	// Number of columns : matrix[0].size()

private:
	std::vector<std::vector<T>> matrix;
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

/*
template <typename T>
MATRIX<T>* operator*(MATRIX<T>& left_matrix, MATRIX<T>& right_matrix)
{
	MATRIX<T>* mtx = new MATRIX<T>();

	if ((left_matrix.get_row_size() > 0 && left_matrix.get_colomn_size() > 0) && (right_matrix.get_row_size() > 0 && right_matrix.get_colomn_size() > 0))
	{
		if (left_matrix.get_colomn_size() == right_matrix.get_row_size())
		{
			//mtx->set_size(left_matrix.get_row_size(), right_matrix.get_colomn_size());
			std::vector<T> ROW;
			for (int i = 0; i < left_matrix.get_row_size(); i++)
			{
				for (int j = 0; j < right_matrix.get_colomn_size(); j++)
				{
					T val;
					val = 0;
					for (int k = 0; k < left_matrix.get_colomn_size(); k++)
					{
						val = val + left_matrix.get_value_at(i, k) * right_matrix.get_value_at(k, j);
					}
					//mtx->add_value_at(val, i, j);
					ROW.push_back(val);
				}
				mtx->add_row(ROW);
			}
		}
	}

	return mtx;
}*/



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
