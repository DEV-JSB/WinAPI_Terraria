#pragma once
#include"pch.h"

template<typename T>
class CFactory
{
public:
	static T* Create();
	// Transform Component
	static T* Create(const Vector3& _pos, const Vector3& _rot, const Vector2& _scale);
};

template<typename T>
inline T* CFactory<T>::Create()
{
	return new T();
}

template<typename T>
inline T* CFactory<T>::Create(const Vector3& _pos, const Vector3& _rot, const Vector2& _scale)
{
	return new T(_pos, _rot, _scale);
}
