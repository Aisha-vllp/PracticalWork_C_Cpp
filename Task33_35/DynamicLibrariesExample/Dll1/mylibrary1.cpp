// MyLibrary1.cpp
#include <iostream>
#include <fstream>
#include <windows.h>
extern "C" {
    __declspec(dllexport) void CopyFileContent(const char* sourceFile, const char* destFile) {
        std::ifstream src(sourceFile, std::ios::binary);
        std::ofstream dst(destFile, std::ios::binary);
        dst << src.rdbuf();
    }
    __declspec(dllexport) void AppendToFile(const char* sourceFile, const char* destFile) {
        std::ifstream src(sourceFile, std::ios::binary);
        std::ofstream dst(destFile, std::ios::app);
        dst << src.rdbuf();
    }
}