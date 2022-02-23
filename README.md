# SimplexMethod

Simplex method is an alghorithm that serves to solve task of linear programming.
In most cases task of linear programming is an economic task.

For more theory read articles:
  - https://en.wikipedia.org/wiki/Linear_programming
  - https://en.wikipedia.org/wiki/Linear_programming#Simplex_algorithm_of_Dantzig
  
Include ```SimplexTable.h``` to use SimplexTable data structure and Compute function <br/>
To solve task make all steps:
  1. Fill first SimplexTable of your task.
  2. Call ```ComputeDeltas``` method.
  3. Call ```Compute``` function and pass first simplex table.
  4. Recieve result from function.
  5. Check your result table to ```NULL/nullptr```. If it is than your task has wrong description.
  6. If your result don't equal to ```NULL/nullptr``` than call ```GetFunctionValue``` method.
  7. Print your result.
  
```C++
#include "SimplexTable.h"

int main(void)
{
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
```
