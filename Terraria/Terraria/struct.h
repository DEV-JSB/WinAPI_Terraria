#pragma once

enum class INPUTSTATE;
enum class KEY;
enum class MOUSE;

// not define is it working?
struct stKeyInfo
{
	bool			bIsPressed;
	INPUTSTATE		eState;
	int				iKey;
};

struct stMouseInfo
{
	bool			bIsPressed;
	INPUTSTATE		eState;
	int				iKey;
};

//
struct stAnimFrame
{

};