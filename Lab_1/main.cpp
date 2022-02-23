#include "SimplexTable.h"
#include <iostream>

int main(void)
{
	SimplexTable table({ 2, 3, 4, 5, 6 }, { 90, 240, 0, 50, 80 }, { 2, 7, 0, 0, 0, 0, 0 },
	{
		{3, 2, 1, 0, 0, 0, 0},
		{4, 1, 0, 1, 0, 0, 0},
		{-3, 1, 0, 0, 1, 0, 0},
		{1, 0, 0, 0, 0, 1, 0},
		{0, 1, 0, 0, 0, 0, 1}
	});

	table.ComputeDeltas();
	SimplexTable* resultTable = Compute(table);

	if (resultTable == nullptr)
		return -1;

	float result = resultTable->GetFunctionValue();
	std::cout << "Q = " << result;

	return 0;
}