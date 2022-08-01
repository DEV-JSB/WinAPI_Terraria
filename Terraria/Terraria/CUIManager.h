#pragma once

class CUI;


class CUIManager
{

public:
	int Release();
	int Update();
	int Render(const HDC _hdc);
private:
	SINGLE(CUIManager);

};

