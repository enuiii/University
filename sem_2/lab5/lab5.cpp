#include <iostream>
#include <vector>

// Структура boolean определяет ссылку на отдельный бит в векторе.
struct boolean {
    char* byte; // Указатель на байт, содержащий данный бит.
    unsigned int n; // Номер бита в байте.

public:
    // Конструктор структуры reference.
    boolean(char* byte, unsigned int n) {
        this->byte = byte;
        this->n = n;
    }

    // Оператор присваивания для установки значения бита.
    boolean& operator = (bool value) {
        char p = (char)pow(2, n); // Вычисляем значение позиции бита в байте.
        if (value) {
            *byte |= p; // Устанавливаем бит.
        } else {
            *byte = *byte & ~p; // Сбрасываем бит.
        }
        return *this;
    }

    // Оператор приведения к типу bool для чтения значения бита.
    operator bool() {
        char p = (char)pow(2, n); // Вычисляем значение позиции бита в байте.
        char new_byte = *byte | p; // Создаем новый байт с установленным битом.
        return *byte == new_byte; // Сравниваем новый байт с исходным и возвращаем результат.
    }
};

// Шаблон класса std::vector для хранения булевых значений.
template<>
class std::vector<bool> {

    std::vector<char> bytes; // Вектор байтов.
    int _size = 0; // Количество битов в векторе.

public:
    // Оператор индексации для получения ссылки на отдельный бит.
    boolean operator[] (int index) {
        return boolean(&bytes[index / 8], index % 8);
    }

    // Метод push_back для добавления нового бита в вектор.
    void push_back(bool value) {
        _size++;
        if (_size % 8 == 1) {
            bytes.push_back(0); // Добавляем новый байт, если это необходимо.
        }
        (*this)[_size - 1] = value; // Устанавливаем значение последнего бита.
    }

    // Метод size для получения количества битов в векторе.
    size_t size() {
        return _size;
    }

    // Метод insert для вставки нового бита в заданную позицию.
    void insert(int n, bool value) {
        this->push_back((*this)[_size - 1]); // Добавляем новый бит в конец вектора.
        for (int i = _size - 1; i >= n; i--) {
            (*this)[i] = (bool)(*this)[i - 1]; // Сдвигаем биты вправо, начиная с заданной позиции.
        }
        (*this)[n] = value; // Устанавливаем значение нового бита.
     }

     // Метод erase для удаления бита из заданной позиции.
     void erase(int n) {
        for (int i = n; i < _size - 1; i++) {
            (*this)[i] = (bool)(*this)[i + 1]; // Сдвигаем биты влево, начиная с заданной позиции.
        }
        _size--;
        if (_size % 8 == 0){
            bytes.erase(bytes.end()); // Удаляем последний байт, если он стал пустым.
        }
    }
};
int main() {
    std::vector<bool> bits;

    // Добавляем несколько битов в вектор.
    bits.push_back(true);
    bits.push_back(false);
    bits.push_back(true);

    // Выводим количество битов в векторе.
    std::cout << "Vector size: " << bits.size() << std::endl;

    // Изменяем значение первого бита в векторе.
    bits[0] = false;

    // Выводим значения всех битов в векторе.
    for (int i = 0; i < bits.size(); i++) {
        std::cout << bits[i] << " ";
    }
    std::cout << std::endl;

    // Вставляем новый бит в середину вектора.
    bits.insert(1, true);

    // Удаляем последний бит из вектора.
    bits.erase(bits.size() - 1);

    // Выводим значения всех битов в векторе.
    for (int i = 0; i < bits.size(); i++) {
        std::cout << bits[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
