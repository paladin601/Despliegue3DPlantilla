#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "../headers/glm/glm.hpp"
#include "../headers/glfw3.h"


using namespace std;
using std::string;
using std::vector;

class Normal
{
protected:
	vector<glm::vec3> normalVertices;
	vector<glm::vec3> normalCaras;
	vector<glm::vec3> facesCenter;
	int numFaces, numVertices;
	float mColor[3], mColorFaces[3];
	GLuint list,listFaces;
public:
	Normal(vector<glm::vec3>, vector<glm::vec3>, int, int);
	~Normal();
	void displayNormalVertices();
	void displayNormalFaces();
	void createList(vector<glm::vec3>);
	void createListFaces();
	void setColor(float *);
	float* getColor();
	void setColorFaces(float *);
	float* getColorFaces();

	void displayNormalVerticesglm(int);
	void displayNormalFacesglm(int);
};

