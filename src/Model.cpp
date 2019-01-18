#include "Model.h"

CModel::CModel()
{
	mTranslation[0] = mTranslation[1] = mTranslation[2] = 0.0f;
}

CModel::~CModel()
{
	mVertices.clear();
}

void CModel::display()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	for (int i = 0; i < mNumOfVertices; i += 3)
	{
		glBegin(GL_TRIANGLES);
			glVertex3f(mVertices[i].x, mVertices[i].y, mVertices[i].z);
			glVertex3f(mVertices[i + 1].x, mVertices[i + 1].y, mVertices[i + 1].z);
			glVertex3f(mVertices[i + 2].x, mVertices[i + 2].y, mVertices[i + 2].z);
		glEnd();
	}
}

void CModel::setTranslation(glm::vec3 translation)
{
	mTranslation = translation;
}

glm::vec3 CModel::getTranslation()
{
	return mTranslation;
}

void CModel::normalize() {
	float m=coordMax();
	for (int i = 0; i < mNumOfVertices; i++) {
		mVertices[i].x = (mVertices[i].x - middle.x)/m;
		mVertices[i].y = (mVertices[i].y - middle.y)/m;
		mVertices[i].z = (mVertices[i].z - middle.z)/m;
	}
}

void CModel::middlePoint() {
	middle.x = max.x - min.x;
	middle.y = max.y - min.y;
	middle.z = max.z - min.z;
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