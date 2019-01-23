#include "Model.h"

CModel::CModel()
{
	fillCheck = pointCheck = wireCheck = boundingBoxCheck = false;
	mColor[0] = mColor[1] = mColor[2] = 1.0f;
	mColorFill[0] = mColorFill[1] = mColorFill[2] = 1.0f;
	mColorPoint[0] = mColorPoint[1] = mColorPoint[2] = 1.0f;
	max = glm::vec3(-1000, -1000, -1000);
	min = glm::vec3(1000, 1000, 1000);
	middle = glm::vec3(0, 0, 0);
	mTranslation[0] = mTranslation[1] = mTranslation[2] = 0.0f;
	mScale[0] = mScale[1] = mScale[2] = 3;
	mRotation[0] = mRotation[1] = mRotation[2] = 0;
	mDisplay = 1;
}

CModel::~CModel()
{
	mVertices.clear();
}

void CModel::display()
{
	if (fillCheck) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3fv(mColorFill);
		selectDisplay();
	}
	glPolygonOffset(2, 2);
	if (wireCheck) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3fv(mColor);
		selectDisplay();
	}
	if (pointCheck) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glColor3fv(mColorPoint);
		glPointSize(3.0f);
		selectDisplay();
		glPointSize(1.0f);
	}
	glPolygonOffset(0, 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (boundingBoxCheck) {
		boundingBox->displayList();
	}
	if (normalsFacesCheck) {
		normals->displayNormalFaces();
	}
	if (normalsVerticesCheck) {
		normals->displayNormalVertices();
	}
}
void CModel::selectDisplay()
{
	switch (mDisplay)
	{
	case 0:
		displayBeginEnd();
		break;
	case 1:
		displayList();
		break;
	default:
		displayList();
		break;
	}
}
void CModel::displayBeginEnd() {
	for (int i = 0; i < mNumOfFaces; i++)
	{
		glBegin(GL_TRIANGLES);
		glVertex3f(mVertices[(int)mFaces[i].x].x, mVertices[(int)mFaces[i].x].y, mVertices[(int)mFaces[i].x].z);
		glVertex3f(mVertices[(int)mFaces[i].y].x, mVertices[(int)mFaces[i].y].y, mVertices[(int)mFaces[i].y].z);
		glVertex3f(mVertices[(int)mFaces[i].z].x, mVertices[(int)mFaces[i].z].y, mVertices[(int)mFaces[i].z].z);
		glEnd();
	}
}

void CModel::displayList() {
	glCallList(list);
}

void CModel::createList() {
	list = glGenLists(1);
	glNewList(list, GL_COMPILE);
	for (int i = 0; i < mNumOfFaces; i++)
	{
		glBegin(GL_TRIANGLES);
		glVertex3f(mVertices[(int)mFaces[i].x].x, mVertices[(int)mFaces[i].x].y, mVertices[(int)mFaces[i].x].z);
		glVertex3f(mVertices[(int)mFaces[i].y].x, mVertices[(int)mFaces[i].y].y, mVertices[(int)mFaces[i].y].z);
		glVertex3f(mVertices[(int)mFaces[i].z].x, mVertices[(int)mFaces[i].z].y, mVertices[(int)mFaces[i].z].z);
		glEnd();
	}
	glEndList();
}

void CModel::setRotation(glm::vec4 rotation)
{
	mRotation = rotation;
}

glm::vec4 CModel::getRotation()
{
	return mRotation;
}

void CModel::setTranslation(glm::vec3 translation)
{
	mTranslation = translation;
}

glm::vec3 CModel::getTranslation()
{
	return mTranslation;
}

void CModel::setScale(glm::vec3 scale)
{
	mScale = scale;
}

glm::vec3 CModel::getScale()
{
	return mScale;
}

void CModel::normalize() {
	float m = coordMax();

	for (int i = 0; i < mNumOfVertices; i++) {
		mVertices[i].x = (mVertices[i].x - middle.x) / m;
		mVertices[i].y = (mVertices[i].y - middle.y) / m;
		mVertices[i].z = (mVertices[i].z - middle.z) / m;
	}
	max.x = (max.x - middle.x) / m;
	max.y = (max.y - middle.y) / m;
	max.z = (max.z - middle.z) / m;

	min.x = (min.x - middle.x) / m;
	min.y = (min.y - middle.y) / m;
	min.z = (min.z - middle.z) / m;

}

void CModel::middlePoint() {
	middle.x = (max.x + min.x) / 2;
	middle.y = (max.y + min.y) / 2;
	middle.z = (max.z + min.z) / 2;
}
float CModel::coordMax() {
	float m;
	m = max.x;
	if (max.y > m) {
		m = max.y;
	}
	if (max.z > m) {
		m = max.z;
	}
	return m;
}

int CModel::getDeployType()
{
	return mDisplay;
}

void CModel::setDeployType(int a)
{
	mDisplay = a;
}

void CModel::setBoundingBoxCheck(bool a)
{
	boundingBoxCheck = a;
}

bool CModel::getBoundingBoxCheck()
{
	return boundingBoxCheck;
}

void CModel::setFillCheck(bool a)
{
	fillCheck = a;
}

bool CModel::getFillCheck()
{
	return fillCheck;
}

void CModel::setWireCheck(bool a)
{
	wireCheck = a;
}

bool CModel::getWireCheck()
{
	return wireCheck;
}

void CModel::setPointCheck(bool a)
{
	pointCheck = a;
}

bool CModel::getPointCheck()
{
	return pointCheck;
}

void CModel::setColorBoundingBox(float *color)
{
	boundingBox->setColor(color);
}

float * CModel::getColorBoundingBox()
{
	return boundingBox->getColor();
}

void CModel::setNormalsFacesCheck(bool a)
{
	normalsFacesCheck = a;
}

bool CModel::getNormalsFacesCheck()
{
	return normalsFacesCheck;
}

void CModel::setNormalsVerticesCheck(bool a)
{
	normalsVerticesCheck = a;
}

bool CModel::getNormalsVerticesCheck()
{
	return normalsVerticesCheck;
}

void CModel::setColor(float *color)
{
	mColor[0] = color[0];
	mColor[1] = color[1];
	mColor[2] = color[2];
}

float * CModel::getColor()
{
	return mColor;
}

void CModel::setColorFill(float *color)
{
	mColorFill[0] = color[0];
	mColorFill[1] = color[1];
	mColorFill[2] = color[2];
}

float * CModel::getColorFill()
{
	return mColorFill;
}

void CModel::setColorPoint(float *color)
{
	mColorPoint[0] = color[0];
	mColorPoint[1] = color[1];
	mColorPoint[2] = color[2];
}

float * CModel::getColorPoint()
{
	return mColorPoint;
}

void CModel::setColorNormalsVertices(float *color)
{
	normals->setColor(color);
}

float * CModel::getColorNormalsVertices()
{
	return normals->getColor();
}

void CModel::setColorNormalsFaces(float *color)
{
	normals->setColorFaces(color);
}

float * CModel::getColorNormalsFaces()
{
	return normals->getColorFaces();
}
