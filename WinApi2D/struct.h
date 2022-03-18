#pragma once

struct iPoint
{
	int x;
	int y;
};

struct fPoint
{
	float x;
	float y;

	fPoint()
	{
		x = 0;
		y = 0;
	}

	fPoint(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	fPoint(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	fPoint(const POINT& _pt)
	{
		x = ((float)_pt.x);
		y = ((float)_pt.y);
	}
	
	fPoint& operator=(const fPoint& other)
	{
		x = other.x;
		y = other.y;

		return *this;
	}
	fPoint operator+ (const fPoint& other)
	{
		return fPoint(x + other.x, y + other.y);
	}
	
	fPoint operator*(float _f)
	{
		return fPoint(x * _f, y * _f);
	}
	fPoint& operator+=(const fPoint& other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	fPoint operator-(const fPoint& other)
	{
		return fPoint(x - other.x, y - other.y);
	}
	fPoint operator / (fPoint Other)
	{
		assert(!(0.f == Other.x || 0.f == Other.y));
		return fPoint(x / Other.x, y / Other.y);
	}
	template <typename T>
	fPoint operator*(T num)
	{
		return fPoint(x * num, y * num);
	}
	template <typename T>
	fPoint operator+(T num)
	{
		return fPoint(x + num, y + num);
	}
	template <typename T>
	fPoint operator-(T num)
	{
		return fPoint(x - num,y - num);
	}
	template <typename T>
	fPoint operator/(T num)
	{
		assert(0 != num);

		return fPoint(x / num, y / num);
	}
	bool IsZero()
	{
		if (x == 0.f && y == 0.f)
		{
			return true;
		}
		return false;
	}
	fPoint& normalize()
	{
		float fLen = Length();
		assert(fLen != 0.f);

		x /= fLen;
		y /= fLen;

		return *this;
	}
	bool IsZeroVec()
	{
		if (0 == x && 0 == y)
		{
			return true;
		}
		return false;
	}

	float Length()
	{
		return (float)sqrt((double)x * x + (double)y * y);
	}
};

typedef iPoint iVec2;
typedef fPoint fVec2;