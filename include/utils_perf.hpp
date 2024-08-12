// TimerTicTok.hpp

#ifndef TIMER_TIC_TOK_HPP
#define TIMER_TIC_TOK_HPP

#include <iostream>
#include <vector>
#include <chrono>

class TimerTicTok {
public:
    TimerTicTok(double window_seconds = 1.0);

    void update();
    void pprint();

private:
    std::chrono::high_resolution_clock::time_point prev;
    double dt;
    std::vector<std::chrono::high_resolution_clock::time_point> timestamps;
    double window_seconds;
};

#endif // TIMER_TIC_TOK_HPP
