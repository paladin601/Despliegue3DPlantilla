#include "Normal.h"



Normal::Normal(vector<glm::vec3> Vertices, vector<glm::vec3> Faces, int nVertices, int nFaces)
{
	mColor[0] = mColor[1] = mColor[2] = 1.0f;
	mColorFaces[0] = mColorFaces[1] = mColorFaces[2] = 1.0f;
	numFaces = nFaces;
	numVertices = nVertices;
	glm::vec3 vec1, vec2, vec3, r1, r2, rt , rtt;
	vector<glm::vec3> rr;
	vector<int> rrt;
	glm::vec3 a = glm::vec3(0, 0, 0);
	for (int j = 0; j < numVertices; j++) {
		rr.push_back(a);
		rrt.push_back(0);
	}
	for (int i = 0; i < nFaces; i++) {
		vec1 = Vertices[(int) Faces[i].x];
		vec2 = Vertices[(int) Faces[i].y];
		vec3 = Vertices[(int) Faces[i].z];
		r1 = vec1 - vec2;
		r2 = vec1 - vec3;
		rt = glm::normalize(glm::cross(r1, r2));
		normalCaras.push_back(rt);
		rtt.x = (Vertices[(int) Faces[i].x].x + Vertices[(int) Faces[i].y].x + Vertices[(int) Faces[i].z].x) / 3.0f;
		rtt.y = (Vertices[(int) Faces[i].x].y + Vertices[(int) Faces[i].y].y + Vertices[(int) Faces[i].z].y) / 3.0f;
		rtt.z = (Vertices[(int) Faces[i].x].z + Vertices[(int) Faces[i].y].z + Vertices[(int) Faces[i].z].z) / 3.0f;
		facesCenter.push_back(rtt);
		rr[(int)Faces[i].x] += rtt;
		rr[(int)Faces[i].y] += rtt;
		rr[(int)Faces[i].z] += rtt;
		rrt[(int)Faces[i].x] += 1;
	}
	for (int j = 0; j < numVertices; j++) {
		rr[j] /=rrt[j];
		normalVertices.push_back(rr[j]);
	}
	createListFaces();
	createList(Vertices);
}


Normal::~Normal()
{
}

void Normal::displayNormalVertices()
{
	glColor3fv(mColor);
	glCallList(list);
}

void Normal::displayNormalFaces()
{
	glColor3fv(mColorFaces);
	glCallList(listFaces);	
}

void Normal::createList(vector<glm::vec3> vertices)
{
	list = glGenLists(1);
	glNewList(list, GL_COMPILE);

	glBegin(GL_LINES);
	for (int i = 0; i < numVertices; i++) {
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
		glVertex3f(normalVertices[i].x, normalVertices[i].y, normalVertices[i].z);
	}
	glEnd();

	glEndList();

}

void Normal::createListFaces()
{
	listFaces = glGenLists(1);
	glNewList(listFaces, GL_COMPILE);

	glBegin(GL_LINES);
	for (int i = 0; i < numFaces; i++) {
		glVertex3f(facesCenter[i].x, facesCenter[i].y, facesCenter[i].z);
		glVertex3f(facesCenter[i].x + normalCaras[i].x, facesCenter[i].y + normalCaras[i].y, facesCenter[i].z + normalCaras[i].z);
	}
	glEnd();

	glEndList();

}

void Normal::setColor(float* color)
{
	mColor[0] = color[0];
	mColor[1] = color[1];
	mColor[2] = color[2];
}

float * Normal::getColor()
{
	return mColor;
}

void Normal::setColorFaces(float* color)
{
	mColorFaces[0] = color[0];
	mColorFaces[1] = color[1];
	mColorFaces[2] = color[2];
}

float * Normal::getColorFaces()
{
	return mColorFaces;
}
