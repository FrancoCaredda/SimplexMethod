#ifndef SIMPLEX_TABLE_H
#define SIMPLEX_TABLE_H

#include <vector>
#include <set>
#include <cstdint>
#include <cmath>
#include <cstdio>

#define SCREEN_RESOLUTION_X 110

#define FLOAT_IS_ZERO(X) (fabs(X) < 0.00000001) ? true : false
#define COMPARE_FLOATS(X, Y) (fabs((X) - (Y)) < 0.00000001) ? true : false

class SimplexTable
{
public:
	SimplexTable(const std::vector<uint32_t>& bases,
		const std::vector<double>& members,
		const std::vector<double>& constants,
		const std::vector<std::vector<double>>& system);

	uint32_t MainRow();
	uint32_t MainColumn();

	bool HasPossibleSolutions();
	bool IsFinal();

	void ComputeDeltas();

	double GetFunctionValue() const;
	std::vector<std::pair<uint32_t, double>> GetRoots() const;

	friend SimplexTable* Compute(SimplexTable& firstTable);
	friend void PrintSimplexTable(const SimplexTable& table);

	~SimplexTable() = default;
private:
	std::vector<std::vector<double>> m_System;
	std::vector<uint32_t> m_Bases;

	std::vector<double> m_Members;
	std::vector<double> m_Constants;

	std::vector<double> m_Deltas;
};

SimplexTable* Compute(SimplexTable& firstTable);
void PrintSimplexTable(const SimplexTable& table);

#endif // !SIMPLEX_TABLE_H
