#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>

    using namespace std;

    // Управление цветом текста в консоли
    void SetConsoleColor(WORD color) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }

    // Установка позиции курсора
    void gotoxy(int x, int y) {
        COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    // Очистка экрана и установка курсора в левый верхний угол
    void clrscr() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD count;
        DWORD cellCount;
        COORD homeCoords = { 0, 0 };

        if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
        cellCount = csbi.dwSize.X * csbi.dwSize.Y;
        FillConsoleOutputCharacter(hConsole, ' ', cellCount, homeCoords, &count);
        FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count);
        SetConsoleCursorPosition(hConsole, homeCoords);
    }

    // Структура заголовка драйвера (для эмуляции)
    struct DR_HEAD {
        string name;   // Имя драйвера
        WORD attr;     // Атрибуты драйвера
    };

    // Константы цветов
    const WORD COLOR_HEADER = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    const WORD COLOR_TITLE = FOREGROUND_RED | FOREGROUND_INTENSITY;
    const WORD COLOR_NORMAL = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    const WORD COLOR_HIGHLIGHT = BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

    // Функция для вывода атрибутов драйвера
    void PrintDriverAttributes(const DR_HEAD& drv) {
        clrscr();
        SetConsoleColor(COLOR_TITLE);
        cout << "--------------------------------------------------" << endl;
        cout << "----------- Атрибуты драйвера " << drv.name << " ------------" << endl;
        cout << "--------------------------------------------------" << endl;
        SetConsoleColor(COLOR_NORMAL);

        WORD attr = drv.attr;
        // Старший бит (0x8000) - 1: символьное устройство, 0: блочное устройство
        bool charDevice = (attr & 0x8000) != 0;

        if (!charDevice) { // Блочное устройство
            if (attr & 0x40) cout << "---- Поддерживает функции DOS 3.2" << endl;
            if (attr & 0x2000) cout << "---- Читает media FAT" << endl;
            if (attr & 0x4) cout << "---- Номер устройств: " << (attr & 0xFF) << endl;
            else cout << "---- Блочное устройство" << endl;
        }
        else { // Символьное устройство
            if (attr & 0x1) cout << "---- Поддерживает функции IOCTL" << endl;
            if (attr & 0x2) cout << "---- Поддерживает функции Open/Close" << endl;
            if (attr & 0x4) cout << "---- Поддерживает функции DOS 3.2" << endl;
            if (attr & 0x8) cout << "---- CLOCK$ (часы)" << endl;
            if (attr & 0x10) cout << "---- Драйвер часов" << endl;
            if (attr & 0x20) cout << "---- Нулевое устройство" << endl;
            if (attr & 0x40) cout << "---- Консоль вывода" << endl;
            if (attr & 0x80) cout << "---- Консоль ввода" << endl;
        }

        cout << endl << "Нажмите любую клавишу для возврата к списку драйверов..." << endl;
        _getch();
    }

    // Главный цикл программы
    void MainLoop(vector<DR_HEAD>& drivers) {
        int index = 0;
        bool running = true;
        clrscr();

        while (running) {
            clrscr();
            SetConsoleColor(COLOR_HEADER);
            cout << "--------------------------------------------------" << endl;
            cout << "         Просмотр списка драйверов устройств      " << endl;
            cout << "--------------------------------------------------" << endl;
            SetConsoleColor(COLOR_NORMAL);

            for (size_t i = 0; i < drivers.size(); i++) {
                if ((int)i == index) {
                    SetConsoleColor(COLOR_HIGHLIGHT);
                    cout << "> ";
                }
                else {
                    cout << "  ";
                }
                cout << i + 1 << ". " << drivers[i].name << "    Атрибуты: " << hex << drivers[i].attr << dec << endl;
                if ((int)i == index) {
                    SetConsoleColor(COLOR_NORMAL);
                }
            }

            cout << "\nИспользуйте стрелки для выбора, Enter для просмотра атрибутов, Esc для выхода." << endl;

            int ch = _getch();
            if (ch == 0 || ch == 224) { // код расширенной клавиши
                int ch2 = _getch();
                switch (ch2) {
                case 72: // Стрелка вверх
                    index--;
                    if (index < 0) index = (int)drivers.size() - 1;
                    break;
                case 80: // Стрелка вниз
                    index++;
                    if (index >= (int)drivers.size()) index = 0;
                    break;
                }
            }
            else {
                switch (ch) {
                case 13: // Enter
                    PrintDriverAttributes(drivers[index]);
                    break;
                case 27: // Esc
                    running = false;
                    break;
                case 32: // Space - можно реализовать другую функцию, например, следующая страница
                    index++;
                    if (index >= (int)drivers.size()) index = 0;
                    break;
                }
            }
        }
    }

    int main() {
        std::locale::global(std::locale(""));
        SetConsoleOutputCP(CP_UTF8); // Устанавливаем кодировку UTF-8

        // Эмуляция списка драйверов с именем и атрибутами
        vector<DR_HEAD> drivers = {
            { "NUL",   0x8004 },
            { "SETVER", 0x8000 },
            { "XMS",   0xA000 },
            { "CON",   0x8013 },
            { "AUX",   0x8000 },
            { "PRN",   0xA0C0 },
            { "CLOCK$",0x8008 },
            { "DRV4",  0x08C2 },
            { "COM1",  0x8000 },
            { "LPT1",  0xA0C0 },
            { "LPT2",  0xA0C0 },
            { "LPT3",  0xA0C0 },
            { "COM2",  0x8000 },
            { "COM3",  0x8000 },
            { "COM4",  0x8000 }
        };

        MainLoop(drivers);

        clrscr();
        SetConsoleColor(COLOR_NORMAL);
        cout << "Конец программы. Спасибо за использование!" << endl;

        return 0;
    }
