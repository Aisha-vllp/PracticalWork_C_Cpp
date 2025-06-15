#include <windows.h>
#include <iostream>

using namespace std;

// Флаг блокировки клавиши '3'
bool isBlocked = false;

// Хук процедуры для обработки клавиатуры
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKeyBoard = (KBDLLHOOKSTRUCT*)lParam;

        // Обрабатываем только события нажатия клавиши
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {

            // Проверяем нажатие комбинации LeftCtrl + RightShift + F3
            // Используем GetAsyncKeyState для определения состояния клавиш-модификаторов
            if ((GetAsyncKeyState(VK_LCONTROL) & 0x8000) &&      // Left Ctrl
                (GetAsyncKeyState(VK_RSHIFT) & 0x8000) &&       // Right Shift
                (pKeyBoard->vkCode == VK_F3))                   // F3
            {
                // Переключаем состояние блокировки клавиши '3'
                isBlocked = !isBlocked;

                // Звуковой сигнал
                Beep(750, 300);

                // Вывод состояния блокировки в консоль
                cout << (isBlocked ? "Клавиша '3' заблокирована" : "Клавиша '3' разблокирована") << endl;

                // Возвращаем значение, разрешая системе обрабатывать эту клавишу
                return CallNextHookEx(NULL, nCode, wParam, lParam);
            }

            // Если клавиша '3' нажата и блокировка активна - блокируем её ввод
            if (pKeyBoard->vkCode == '3' && isBlocked) {
                // Блокируем клавишу '3', не пропуская её дальше
                return 1; // Блокируем ввод клавиши '3'
            }
        }
    }

    // Для всех остальных клавиш вызываем следующий хук (системная обработка без изменений)
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    std::locale::global(std::locale(""));
    SetConsoleOutputCP(CP_UTF8); // Устанавливаем кодировку UTF-8

    // Устанавливаем глобальный низкоуровневый хук на клавиатуру
    HHOOK hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);

    if (!hHook) {
        cerr << "Ошибка установки перехватчика клавиатуры!" << endl;
        return 1;
    }
    cout << "Перехват клавиатуры запущен. Используйте комбинацию Левый Ctrl + Правый Shift + F3 для переключения блокировки клавиши '3'." << endl;

    // Цикл обработки сообщений, необходимый для работы хука
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Убираем хук при завершении
    UnhookWindowsHookEx(hHook);
    return 0;
}


