//
// Created by yalavrinenko on 27.09.2021.
//

#ifndef SORTS_EXTENSION_HPP
#define SORTS_EXTENSION_HPP

#include <random>
#include <chrono>

class Timer {
public:
    void start() {
        start_ = current_time();
    }
    void stop() {
        stop_ = current_time();
    }
    unsigned long long elapsed() const {
        return std::chrono::duration_cast<std::chrono::microseconds>(stop_ - start_).count();
    }

private:
    static std::chrono::high_resolution_clock::time_point current_time() {
        return std::chrono::high_resolution_clock::now();
    }

    std::chrono::high_resolution_clock::time_point start_, stop_;
};

class Utils {
public:
    void generate_data(long* main, long* test, unsigned long long N);

    static bool check_order(long const* array, unsigned long long N);

private:
    std::mt19937_64 engine_{ std::random_device{}() };
    std::uniform_int_distribution<long> uni_{ -1000, 1000 };
};

void Utils::generate_data(long* main, long* test, unsigned long long int N) {
    Timer t;
    t.start();

    for (auto i = 0ul; i < N; ++i)
        main[i] = test[i] = uni_(engine_);

    t.stop();
    std::cout << "Generated " << N << " elements. Elapsed time: " << t.elapsed() << " microseconds." << std::endl;
}

bool Utils::check_order(long const* array, unsigned long long int N) {
    for (auto i = 1; i < N; ++i)
        if (array[i - 1] > array[i]) {
            std::cout << "*****" << array[i - 1] << " is grater than " << array[i] << std::endl;
            return false;
        }

    return true;
}

#endif //SORTS_EXTENSION_HPP
