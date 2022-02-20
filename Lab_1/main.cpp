#include "SimplexTable.h"
#include <iostream>

int main(void)
{
	//SimplexTable table({ 4, 5, 6 }, { 180, 210, 800 }, { 9, 6, 4, 7, 0, 0, 0 },
	//{
	//	{1, 0, 2, 1, 1, 0, 0},
	//	{0, 1, 3, 2, 0, 1, 0},
	//	{4, 2, 0, 4, 0, 0, 1}
	//});

	SimplexTable table({ 2, 3, 4 }, { 600, 600, 600 }, { 200, 300, 0, 0, 0 },
	{
		{10, 5, 1, 0, 0},
		{6, 20, 0, 1, 0},
		{8, 15, 0, 0, 1}
	});

	table.ComputeDeltas();
	SimplexTable* resultTable = Compute(table);

	if (resultTable == nullptr)
		return -1;

	float result = resultTable->GetFunctionValue();
	std::cout << "Q = " << result;

	return 0;
}