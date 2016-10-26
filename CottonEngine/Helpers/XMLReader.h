#pragma once
#include "../stdafx.h"
#include <vector>

struct Data
{
	vector<string> title;
	vector<string> data;
};

class XMLReader
{
public:
	XMLReader();
	~XMLReader();

	vector<Data> ReadFile(string path);
};

