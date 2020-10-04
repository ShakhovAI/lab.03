#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
using namespace std;


struct Input {
    vector<double> numbers;
    size_t bin_count;
};


vector<double> input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for (double& number: result)
    {
        in >> number;
    }
    return result;
}

Input
read_input(istream& in) {
    Input data;

    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    cerr << "Enter bin count: ";
    size_t bin_count;
    in >> bin_count;
    data.bin_count = bin_count;

    return data;
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
    Input input_data = read_input(cin);
    vector<double> numbers = input_data.numbers;
    size_t bin_count = input_data.bin_count;

    double numbers_min, numbers_max;
    find_minmax(numbers, numbers_min, numbers_max);

    auto bins = make_histogram(bin_count, numbers, numbers_min, numbers_max);

    show_histogram_svg(bins);

return 0;
}
