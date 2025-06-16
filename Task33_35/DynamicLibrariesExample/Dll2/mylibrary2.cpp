// MyLibrary2.cpp
#include <iostream>
#include <fstream>
#include <windows.h>

extern "C" {
    __declspec(dllexport) void CopyFileContent(const char* sourceFile, const char* destFile);
    __declspec(dllexport) void AppendToFile(const char* sourceFile, const char* destFile);
}
