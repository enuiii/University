#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>

std::string multiply(std::string num1, std::string num2)
{
    int len1 = num1.size();
    int len2 = num2.size();
    if (len1 == 0 || len2 == 0)
        return "0";

    // Сохраняем номер рузультата в векторе в обратном порядке
    std::vector<int> result(len1 + len2, 0);

    // Используем два индекса для поиска позиций в результате
    int i_n1 = 0;
    int i_n2 = 0;

    // В n1 идем справа налево
    for (int i = len1 - 1; i >= 0; i--)
    {
        int carry = 0;
        int n1 = num1[i] - '0';

        // Для смещения позиции влево после каждого умножение цифры в n2
        i_n2 = 0;

        // в n2 идем справа налево           
        for (int j = len2 - 1; j >= 0; j--)
        {
            // Взять текущую цифру второго числа
            int n2 = num2[j] - '0';

            // Умножаем на текущую цифру первого числа и добавляем результат к ранее сохраненному результату в текущей позиции
            int sum = n1 * n2 + result[i_n1 + i_n2] + carry;

            // Переносим на следующую итерацию
            carry = sum / 10;

            // Сохраняем результат
            result[i_n1 + i_n2] = sum % 10;

            i_n2++;
        }

        // Сохраняем перенос в следующей ячейке
        if (carry > 0)
            result[i_n1 + i_n2] += carry;

        // Смещение позиции влево после каждого умножения цифры в n1.
        i_n1++;
    }

    // Игнорируем нули справа
    int i = result.size() - 1;
    while (i >= 0 && result[i] == 0)
        i--;

    // Если все были нули - значит либо оба, либо один из n1 или n2 был ноль
    if (i == -1)
        return "0";

    // Результирующая строка
    std::string s = "";

    while (i >= 0)
        s += std::to_string(result[i--]);

    return s;
}

std::string findSum(std::string str1, std::string str2)
{
    // Проверка на то, что длина из str2 больше
    if (str1.length() > str2.length())
        swap(str1, str2);

    // Пустая строка для хранения результата
    std::string str = "";

    // Вычисляем длину обеих строк
    int n1 = str1.length(), n2 = str2.length();

    // Reverse both of strings
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());

    int carry = 0;
    for (int i = 0; i < n1; i++)
    {
        // Считаем сумму текущих цифр и переносим их
        int sum = ((str1[i] - '0') + (str2[i] - '0') + carry);
        str.push_back(sum % 10 + '0');

        // Расчитываем перенос для следующего шага
        carry = sum / 10;
    }

    // Добавляем оставшиеся цифры большего числа
    for (int i = n1; i < n2; i++)
    {
        int sum = ((str2[i] - '0') + carry);
        str.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

    // Добавляем оставшийся перенос
    if (carry)
        str.push_back(carry + '0');

    // Создаем обратную результирующую строку
    reverse(str.begin(), str.end());

    return str;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string str1, str2;

	std::cout << "Введите первое большое число: "; std::cin >> str1;
	std::cout << "Введите второе большое число: "; std::cin >> str2;
	std::cout << "Сумма двух больших чисел: " << findSum(str1, str2);
	std::cout << std::endl;
	std::cout << "Разность двух больших чисел: " << multiply(str1, str2);
	std::cout << std::endl;

	return 0;
}