#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "histogram.h"
#include "svg.h"
#include <windows.h>
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

size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx) {

    size_t data_size = item_size * item_count;
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    string* stringItems = reinterpret_cast<string*>(items);
    buffer->write(stringItems->c_str(), data_size);

    return 0;
}

Input
download(const string& address) {
    stringstream buffer;
    CURL *curl = curl_easy_init();
    if (curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        if (!res) {
            exit(1);
            cout <<  curl_easy_strerror(res) << endl;
        }
        curl_easy_cleanup(curl);
    }
    return read_input(buffer, false);
}

int main(int argc, char* argv[])
{
    curl_global_init(CURL_GLOBAL_ALL);
    Input input;
    if (argc > 1) {
        input = download(argv[1]);
    }
    else {
        input = read_input(cin, true);
    }
    const auto bins = make_histogram(input);
    show_histogram_svg(bins);

}
