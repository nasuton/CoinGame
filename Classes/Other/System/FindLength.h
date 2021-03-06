#ifndef FindLength_h
#define FindLength_h

#include "stdio.h"

namespace FindLength
{
	//配列の長さを求めるだけ
	template<typename Type, std::size_t Length>
	std::size_t ArrayLength(const Type(&)[Length])
	{
		return Length;
	}
}

#endif 