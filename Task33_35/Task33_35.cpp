// main.cpp
#include <iostream>
#include <windows.h>

typedef void (*CopyFileContentFunc)(const char*, const char*);
typedef void (*AppendToFileFunc)(const char*, const char*);

int main() {
    std::locale::global(std::locale(""));
    SetConsoleOutputCP(CP_UTF8); // Устанавливаем кодировку UTF-8

    HMODULE hLib1 = LoadLibrary("MyLibrary1.dll");
    HMODULE hLib2 = LoadLibrary("MyLibrary2.dll");

    if (hLib1 && hLib2) {
        CopyFileContentFunc CopyFileContent = (CopyFileContentFunc)GetProcAddress(hLib1, "CopyFileContent");
        AppendToFileFunc AppendToFile = (AppendToFileFunc)GetProcAddress(hLib2, "AppendToFile");

        if (CopyFileContent && AppendToFile) {
            CopyFileContent("source.txt", "destination.txt");
            AppendToFile("source.txt", "destination.txt");
            std::cout << "Файлы успешно обработаны." << std::endl;
        }

        FreeLibrary(hLib1);
        FreeLibrary(hLib2);
    } else {
        std::cerr << "Ошибка загрузки библиотек." << std::endl;
    }

    return 0;
}
