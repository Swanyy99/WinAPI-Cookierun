#pragma once

//========================================
//##				백터					##
//========================================

struct Vector
{
	float x;
	float y;

	Vector()
	{
		x = 0;
		y = 0;
	}

	Vector(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector operator+(const Vector& other)
	{
		return Vector(x + other.x, y + other.y);
	}

	Vector& operator+=(const Vector& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector operator-(const Vector& other)
	{
		return Vector(x - other.x, y - other.y);
	}

	Vector& operator-=(const Vector& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	template <typename T>
	Vector operator*(T num)
	{
		return Vector(x * num, y * num);
	}

	template <typename T>
	Vector& operator*=(T num)
	{
		x *= num;
		y *= num;
		return *this;
	}

	template <typename T>
	Vector operator/(T num)
	{
		assert(0 != num);
		return Vector(x / num, y / num);
	}

	template <typename T>
	Vector& operator/=(T num)
	{
		assert(0 != num);
		x /= num;
		y /= num;
		return *this;
	}

	float Magnitude()
	{
		return sqrtf(x * x + y * y);
	}

	// 거리연산(피타고라스)의 루트연산이 굉장히 많은 시간을 요구하기 때문에
	// 거리의 차이만 비교하고 싶을 경우 루트연산을 하지 않은 길이의 제곱끼리 비교
	float SqrMagnitude()
	{
		return x * x + y * y;
	}

	float Length()
	{
		return Magnitude();
	}

	// 정규화(표준화) : 길이가 1인 백터(단위백터)로 변환
	// 방향성백터와 같이 길이가 1인 백터가 필요할 경우 변환
	void Normalize()
	{
		if (SqrMagnitude() == 0)
		{
			x = 0;
			y = 0;
		}
		else
		{
			float length = Length();
			x = x / length;
			y = y / length;
		}
	}

	// 단위백터를 반환
	Vector Normalized()
	{
		if (SqrMagnitude() == 0)
		{
			return Vector(0, 0);
		}
		else
		{
			float length = Length();
			return Vector(x / length, y / length);
		}
	}
};

//========================================
//##				색상					##
//========================================

struct Color
{
	Color()
	{
		r = 0;
		g = 0;
		b = 0;
		a = 1;
	}

	Color(BYTE r, BYTE g, BYTE b, FLOAT a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	BYTE r, g, b;
	FLOAT a;
};