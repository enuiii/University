#include <iostream>
#include <vector>

int main()
{
	setlocale(LC_ALL, "russian");

	// push_back(), erase(), insert()

	/*1. Функция push_back() — это один из способов вставить новый элемент в конец вектора,
	который увеличивает размер вектора на 1*/
    std::vector<int> example;

	for (int i = 0; i < 10; i++)
	{
		example.push_back(i);
	}

	/*2. Функция erase() позволяет удалить элемент из середины или начала контейнера*/
	std::vector<int> numbers = { 1, 2, 3, 4, 5, 6 };

	numbers.erase(numbers.begin(), numbers.begin() + 3);

	/*3. Функция insert() используется для добавления одного или нескольких новых
	элементов перед конкретным элементом векторного объекта путем упоминания позиции
	этого элемента, следующие элементы */
	numbers.insert(numbers.begin() + 1, 3, 4);

	// emplace_back() создает объект в конце вектора без лишнего копирования(в отличие от push_back)
	numbers.emplace_back(321);

	// resize(), reserve(), shrink_to_fit(), capacity()

	// 1. resize() меняет размер вектора
	numbers.resize(4);

	// 2. reserve() меняет вместимость вектора
	numbers.reserve(20);

	// 3. shrink_to_fit() уменьшает количество используемой памяти для нашего вектора(меняет вместимость исходя из кол-ва элементов)
	numbers.shrink_to_fit();

	// 4. capacity() возвращает количество элементов, выделенное для массива
	numbers.capacity();

	// clear() удаляет все элементы из вектора
	//numbers.clear();

	// оператор присваивания и []
	for (int i = 0; i < numbers.size(); i++)
	{
		std::cout << numbers[i] << " "; // [] для получения элемента по индексу i
		numbers[i] = +10; // оператор присваивания, чтобы поменять значение числа по этому индексу
	}
}