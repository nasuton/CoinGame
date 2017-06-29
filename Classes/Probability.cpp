#include "Probability.h"

#include <random>
#include <math.h>

Probability::Probability()
{

}

Probability::~Probability()
{

}

std::string Probability::SelectOne(std::map<std::string, float> const& targetDict)
{
	float total = 0.0f;
	for (auto itr = targetDict.begin(); itr != targetDict.end(); itr++)
	{
		total += itr->second;
	}

	std::random_device rand_device;
	std::mt19937 mersenne(rand_device());
	std::uniform_real_distribution<float> rand(0.0f, total);
	float randomResult = rand(mersenne);

	for (auto itr = targetDict.begin(); itr != targetDict.end(); itr++)
	{
		randomResult -= itr->second;

		if (randomResult < 0.0f)
		{
			return itr->first;
		}
	}

	return "";
}

bool Probability::PercentJudgment(float percent)
{
	int decimalPoint = 1;

	int rate = (int)powf(10, decimalPoint);

	int randomLimit = 100 * rate;
	int border = (int)(rate * percent);

	std::random_device rand_device;
	std::mt19937 mersenne(rand_device());
	std::uniform_int_distribution<int> rand(0, randomLimit);
	int randomResult = rand(mersenne);

	return randomResult < border;
}