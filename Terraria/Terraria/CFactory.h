#pragma once
#include"CResource.h"
#include"CObject.h"


class CFactory
{
	const CResource* CreateResource(RESOURCE _type)const;
	const CObject* CreateObject(OBJECT _type)const;
};

