#include <iostream>
#include <string>

template<class T>
class Stack {
private:
    unsigned int maxNumberOfElements, numberOfElements = 0;
    T *elements;

public:
    // Конструктор класса Stack.
    Stack(unsigned int size) {
        maxNumberOfElements = size;

        try {
            elements = new T[size]; // Выделяем память под элементы стека.
        } catch (const std::bad_alloc &e) {
            std::cout << "INIT ERROR: too big size"; // Обработка исключения, если невозможно выделить память.
        }
    }

    // Деструктор класса Stack.
    ~Stack() {
        delete[] elements; // Освобождаем память, выделенную для элементов стека.
    }

    // Возвращает количество элементов в стеке.
    int size() {
        return numberOfElements;
    }

    // Проверяет, пуст ли стек.
    bool empty() {
        return numberOfElements != 0;
    }

    // Добавляет новый элемент в стек.
    bool push(T new_element) {
        if (numberOfElements < maxNumberOfElements) { // Если стек не переполнен,
            elements[numberOfElements] = new_element; // добавляем элемент в стек,
            numberOfElements++; // увеличиваем количество элементов в стеке,
            return true;
        } else {
            throw std::overflow_error("PUSH EXCEPTION: stack is full"); // Иначе генерируем исключение.
        }
    }

    // Извлекает верхний элемент из стека.
    T pop() {
        if (numberOfElements == 0) {
            throw std::out_of_range("POP EXCEPTION: stack is empty"); // Если стек пуст, генерируем исключение.
        } else {
            T element = elements[0]; // Сохраняем верхний элемент стека.
            for (int i = 0; i < maxNumberOfElements - 1; i++) {
                elements[i] = elements[i + 1]; // Сдвигаем остальные элементы стека на одну позицию вверх.
            }
            numberOfElements--; // Уменьшаем количество элементов в стеке.
            return element; // Возвращаем сохраненный верхний элемент стека.
        }
    }

    // Показывает верхний элемент стека, но не удаляет его.
    void top() {
        if (numberOfElements == 0) {
            throw std::logic_error("TOP EXCEPTION: stack is empty"); // Если стек пуст, генерируем исключение.
        } else {
            std::cout << elements[numberOfElements - 1] << std::endl; // Выводим верхний элемент стека.
        }
    }
};

int main() {
    try {
        Stack<int> stack(5); // Создаем объект класса Stack с размером 5.

        std::cout << "Stack is empty: " << stack.empty() << std::endl;

        for (int i = 0; i < 10; i++) {
            stack.push(i); // Пытаемся добавить 10 элементов в стек.
        }

        std::cout << "Stack is empty: " << stack.empty() << std::endl;
        std::cout << "Stack size: " << stack.size() << std::endl;

        stack.top(); // Показываем верхний элемент стека.

        for (int i = 0; i < 6; i++) {
            std::cout << "Element from stack: " << stack.pop() << std::endl; // Пытаемся извлечь 6 элементов из стека.
        }
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl; // Выводим сообщение об ошибке, если она произошла.
    }

    return 0; // Завершаем программу.
}
