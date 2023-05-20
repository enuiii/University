#include <iostream>
#include <cstring>
#include <string>
#pragma warning( disable : 4996 )

class String {
private:
	char* str;
	int length;

public:
	// Базовый конструктор
	String() : str(nullptr), length(0) {}

	// Конструктор с одним параметром
	String(const char* s) {
		length = std::strlen(s);
		str = new char[length + 1];
		std::strcpy(str, s);
	}

	// Конструктор копирования
	String(const String& other) {
		length = other.length;
		str = new char[length + 1];
		std::strcpy(str, other.str);
	}

	// Оператор присваивания копированием
	String& operator=(const String& other) {
		if (this != &other) {
			delete[] str;
			length = other.length;
			str = new char[length + 1];
			std::strcpy(str, other.str);
		}
		return *this;
	}

	// Деструктор
	~String() {
		delete[] str;
	}

	// Оператор +
	String operator+(const String& other) const {
		String result;
		result.length = length + other.length;
		result.str = new char[result.length + 1];
		std::strcpy(result.str, str);
		std::strcat(result.str, other.str);
		return result;
	}

	// Оператор +=
	String& operator+=(const String& other) {
		char* temp = new char[length + 1];
		std::strcpy(temp, str);
		delete[] str;
		length += other.length;
		str = new char[length + 1];
		std::strcpy(str, temp);
		std::strcat(str, other.str);
		delete[] temp;
		return *this;
	}

	// Оператор []
	char& operator[](int index) {
		if (index >= 0 && index < length) {
			return str[index];
		}
		throw std::out_of_range("Index out of range");
	}

	const char& operator[](int index) const {
		if (index >= 0 && index < length) {
			return str[index];
		}
		throw std::out_of_range("Index out of range");
	}

	// Операторы сравнения
	bool operator<(const String& other) const {
		return std::strcmp(str, other.str) < 0;
	}

	bool operator>(const String& other) const {
		return std::strcmp(str, other.str) > 0;
	}

	bool operator==(const String& other) const {
		return std::strcmp(str, other.str) == 0;
	}

	// Операторы ввода и вывода в поток
	friend std::ostream& operator<<(std::ostream& os, const String& s);
	friend std::istream& operator>>(std::istream& is, String& s);

	// Метод find
	int find(char c) const {
		for (int i = 0; i < length; i++) {
			if (str[i] == c) {
				return i;
			}
		}
		return -1;
	}

	// Метод length
	int size() const {
		return length;
	}

	// Метод c_str
	const char* c_str() const {
		return str;
	}

	// Метод at
	char& at(int index) {
		if (index >= length || index < 0) {
			throw std::out_of_range("Index out of range");
		}
		return str[index];
	}

	const char& at(int index) const {
		if (index >= length || index < 0) {
			throw std::out_of_range("Index out of range");
		}
		return str[index];
	}
};

// Оператор вывода в поток
std::ostream& operator<<(std::ostream& os, const String& s) {
	return os << s.str;
}

// Оператор ввода из потока
std::istream& operator>>(std::istream& is, String& s) {
	std::string temp;
	std::getline(is, temp);
	s = temp.c_str();
	return is;
}

int main() {
	String s0; // Базовый конструктор
	String s1("hello"); // Базовый конструктор с одним параметром
	String s2("world");
	String s3 = s2; // Конструктор копирования
	s1 = s2; // Оператор присваивания копированием
	String s4 = s1 + s2; // Оператор +
	s1 += s2; // Оператор +=
	char c = s1[0]; // Оператор []
	bool b1 = (s1 < s2); // Операторы сравнения
	bool b2 = (s1 == s2);
	std::cout << s1 << std::endl; // Оператор вывода в поток
	std::cin >> s1; // Оператор ввода из потока
	int pos = s1.find('1'); // Метод find
	int len = s1.size(); // Метод length
	const char* str = s1.c_str(); // Метод c_str
	char c1 = s1.at(2); // Метод at
}
