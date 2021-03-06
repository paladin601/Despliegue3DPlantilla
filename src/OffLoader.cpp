#include "OffLoader.h"
#include "Model.h"


OffLoader::OffLoader()
{

}


OffLoader::~OffLoader()
{
}

bool OffLoader::load(string path)
{
	fstream file;
	string token, v1, v2, v3;
	float f1, f2, f3,car;
	int cont = 0;
	file.open(path, std::ios::in);

	file >> token;

	if (token != "OFF")
	{
		file.close();
		return false;
	}
	else
	{
		file >> token;
		mNumOfVertices = atoi(token.c_str());
		file >> token;
		mNumOfFaces = atoi(token.c_str());
		file >> token;

		for (int i = 0; i < mNumOfVertices; i++)
		{
			file >> v1;
			f1 = (float)atof(v1.c_str());
			file >> v2;
			f2 = (float)atof(v2.c_str());
			file >> v3;
			f3 = (float)atof(v3.c_str());
			if (f1 > max.x) {
				max.x = f1;
			}
			if (f2 > max.y) {
				max.y = f2;
			}
			if (f3 > max.z) {
				max.z = f3;
			}

			if (f1 < min.x) {
				min.x = f1;
			}
			if (f2 < min.y) {
				min.y = f2;
			}
			if (f3 < min.z) {
				min.z = f3;
			}
			mVertices.push_back(glm::vec3(f1, f2, f3));
		}
		for (int i = 0; i < mNumOfFaces; i++)
		{
			file >> token;
			car=(float)atof(token.c_str());
			car -= 2;
			file >> v1;
			f1 = (float)atof(v1.c_str());
			file >> v2;
			f2 = (float)atof(v2.c_str());
			for (int j = 0; j < car; j++) {
				file >> v3;
				f3 = (float)atof(v3.c_str());
				mFaces.push_back(glm::vec3(f1, f2, f3));
				f2 = f3; 
				cont++;
			}
			getline(file, token);
		}
		mNumOfFaces = cont;
		file.close();
		normals = new Normal(mVertices, mFaces, mNumOfVertices, mNumOfFaces);
		middlePoint();
		normalize();
		createList();
		boundingBox = new BoundingBox(min, max);
		return true;
	}
}

