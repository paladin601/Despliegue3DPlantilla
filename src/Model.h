#pragma once

#include "../headers/glfw3.h"
#include "../headers/glm/glm.hpp"
#include "BoundingBox.h"
#include "Normal.h"
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
	BoundingBox *boundingBox;
	glm::vec4 mRotation;
	glm::vec3 mScale;
	glm::vec3 mTranslation;
	GLuint list;
	Normal *normals;
	float mColor[3], mColorFill[3], mColorPoint[3];
	int mNumOfVertices, mNumOfFaces, mDisplay;
	bool boundingBoxCheck, wireCheck, pointCheck, fillCheck, normalsFacesCheck, normalsVerticesCheck;

public:
	CModel();
	~CModel();
	virtual bool load(string path) = 0;
	virtual void display();
	void selectDisplay();
	void displayBeginEnd();
	void displayList();
	void createList();
	void setRotation(glm::vec4);
	glm::vec4 getRotation();
	void setScale(glm::vec3);
	glm::vec3 getScale();
	void setTranslation(glm::vec3);
	glm::vec3 getTranslation();
	void normalize();
	void middlePoint();
	float coordMax();
	int getDeployType();
	void setDeployType(int);

	void setBoundingBoxCheck(bool);
	bool getBoundingBoxCheck();
	void setFillCheck(bool);
	bool getFillCheck();
	void setWireCheck(bool);
	bool getWireCheck();
	void setPointCheck(bool);
	bool getPointCheck();
	void setColorBoundingBox(float *);
	float* getColorBoundingBox();
	void setNormalsFacesCheck(bool);
	bool getNormalsFacesCheck();
	void setNormalsVerticesCheck(bool);
	bool getNormalsVerticesCheck();

	void setColor(float *);
	float* getColor();
	void setColorFill(float *);
	float* getColorFill();
	void setColorPoint(float *);
	float* getColorPoint();

	void setColorNormalsVertices(float *);
	float* getColorNormalsVertices();
	void setColorNormalsFaces(float *);
	float* getColorNormalsFaces();

};