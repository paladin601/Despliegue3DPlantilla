#pragma once
#include "Model.h"
#include <iostream>
#include <fstream>

using std::fstream;

class OffLoader : public CModel
{
public:
	OffLoader();
	~OffLoader();
	bool load(string path);
	void display();
};

