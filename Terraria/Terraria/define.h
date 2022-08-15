#pragma once


// Funtion Error then return 503
#define FUNC_ERROR 503

#define FRIEND_FACTORY(classname) friend class CFactory<classname>;
#define HIDE_CONSTRUCTOR(classname)private:\
									friend class CFactory<classname>;\
									classname();\

#define GET_DT CTimeMgr::GetInstance()->GetDT();

#define CLIENT_WIDTH 1280
// 80
#define CLIENT_HEIGHT 720
// 45
#define CHECK_POS_IN_TRANSRECT(trans,pos)((trans->GetPosition_X() - trans->GetScale_Width() * 0.5f) <= pos.x\
									&& pos.x <= (trans->GetPosition_X() + trans->GetScale_Width() * 0.5f)\
									&& (trans->GetPosition_Y() - trans->GetScale_Height() * 0.5f) <= pos.y\
									&& pos.y <= (trans->GetPosition_Y() + trans->GetScale_Height() * 0.5f))\

#define RTTI_DYNAMIC_CAST(classpointer,changeclass) dynamic_cast<changeclass*>(classpointer)

#define RTTI_DYNAMIC_CAST_MAP(classname,map,type) 	dynamic_cast<classname*>((*map.find(type)).second);
#define GET_COMPONENT(classname,map,type) RTTI_DYNAMIC_CAST_MAP(classname,map,type)
#define SINGLE(classname)private:\
						classname(); \
						~classname();\
						public:			\
							static classname* GetInstance()\
							{							   \
								static classname mgr;	   \
								return &mgr;			   \
							}\


#define DEFAULT_GRAVITYPOWER 70.f
#define DEFAULT_MAXSPEED 50.f
#define DEFAULT_FRICTION 25.f
#define DEFAULT_MASS 1.f



enum class RIGIDBODY
{
	RIGIDBODY_FRICTION,
	RIGIDBODY_JUMPPOWER,
	RIGIDBODY_SPEED,
	RIGIDBODY_MAXSPEED,
	RIGIDBODY_MASS,
	RIGIDBODY_GRAVITY,
	RIGIDBODY_END
};


enum class PLAYER_IDLEANI
{
	PLAYER_IDLEANI_HAIR,
	PLAYER_IDLEANI_LEG,
	PLAYER_IDLEANI_HEAD,
	PLAYER_IDLEANI_CLOTH,
	PLAYER_IDLEANI_LEFTARM,
	PLAYER_IDLEANI_RIGHTARM,
	PLAYER_IDLEANI_END
};

enum class UI_TYPE
{
	UI_PARENT,
	UI_BUTTON,
	UI_ANIMTAION,
	UI_END
};
enum class COLLIDER
{
	COLLIDER_CIRCLE,
	COLLIDER_RECT,
	COLLIDER_END
};
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
	COMPONENT_RIGIDBODY,
	// BOX,CIRCLE COLLIDER Is Only Use In Factory
	// Update and Scene Must Have Only PARENT COLLIDER Pointer
	COMPONENT_COLLIDER,
	COMPONENT_BOXCOLLIDER,
	COMPONENT_CIRCLECOLLIDER,
	COMPONENT_ANIMATOR,
	COMPONENT_SKIN,
	COMPONENT_END
};
// Object
enum class OBJECT
{
	OBJECT_BACKGROUND,
	OBJECT_PLAYER,
	OBJECT_UI,
	OBJECT_TILE,
	OBJECT_END
};

// Tile Type
enum class TILE
{
	TILE_GROUNDUP,
	TILE_GROUNDDOWN,
	TILE_ROCK,
	TILE_IRON,
	TILE_COPPER,
	TILE_END
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