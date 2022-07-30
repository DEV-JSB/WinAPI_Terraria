#pragma once


// Funtion Error then return 503
#define FUNC_ERROR 503

#define CLIENT_WIDTH 1280
#define CLIENT_HEIGHT 720

#define RTTI_DYNAMIC_CAST(classname,map,type) 	dynamic_cast<classname*>((*map.find(type)).second);
#define GET_COMPONENT(classname,map,type) RTTI_DYNAMIC_CAST(classname,map,type)
#define SINGLE(classname)private:\
						classname(); \
						~classname();\
						public:			\
							static classname* GetInstance()\
							{							   \
								static classname mgr;	   \
								return &mgr;			   \
							}\

enum class SCENE
{
	SCENE_MENU,
	SCENE_WORLD,
	SCENE_ANITOOL,
	SCENE_END
};

// Input State type
enum class INPUTSTATE
{
	INPUTSTATE_NONE,
	INPUTSTATE_TAP,
	INPUTSTATE_HOLD,
	INPUTSTATE_AWAY,
	INPUTSTATE_END
};

// Resource Enum
enum class RESOURCE
{
	RESOURCE_TEXTURE,
	RESOURCE_END
};

// Component
enum class COMPONENT
{
	COMPONENT_TRANSFORM2D,
	COMPONENT_ANIMATOR,
	COMPONENT_END
};
// Object
enum class OBJECT
{
	OBJECT_PLAYER,
	OBJECT_BLOCK,
	OBJECT_UI,
	OBJECT_END
};

// Keyboard Input Type
enum class KEY
{
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,

	KEY_Q,
	KEY_W,
	KEY_E,
	KEY_R,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_F,


	KEY_CTRL,
	KEY_SPACE,
	KEY_ENTER,
	KEY_ESC,

	KEY_LAST
};

// Mouse Input Type
enum class MOUSE
{
	MOUSE_LBTN,
	MOUSE_RBTN,
	MOUSE_END
};