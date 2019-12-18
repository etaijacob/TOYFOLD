//point.cpp

#include "point.h"

inline std::ostream& operator<<(std::ostream &out, point p)
{
	
	out<<"("<<p.x<<", "<<p.y<<")";
	return out;
}
