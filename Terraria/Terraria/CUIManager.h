#pragma once

class CUI;


class CUIManager
{

public:
	int Update();


private:
	CUI* m_pUI;
private:
	SINGLE(CUIManager);

};

