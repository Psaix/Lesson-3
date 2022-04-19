#include <iostream>
#include <vector>
#include <list>
#include <ostream>
#include <math.h>


// Task 1

void AveragePushBack(std::list<double>& average)
{
	size_t count{ 0 };
	double sum{ 0 };
	for (auto& a : average)
	{
		sum += a;
		count++;
	}
	average.push_back(sum / count);
}

void PrintList(std::list<double>& list)
{
	for (const auto& it : list)
		std::cout << it << " ";
	std::cout << "\n\n";
}


// Task 2

template<class T>
class Matrix {
private:
	size_t _size;
	T** tMatrix;

public:

	class iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
	public:
		iterator();
		iterator(const iterator& other);
		iterator& operator=(const iterator& other);
		T& operator*() const;
		T* operator->() const;
		bool operator==(const iterator& other) const;
		bool operator!=(const iterator& o) const;
		iterator& operator++();
		iterator operator++(int);
		iterator& operator--();
		iterator operator--(int);
	};

	Matrix() {};

	Matrix(std::vector<T> matrix) {
		size_t index = 0;
		_size = sqrt(matrix.size());
		tMatrix = new T * [_size];
		for (size_t i = 0; i < _size; i++) {
			tMatrix[i] = new T[_size];
		}
		for (size_t i = 0; i < _size; i++) {
			for (size_t j = 0; j < _size; j++) {
				tMatrix[i][j] = matrix[index++];
			}
		}
	};

	Matrix(std::initializer_list<std::initializer_list<T>> matrix) {
		_size = matrix.size();
		tMatrix = new T * [_size];
		for (size_t i = 0; i < _size; i++) {
			tMatrix[i] = new T[_size];
		}
		std::vector<std::vector<T>> init_matrix;
		for (auto it : matrix)
		{
			init_matrix.push_back(it);
		}
		for (size_t i = 0; i < _size; i++) {
			for (size_t j = 0; j < _size; j++) {
				tMatrix[i][j] = init_matrix[i][j];
			}
		}
	};

	T*& operator [](const int& index) const
	{
		return  tMatrix[index];
	}

	T GetDeterminant() {

		size_t start = 1;
		int det = 0;
		int degree = 1;
		int index = 0;
		std::vector<T> sub_matrix;

		if (_size == 1)
		{
			return tMatrix[0][0];
		}
		if (_size == 2)
		{
			return (tMatrix[0][0] * tMatrix[1][1]) - (tMatrix[1][0] * tMatrix[0][1]);
		};

		for (size_t head = 0; head < _size; head++)
		{
			if (head > 0)
				start = 0;

			for (size_t rows = 1; rows < _size; rows++)
			{
				for (size_t cols = start; cols < _size; cols++)
				{
					if (cols == head)
						continue;
					sub_matrix.push_back(tMatrix[rows][cols]);
				}
			}

			Matrix matrix(sub_matrix);
			sub_matrix.erase(sub_matrix.begin(), sub_matrix.end());

			det += (degree * tMatrix[index][head] * matrix.GetDeterminant());

			degree *= -1;
		}
		return det;
	}

	friend std::ostream& operator<<(std::ostream& os, Matrix& matrix) {
		for (size_t i = 0; i < matrix._size; i++)
		{
			for (size_t j = 0; j < matrix._size; j++)
			{
				os << matrix.tMatrix[i][j] << ' ';
			}
			std::cout << '\n';
		}
		return os;
	}

	~Matrix() {
		for (size_t i = 0; i < _size; i++) {
			delete[] tMatrix[i];
		}
		delete[] tMatrix;
	}
};



int main() {


	std::list<double> list{ 1.2, 1.4, 1.5, 1.3, 1.7 };

	PrintList(list);

	AveragePushBack(list);

	PrintList(list);

	Matrix<int> matrix{
		{0, 12, -12, 12, 6},
		{-3, -9, 9, 9, -6},
		{0, 0, -2, 4, -2},
		{-3, -17, 13, 3, -8},
		{0, 0, 4, -8, 0}
	};

	std::cout << matrix << "\n";

	std::cout << "Determinator of the matrix is: " << matrix.GetDeterminant() << "\n";

	return 0;
}