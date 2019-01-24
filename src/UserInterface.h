#pragma once

#include "../headers/AntTweakBar.h"
#include "../headers/glm/glm.hpp"
#include "../headers/glfw3.h"
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
	int pick, pickLight;
	float mModelColor[3], mBoundingBoxColor[3], mPointColor[3], mFillColor[3], mNormalsFacesColor[3], mNormalsVerticesColor[3];
	bool boundingBoxCheck, fillCheck, pointCheck, wireCheck, normalsFacesCheck, normalsVerticesCheck;
	bool backFace, zBuffer, camera, light, flat;
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat position[4];

public:
	///Method to obtain the only instance of the calls
	static CUserInterface * Instance();
	~CUserInterface();
	void reshape();
	void show();
	void hide();
	void setTranslation(glm::vec3 modelTranslation);
	glm::vec3 getTranslation();
	void setScale(glm::vec3 modelScale);
	glm::vec3 getScale();
	void setRotation(glm::vec4 modelRotation);
	glm::vec4 getRotation();
	int getDeployType();
	void setDeployType(int);

	int getPicked();

	void setColor(float*);
	float* getColor();
	void setColorFill(float*);
	float* getColorFill();
	void setColorPoint(float*);
	float* getColorPoint();
	void setColorBoundingBox(float*);
	float* getColorBoundingBox();
	void setColorNormalsFaces(float*);
	float* getColorNormalsFaces();
	void setColorNormalsVertices(float*);
	float* getColorNormalsVertices();

	int getLightPicked();
	void setLightPosition(GLfloat *a);
	GLfloat* getLightPosition();
	void setLightSpecular(GLfloat *a);
	GLfloat* getLightSpecular();
	void setLightDiffuse(GLfloat *a);
	GLfloat* getLightDiffuse();
	void setLightAmbient(GLfloat *a);
	GLfloat* getLightAmbient();

	void setBoundingBoxCheck(bool);
	bool getBoundingBoxCheck();
	bool getFillCheck();
	void setFillCheck(bool);
	void setPointCheck(bool);
	bool getPointCheck();
	void setWireCheck(bool);
	bool getWireCheck();
	void setNormalsFacesCheck(bool);
	bool getNormalsFacesCheck();
	void setNormalsVerticesCheck(bool);
	bool getNormalsVerticesCheck();

	bool getFlatCheck();
	bool getLightsCheck();
	bool getBackFaceCheck();
	bool getZBufferCheck();
	bool getCameraCheck();

private:
	///Private constructor
	CUserInterface();
};