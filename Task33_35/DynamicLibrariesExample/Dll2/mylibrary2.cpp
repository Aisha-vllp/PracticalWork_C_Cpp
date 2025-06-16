// MyLibrary2.cpp
#include <stdafx.h>
#include <iostream>
#include <fstream>
#include <windows.h>

extern "C" {

    // Реализация функции копирования содержимого файла
    __declspec(dllexport) void CopyFileContent(const char* sourceFile, const char* destFile) {
        std::ifstream src(sourceFile, std::ios::binary);
        std::ofstream dst(destFile, std::ios::binary | std::ios::app); // Здесь для различия — добавляем в файл
        dst << src.rdbuf();
    }

    // Реализация функции добавления содержимого файла (просто для примера)
    __declspec(dllexport) void AppendToFile(const char* sourceFile, const char* destFile) {
        std::ifstream src(sourceFile, std::ios::binary);
        std::ofstream dst(destFile, std::ios::binary | std::ios::app);
        dst << src.rdbuf();
    }

}

#include "pch.h" //useless & meaningless. just for compiling
