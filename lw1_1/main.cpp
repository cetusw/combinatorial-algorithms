#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

void readMatrix(std::ifstream &file, std::vector<std::vector<int>> &matrix)
{
    matrix.clear();
    std::string fileLine;

    while (std::getline(file, fileLine))
    {
        std::istringstream lineStream(fileLine);
        std::string value;
        std::vector<int> matrixRow;

        while (std::getline(lineStream, value, ','))
        {
            value.erase(0, value.find_first_not_of(' '));
            value.erase(value.find_first_not_of(' ') + 1);
            matrixRow.push_back(std::stoi(value));
        }
        matrix.push_back(matrixRow);
    }
}

int main() {
    std::vector<std::vector<int>> distance = {};
    std::vector<std::vector<int>> cargo = {};
    std::string distanceFileName = "distance.txt";
    std::string cargoFileName = "cargo.txt";

    std::ifstream distanceInput("../" + distanceFileName);
    std::ifstream cargoInput("../" + cargoFileName);

    readMatrix(distanceInput, distance);
    readMatrix(cargoInput, cargo);

    std::cout << distance.size() << std::endl;
    // прочитать матрицу расстояний и заполнить distance
    // прочитать матрицу объёмов и заполнить cargo
    // сгенерировали перестановки
    // сам алгоритм
}