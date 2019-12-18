//point.h

#ifndef POINT_HEADER
#define POINT_HEADER

#include <iostream>

 
class point
{
public:
	int x;
	int y;
	
	//CTOR
	point()
	{
		x = 0;
		y = 0;
	}
	
	point(int a, int b)
	{
		x = a;
		y = b;
	}
	
	~point()
	{
		
	}
	
	
	
	inline point& operator=(const point& rightside)
	{
      		x = rightside.x;
		y = rightside.y;
      		return *this;
	}
	
	inline bool operator==(const point& right) 
	{

		if((x == right.x) &&
	   	(y == right.y) )
			return true; 
		else 
			return false;
	} 
	inline bool operator!=(const point& right) 
	{

		if((x != right.x) ||
	   	(y != right.y) )
			return true; 
		else 
			return false;
	} 

	inline bool operator<(const point& right) 
	{

		if( (x + y) < (right.x + right.y) )
			return true; 
		else 
			return false;
	} 

	inline point& operator+=(const point& rightside) 
	{
      		x += rightside.x;
	  	y += rightside.y;
     		 return *this;
	}

	inline point& operator-=(const point& rightside) 
	{	
      		//cout<<"Point is: ("<<x<<", "<<y<<")\n";
     	 	x -= rightside.x;
      		//cout<<"RightSide.x: "<<rightside.x<<"\n";
      		y -= rightside.y;
      		//cout<<"RightSide.y: "<<rightside.y<<"\n";
      		return *this;
	} 
 
	inline point& operator^=(const point& right) 
	{
      		//point temp = *this;
      		x ^= right.x;
	  	y ^= right.y;
      		return *this;          // use Copy Constructor to copy temp to return location
	} 
	
	inline point operator+(const point& right) 
	{
      		point temp(*this);   
	     	temp += right;        
      		return temp;          
	}
	
	inline point abs()
	{
		point p;
	
		if( x < 0 )
			p.x = -x;
		else
			p.x = x;
		if( y < 0 )
			p.y = -y;
		else
			p.y = y;
	
		return p;
	}
	
	friend std::ostream& operator<<(std::ostream &out, point p);

};

#endif//POINT_HEADER
