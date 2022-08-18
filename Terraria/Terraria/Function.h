#pragma once
#include"CObject.h"


template<typename T>
int Delete_Vec(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (nullptr != _vec[i])
			delete _vec[i];
	}
	_vec.clear();
	return 0;
}
template<typename T1,typename T2>
int Delete_Map(map<T1, T2>& _map)
{
	for (auto iter = _map.begin(); iter != _map.end(); ++iter)
	{
		if (iter->second != nullptr)
		{
			delete iter->second;
		}
	}
	return 0;
}
