#include <windows.h>
#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>

using namespace std;

const int WIDTH = 80;  // Ширина консоли
const int HEIGHT = 25; // Высота консоли
const char BALL = 'O'; // Символ мячика
const char EMPTY = ' '; // Пустое пространство

// Структура для хранения позиции мяча
struct Ball {
    int x, y;
    int dx, dy; // Направление движения
};

// Функция для установки курсора в заданную позицию
void gotoxy(int x, int y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Функция для отрисовки мяча
void drawBall(Ball& ball) {
    gotoxy(ball.x, ball.y);
    cout << BALL;
}

// Функция для очистки мяча
void clearBall(Ball& ball) {
    gotoxy(ball.x, ball.y);
    cout << EMPTY;
}

// Функция для обновления позиции мяча
void updateBall(Ball& ball) {
    clearBall(ball);
    ball.x += ball.dx;
    ball.y += ball.dy;

    // Проверка на столкновение с границами
    if (ball.x <= 0 || ball.x >= WIDTH - 1) {
        ball.dx = -ball.dx; // Изменяем направление по X
    }
    if (ball.y <= 0 || ball.y >= HEIGHT - 1) {
        ball.dy = -ball.dy; // Изменяем направление по Y
    }

    drawBall(ball);
}

int main() {
    // Инициализация мяча
    Ball ball;
    ball.x = WIDTH / 2;
    ball.y = HEIGHT / 2;
    ball.dx = 1; // Направление по X
    ball.dy = 1; // Направление по Y

    // Основной цикл
    while (true) {
        updateBall(ball);
        this_thread::sleep_for(chrono::milliseconds(100)); // Задержка для управления скоростью
        if (_kbhit() && _getch() == 27) { // Выход по нажатию Esc
            break;
        }
    }

    // Очистка экрана перед выходом
    system("cls");
    return 0;
}
