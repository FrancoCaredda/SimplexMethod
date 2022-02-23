#include "SimplexTable.h"
#include <iostream>
#include <algorithm>

int main(void)
{
	uint32_t variablesCount;
	uint32_t basesCount;
	
	std::cout << "Enter variables count: ";
	std::cin >> variablesCount;
	std::cout << "Enter bases count: ";
	std::cin >> basesCount;

	std::vector<double> coeficients(variablesCount);

	std::cout << "Enter function coeficients: ";
	
	for (int i = 0; i < variablesCount; i++)
		std::cin >> coeficients[i];
	
	std::vector<uint32_t> bases(basesCount);
	std::vector<double> members(basesCount);


	std::cout << "Enter bases (must be from 0): ";
	
	for (int i = 0; i < basesCount; i++)
		std::cin >> bases[i];

	std::cout << "Enter membsers: ";

	for (int i = 0; i < basesCount; i++)
		std::cin >> members[i];

	std::vector<std::vector<double>> system(basesCount);

	for (int i = 0; i < basesCount; i++)
		system[i].resize(variablesCount);

	std::cout << "Enter system: " << std::endl;

	for (int i = 0; i < basesCount; i++)
	{
		std::cout << "\tEnter row#" << i + 1 << ": ";

		for (int j = 0; j < variablesCount; j++)
			std::cin >> system[i][j];
	}

	SimplexTable table(bases, members, coeficients, system);
	table.ComputeDeltas();

	SimplexTable* result = Compute(table);

	if (result == nullptr)
	{
		std::cout << std::endl << "Task has no solutions";
		return -1;
	}

	std::vector<std::pair<uint32_t, double>> roots = result->GetRoots();
	double value = result->GetFunctionValue();

	std::sort(roots.begin(), roots.end(), [](const std::pair<uint32_t, double>& a, const std::pair<uint32_t, double>& b) {
		return a.first <= b.first;
	});

	std::cout << std::endl;
	for (auto& i : roots)
		std::cout << "x" << i.first << " = " << i.second << std::endl;

	std::cout << "Q(X) = " << value;

	delete result;

	return 0;
}