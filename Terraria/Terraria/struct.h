#pragma once

enum class INPUTSTATE;
enum class KEY;
enum class MOUSE;
// not define is it working?





// HavePower & Size
typedef struct MyVector2
{
	float x;
	float y;

	float Length()const
	{
		return (float)(sqrt(pow(x, 2) + pow(y, 2)));
	}
	MyVector2 operator - (MyVector2& p)
	{
		return Vector2({ this->x - p.x,this->y - p.y });
	}
	MyVector2& Normalize()
	{
		float length = this->Length();
		this->x /= length;
		this->y /= length;
		return *this;
	}
	MyVector2 operator-()const
	{
		return MyVector2({ -x , -y});
	}
	MyVector2 operator+(MyVector2& _vec)const
	{
		return MyVector2({ x + _vec.x, y + _vec.y });
	}
	MyVector2 operator+(const MyVector2& _vec)const
	{
		return MyVector2({ x + _vec.x, y + _vec.y });
	}
	MyVector2& operator+=(const MyVector2& _vec)
	{
		this->x += _vec.x;
		this->y += _vec.y;
		return *this;
	}
	MyVector2 operator * (const float _f)
	{
		return MyVector2({ this->x * _f, this->y * _f });
	}
	MyVector2 operator * (const float _f) const
	{
		return MyVector2({ this->x * _f, this->y * _f });
	}
	MyVector2 operator * (const double _d)
	{
		return MyVector2({ this->x * (float)_d, this->y * (float)_d });
	}
	MyVector2& operator *= (const float _f)
	{
		this->x *= _f;
		this->y *= _f;
		return *this;
	}
	MyVector2& operator /= (const float _f)
	{
		this->x /= _f;
		this->y /= _f;
		return *this;
	}
	MyVector2 operator - (POINT& p)
	{
		return Vector2({ this->x - p.x,this->y - p.y });
	}

}Vector2;


typedef struct MyVector3
{
	float x;
	float y;
	float z;


	MyVector3 operator+(MyVector3& _vec)const
	{
		return MyVector3({ x + _vec.x, y + _vec.y,z + _vec.z });
	}

	MyVector3& operator+=(MyVector3& _vec)
	{
		this->x += _vec.x;
		this->y += _vec.y;
		this->z += _vec.z;
		return *this;
	}

}Vector3;

// Use In InputMgr KeyboardInformation
struct stKeyInfo
{
	bool			bIsPressed;
	INPUTSTATE		eState;
	int				iKey;
};

// Use In InputMgr MouseInformation
struct stMouseInfo
{
	bool			bIsPressed;
	INPUTSTATE		eState;
	int				iKey;
};

struct stSkinInfo
{
	// VewPivot Left Top
	Vector2 vLT;
	// Slice Size
	Vector2 vSliceSize;
};

// Use In Animation
struct stAnimFrame
{
	// VewPivot Left Top
	Vector2 vLT;
	// Slice Size
	Vector2 vSliceSize;
	// for View Pivot Offset
	Vector2 vOffset;

	// Float During Play
	float fDuration;
};

