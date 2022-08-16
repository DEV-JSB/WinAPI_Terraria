#include "pch.h"
#include "CComponent.h"



int CComponent::RenderLocalSpace(const HDC _dc)const
{
	return 0;
}

CComponent::CComponent(bool _wiilRender)
	:m_bRender(_wiilRender)
{
}

CComponent::~CComponent()
{
}
