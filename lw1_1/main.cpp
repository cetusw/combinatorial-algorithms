#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <limits>
#include <chrono>

constexpr int SECONDS_PER_YEAR = 60 * 60 * 24 * 365;

constexpr long double EARTH_AGE_YEARS = 4540000000;
constexpr long double UNIVERSE_AGE_YEARS = 13800000000;

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
            matrixRow.push_back(std::stoi(value));
        }
        matrix.push_back(matrixRow);
    }
}

int findMinimumProductOfDistanceAndCargo(std::vector<int> permutations, const std::vector<std::vector<int>> &distance, const std::vector<std::vector<int>> &cargo)
{
    int minSumOfDistanceAndFlow = std::numeric_limits<int>::max();

    do
    {
        int currentDistanceAndFlow = 0;
        for (int i = 0; i < permutations.size(); i++)
        {
            for (int j = 0; j < permutations.size(); j++)
            {
                currentDistanceAndFlow += distance[i][j] * cargo[permutations[i]][permutations[j]];
            }
        }
        if (currentDistanceAndFlow < minSumOfDistanceAndFlow)
        {
            minSumOfDistanceAndFlow = currentDistanceAndFlow;
        }
    } while (std::ranges::next_permutation(permutations).found);

    return minSumOfDistanceAndFlow;
}

int countMatrixColumns(std::ifstream &matrix)
{
    matrix.clear();
    matrix.seekg(0, std::ios::beg);
    int numberOfColumns = 0;

    std::string matrixLine;
    std::getline(matrix, matrixLine);
    for (const char ch : matrixLine)
    {
        if (ch == ',')
        {
            numberOfColumns++;
        }
    }

    return numberOfColumns + 1;
}

std::vector<int> generateElements(const int numberOfElements)
{
    std::vector<int> elements;
    for (int i = 0; i < numberOfElements; i++)
    {
        elements.push_back(i);
    }

    return elements;
}

std::chrono::duration<long double> calculateLeadTime(const std::chrono::duration<long double> &startTime, const int currentNumberOfElements, const int maxNumberOfElements)
{
    std::chrono::duration<long double> leadTime = startTime;
    for (int i = currentNumberOfElements + 1; i <= maxNumberOfElements; i++)
    {
        leadTime *= i;
    }
    return leadTime;
}

long double durationToYears(const std::chrono::duration<long double> &duration)
{
    const long double totalSeconds = duration.count();

    const long double years = totalSeconds / SECONDS_PER_YEAR;

    return years;
}

void calculateDuration(const std::chrono::duration<long double> &functionDuration, const int numberOfFactories, const int newNumberOfFactories)
{
    std::chrono::duration<long double> calculatedDuration{};
    calculatedDuration = calculateLeadTime(functionDuration, numberOfFactories, newNumberOfFactories);
    std::cout << "Время для " << newNumberOfFactories << " производств: " << durationToYears(calculatedDuration) << " лет" << std::endl;
    std::cout << durationToYears(calculatedDuration) / EARTH_AGE_YEARS << " возраста Земли" << std::endl;
    std::cout << durationToYears(calculatedDuration) / UNIVERSE_AGE_YEARS << " возраста Вселенной" << std::endl;
    std::cout << std::endl;
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

    int numberOfFactories = countMatrixColumns(distanceInput);
    std::vector<int> factories = generateElements(numberOfFactories);

    auto start = std::chrono::high_resolution_clock::now();
    int min = findMinimumProductOfDistanceAndCargo(factories, distance, cargo);
    auto end = std::chrono::high_resolution_clock::now();
    auto functionDuration = end - start;

    std::cout << min << std::endl;
    std::cout << std::chrono::duration<long double>(functionDuration) << std::endl;
    std::cout << std::endl;

    calculateDuration(functionDuration, numberOfFactories, 15);
    calculateDuration(functionDuration, numberOfFactories, 20);
    calculateDuration(functionDuration, numberOfFactories, 50);
    calculateDuration(functionDuration, numberOfFactories, 100);
}
