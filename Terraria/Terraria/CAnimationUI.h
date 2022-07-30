#pragma once
#include"CUI.h"
#include"CFactory.h"

class CAnimationUI : public CUI
{




private:
	friend class CFactory<CAnimationUI>;
	CAnimationUI();
};

