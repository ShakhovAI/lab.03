#include "histogram.h"
#include <iostream>
#include <cassert>

void find_minmax(vector<double> numbers, double& min, double& max)
{
    if (numbers.empty()) {
        std::cerr << "vector is empty\n";
        assert(false);
        return;
    }
    else {
        min = numbers[0];
        max = numbers[0];
    }
    for (double number : numbers)
    {
        if (number < min)
        {
            min = number;
        }
        if (number > max)
        {
            max = number;
        }
    }
}
