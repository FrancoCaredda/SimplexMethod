#include "SimplexTable.h"

SimplexTable::SimplexTable(const std::vector<uint32_t>& bases, 
	const std::vector<double>& members, 
	const std::vector<double>& constants, 
	const std::vector<std::vector<double>>& system)
{
	m_Bases = bases;
	m_Members = members;
	m_Constants = constants;
	m_System = system;
}

uint32_t SimplexTable::MainRow()
{
	uint32_t mainColumn = MainColumn();

	std::vector<std::pair<uint32_t, double>> ratios;

	// Computing all ratios
	for (int i = 0; i < m_System.size(); i++)
	{
		if (m_System[i][mainColumn] > 0)
			ratios.push_back({ m_Bases[i], m_Members[i] / m_System[i][mainColumn]});
	}

	// Finding minimum ration
	double value = ratios[0].second;
	uint32_t index = ratios[0].first;

	for (int i = 1; i < ratios.size(); i++)
	{
		if (value > ratios[i].second)
		{
			value = ratios[i].second;
			index = ratios[i].first;
		}
	}

	return index;
}

uint32_t SimplexTable::MainColumn()
{
	std::vector<std::pair<uint32_t, double>> deltas;

	// Getting all deltas
	for (int i = 0; i < m_Deltas.size(); i++)
	{
		if (m_Deltas[i] < 0)
			deltas.push_back({ i, m_Deltas[i] });
	}

	// Finding maximum absolute delta
	double value = -deltas[0].second;
	uint32_t index = deltas[0].first;

	for (int i = 1; i < deltas.size(); i++)
	{
		if (value < -deltas[i].second)
		{
			value = -deltas[i].second;
			index = deltas[i].first;
		}
	}

	return index;
}

bool SimplexTable::HasPossibleSolutions()
{
	for (int i = 0; i < m_Deltas.size(); i++)
	{
		if (m_Deltas[i] < 0)
		{
			for (int j = 0; j < m_System.size(); j++)
			{
				if (m_System[j][i] > 0)
					return true;
			}
		}
	}

	return false;
}

bool SimplexTable::IsFinal()
{
	int count = 0;

	for (int i = 0; i < m_Deltas.size(); i++)
	{
		if (m_Deltas[i] > 0 || FLOAT_IS_ZERO(m_Deltas[i]))
			count++;
	}

	return count == m_Deltas.size();
}

void SimplexTable::ComputeDeltas()
{
	if (m_Deltas.empty())
		m_Deltas.resize(m_Constants.size());

	std::fill(m_Deltas.begin(), m_Deltas.end(), 0);

	double z = 0;
	for (int i = 0; i < m_Deltas.size(); i++)
	{
		z = 0;
		if (std::find(m_Bases.begin(), m_Bases.end(), i) == m_Bases.end())
		{
			for (int j = 0; j < m_System.size(); j++)
			{
				z += m_Constants[m_Bases[j]] 
					* m_System[j][i];
			}

			m_Deltas[i] = z - m_Constants[i];
		}
	}
}

double SimplexTable::GetFunctionValue() const
{
	double result = 0;

	for (int i = 0; i < m_Members.size(); i++)
		result += m_Members[i] * m_Constants[m_Bases[i]];

	return result;
}

std::vector<std::pair<uint32_t, double>> SimplexTable::GetRoots() const
{
	std::vector<std::pair<uint32_t, double>> roots;

	for (int i = 0; i < m_Bases.size(); i++)
	{
		roots.push_back({ m_Bases[i], m_Members[i] });
	}

	return roots;
}

static uint32_t IndexOf(const std::vector<uint32_t>& vector, uint32_t value)
{
	uint32_t index = -1;

	for (int i = 0; i < vector.size(); i++)
	{
		if (vector[i] == value)
		{
			index = i;
			break;
		}
	}

	return index;
}

SimplexTable* Compute(SimplexTable& firstTable)
{
	SimplexTable* table = new SimplexTable(firstTable);

	for (int i = 0; i < table->m_Members.size(); i++)
	{
		if (table->m_Members[i] < 0)
			return nullptr;
	}

	int c = 0;

	while (true)
	{
		SimplexTable copy(*table);

		if (table->IsFinal())
		{
			return table;
		}
		else if (table->HasPossibleSolutions())
		{
			uint32_t j = table->MainColumn();
			uint32_t i = table->MainRow();

			uint32_t k = IndexOf(table->m_Bases, i);

			table->m_Bases[k] = j;

			// Updating main row
			double mainElement = table->m_System[k][j];

			for (int s = 0; s < table->m_System[k].size(); s++)
			{
				table->m_System[k][s] = copy.m_System[k][s] / mainElement;
				PrintSimplexTable(*table);
				printf("\n");
			}

			table->m_Members[k] = copy.m_Members[k] / mainElement;

			// Update members
			for (int s = 0; s < table->m_Members.size(); s++)
			{
				if (s != k)
				{
					table->m_Members[s] = copy.m_Members[s] - copy.m_Members[k] * 
						copy.m_System[s][j] / mainElement;

					PrintSimplexTable(*table);
					printf("\n");
				}
			}

			// Update system
			for (int s = 0; s < table->m_System.size(); s++)
			{
				if (s != k)
				{
					for (int l = 0; l < table->m_System[s].size(); l++)
					{
						if (std::find(table->m_Bases.begin(), table->m_Bases.end(), l)
							== table->m_Bases.end())
						{
							table->m_System[s][l] = copy.m_System[s][l] - copy.m_System[s][j] *
								copy.m_System[k][l] / mainElement;

							PrintSimplexTable(*table);
							printf("\n");
						}
					}
				}
			}

			// Update base columns
			for (int s = 0; s < table->m_System.size(); s++)
			{
				for (int l = 0; l < table->m_System[s].size(); l++)
				{
					if ((std::find(table->m_Bases.begin(), table->m_Bases.end(), l)
						!= table->m_Bases.end()) &&
						(l == table->m_Bases[s]))
					{
						table->m_System[s][l] = 1;
					}
					else if ((std::find(table->m_Bases.begin(), table->m_Bases.end(), l)
						!= table->m_Bases.end()))
					{
						table->m_System[s][l] = 0;
					}

					PrintSimplexTable(*table);
					printf("\n");
				}
			}

			table->ComputeDeltas();

			printf("CT-%d\n", c++);
			PrintSimplexTable(*table);
			printf("\n");
		}
		else
		{
			return nullptr;
		}
	}
}

void PrintSimplexTable(const SimplexTable& table)
{
	for (int i = 0; i < SCREEN_RESOLUTION_X; i++)
		 printf("-");

	printf("\n");
	printf("x[b]\t%c\t", '|');
	printf("P0\t%c", '|');

	for (int i = 0; i < table.m_Constants.size(); i++)
		printf("c%d=%.3lf%6c ", i, table.m_Constants[i], '|');

	printf("\n");

	for (int i = 0; i < SCREEN_RESOLUTION_X; i++)
		 printf("-");

	printf("\n");

	for (int i = 0; i < table.m_Bases.size(); i++)
	{
		printf("%5d\t%c\t",table.m_Bases[i], '|');
		printf("%5.3lf\t%c\t", table.m_Members[i], '|');

		for (int j = 0; j < table.m_System[i].size(); j++)
			printf("%5.3lf\t%c\t", table.m_System[i][j], '|');

		printf("\n");
		for (int i = 0; i < SCREEN_RESOLUTION_X; i++)
			 printf("-");

		printf("\n");
	}

	printf("Q=%3.3lf%c\t\t\t", table.GetFunctionValue(), '|');

	for (int i = 0; i < table.m_Deltas.size(); i++)
		printf("%5.3lf\t%c\t", table.m_Deltas[i], '|');

	printf("\n");

	for (int i = 0; i < SCREEN_RESOLUTION_X; i++)
		printf("-");

	printf("\n");
}
