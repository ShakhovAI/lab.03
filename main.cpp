#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
#include <curl/curl.h>
using namespace std;


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
read_input(istream& in, bool prompt) {
    Input data;

    if (prompt) cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    if (prompt) cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    if (prompt) cerr << "Enter bin count: ";
    size_t bin_count;
    in >> bin_count;
    data.bin_count = bin_count;

    return data;
}

vector<size_t> make_histogram(const Input& input)
{
    auto bin_count = input.bin_count;
    auto numbers = input.numbers;
    vector<size_t> bins(bin_count);
    double numbers_min, numbers_max;
    find_minmax(numbers, numbers_min, numbers_max);
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
    curl_global_init(CURL_GLOBAL_ALL);
    const auto input_data = read_input(cin, true);
    const auto bins = make_histogram(input_data);
    show_histogram_svg(bins); ///
}
