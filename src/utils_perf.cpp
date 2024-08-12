// utils_perf.cpp

#include "utils_perf.hpp"
#include <algorithm>

TimerTicTok::TimerTicTok(double window_seconds)
    : prev(std::chrono::high_resolution_clock::now()), dt(0.0), window_seconds(window_seconds) {}

void TimerTicTok::update() {
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapse = now - prev;
    prev = now;
    dt = elapse.count();

    // Add the current time to the list of timestamps
    timestamps.push_back(now);

    // Remove timestamps that are outside the window
    timestamps.erase(std::remove_if(timestamps.begin(), timestamps.end(),
                        [now, this](const auto& t) {
                            return std::chrono::duration<double>(now - t).count() > window_seconds;
                        }),
                     timestamps.end());
}

void TimerTicTok::pprint() {
    // Calculate average frequency based on the number of timestamps in the window
    int num_updates = timestamps.size();
    double average_freq = 0.0;
    if (num_updates > 1) {
        std::chrono::duration<double> total_time = timestamps.back() - timestamps.front();
        if (total_time.count() > 0) {
            average_freq = (num_updates - 1) / total_time.count();
        }
    }
    
    std::cout << "dt = " << dt << " sec, freq = " << 1.0 / dt << " Hz, avg freq = " << average_freq << " Hz" << std::endl;
}
