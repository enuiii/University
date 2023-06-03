#include <iostream>

template <typename T>
// Функция для конвертации данных из исходного массива в массив для результата
void convertData(T* source, T* output, int size) {
    // Указатель на исходный массив, приведенный к типу long long
    const long long* pointer1 = (const long long*)source;
    // Указатель на массив для результата, приведенный к типу long long
    long long* t_pointer1 = (long long*)output;

    // Количество элементов long long, необходимых для копирования
    int m = sizeof(int) * size / sizeof(long long);
    // Копирование long long из исходного массива в массив для результата
    for (int i = 0; i < m; ++i) {
        *(t_pointer1++) = *(pointer1++);
    }

    // Указатель на оставшиеся байты в исходном массиве
    char* pointer2 = (char*)pointer1;
    // Указатель на оставшиеся байты в массиве для результата
    char* t_pointer2 = (char*)t_pointer1;

    // Количество оставшихся байтов для копирования
    m = (sizeof(int) * size) % sizeof(long long);
    // Копирование оставшихся байтов из исходного массива в массив для результата
    for (int i = 0; i < m; i++) {
        *(t_pointer2++) = *(pointer2++);
    }

    // Если остались оставшиеся байты после копирования long long,
    // то копировать их в массив для результата как char
    if (m > 0) {
        // Указатель на оставшиеся байты в исходном массиве, приведенный к типу char
        char* c_pointer1 = (char*)(source + sizeof(int) * m / sizeof(char));
        // Указатель на оставшиеся байты в массиве для результата, приведенный к типу char
        char* c_pointer2 = (char*)(output + sizeof(long long) * m / sizeof(char));
        // Копирование оставшихся байтов из исходного массива в массив для результата
        for (int i = 0; i < m; i++) {
            *(c_pointer2++) = *(c_pointer1++);
        }
    }
}

int main() {
    const int N = 100;
    int mas_a[N] = { 1, 2, 3, 4, 5 };
    int mas_b[N] = { 0 };

    convertData(mas_a, mas_b, N);

    // Вывод результата в консоль
    std::cout << "mas_a: ";
    for (int i = 0; i < N; i++) {
        std::cout << mas_a[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "mas_b: ";
    for (int i = 0; i < N; i++) {
        std::cout << mas_b[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
