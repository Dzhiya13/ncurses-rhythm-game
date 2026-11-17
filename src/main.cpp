#include <iostream>
#include <chrono>
#include <thread>
#include <ncurses.h>


int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    bool running = true;
    auto last_time = std::chrono::high_resolution_clock::now();

    while (running) {
        auto current_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsed = current_time - last_time;
        if (elapsed.count() < 0.016f) {
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
            continue;
        }
        last_time = current_time;

        int ch = getch();
        if (ch == 'q' || ch == 'Q') {
            running = false;
        }

        clear();
        mvprintw(1, 2, "=== NCURSES RHYTHM GAME (CORE ENGINE) ===");
        mvprintw(3, 2, "Tekan 'Q' untuk keluar.");
        mvprintw(max_y / 2, (max_x - 30) / 2, "Menunggu modul Audio & Renderer...");
        refresh();
    }

    endwin();
    return 0;
}