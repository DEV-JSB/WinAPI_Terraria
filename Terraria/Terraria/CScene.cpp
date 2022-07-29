#include "pch.h"
#include "CScene.h"


CScene::CScene()
{
	// InputList
	for (int i = 0; i < (int)OBJECT::OBJECT_END; ++i)
		m_arrObjectVec[i];

}

CScene::~CScene()
{
	for (int i = 0; i < (int)OBJECT::OBJECT_END; ++i)
	{
		Delete_Vec<CObject*>(m_arrObjectVec[i]);
	}
}

