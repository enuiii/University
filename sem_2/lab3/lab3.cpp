#include <iostream>

class Complex
{
private:
	double re, im; // действительная и мнимая части

public:
	// конструкторы
	
	 Complex() // базовый конструктор
  	{
    		re = 0;
    		im = 0;
  	}

	Complex(double r, double i)
	{
		re = r;
		im = i;
	}

	Complex(const Complex& c) // конструктор копирования
	{
		re = c.re;
		im = c.im;
	}

	// деструктор
	~Complex()
	{
	}

	// оператор присваивания
	Complex& operator = (Complex& c)
	{
		re = c.re;
		im = c.im;

		return (*this);
	}

	// оператор сложения
	Complex operator + (const Complex& c)
	{
		return Complex(re + c.re, im + c.im);
	}

	// оператор +=
	Complex& operator += (Complex& c)
	{
		re += c.re;
		im += c.im;
		return *this;
	}

	// оператор умножения
	Complex operator * (const Complex& c)
	{
		return Complex(re * c.re - im * c.im, re * c.im + im * c.re);
	}

	// оператор *=
	Complex& operator *= (Complex& c)
	{
		re *= c.re;
		im *= c.im;
		return *this;
	}

	// префиксное ++
	Complex operator ++ ()
	{
		re += 1;
		return *this;
	}

	// постфиксное ++
	Complex operator ++ (int)
	{
		Complex temp = *this;
		re += 1;
		return temp;
	}

	friend std::ostream& operator<< (std::ostream&, const Complex&);
	friend std::istream& operator>> (std::istream&, Complex&);
};

// оператор вывода
std::ostream& operator<< (std::ostream& out, const Complex& c)
{
	out << "(" << c.re << ", " << c.im << ")";
	return out;
}

// оператор ввода
std::istream& operator>> (std::istream& in, Complex& c)
{
	in >> c.re >> c.im;
	return in;
}

int main()
{
	Complex a(5, 2);
	Complex b(3, -3);

	std::cout << "a = " << a << "; b =" << b << std::endl;

	std::cout << a++;

	return 0;
}
