#include "BoundingBox.h"



BoundingBox::BoundingBox(glm::vec3 min, glm::vec3 max)
{
	mColor[0] = 1.0f;
	mColor[1] = mColor[2] = 0.0f;
	min.x -= 0.01f;
	min.y -= 0.01f;
	min.z -= 0.01f;
	max.x += 0.01f;
	max.y += 0.01f;
	max.z += 0.01f;
	mVertices.push_back(min);
	mVertices.push_back(glm::vec3(min.x, max.y, min.z));
	mVertices.push_back(glm::vec3(max.x, max.y, min.z));
	mVertices.push_back(glm::vec3(max.x, min.y, min.z));

	mVertices.push_back(glm::vec3(min.x, min.y, max.z));
	mVertices.push_back(glm::vec3(min.x, max.y, max.z));
	mVertices.push_back(max);
	mVertices.push_back(glm::vec3(max.x, min.y, max.z));
	createList();
}


BoundingBox::~BoundingBox()
{
}

void BoundingBox::display()
{
	glColor3fv(mColor);
	glBegin(GL_LINES);
	glVertex3f(mVertices[0].x, mVertices[0].y, mVertices[0].z);
	glVertex3f(mVertices[1].x, mVertices[1].y, mVertices[1].z);

	glVertex3f(mVertices[1].x, mVertices[1].y, mVertices[1].z);
	glVertex3f(mVertices[2].x, mVertices[2].y, mVertices[2].z);

	glVertex3f(mVertices[2].x, mVertices[2].y, mVertices[2].z);
	glVertex3f(mVertices[3].x, mVertices[3].y, mVertices[3].z);

	glVertex3f(mVertices[3].x, mVertices[3].y, mVertices[3].z);
	glVertex3f(mVertices[0].x, mVertices[0].y, mVertices[0].z);

	glVertex3f(mVertices[0].x, mVertices[0].y, mVertices[0].z);
	glVertex3f(mVertices[4].x, mVertices[4].y, mVertices[4].z);

	glVertex3f(mVertices[1].x, mVertices[1].y, mVertices[1].z);
	glVertex3f(mVertices[5].x, mVertices[5].y, mVertices[5].z);

	glVertex3f(mVertices[2].x, mVertices[2].y, mVertices[2].z);
	glVertex3f(mVertices[6].x, mVertices[6].y, mVertices[6].z);

	glVertex3f(mVertices[3].x, mVertices[3].y, mVertices[3].z);
	glVertex3f(mVertices[7].x, mVertices[7].y, mVertices[7].z);

	glVertex3f(mVertices[4].x, mVertices[4].y, mVertices[4].z);
	glVertex3f(mVertices[5].x, mVertices[5].y, mVertices[5].z);

	glVertex3f(mVertices[5].x, mVertices[5].y, mVertices[5].z);
	glVertex3f(mVertices[6].x, mVertices[6].y, mVertices[6].z);

	glVertex3f(mVertices[6].x, mVertices[6].y, mVertices[6].z);
	glVertex3f(mVertices[7].x, mVertices[7].y, mVertices[7].z);

	glVertex3f(mVertices[7].x, mVertices[7].y, mVertices[7].z);
	glVertex3f(mVertices[4].x, mVertices[4].y, mVertices[4].z);

	glEnd();
}

void BoundingBox::displayList()
{
	glColor3fv(mColor);
	glCallList(list);
}

void BoundingBox::createList()
{
	list = glGenLists(1);
	glNewList(list, GL_COMPILE);

		glBegin(GL_LINES);
		glVertex3f(mVertices[0].x, mVertices[0].y, mVertices[0].z);
		glVertex3f(mVertices[1].x, mVertices[1].y, mVertices[1].z);

		glVertex3f(mVertices[1].x, mVertices[1].y, mVertices[1].z);
		glVertex3f(mVertices[2].x, mVertices[2].y, mVertices[2].z);

		glVertex3f(mVertices[2].x, mVertices[2].y, mVertices[2].z);
		glVertex3f(mVertices[3].x, mVertices[3].y, mVertices[3].z);

		glVertex3f(mVertices[3].x, mVertices[3].y, mVertices[3].z);
		glVertex3f(mVertices[0].x, mVertices[0].y, mVertices[0].z);

		glVertex3f(mVertices[0].x, mVertices[0].y, mVertices[0].z);
		glVertex3f(mVertices[4].x, mVertices[4].y, mVertices[4].z);

		glVertex3f(mVertices[1].x, mVertices[1].y, mVertices[1].z);
		glVertex3f(mVertices[5].x, mVertices[5].y, mVertices[5].z);

		glVertex3f(mVertices[2].x, mVertices[2].y, mVertices[2].z);
		glVertex3f(mVertices[6].x, mVertices[6].y, mVertices[6].z);

		glVertex3f(mVertices[3].x, mVertices[3].y, mVertices[3].z);
		glVertex3f(mVertices[7].x, mVertices[7].y, mVertices[7].z);

		glVertex3f(mVertices[4].x, mVertices[4].y, mVertices[4].z);
		glVertex3f(mVertices[5].x, mVertices[5].y, mVertices[5].z);

		glVertex3f(mVertices[5].x, mVertices[5].y, mVertices[5].z);
		glVertex3f(mVertices[6].x, mVertices[6].y, mVertices[6].z);

		glVertex3f(mVertices[6].x, mVertices[6].y, mVertices[6].z);
		glVertex3f(mVertices[7].x, mVertices[7].y, mVertices[7].z);

		glVertex3f(mVertices[7].x, mVertices[7].y, mVertices[7].z);
		glVertex3f(mVertices[4].x, mVertices[4].y, mVertices[4].z);

		glEnd();

	glEndList();

}

void BoundingBox::setColor(float* color)
{
	mColor[0] = color[0];
	mColor[1] = color[1];
	mColor[2] = color[2];
}

float * BoundingBox::getColor()
{
	return mColor;
}
