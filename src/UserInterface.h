#pragma once

#include "../headers/AntTweakBar.h"
#include "../headers/glm/glm.hpp"
#include <iostream>
#include <string>

using std::string;
typedef enum { GL_BEGIN_GL_END, DISPLAY_LIST, VERTEX_POINTER, VBO } DEPLOY_TYPE;

//Singleton user interface class

class CUserInterface
{
private:

	static CUserInterface * mInterface; //Holds the instance of the class
	TwBar *mUserInterface;
	glm::vec3 mModelTranslation;
	glm::vec3 mModelScale;
	glm::vec4 mModelRotation;
	string mDeployMode;
	DEPLOY_TYPE m_currentDeploy;
	float mModelColor[3], mBoundingBoxColor[3];
	bool boundingBoxCheck;

public:
	///Method to obtain the only instance of the calls
	static CUserInterface * Instance();
	~CUserInterface();
	void reshape();
	void show();
	void hide();
	void setModelTranslation(float *modelTranslation);
	glm::vec3 getModelTranslation();
	void setModelScale(float *modelScale);
	glm::vec3 getModelScale();
	void setModelRotation(float *modelRotation);
	glm::vec4 getModelRotation();
	int getDeployType();
	void setDeployType(int);
	void setColor(float, float, float);
	float* getColor();
	void setColorBoundingBox(float, float, float);
	float* getColorBoundingBox();
	void setBoundingBoxCheck(bool);
	bool getBoundingBoxCheck();

private:
	///Private constructor
	CUserInterface(); 
};