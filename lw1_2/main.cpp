#include <chrono>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

void ReadSkills(
	const std::string& path, std::string& requiredSkills, std::vector<std::string>& employeeSkills)
{
	auto inputFile = std::ifstream(path);
	std::string line;

	if (!inputFile.is_open())
	{
		std::cout << "Ошибка при открытии файла" << std::endl;
	}

	std::getline(inputFile, line);
	requiredSkills = line;
	while (std::getline(inputFile, line))
	{
		employeeSkills.push_back(line);
	}
}

bool NextCombinations(const size_t dim, std::vector<size_t>& state)
{
	const int k = static_cast<int>(state.size());
	int i = k - 1;

	while (i >= 0 && state[i] == dim - k + i)
	{
		i--;
	}
	if (i < 0)
	{
		return false;
	}
	state[i]++;

	for (int j = i + 1; j < k; j++)
	{
		state[j] = state[j - 1] + 1;
	}
	return true;
}

std::set<char> GetUnionSkills(
	std::vector<std::string> employees, const std::vector<size_t>& combination)
{
	std::set<char> unionSkills;
	for (const size_t index : combination)
	{
		for (char ch : employees[index])
		{
			unionSkills.insert(ch);
		}
	}
	return unionSkills;
}

bool IsAllSkillsIncluded(const std::string& requiredSkills, const std::set<char>& actualSkills)
{
	for (char req : requiredSkills)
	{
		if (!actualSkills.contains(req))
		{
			return false;
		}
	}
	return true;
}

void PrintTeam(const std::vector<size_t>& team)
{
	if (team.empty())
	{
		std::cout << "Невозможно создать команду со всеми необходимыми навыками" << std::endl;
	}
	else
	{
		std::cout << "Наименьшая подгруппа:" << std::endl;
		for (const size_t index : team)
		{
			std::cout << team[index] << " ";
		}
		std::cout << std::endl;
	}
}

std::vector<size_t> FindBestTeam(const size_t numberOfEmployees,
	const std::vector<std::string>& employeeSkills, const std::string& requiredSkills)
{
	std::vector<size_t> bestTeam;
	for (size_t teamSize = 1; teamSize <= numberOfEmployees; teamSize++)
	{
		std::vector<size_t> combination(teamSize);
		for (size_t i = 0; i < teamSize; i++)
		{
			combination[i] = i;
		}

		do
		{
			std::set<char> unionSkills = GetUnionSkills(employeeSkills, combination);
			if (IsAllSkillsIncluded(requiredSkills, unionSkills))
			{
				bestTeam = combination;
				break;
			}
		} while (NextCombinations(numberOfEmployees, combination));

		if (!bestTeam.empty())
		{
			break;
		}
	}
	return bestTeam;
}

int main(const int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Неверное количество аргументов" << std::endl;
		return 1;
	}

	std::string requiredSkills;
	std::vector<std::string> employeeSkills;

	ReadSkills(argv[1], requiredSkills, employeeSkills);
	const auto start = std::chrono::high_resolution_clock::now();
	const std::vector<size_t> bestTeam
		= FindBestTeam(employeeSkills.size(), employeeSkills, requiredSkills);
	const auto end = std::chrono::high_resolution_clock::now();
	const auto functionDuration = end - start;
	PrintTeam(bestTeam);
	std::cout << std::chrono::duration<long double>(functionDuration) << std::endl;

	return 0;
}
