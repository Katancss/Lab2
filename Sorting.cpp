/***
 * Требуется:
 * 1. Реализовать алгоритм медленной сортировки (один из: сортировка выбором, вставками, пузырьком)
 * 2. Реализовать алгоритм быстрой сортировки (сортировка Хоара или сортировка слиянием)
 * 3. Реализовать алгоритмы поиска элемента в отсортированном массиве (тривиальный алгоритм, бинарный поиск)
* Вопросы к заданию:
 * 1. Определить зависимость времени работы медленной сортировки (сортировки выбором) от числа элементов массива
 * 2. Определить зависимость времени работы быстрой сортировки (сортировка Хоара/сортировка слиянием)  от числа элементов массива
 * 3. Определить количество элементов массива при котором медленная сортировка работает быстрее быстрой.
 * 4. Определить зависимость времени работы тривиального поиска от количества элементов массива и количества запросов поиска
 * 5. Определить зависимость времени работы бинарного поиска от количества элементов массива и количества запросов поиска
 * 6. Обменяться кодами быстрой сортировки с одногрупниками, провести исследование времени работы альтернативного алгоритма.
 * 7. Определить диапазоны значений параметра N, для которых тот или иной алгоритм сортировки применим
 * 8. Определите максимальное значение параметра MAX_N (с точностью до десятков тысяч) при котором программа может работать
*/

#include <iostream>
#include "extension.hpp"

unsigned long long const MAX_N = 100000; //Максимальное количество элементов в массиве

//******************************Поиск элемента в массиве**********************************

int trivial_search(long A[], long key, int low, int high) {
    for (int i = low; i < high + 1; ++i) {
        if (A[i] == key)
            return i;
    }
}

int bin_search(long A[], long key, long low, long high)
{
    if (low > high)
    {
        return -1;
    }
    long mid = (low + high) / 2;
    if (A[mid] == key)
    {
        return mid;
    }
    if (A[mid] < key)
        return bin_search(A, key, mid + 1, high);
    if (A[mid] > key)
        return bin_search(A, key, low, mid - 1);
}

//***************************************************************************************

//***********************Сортировка выбором********************************************

void selection_sort(long A[], unsigned long long N) {
    for (unsigned long long i = 0; i < N - 1; ++i) {
        unsigned long long min_i = i;
        for (unsigned long long j = i + 1; j < N; ++j) {
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

//***************************************************************************************

//**********************************Пирамидальная сортировка*********************************

void heapify(long A[], int n, int i) {
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

void heapSort(long A[], int n)
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

//***************************************************************************************

//**********************************Сортировка Хоара*************************************

void hoar_sort(long int A[], long int first, long int last)
{

    int i = first, j = last;
    double tmp, x = A[(first + last) / 2];
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

//***************************************************************************************

void search_test_function(long A[MAX_N], unsigned long N, unsigned long requests_counts) {
        Utils util;
        long* requests = new long[requests_counts];
        util.generate_data(requests, requests, requests_counts);

        Timer t; t.start();
        unsigned long misses = 0;
        for (auto i = 0ul; i < requests_counts; ++i) {
            unsigned long index = 0;
            index = bin_search(A, requests[i], 0, N);
            //index = trivial_search(A, requests[i], 0, N);
            if (index >= N) {
                ++misses;
            }
            if (index < N && A[index] != requests[i]) {
                std::cout << "Fail to search " << requests[i] << ". A[index] == " << A[index] << std::endl;
                return;
            }
        }
        t.stop();

        delete[] requests;
}

int main() {
    Utils util;

    long slow_data[MAX_N], rapid_data[MAX_N];

    unsigned long const N = 1000; //Варьируемый параметр. Можно смело изменять для получения зависимости времени от N. N <= MAX_N

    //Генерация N произвольных числе из отрезка [-1000, 1000] в массивы slow_data и rapid_data. slow_data[i] == rapid_data[i]
    util.generate_data(slow_data, rapid_data, N);

    //*****************************Тестирование медленной сортировки******************************************************
    {
        Timer t;
        t.start();

        selection_sort(slow_data, N);

        t.stop();

        if (!util.check_order(slow_data, N)) {
            std::cout << "Sort order is wrong. Check the sort function." << std::endl;
        }
        else {
            std::cout << "Performed slow sort of " << N << " elements. Elapsed time: " << t.elapsed() << " microseconds.\n";
        }
        
            std::cout << "First min(" << N << ", 10) elements:\n";
        for (auto i = 0; i < std::min(N, 10ul); ++i)
            std::cout << slow_data[i] << " ";
        std::cout << std::endl;
    }
    //********************************************************************************************************************

    //*****************************Тестирование быстрой сортировки********************************************************
    {
        Timer t;
        t.start();

        hoar_sort(rapid_data, 0, N);

        t.stop();

        if (!util.check_order(rapid_data, N)) {
            std::cout << "Sort order is wrong. Check the sort function." << std::endl;
        }
        else {
            std::cout << "Performed rapid sort of " << N << " elements. Elapsed time: " << t.elapsed() << " microseconds.\n";
        }

        std::cout << "First min(" << N << ", 10) elements:\n";
        for (auto i = 0; i < std::min(N, 10ul); ++i)
            std::cout << rapid_data[i] << " ";
        std::cout << std::endl;
    }
    //********************************************************************************************************************

    //*****************************Тестирование поиска элемента в массиве*************************************************
    unsigned long request_count = 1000; //Количество запросов поиска. Можно варьировать в неограниченных (в разумной степени) пределах
    search_test_function(slow_data, N, request_count);
    //********************************************************************************************************************
    return 0;
}
