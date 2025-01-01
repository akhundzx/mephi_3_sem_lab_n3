//
// Created by akhundzx on 26.12.2024.
//

#ifndef TEST_HISTOGRAM_H
#define TEST_HISTOGRAM_H

#include "histogram.h"
#include <iostream>

void test_histogram() {
    std::cout << "Testing Histogram...\n";

    {
        std::cout << "  Adding elements to the histogram...\n";
        Histogram<std::string> histogram;

        histogram.Add("apple");
        histogram.Add("banana");
        histogram.Add("apple");
        histogram.Add("orange");
        histogram.Add("banana");
        histogram.Add("apple");

        std::cout << "    Current histogram contents:\n";
        histogram.Print();
        std::cout << "\n";

        std::cout << "    Verifying counts:\n";
        std::cout << "      Count of 'apple': " << histogram.GetCount("apple") << " (expected: 3)\n";
        std::cout << "      Count of 'banana': " << histogram.GetCount("banana") << " (expected: 2)\n";
        std::cout << "      Count of 'orange': " << histogram.GetCount("orange") << " (expected: 1)\n";
        std::cout << "      Count of 'grape': " << histogram.GetCount("grape") << " (expected: 0)\n";
    }

    {
        std::cout << "  Removing elements from the histogram...\n";
        Histogram<std::string> histogram;

        histogram.Add("apple");
        histogram.Add("banana");
        histogram.Add("apple");
        histogram.Add("orange");

        std::cout << "    Before removal:\n";
        histogram.Print();
        std::cout << "\n";

        histogram.Remove("apple");
        std::cout << "    After removing 'apple' once:\n";
        histogram.Print();
        std::cout << "\n";

        histogram.Remove("apple");
        std::cout << "    After removing 'apple' again:\n";
        histogram.Print();
        std::cout << "\n";

        try {
            histogram.Remove("apple");
            std::cout << "    Unexpected success: removed 'apple' from an empty count!\n";
        } catch (const std::runtime_error& e) {
            std::cout << "    Exception caught as expected: " << e.what() << "\n";
        }
    }

    {
        std::cout << "  Testing total count...\n";
        Histogram<int> histogram;

        histogram.Add(1);
        histogram.Add(2);
        histogram.Add(3);
        histogram.Add(1);

        std::cout << "    Histogram contents:\n";
        histogram.Print();
        std::cout << "\n";

        std::cout << "    Total count: " << histogram.TotalCount() << " (expected: 3)\n";

        histogram.Remove(1);
        std::cout << "    Total count after removing '1': " << histogram.TotalCount() << " (expected: 3)\n";
    }

    std::cout << "Histogram tests completed.\n";
}

#endif //TEST_HISTOGRAM_H
