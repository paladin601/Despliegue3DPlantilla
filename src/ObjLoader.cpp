#include "ObjLoader.h"



ObjLoader::ObjLoader()
{
}


ObjLoader::~ObjLoader()
{
}

bool ObjLoader::load(string path)
{
	ifstream file;
	string token, v, v1, v2;
	float f[3], car;
	int cont = 0;
	file.open(path, std::ios::in);
	mNumOfVertices = 0;
	mNumOfFaces = 0;
	while (!file.eof() ) {
		file >> token;
		if (token == "v") {
			mNumOfVertices++;
			for (int xx = 0; xx < 3; xx++) {
				file >> v;
				f[xx] = (float)atof(v.c_str());
				switch (xx)
				{
				case 0:
					if (f[xx] > max.x) {
						max.x = f[xx];
					}
					if (f[xx] < min.x) {
						min.x = f[xx];
					}
					break;
				case 1:
					if (f[xx] > max.y) {
						max.y = f[xx];
					}
					if (f[xx] < min.y) {
						min.y = f[xx];
					}
					break;
				default:
					if (f[xx] > max.z) {
						max.z = f[xx];
					}
					if (f[xx] < min.z) {
						min.z = f[xx];
					}
					break;
				}
			}
			mVertices.push_back(glm::vec3(f[0], f[1], f[2]));
		}
		else {
			if (token == "f") {
				mNumOfFaces++;
				file >> v;
				file >> v1;
				file >> v2;
				f[0] = (float)atof(v.substr(0, v.find("/")).c_str());
				f[1] = (float)atof(v1.substr(0, v1.find("/")).c_str());
				f[2] = (float)atof(v2.substr(0, v2.find("/")).c_str());
				mFaces.push_back(glm::vec3(f[0], f[1], f[2]));
			}
			else {
				getline(file, token);
			}

		}
	}
	file.close();
	middlePoint();
	normalize();
	return true;
}

void ObjLoader::display() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	for (int i = 0; i < mNumOfFaces; i++)
	{
		glBegin(GL_TRIANGLES);
		glVertex3f(mVertices[(int)mFaces[i].x-1].x, mVertices[(int)mFaces[i].x-1].y, mVertices[(int)mFaces[i].x-1].z);
		glVertex3f(mVertices[(int)mFaces[i].y-1].x, mVertices[(int)mFaces[i].y-1].y, mVertices[(int)mFaces[i].y-1].z);
		glVertex3f(mVertices[(int)mFaces[i].z-1].x, mVertices[(int)mFaces[i].z-1].y, mVertices[(int)mFaces[i].z-1].z);
		glEnd();
	}
}