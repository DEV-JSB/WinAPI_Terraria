#include "pch.h"
#include "CScene.h"

CScene::CScene()
{
	// InputList
	for (int i = 0; i < (int)OBJECT::OBJECT_END; ++i)
		m_vecObjectList[i];

}

CScene::~CScene()
{
}
