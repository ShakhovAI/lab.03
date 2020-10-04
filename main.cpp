#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
#include <cstdio>

using namespace std;

vector<double> input_numbers(size_t count)
{
    vector<double> result(count);
    cerr << "Enter numbers: ";
    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }
    return result;
}

vector<size_t> make_histogram(int bin_count, const vector<double>& numbers, double numbers_min, double numbers_max)
{
    vector<size_t> bins(bin_count);
    for (double number : numbers)
    {
        size_t bin = (size_t)((number - numbers_min) / (numbers_max - numbers_min) * bin_count);
        if (bin == bin_count)
        {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}

int main()
{
    const char* name = "Artur";
    const char* operating_system = "Arch Linux";
    size_t age = 19;
    printf("My name is %s. I'm %d years old.\n I use %s btw...\n", name, age, operating_system);
    return 0;

    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;

    double numbers_min, numbers_max;
    find_minmax(numbers, numbers_min, numbers_max);

    auto bins = make_histogram(bin_count, numbers, numbers_min, numbers_max);

    show_histogram_svg(bins);

    return 0;
}
