#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Функция для получения списка загруженных драйверов
void listLoadedDrivers() {
    DWORD bytesNeeded;
    DWORD driverCount;
    LPVOID driverInfo = NULL;

    // Получаем количество загруженных драйверов
    if (!EnumDeviceDrivers(NULL, 0, &bytesNeeded)) {
        cout << "Ошибка при получении количества драйверов." << endl;
        return;
    }

    driverCount = bytesNeeded / sizeof(LPVOID);
    driverInfo = new BYTE[bytesNeeded];

    // Получаем информацию о загруженных драйверах
    if (!EnumDeviceDrivers(driverInfo, bytesNeeded, &bytesNeeded)) {
        cout << "Ошибка при получении информации о драйверах." << endl;
        delete[] driverInfo;
        return;
    }

    // Выводим информацию о каждом драйвере
    for (size_t i = 0; i < driverCount; i++) {
        TCHAR driverName[MAX_PATH];
        if (GetDeviceDriverBaseName((LPVOID)((LPBYTE)driverInfo + i * sizeof(LPVOID)), driverName, sizeof(driverName) / sizeof(TCHAR))) {
            cout << "Драйвер " << i + 1 << ": " << driverName << endl;
        }
    }

    delete[] driverInfo;
}

int main() {
    std::locale::global(std::locale(""));
    SetConsoleOutputCP(CP_UTF8); // Устанавливаем кодировку UTF-8

    cout << "---------------" << endl;
    cout << "             Список загруженных драйверов             " << endl;
    cout << "---------------" << endl;

    listLoadedDrivers();

    cout << "---------------" << endl;
    cout << "Нажмите любую клавишу для выхода..." << endl;
    cin.get();

    return 0;
}
