#include <iostream>
#include <cmath>
#include <vector>

// Базовый класс фигур
class Shape {
public:
    // Виртуальная функция для вычисления площади фигуры
    virtual double getArea() const = 0;
    // Виртуальная функция для вывода информации о фигуре на экран
    virtual void printInfo() const = 0;
};

// Класс для треугольника
class Triangle : public Shape {
private:
    double x1, y1, x2, y2, x3, y3; // Координаты вершин треугольника
    std::string color; // Цвет треугольника
public:
    // Конструктор класса Triangle
    Triangle(double _x1, double _y1, double _x2, double _y2, double _x3, double _y3, std::string _color) : x1(_x1), y1(_y1), x2(_x2), y2(_y2), x3(_x3), y3(_y3), color(_color) {}
    // Реализация метода вычисления площади для треугольника
    double getArea() const override {
        double a = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)); // Расстояние между точками (x1, y1) и (x2, y2)
        double b = sqrt(pow(x3 - x2, 2) + pow(y3 - y2, 2)); // Расстояние между точками (x2, y2) и (x3, y3)
        double c = sqrt(pow(x1 - x3, 2) + pow(y1 - y3, 2)); // Расстояние между точками (x3, y3) и (x1, y1)
        double p = (a + b + c) / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
    // Реализация метода вывода информации о треугольнике на экран
    void printInfo() const override {
        std::cout << "Triangle with сoordinates (" << x1 << ", " << y1 << "), (" << x2 << ", " << y2 << "), (" << x3 << ", " << y3 << ") and color " << color << std::endl;
    }
};

// Класс для прямоугольника
class Rectangle : public Shape {
private:
    double width, height; // Ширина и высота прямоугольника
    std::string color; // Цвет прямоугольника
public:
    // Конструктор класса Rectangle
    Rectangle(double _width, double _height, std::string _color) : width(_width), height(_height), color(_color) {}
    // Реализация метода вычисления площади для прямоугольника
    double getArea() const override {
        return width * height;
    }
    // Реализация метода вывода информации о прямоугольнике на экран
    void printInfo() const override {
        std::cout << "Rectangle with width " << width << ", height " << height << " and color " << color << std::endl;
    }
};

// Класс для круга
class Circle : public Shape {
private:
    double radius; // Радиус круга
    std::string color; // Цвет круга
public:
    // Конструктор класса Circle
    Circle(double _radius, std::string _color) : radius(_radius), color(_color) {}
    // Реализация метода вычисления площади для круга
    double getArea() const override {
        return M_PI * radius * radius;
    }
    // Реализация метода вывода информации о круге на экран
    void printInfo() const override {
        std::cout << "Circle with radius " << radius << " and color " << color << std::endl;
    }
};

int main() {
    // Создание вектора указателей на базовый класс Shape и добавление в него объектов трех разных классов
    std::vector<Shape*> shapes = {
        new Triangle(0, 0, 3, 0, 0, 4, "red"),
        new Rectangle(2, 5, "green"),
        new Circle(5, "blue")
    };

// Вывод информации о каждой фигуре на экран, включая ее площадь
for (const auto& shape : shapes) {
    shape->printInfo();
    std::cout << "Area: " << shape->getArea() << std::endl;
}

// Освобождение памяти, занятой объектами вектора
for (const auto& shape : shapes) {
    delete shape;
}

return 0;
}
