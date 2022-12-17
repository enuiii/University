#include <iostream>
#include <Windows.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	short x;
	short* p;
	p = &x;

	std::cout << "Введите любое целое число: ";
	std::cin >> x;
	std::cout << std::endl;

	std::cout << p << std::endl;

	for (int i = 0; i < sizeof(short); i++)
	{
		printf("%hhu ", *(((char*)&p) + i));
	}
}