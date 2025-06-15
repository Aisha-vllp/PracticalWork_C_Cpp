#include <windows.h>
#include <iostream>

using namespace std;

bool isBlocked = false; // Флаг блокировки клавиши "3"

// Функция для обработки нажатий клавиш
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKeyBoard = (KBDLLHOOKSTRUCT*)lParam;

        // Проверяем нажатие клавиши "3"
        if (pKeyBoard->vkCode == '3' && isBlocked) {
            // Блокируем ввод клавиши "3"
            return 1; // Возвращаем 1, чтобы игнорировать нажатие
        }

        // Проверяем нажатие комбинации клавиш LeftCtrl + RightShift + F3
        if ((GetAsyncKeyState(VK_LCONTROL) & 0x8000) &&
            (GetAsyncKeyState(VK_RSHIFT) & 0x8000) &&
            (pKeyBoard->vkCode == VK_F3)) {
            // Переключаем состояние блокировки
            isBlocked = !isBlocked;
            if (isBlocked) {
                cout << "Клавиша \"3\" заблокирована" << endl;
            }
            else {
                cout << "Клавиша \"3\" разблокирована" << endl;
            }
            // Звуковой сигнал
            Beep(750, 300);
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    std::locale::global(std::locale(""));
    SetConsoleOutputCP(CP_UTF8); // Устанавливаем кодировку UTF-8

    // Устанавливаем перехватчик клавиатуры
    HHOOK hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (!hhkLowLevelKybd) {
        cerr << "Не удалось установить перехватчик клавиатуры!" << endl;
        return 1;
    }

    // Цикл обработки сообщений
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Удаляем перехватчик клавиатуры
    UnhookWindowsHookEx(hhkLowLevelKybd);
    return 0;
}