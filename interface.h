//
// Created by akhundzx on 26.12.2024.
//

#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include "HashTable.h"
#include "Histogram.h"
#include "sparse_vector.h"
#include "sparcematrix.h"
#include "person.h"
#include <sstream>
#include <vector>
#include <fstream>

std::vector<Person> LoadPersonsFromFile(const std::string& filename) {
    std::vector<Person> persons;
    std::ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Couldn't open the file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Person person;
        if (iss >> person.name >> person.surname >> person.age >> person.height) {
            persons.push_back(person);
        }
    }

    file.close();
    return persons;
}

void BuildPersonHistogram(const std::vector<Person>& people) {
    std::cout << "choose data type:\n";
    std::cout << "1. age\n";
    std::cout << "2. height\n";
    int choice;
    std::cin >> choice;
    std::vector<std::pair<int, int>> ranges; // Диапазоны
    std::cout << "Enter the ranges in the start-end format, for ':\n";
    std::string rangeInput;
    while (true) {
        std::cin >> rangeInput;
        if (rangeInput == "end") break;
        std::replace(rangeInput.begin(), rangeInput.end(), '-', ' ');
        std::istringstream iss(rangeInput);
        int start, end;
        iss >> start >> end;
        ranges.emplace_back(start, end);
    }

    Histogram<std::string> histogram;
    for (const auto& person : people) {
        if (choice == 1) { // Возраст
            for (const auto& range : ranges) {
                if (person.age >= range.first && person.age <= range.second) {
                    histogram.Add(std::to_string(range.first) + "-" + std::to_string(range.second));
                    break;
                }
            }
        } else if (choice == 2) { // Рост
            for (const auto& range : ranges) {
                if (person.height >= range.first && person.height <= range.second) {
                    histogram.Add(std::to_string(range.first) + "-" + std::to_string(range.second));
                    break;
                }
            }
        }
    }

    std::cout << "Result of histogramm:\n";
    histogram.Print();
}

void HistogramMenu() {
    std::cout << "\n--- Histogram Menu ---\n";
    std::cout << "Choose data type:\n";
    std::cout << "1. Integer\n";
    std::cout << "2. Double\n";
    std::cout << "3. String\n";
    std::cout << "4. Person\n";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        Histogram<int> histogram;
        int value;
        while (true) {
            std::cout << "1. Add\n2. Remove\n3. Print\n4. Back\n";
            int action;
            std::cin >> action;
            switch (action) {
                case 1:
                    std::cout << "Enter value: ";
                    std::cin >> value;
                    histogram.Add(value);
                    break;
                case 2:
                    std::cout << "Enter value: ";
                    std::cin >> value;
                    histogram.Remove(value);
                    break;
                case 3:
                    histogram.Print();
                    break;
                case 4:
                    return;
            }
        }
    } else if (choice == 2) {
        Histogram<double> histogram;
        double value;
        while (true) {
            std::cout << "1. Add\n2. Remove\n3. Print\n4. Back\n";
            int action;
            std::cin >> action;
            switch (action) {
                case 1:
                    std::cout << "Enter value: ";
                    std::cin >> value;
                    histogram.Add(value);
                    break;
                case 2:
                    std::cout << "Enter value: ";
                    std::cin >> value;
                    histogram.Remove(value);
                    break;
                case 3:
                    histogram.Print();
                    break;
                case 4:
                    return;
            }
        }
    } else if (choice == 3) {
        Histogram<std::string> histogram;
        std::string value;
        while (true) {
            std::cout << "1. Add\n2. Remove\n3. Print\n4. Back\n";
            int action;
            std::cin >> action;
            switch (action) {
                case 1:
                    std::cout << "Enter value: ";
                    std::cin >> value;
                    histogram.Add(value);
                    break;
                case 2:
                    std::cout << "Enter value: ";
                    std::cin >> value;
                    histogram.Remove(value);
                    break;
                case 3:
                    histogram.Print();
                    break;
                case 4:
                    return;
            }
        }
    } else if (choice == 4) {
        std::string filename = "persons.txt";
        std::vector<Person> persons = LoadPersonsFromFile(filename);
        BuildPersonHistogram(persons);
    }
}

void SparseVectorMenu() {
    UnqPtr<HashTable<int, double>> dictionary(new HashTable<int, double>());
    SparseVector<double> vector(500, (std::move(dictionary)));
    while (true) {
        std::cout << "\n-- Sparse Vector Menu --\n";
        std::cout << "1. Set Element\n2. Get Element\n3. Print Vector\n4. Back to Main Menu\nChoose: ";
        int choice, index;
        double value;
        std::cin >> choice;
        switch (choice) {
            case 1:
                std::cout << "Enter index and value: ";
                std::cin >> index >> value;
                vector.SetElement(index, value);
                break;
            case 2:
                std::cout << "Enter index: ";
                std::cin >> index;
                std::cout << "Value: " << vector.GetElement(index) << std::endl;
                break;
            case 3:
                vector.ForEach([](int key, const double &value) {
                    std::cout << "Index " << key << ": " << value << std::endl;
                });
                break;
            case 4:
                return;
            default:
                std::cout << "Invalid choice!";
        }
    }
}

void SparseMatrixMenu() {
    UnqPtr<HashTable<IndexPair, double>> dictionary(new HashTable<IndexPair, double>());
    SparseMatrix<double> matrix(1000, 1000, std::move(dictionary));
    while (true) {
        std::cout << "\n-- Sparse Matrix Menu --\n";
        std::cout << "1. Set Element\n2. Get Element\n3. Print Matrix\n4. Back to Main Menu\nChoose: ";
        int choice, row, col;
        double value;
        std::cin >> choice;
        switch (choice) {
            case 1:
                std::cout << "Enter row, column, and value: ";
                std::cin >> row >> col >> value;
                matrix.SetElement(row, col, value);
                break;
            case 2:
                std::cout << "Enter row and column: ";
                std::cin >> row >> col;
                std::cout << "Value: " << matrix.GetElement(row, col) << std::endl;
                break;
            case 3:
                matrix.ForEach([](const IndexPair &key, const double &value) {
                    std::cout << "(" << key.row << ", " << key.column << "): " << value << std::endl;
                });
                break;
            case 4:
                return;
            default:
                std::cout << "Invalid choice!";
        }
    }
}

void MainMenu() {
    while (true) {
        std::cout << "\n-- Main Menu --\n";
        std::cout << "1. Histogram\n2. Sparse Vector\n3. Sparse Matrix\n4. Exit\nChoose: ";
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1:
                HistogramMenu();
            break;
            case 2:
                SparseVectorMenu();
            break;
            case 3:
                SparseMatrixMenu();
            break;
            case 4:
                std::cout << "Exiting...\n";
            return;
            default:
                std::cout << "Invalid choice!";
        }
    }
}


#endif //INTERFACE_H
