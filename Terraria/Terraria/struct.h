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

	MyVector2 operator+(MyVector2& _vec)const
	{
		return MyVector2({ x + _vec.x, y + _vec.y });
	}

	MyVector2& operator+=(MyVector2& _vec)
	{
		this->x += _vec.x;
		this->y += _vec.y;
		return *this;
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

