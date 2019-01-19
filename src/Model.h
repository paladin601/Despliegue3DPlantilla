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
		vector < glm::vec3 > mVerticesBoundingBox;
		glm::vec3 mTranslation;
		glm::vec3 mRotation;
		GLuint list;
		int mNumOfVertices, mNumOfFaces, mDisplay;

	public:
		CModel();
		~CModel();
		virtual bool load(string path) = 0;
		virtual void display();
		void displayBeginEnd();
		void displayList();
		void createList();
		void setTranslation(glm::vec3 translation);
		glm::vec3 getTranslation();
		void normalize();
		void middlePoint();
		float coordMax();
		int getDeployType();
		void setDeployType(int);
};