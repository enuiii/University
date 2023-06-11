#include <iostream>
#include <string>
#include <fstream>

class Device {
private:
    std::string name; // Имя устройства.

public:
    explicit Device(const std::string& name) { // Конструктор принимает имя устройства.
        this->name = name;
    }

    void poll() { // Метод, который будет вызываться для каждого устройства в системе.
        std::cout << name << std::endl; // В данном случае, выводим имя устройства в консоль.
    }
};

// Класс ElectricityMeter представляет устройство для измерения электроэнергии.
class ElectricityMeter : public Device {
public:
    explicit ElectricityMeter(const std::string& name) : Device(name) {}; // Конструктор принимает имя устройства и передает его в конструктор базового класса.
};

// Класс DiscreteInputBlock представляет устройство для ввода дискретных сигналов.
class DiscreteInputBlock : public Device {
public:
    explicit DiscreteInputBlock(const std::string& name) : Device(name) {}; // Конструктор принимает имя устройства и передает его в конструктор базового класса.
};

// Класс HeatingControlBlock представляет устройство для управления отоплением.
class HeatingControlBlock : public Device {
public:
    explicit HeatingControlBlock(const std::string& name) : Device(name) {}; // Конструктор принимает имя устройства и передает его в конструктор базового класса.
};

// Массивы строк с названиями устройств каждого типа.
std::string electricitymeters[] = { "Меркурий 230", "Меркурий 230", "Энергомера CE308" };
std::string discreteInputblocks[] = { "Reallab NL-16HV", "Приборэлектро PRE-16", "Энергосервис ЭНМВ-1-24" };
std::string heatingcontrolblocks[] = { "Ouman S203", "Овен ТРМ232" };

// Структура, в которой будут храниться указатели на экземпляры классов для каждого типа устройств.
struct {
    ElectricityMeter* electricitymeter = nullptr;
    DiscreteInputBlock* discreteinputblock = nullptr;
    HeatingControlBlock* heatingcontrolblock = nullptr;
} configuration;

int main() {
    setlocale(LC_ALL, "ru");
    std::ifstream devices("../configuration.txt"); // Открываем файл с конфигурацией умного дома.
    std::string currentDevice;

    while (getline(devices, currentDevice)) { // Считываем каждое устройство из файла.
        int n = sizeof(electricitymeters) / sizeof(std::string);
        for (int i = 0; i < n; i++) { // Проверяем, является ли устройство счетчиком электрической энергии.
            if (electricitymeters[i] == currentDevice) {
                ElectricityMeter* electricitymeter = new ElectricityMeter(currentDevice);
                configuration.electricitymeter = electricitymeter;
            }
        }
        n = sizeof(discreteInputblocks) / sizeof(std::string);
        for (int i = 0; i < n; i++) { // Проверяем, является ли устройство блоком ввода дискретных сигналов.
            if (discreteInputblocks[i] == currentDevice) {
                DiscreteInputBlock* discreteinputblock = new DiscreteInputBlock(currentDevice);
                configuration.discreteinputblock = discreteinputblock;
            }
        }
        n = sizeof(heatingcontrolblocks) / sizeof(std::string);
        for (int i = 0; i < n; i++) { // Проверяем, является ли устройство блоком управления отоплением.
            if (heatingcontrolblocks[i] == currentDevice) {
                HeatingControlBlock* heatingcontrolblock = new HeatingControlBlock(currentDevice);
                configuration.heatingcontrolblock = heatingcontrolblock;
            }
        }
    }
}