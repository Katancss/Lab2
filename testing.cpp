#include <iostream>
#include <random>
#include <time.h>
#include <chrono>
#include <vector>
#include <cmath>

using namespace std;
using namespace std::chrono;
std::default_random_engine randomEngine(time(NULL));

unsigned long long N_MAX = 100000;

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

int rnd(int a, int b)
{
    std::uniform_int_distribution<int> randomNum(a, b);
    return randomNum(randomEngine);
}

vector<long> generate_nums(unsigned long long N) {
    vector<long> vec;
    for (unsigned long long i = 0; i < N; ++i) {
        vec.push_back(rnd(-1000, 1000));
    }
    return vec;
}

void selection_sort(vector<long> &A) {
    for (unsigned long long i = 0; i < A.size() - 1; ++i) {
        unsigned long long min_i = i;
        for (unsigned long long j = i + 1; j < A.size(); ++j) {
            if (A[j] < A[min_i])
                min_i = j;
        }
        if (min_i != i) {
            long tmp = A[i];
            A[i] = A[min_i];
            A[min_i] = tmp;
        }
    }
}

void hoar_sort(vector<long> &A, long first, long last)
{
    int i = first, j = last;
    long tmp, x = A[(first + last) / 2];
    do {
        while (A[i] < x)
            i++;
        while (A[j] > x)
            j--;

        if (i <= j)
        {
            if (i < j)
            {
                tmp = A[i];
                A[i] = A[j];
                A[j] = tmp;
            }
            i++;
            j--;
        }
    } while (i <= j);

    if (i < last)
        hoar_sort(A, i, last);
    if (first < j)
        hoar_sort(A, first, j);
}

void heapify(vector<long> &A, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && A[left] > A[largest])
        largest = left;
    if (right < n && A[right] > A[largest])
        largest = right;

    if (largest != i) {
        int tmp = A[i];
        A[i] = A[largest];
        A[largest] = tmp;

        heapify(A, n, largest);
    }
}

void heap_sort(vector<long> &A, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(A, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        int tmp = A[0];
        A[0] = A[i];
        A[i] = tmp;

        heapify(A, i, 0);
    }
}


void test1() {
    for (unsigned long long i = 10; i < N_MAX; i += 100) {
        unsigned long long timer = 0;
        for (int j = 0; j < 1000; ++j) {
            vector<long> v = generate_nums(i);

            Timer t;
            t.start();

            selection_sort(v);

            t.stop();
            timer += t.elapsed();
            v.clear();
        }
        cout << "{" << i * i << ", " << timer / 1000 << "},";
    }
}

void test2() {
    for (unsigned long long i = 10; i < N_MAX; i += 1000) {
        unsigned long long timer = 0;
        for (int j = 0; j < 1000; ++j) {
            vector<long> v = generate_nums(i);

            Timer t;
            t.start();

            hoar_sort(v, 0, i - 1);

            t.stop();
            timer += t.elapsed();
            v.clear();
        }
        cout << "{" << i * log(i) << ", " << timer / 1000 << "},";
    }
}

void test3() {
    for (unsigned long long i = 10; i < N_MAX; i += 1000) {
        unsigned long long timer = 0;
        for (int j = 0; j < 1000; ++j) {
            vector<long> v = generate_nums(i);

            Timer t;
            t.start();

            heap_sort(v, v.size());

            t.stop();
            timer += t.elapsed();
            v.clear();
        }
        cout << "{" << i * log(i) << ", " << timer / 1000 << "},";
    }
}



int main() {
    test3();
    
    return 0;
}

