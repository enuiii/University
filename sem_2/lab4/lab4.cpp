#include <iostream>

template <typename T, size_t N, size_t M>
class Matrix {
private:
	T data[N][M];

public:
	// Базовый конструктор
	Matrix() {}

	// Конструктор копирования
	Matrix(const Matrix& other) {
		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < M; j++) {
				data[i][j] = other.data[i][j];
			}
		}
	}

	// Оператор присваивания копированием
	Matrix& operator=(const Matrix& other) {
		if (this != &other) {
			for (size_t i = 0; i < N; i++) {
				for (size_t j = 0; j < M; j++) {
					data[i][j] = other.data[i][j];
				}
			}
		}
		return *this;
	}

	// Оператор вывода
	friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < M; j++) {
				os << matrix.data[i][j] << " ";
			}
			os << std::endl;
		}
		return os;
	}

	// Оператор ввода
	friend std::istream& operator>>(std::istream& is, Matrix& matrix) {
		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < M; j++) {
				is >> matrix.data[i][j];
			}
		}
		return is;
	}

	// Операторы сложения и присваивания суммы
	Matrix operator+(const Matrix& other) const {
		Matrix result;
		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < M; j++) {
				result.data[i][j] = data[i][j] + other.data[i][j];
			}
		}
		return result;
	}

	Matrix& operator+=(const Matrix& other) {
		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < M; j++) {
				data[i][j] += other.data[i][j];
			}
		}
		return *this;
	}

	// Операторы умножения и присваивания произведения
	template <size_t K>
	Matrix<T, N, K> operator*(const Matrix<T, M, K>& other) const {
		Matrix<T, N, K> result;
		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < K; j++) {
				result.data[i][j] = 0;
				for (size_t k = 0; k < M; k++) {
					result.data[i][j] += data[i][k] * other.data[k][j];
				}
			}
		}
		return result;
	}

	Matrix& operator*=(const T& scalar) {
		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < M; j++) {
				data[i][j] *= scalar;
			}
		}
		return *this;
	}

	Matrix operator*(const T& scalar) const {
		Matrix result(*this);
		result *= scalar;
		return result;
	}

	// Оператор инкремента
	Matrix& operator++() {
		for (size_t i = 0; i < N; i++) {
			for (size_t j = 0; j < M; j++) {
				data[i][j]++;
			}
		}
		return *this;
	}

	// Метод вычисления определителя
	T determinant() const {
		static_assert(N == M, "Matrix must be square");
		if (N == 1) {
			return data[0][0];
		}
		else if (N == 2) {
			return data[0][0] * data[1][1] - data[0][1] * data[1][0];
		}
		else if (N == 3) {
			return data[0][0] * data[1][1] * data[2][2] +
				data[0][1] * data[1][2] * data[2][0] +
				data[0][2] * data[1][0] * data[2][1] -
				data[0][2] * data[1][1] * data[2][0] -
				data[0][1] * data[1][0] * data[2][2] -
				data[0][0] * data[1][2] * data[2][1];
		}
		else {
			throw std::invalid_argument("Matrix size is not supported");
		}
	}

	// Метод получения элемента матрицы по индексу
	T& operator()(size_t i, size_t j) {
		return data[i][j];
	}

	// Константный метод получения элемента матрицы по индексу
	const T& operator()(size_t i, size_t j) const {
		return data[i][j];
	}
};

int main() {
	// Примеры конструкторов
	Matrix<int, 3, 3> matrix1; // инициализация пустой матрицы
	Matrix<int, 3, 3> matrix2(matrix1); // копирование матрицы
	Matrix<int, 2, 4> matrix3; // матрица другого размера

	// Пример оператора присваивания
	matrix2 = matrix1;

	// Пример оператора вывода
	std::cout << "matrix1:\n";
	std::cout << matrix1;

	// Пример оператора ввода
	std::cout << "Enter matrix3:\n";
	std::cin >> matrix3;

	// Пример оператора сложения
	Matrix<int, 3, 3> sum = matrix1 + matrix2;

	// Пример оператора присваивания суммы
	matrix1 += matrix2;

	// Пример оператора умножения
	Matrix<int, 3, 4> product = matrix1 * matrix3;

	// Пример оператора присваивания произведения
	matrix1 *= 2;

	// Пример оператора умножения на скаляр
	Matrix<int, 3, 3> scaled = matrix1 * 3;

	// Пример оператора инкремента
	++matrix1;

	// Пример метода получения элемента матрицы по индексу
	int element = matrix1(0, 0);

	// Пример константного метода получения элемента матрицы по индексу
	const Matrix<int, 3, 3> constMatrix(matrix1);
	int constElement = constMatrix(0, 0);

	// Пример метода вычисления определителя
	int determinant = matrix1.determinant();

	return 0;
}
