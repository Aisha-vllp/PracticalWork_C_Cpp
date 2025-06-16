// main.cpp
#include <iostream>
#include <windows.h>

typedef void (*CopyFileContentFunc)(const char*, const char*);
typedef void (*AppendToFileFunc)(const char*, const char*);

int main() {
    std::locale::global(std::locale(""));
    SetConsoleOutputCP(CP_UTF8); // Устанавливаем кодировку UTF-8

    HMODULE hLib1 = LoadLibrary("D:/Osim/C_n_C++projs/Viola/PracticalWork_C_Cpp/Task33_35/DynamicLibrariesExample/Dll1/x64/Debug/Dll1.dll");
    HMODULE hLib2 = LoadLibrary("D:/Osim/C_n_C++projs/Viola/PracticalWork_C_Cpp/Task33_35/DynamicLibrariesExample/Dll2/x64/Debug/Dll2.dll");

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
