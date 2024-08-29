#include <iostream>
#include <termios.h>
#include <unistd.h>

void setRawMode() {
    struct termios newt;
    tcgetattr(STDIN_FILENO, &newt);
    newt.c_lflag &= ~(ICANON | ECHO); // Выключаем канонический режим и эхо
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void resetMode(struct termios& oldt) {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

int main() {
    struct termios oldt;
    tcgetattr(STDIN_FILENO, &oldt); // Сохранение текущих настроек

    setRawMode(); // Установка сырого режима

    std::cout << "Нажимайте клавиши (ESC для выхода):" << std::endl;

    while (true) {
        char c;
        read(STDIN_FILENO, &c, 1); // Чтение одного символа
        if (c == 27) { // ESC для выхода
            break;
        }
        std::cout << "Нажата клавиша: " << c << std::endl;
    }

    resetMode(oldt); // Сброс настроек терминала
    return 0;
}
