#pragma once

#include "../headers/glfw3.h"
#include "../headers/glm/glm.hpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
using std::string;
using std::vector;

class CModel
{
	protected:
		glm::vec3 max;
		glm::vec3 min;
		glm::vec3 middle; 
		vector < glm::vec3 > mVertices;
		vector < glm::vec3 > mFaces;
		vector < glm::vec3 > out_vertices;
		vector < glm::vec2 > out_uvs;
		vector < glm::vec3 > out_normals;
		glm::vec3 mTranslation;
		int mNumOfVertices, mNumOfFaces;

	public:
		CModel();
		~CModel();
		virtual bool load(string path) = 0;
		virtual void display();
		void setTranslation(glm::vec3 translation);
		glm::vec3 getTranslation();
		void normalize();
		void middlePoint();
		float coordMax();
};