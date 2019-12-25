#pragma once
#ifndef WRCHARTMATH
#define WRCHARTMATH

namespace WRMath
{
	//将指定的值四舍五入到最近的整数。
	inline double round(double v)
	{
		if (v < 0) return v - 0.5;
		return v + 0.5;
	}
}

#endif //WRCHARTMATH
