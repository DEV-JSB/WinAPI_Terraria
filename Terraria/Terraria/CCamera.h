#pragma once


class CObject;

class CCamera
{
public:// Get
	Vector2 GetDifference()const { return m_vDifference; }
	Vector2 GetLookAt()const { return m_vLookAt; }
	Vector2 GetResolutuon()const { return m_vResolution; }
public:
	// Caculator Diffrence
	int Update();
	// Setting Targets
	int Init();

private:
	CObject* SettingTargetPlayer();

private:

	// Resolution
	Vector2 m_vResolution;

	// Look Vector
	Vector2 m_vLookAt; 

	// Difference Value
	Vector2 m_vDifference;

	// Render Pivot Player
	CObject* m_pTarget;

private:
	SINGLE(CCamera);
};

