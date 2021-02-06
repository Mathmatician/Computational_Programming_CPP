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
	void set_size(const int rows, const int cols);
	void set_size(const int rows, const int cols, const T val);
	void add_value_at(T val, const int rows, const int cols);
	T get_value_at(const int rows, const int cols);
	void display_matrix();
	MATRIX<T>& get_matrix();



	MATRIX* operator*(MATRIX<T>& right_matrix)
	{
		MATRIX* mtx = new MATRIX();
		
		if ((matrix.size() > 0 && matrix[0].size() > 0) && (right_matrix.matrix.size() > 0 && right_matrix.matrix[0].size() > 0))
		{
			if (matrix[0].size() == right_matrix.matrix.size())
			{
				for (int i = 0; i < matrix.size(); i++)
				{
					std::vector<double> ROW;
					for (int j = 0; j < right_matrix.matrix[0].size(); j++)
					{
						T val = 0;
						for (int k = 0; k < matrix[0].size(); k++)
						{
							val += matrix[i][k] * right_matrix.matrix[k][j];
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
MATRIX<T>::MATRIX() {}


template <typename T>
MATRIX<T>::MATRIX(int rows, int cols)
{
	set_size(rows, cols);
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
