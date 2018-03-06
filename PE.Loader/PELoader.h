#pragma once
#include <string>

class PELoader
{
public:
	PELoader();

	void Load(const std::wstring& path);

};
