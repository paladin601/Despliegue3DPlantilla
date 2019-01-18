#pragma once
#include "Model.h"
#include <iostream>
#include <fstream>

using std::fstream;

class ObjLoader : public CModel
{
public:
	ObjLoader();
	~ObjLoader();
	bool load(string path);
	void display();
};

