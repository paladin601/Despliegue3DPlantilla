#include "Model.h"

CModel::CModel()
{
	mTranslation[0] = mTranslation[1] = mTranslation[2] = 0.0f;
	mScale[0] = mScale[1] = mScale[2] = 1;
	mRotation[0] = mRotation[1] = mRotation[2] = 0;
	mDisplay = 1;
}

CModel::~CModel()
{
	mVertices.clear();
}

void CModel::display()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
}

void CModel::middlePoint() {
	middle.x = (max.x - min.x) / 2;
	middle.y = (max.y - min.y) / 2;
	middle.z = (max.z - min.z) / 2;
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
