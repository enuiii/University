#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

// Класс KinematicSolver решает обратную кинематику для двухзвенного манипулятора.
class KinematicSolver
{
public:
	int L1 = 0; // Длина первого звена.
	int L2 = 0; // Длина второго звена.
	double x = 0; // Координата X конца второго звена.
	double y = 0; // Координата Y конца второго звена.
	double alpha = 0; // Угол первого звена.
	double beta = 0; // Угол второго звена.

public:
	KinematicSolver() {};

	// Метод SetLengths устанавливает длины звеньев манипулятора.
	void SetLengths(unsigned int a_L1, unsigned int a_L2)
	{
		L1 = a_L1;
		L2 = a_L2;
	}

	// Метод Solve решает обратную кинематику для заданных координат конца второго звена.
	void Solve(double x, double y)
	{
		double B = sqrt(pow(x, 2) + pow(y, 2)); // Вычисляем длину отрезка от начала координат до конца второго звена.

		// Вычисляем углы первого и второго звена по формулам обратной кинематики.
		alpha = acos(x / B) - acos((pow(L1, 2) - pow(L2, 2) + (B * B)) / (2 * B * L1));
		beta = acos(-1) - acos((pow(L1, 2) + pow(L2, 2) - (B * B)) / (2 * L1 * L2));

		// Если sin(m_alpha) >= 0, то первое звено находится выше X-оси. 
		// В противном случае первое звено находится ниже X-оси, и нужно использовать другие значения углов.
		if (sin(alpha) >= 0) {
			x = L1 * cos(alpha);
			y = L1 * sin(alpha);
		}
		else {
			alpha = acos(x / B) + acos((pow(L1, 2) - pow(L2, 2) + (B * B)) / (2 * B * L1));
			beta = -beta;
			x = L1 * cos(alpha);
			y = L1 * sin(alpha);
		}

		// Переводим углы из радиан в градусы.
		alpha = static_cast<float>(alpha * 180 / acos(-1));
		beta = alpha + static_cast<float>(beta * 180 / acos(-1));
	}
};

// Функция main демонстрирует работу с классом KinematicSolver и отображает манипулятор с использованием SFML.
int main()
{
	setlocale(LC_ALL, "Russian");

	KinematicSolver Solver;
	std::cout << "(При вводе значений используйте величины от 1 до 10)" << std::endl;
	int L1, L2;
	std::cout << "Введите длину линий: " << std::endl;
	std::cin >> L1;
	std::cin >> L2;

	Solver.SetLengths(L1, L2);

	int x, y;
	std::cout << "Введите x и y: " << std::endl;
	std::cin >> x;
	std::cin >> y;

	Solver.Solve(x, y);

	std::cout << "Углы: " << Solver.alpha << ", " << Solver.beta << std::endl; // Выводим углы на консоль.

	sf::RenderWindow window(sf::VideoMode(1000.f, 800.f), "Kinematic Solver");

	sf::RectangleShape line1(sf::Vector2f(static_cast<float>(50 * Solver.L1), 5.f)); // Создаем прямоугольник для первого звена манипулятора.
	sf::RectangleShape line2(sf::Vector2f(static_cast<float>(50 * Solver.L2), 5.f)); // Создаем прямоугольник для второго звена манипулятора.
	line1.setFillColor(sf::Color::Green); // Задаем цвет первого звена.
	line2.setFillColor(sf::Color::Yellow); // Задаем цвет второго звена.

	line1.setPosition(500.f, 500.f); // Задаем начальную позицию первого звена.
	line2.setPosition(static_cast<float>(500 + 50 * Solver.x), static_cast<float>(500 - 50 * Solver.y)); // Задаем начальную позицию второго звена.

	line1.rotate(-1 * Solver.alpha); // Поворачиваем первое звено на угол alpha.
	line2.rotate(-1 * Solver.beta); // Поворачиваем второе звено на угол beta.

	while (window.isOpen()) // Запускаем главный цикл приложения.
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(line1); // Отображаем первое звено манипулятора.
		window.draw(line2); // Отображаем второе звено манипулятора.
		window.display(); // Обновляем содержимое окна.
	}
}
