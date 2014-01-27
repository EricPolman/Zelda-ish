#pragma once
#include <math.h>

enum Direction{DOWN,RIGHT,UP,LEFT};
enum CollisionType{FULL, NONE, HALF_LEFT, HALF_RIGHT, HALF_TOP, HALF_BOTTOM, BOOMERANGABLE};

class Vector2{
public: 
	Vector2(){x = 0; y = 0;}
	Vector2(const Vector2& a_vec){x = a_vec.x; y = a_vec.y;}
	Vector2(float a_fX, float a_fY){x = a_fX; y = a_fY;}
	float x; 
	float y;
	void Normalize(){
		if(x != 0 || y != 0)
		{
			float mag = sqrt(x*x + y*y);
			x /= mag; 
			y /= mag;
		}
	}
	float Magnitude(){return sqrt(x*x + y*y);}
	float Distance(Vector2 a_vec){float distX = x - a_vec.x; float distY = y - a_vec.y;return sqrt(distX*distX + distY*distY);}
	Vector2 operator+(Vector2 a_vec){return Vector2(x + a_vec.x, y + a_vec.y);}
	Vector2 operator-(Vector2 a_vec){return Vector2(x - a_vec.x, y - a_vec.y);}
	Vector2 operator*(float a_scalar){return Vector2(x * a_scalar, y * a_scalar);}
	Vector2 operator-(){return Vector2(-x, -y);}
	std::string ToString()
	{
		std::stringstream ss;		
		ss << "{ " << x << ", " << y << " }";
		return ss.str();
	}
};


class Vector2i
{
public:
	Vector2i(int a_x, int a_y){x = a_x; y = a_y;}
	Vector2i(){x = 0; y = 0;}
	int x;
	int y;
};

struct CollisionInfo{
	bool isColliding;
	Direction direction;
	Vector2 depth;
};

class CollisionRectangle
{
public:
	CollisionRectangle(int a_x, int a_y, int a_width, int a_height)
	{
		x = a_x;
		y = a_y;
		width = a_width;
		height = a_height;
	}
	CollisionRectangle(){x = 0; y = 0; width = 0; height = 0;}
	int x;
	int y;
	int width;
	int height;

	CollisionInfo Intersects(CollisionRectangle a_other)
	{
		CollisionInfo info;
		info.isColliding = true;
		info.depth = Vector2(0,0);
		info.direction = DOWN;

		if(x > a_other.x + a_other.width) info.isColliding = false;
		if(x + width < a_other.x)  info.isColliding = false;
		if(y > a_other.y + a_other.height) info.isColliding = false;
		if(y + height < a_other.y) info.isColliding = false;
		if( !info.isColliding )
			return info;

		//Now we know there is a collision.
		if(x + width > a_other.x)
		{
			info.depth.x -= a_other.x - (x + width);
		}
		if(x < a_other.x + a_other.width)
		{
			info.depth.x -= (a_other.x + a_other.width) - x;
		}
		if(y + height > a_other.y)
		{
			info.depth.y -= a_other.y - (y + height);
		}
		if(y < a_other.y + a_other.height)
		{
			info.depth.y -= (a_other.y + a_other.height) - y;
		}

		return info;
	}

	std::string ToString()
	{
		std::stringstream ss;		
		ss << "{ " << x << ", " << y << ", " << width << ", " << height << " }";
		return ss.str();
	}
};
