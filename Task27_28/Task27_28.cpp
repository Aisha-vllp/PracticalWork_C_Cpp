#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Функция для получения версии Windows
void getWindowsVersion() {
    OSVERSIONINFO osvi;
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osvi);

    cout << "Версия Windows: " << osvi.dwMajorVersion << "." << osvi.dwMinorVersion << endl;
}

// Функция для получения информации о системе
void getSystemInfo() {
    SYSTEM_INFO si;
    GetSystemInfo(&si);

    cout << "Количество процессоров: " << si.dwNumberOfProcessors << endl;
    cout << "Размер страницы: " << si.dwPageSize << " байт" << endl;
    cout << "Тип процессора: " << si.dwProcessorType << endl;
}

// Функция для получения информации о памяти
void getMemoryInfo() {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    cout << "Объем физической памяти: " << memInfo.ullTotalPhys / (1024 * 1024) << " МБ" << endl;
    cout << "Объем доступной памяти: " << memInfo.ullAvailPhys / (1024 * 1024) << " МБ" << endl;
}

int main() {
    std::locale::global(std::locale(""));
    SetConsoleOutputCP(CP_UTF8); // Устанавливаем кодировку UTF-8

    cout << "---------------" << endl;
    cout << "             Информация о системе             " << endl;
    cout << "---------------" << endl;

    getWindowsVersion();
    getSystemInfo();
    getMemoryInfo();

    cout << "---------------" << endl;
    cout << "Нажмите любую клавишу для выхода..." << endl;
    cin.get();

    return 0;
}
