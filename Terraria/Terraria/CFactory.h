#pragma once

class CResource;
class CObject;
class CScene;

class CFactory
{
	const CResource* CreateResource(RESOURCE _type)const;
	const CObject* CreateObject(OBJECT _type)const;
	const CScene* CreateScene(SCENE _type)const;
};

