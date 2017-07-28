#ifndef Probability_h
#define Probability_h

#include <map>

class Probability
{
public:
	Probability();
	virtual ~Probability();

	//strinig(名前など)とfloat(確率)のマップをわたすとそれに応じたstringを返す
	static std::string SelectOne(std::map<std::string, float> const& targetDict);

	//渡した数字によってtureかfalseを返す
	static bool PercentJudgment(float percent);
};

#endif