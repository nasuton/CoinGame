#ifndef FindLength_h
#define FindLength_h

#include "stdio.h"

namespace FindLength
{
	//”z—ñ‚Ì’·‚³‚ğ‹‚ß‚é‚¾‚¯
	template<typename Type, std::size_t Length>
	std::size_t ArrayLength(const Type(&)[Length])
	{
		return Length;
	}
}

#endif 