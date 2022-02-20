#ifndef SIMPLEX_TABLE_H
#define SIMPLEX_TABLE_H

#include <vector>
#include <set>
#include <cstdint>
#include <cmath>

#define FLOAT_IS_ZERO(X) (fabs(X) < 0.00000001f) ? true : false
#define COMPARE_FLOATS(X, Y) (fabs((X) - (Y)) < 0.00000001f) ? true : false

class SimplexTable
{
public:
	SimplexTable(const std::vector<uint32_t>& bases,
		const std::vector<float>& members,
		const std::vector<float>& constants,
		const std::vector<std::vector<float>>& system);

	uint32_t MainRow();
	uint32_t MainColumn();

	bool HasPossibleSolutions();
	bool IsFinal();

	void ComputeDeltas();

	float GetFunctionValue();

	friend SimplexTable* Compute(SimplexTable& firstTable);

	~SimplexTable() = default;
private:
	std::vector<std::vector<float>> m_System;
	std::vector<uint32_t> m_Bases;

	std::vector<float> m_Members;
	std::vector<float> m_Constants;

	std::vector<float> m_Deltas;
};

SimplexTable* Compute(SimplexTable& firstTable);

#endif // !SIMPLEX_TABLE_H
