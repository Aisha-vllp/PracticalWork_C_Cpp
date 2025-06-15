#include <dos.h>
#include <conio.h>
#include <stdio.h>

#define byte unsigned char
#define word unsigned int

struct DR_HEAD {
    struct DR_HEAD* next;     /* адрес следующего */
    word attr;                /* атрибуты */
    word strat_off, intr_off; /* смещения секций */
    char name[8];             /* имя */
};

void clrbuf(void) {
    while (kbhit()) getch();
}

byte GetSym(int x1, int y1) {
    return peekb(0xb800, y1 * 160 + x1 * 2);
}

byte GetAtr(int x1, int y1) {
    return peekb(0xb800, y1 * 160 + x1 * 2 + 1);
}

void PutSym(int x1, int y1, byte sym) {
    pokeb(0xb800, y1 * 160 + x1 * 2, sym);
}

void PutAtr(int x1, int y1, byte atr) {
    pokeb(0xb800, y1 * 160 + x1 * 2 + 1, atr);
}

void FlDrv(struct DR_HEAD* drv) {
    // Функция для отображения атрибутов драйвера
    // Здесь можно добавить логику для отображения атрибутов
}

int main() {
    std::locale::global(std::locale(""));
    SetConsoleOutputCP(CP_UTF8); // Устанавливаем кодировку UTF-8

    struct DR_HEAD* drv;
    union REGS rr;
    struct SREGS sr;

    // Получение адреса CVT
    rr.h.ah = 0x52;
    intdosx(&rr, &rr, &sr);

    // Получение адреса первого драйвера
    drv = (struct DR_HEAD*)MK_FP(sr.es, rr.x.bx + 34);

    clrscr();
    cprintf("---------------\n");
    cprintf("             Список драйверов             \n");
    cprintf("---------------\n");

    while (drv->next != (struct DR_HEAD*)0xFFFF) {
        cprintf("Драйвер: %s, Атрибуты: %04X\n", drv->name, drv->attr);
        drv = drv->next; // Переход к следующему драйверу
    }

    cprintf("Конец списка. Нажмите любую клавишу...\n");
    getch();
    return 0;
}
