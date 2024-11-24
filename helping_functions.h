

#ifndef A2_HELPING_FUNCTIONS_H
#define A2_HELPING_FUNCTIONS_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "algorithm"

inline void writeCSV(const std::vector<std::vector<double>>& data, const std::string& filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error while opening file: " << filename << std::endl;
        return;
    }

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            std::ostringstream oss;
            oss << row[i]; // Записываем число в строковый поток
            std::string value = oss.str(); // Получаем строку

            // Заменяем . на ,
            std::replace(value.begin(), value.end(), '.', ',');

            file << value; // Записываем строку в файл

            if (i < row.size() - 1) {
                file << ";";
            }
        }
        file << "\n";
    }

    file.close();
    std::cout << "CSV file saved: " << filename << std::endl;
}

template <typename T>
void printVector(const std::vector<T>& vec) {
    std::cout << "[ ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << "]" << std::endl;
}

#endif //A2_HELPING_FUNCTIONS_H
