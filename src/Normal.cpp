#include "Normal.h"



Normal::Normal(vector<glm::vec3> Vertices, vector<glm::vec3> Faces, int nVertices, int nFaces)
{
	mColor[0] = mColor[1] = mColor[2] = 1.0f;
	mColorFaces[0] = mColorFaces[1] = mColorFaces[2] = 1.0f;
	numFaces = nFaces;
	numVertices = nVertices;
	glm::vec3 vec1, vec2, vec3, r1, r2, normal, center;
	vector<glm::vec3> prom;
	vector<int> cont;
	glm::vec3 a = glm::vec3(0, 0, 0);
	for (int j = 0; j < numVertices; j++) {
		prom.push_back(a);
		cont.push_back(0);
	}
	for (int i = 0; i < numFaces; i++) {
		cont[(int)Faces[i].x] += 1;
		cont[(int)Faces[i].y] += 1;
		cont[(int)Faces[i].z] += 1;
		r1 = Vertices[(int)Faces[i].y] - Vertices[(int)Faces[i].x];
		r2 = Vertices[(int)Faces[i].z] - Vertices[(int)Faces[i].x];
		normal = glm::normalize(glm::cross(r1, r2));
		
		prom[(int)Faces[i].x].x += normal.x;
		prom[(int)Faces[i].x].y += normal.y;
		prom[(int)Faces[i].x].z += normal.z;
		prom[(int)Faces[i].y].x += normal.x;
		prom[(int)Faces[i].y].y += normal.y;
		prom[(int)Faces[i].y].z += normal.z;
		prom[(int)Faces[i].z].x += normal.x;
		prom[(int)Faces[i].z].y += normal.y;
		prom[(int)Faces[i].z].z += normal.z;
		normalCaras.push_back(normal);
		center.x = (Vertices[(int)Faces[i].x].x + Vertices[(int)Faces[i].y].x + Vertices[(int)Faces[i].z].x) / 3.0f;
		center.y = (Vertices[(int)Faces[i].x].y + Vertices[(int)Faces[i].y].y + Vertices[(int)Faces[i].z].y) / 3.0f;
		center.z = (Vertices[(int)Faces[i].x].z + Vertices[(int)Faces[i].y].z + Vertices[(int)Faces[i].z].z) / 3.0f;
		facesCenter.push_back(center);
	}
	for (int j = 0; j < numVertices; j++) {
		prom[j].x /= (float)cont[j];
		prom[j].y /= (float)cont[j];
		prom[j].z /= (float)cont[j];
		normalVertices.push_back(prom[j]);
	}
	createList(Vertices);
	createListFaces();
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
		glVertex3f(vertices[i].x + normalVertices[i].x, vertices[i].y + normalVertices[i].y, vertices[i].z + normalVertices[i].z);
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

void Normal::displayNormalVerticesglm(int i)
{
	glNormal3f(normalVertices[i].x, normalVertices[i].y, normalVertices[i].z);
}

void Normal::displayNormalFacesglm(int i)
{
	glNormal3f(normalCaras[i].x, normalCaras[i].y, normalCaras[i].z);
}
