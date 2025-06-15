#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <conio.h>

using namespace std;

// Структура для представления блока управления памятью (MCB)
struct MCB {
    char type; // Тип блока
    unsigned short owner; // Владелец
    unsigned short size; // Размер блока в параграфах
    char pgmname[8]; // Имя программы (только для DOS 4.0 и выше)
};

// Глобальные переменные
vector<MCB> memoryBlocks; // Вектор для хранения блоков памяти
unsigned short memtop; // Сегментный адрес начала памяти
unsigned char dosVersion; // Версия DOS

// Функция для получения версии DOS
void get_DOS_ver_h() {
    // Эмулируем получение версии DOS
    dosVersion = 4; // Пример: версия DOS 4.0
}

// Функция для вывода заголовка
void print_head() {
    cout << "---------------" << endl;
    cout << "              Практическая работа N31-32              " << endl;
    cout << "---------------" << endl;
    cout << "                 Управление памятью               " << endl;
    cout << "---------------" << endl;
    cout << "Карта распределяемой памяти." << endl;
}

// Функция для инициализации блоков памяти (эмуляция)
void initializeMemoryBlocks() {
    // Эмулируем несколько блоков памяти
    memoryBlocks.push_back({ 'M', 0x0008, 0x1234, "BLOCK1" });
    memoryBlocks.push_back({ 'M', 0x0008, 0x0040, "BLOCK2" });
    memoryBlocks.push_back({ 'M', 0x04A0, 0x0030, "BLOCK3" });
    memoryBlocks.push_back({ 'M', 0x04A0, 0x00A0, "BLOCK4" });
    memoryBlocks.push_back({ 'Z', 0x0000, 0x0000, "" }); // Конец списка
}

// Функция для вывода карты распределяемой памяти
void printMemoryMap() {
    for (const auto& block : memoryBlocks) {
        cout << "Addr=0000:0000  "; // Здесь можно добавить сегментный адрес
        cout << "PID=" << hex << setw(4) << setfill('0') << block.owner << "  ";
        cout << "Size=" << dec << block.size * 16 << "    "; // Размер в байтах
        if (block.owner == 0) {
            cout << "Free"; // Блок свободен
        }
        else {
            cout << "Used"; // Блок занят
            if (dosVersion >= 4) {
                cout << " " << block.pgmname; // Имя программы
            }
        }
        cout << endl;
    }
}

int main() {
    std::locale::global(std::locale(""));
    SetConsoleOutputCP(CP_UTF8); // Устанавливаем кодировку UTF-8

    print_head();
    get_DOS_ver_h();
    initializeMemoryBlocks();
    printMemoryMap();

    cout << "Нажмите любую клавишу для выхода..." << endl;
    _getch(); // Ожидание нажатия клавиши
    return 0;
}
