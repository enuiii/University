#include <iostream>
#include <Windows.h>

// Класс
class Square
{
	// Абстракция
private:
	double side_;

	// Инкапсуляция
public:
	Square(double side) : side_(side)
	{}

	// Функция для нахождения диагонали
	double get_diagonal()
	{
		return sqrt(2) * side_;
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int n = 0;

	std::cout << "Введите сторону квадрата: "; std::cin >> n; std::cout << std::endl;
	Square square1(n);
	std::cout << "Диагональ квадрата равна: " << square1.get_diagonal(); std::cout << std::endl;
}