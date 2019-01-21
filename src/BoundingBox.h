#include "../headers/glm/glm.hpp"
#include "../headers/glfw3.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
using std::string;
using std::vector;

class BoundingBox
{
protected:
	vector<glm::vec3> mVertices;
	float mColor[3];
	GLuint list;
public:
	BoundingBox(glm::vec3,glm::vec3);
	~BoundingBox();
	void display();
	void displayList();
	void createList();
	void setColor(float *);
	float* getColor();
};

