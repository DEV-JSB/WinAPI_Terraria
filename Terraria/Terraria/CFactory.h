#pragma once
#include"pch.h"

template<typename T>
class CFactory
{
public:

	static T* Create();
	// Transform Component
	static T* Create(const Vector3& _pos, const Vector3& _rot, const Vector2& _scale);
	static T* Create(const Vector3& _pos, const Vector3& _rot, const Vector2& _scale, const bool _b);
	// AnimatorComponent
	static T* Create(const bool _willRender);
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

// Create UI Constructor
template<typename T>
inline T* CFactory<T>::Create(const Vector3& _pos, const Vector3& _rot, const Vector2& _scale,const bool _b)
{
	return new T(_pos, _rot, _scale,_b);
}

template<typename T>
inline T* CFactory<T>::Create(const bool _willRender)
{
	return new T(_willRender);
}
