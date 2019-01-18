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
	float m;
	for (int i = 0; i < mNumOfVertices; i++) {

		mVertices[i].x = (mVertices[i].x - middle.x);
		mVertices[i].y = (mVertices[i].y - middle.y);
		mVertices[i].z = (mVertices[i].z - middle.z);

	}
}

void CModel::middlePoint() {
	middle.x = (max.x - min.x) / 2;
	middle.y = (max.y - min.y) / 2;
	middle.z = (max.z - min.z) / 2;
}