#ifndef Probability_h
#define Probability_h

#include <map>

class Probability
{
public:
	Probability();
	virtual ~Probability();

	static std::string SelectOne(std::map<std::string, float> const& targetDict);

	static bool PercentJudgment(float percent);
};

#endif