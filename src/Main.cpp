#include "Main.h"
#include "Model.h"
#include "SOff.h"
#include "OffLoader.h"
#include "ObjLoader.h"
#include "UserInterface.h"
#include <iostream> 
#include <fstream> 
using namespace std;
using std::vector;

GLFWwindow *gWindow;
int gWidth, gHeight;
CUserInterface * userInterface;
vector <CModel *> models;
int picked;

void updateUserInterface()
{
	if (picked > -1)
		models[picked]->setTranslation(userInterface->getModelTranslation());
		models[picked]->setScale(userInterface->getModelScale());
		models[picked]->setRotation(userInterface->getModelRotation());
		models[picked]->setDeployType(userInterface->getDeployType());

}

void display()
{
	glClearColor(0.25f, 0.25f, 0.25f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	for (unsigned int i = 0; i < models.size(); i++)
	{
		glm::vec3 translation = models[i]->getTranslation();
		glm::vec3 scale = models[i]->getScale();
		glm::vec4 rotation = models[i]->getRotation();
		//GLfloat matriz[16];
		glPushMatrix();
		glScalef(scale.x, scale.y, scale.z);
		glTranslatef(translation.x, translation.y, translation.z);
		//ConvertQuaternionToMatrix(rotation, matriz);
		//glMultMatrixf(matriz);

		models[i]->display();
		glPopMatrix();
	}

}

void ConvertQuaternionToMatrix(glm::vec4 quat, float *mat)
{
	float yy2 = 2.0f * quat[1] * quat[1];
	float xy2 = 2.0f * quat[0] * quat[1];
	float xz2 = 2.0f * quat[0] * quat[2];
	float yz2 = 2.0f * quat[1] * quat[2];
	float zz2 = 2.0f * quat[2] * quat[2];
	float wz2 = 2.0f * quat[3] * quat[2];
	float wy2 = 2.0f * quat[3] * quat[1];
	float wx2 = 2.0f * quat[3] * quat[0];
	float xx2 = 2.0f * quat[0] * quat[0];
	mat[0 * 4 + 0] = -yy2 - zz2 + 1.0f;
	mat[0 * 4 + 1] = xy2 + wz2;
	mat[0 * 4 + 2] = xz2 - wy2;
	mat[0 * 4 + 3] = 0;
	mat[1 * 4 + 0] = xy2 - wz2;
	mat[1 * 4 + 1] = -xx2 - zz2 + 1.0f;
	mat[1 * 4 + 2] = yz2 + wx2;
	mat[1 * 4 + 3] = 0;
	mat[2 * 4 + 0] = xz2 + wy2;
	mat[2 * 4 + 1] = yz2 - wx2;
	mat[2 * 4 + 2] = -xx2 - yy2 + 1.0f;
	mat[2 * 4 + 3] = 0;
	mat[3 * 4 + 0] = mat[3 * 4 + 1] = mat[3 * 4 + 2] = 0;
	mat[3 * 4 + 3] = 1;
}

void reshape(GLFWwindow *window, int width, int height)
{
	gWidth = width;
	gHeight = height;

	glViewport(0, 0, gWidth, gHeight);

	userInterface->reshape();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)gWidth / (float)gHeight, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
}

void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (TwEventKeyGLFW(key, action))
		return;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		}
	}
}

void mouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (TwEventMouseButtonGLFW(button, action))
		return;
}

void cursorPos(GLFWwindow* window, double x, double y)
{
	if (TwEventMousePosGLFW(int(x), int(y)))
		return;
}

void charInput(GLFWwindow* window, unsigned int scanChar)
{
	if (TwEventCharGLFW(scanChar, GLFW_PRESS))
		return;
}

void destroy()
{
	for (unsigned int i = 0; i < models.size(); i++)
		delete models[i];

	delete userInterface;

	TwTerminate();
	glfwDestroyWindow(gWindow);
	glfwTerminate();
}

bool initGlfw()
{
	if (!glfwInit())
		return false;

	gWindow = glfwCreateWindow(gWidth, gHeight, "Chapter 2", NULL, NULL);

	if (!gWindow)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(gWindow);

	const GLFWvidmode * vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(gWindow, (vidMode->width - gWidth) >> 1, (vidMode->height - gHeight) >> 1);

	glfwSetWindowSizeCallback(gWindow, reshape);
	glfwSetKeyCallback(gWindow, keyInput);
	glfwSetMouseButtonCallback(gWindow, mouseButton);
	glfwSetCursorPosCallback(gWindow, cursorPos);
	glfwSetCharCallback(gWindow, charInput);

	return true;
}

bool initUserInterface()
{
	if (!TwInit(TW_OPENGL, NULL))
		return false;

	userInterface = CUserInterface::Instance();

	return true;
}

bool initScene()
{
	ObjLoader* offLoader = new ObjLoader();

	CSOff* soff = new CSOff();
	if(!soff->load("../files/cube.soff"))
		return false;

	if (!offLoader->load("../files/Batman.obj"))
		return false;

	models.push_back(offLoader);
	return true;
}

int main(void)
{
	gWidth = 1200;
	gHeight = 680;
	picked = 0;

	if (!initGlfw() || !initScene() || !initUserInterface())
		return EXIT_FAILURE;

	glEnable(GL_DEPTH_TEST);

	reshape(gWindow, gWidth, gHeight);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3.0f, 3.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	while (!glfwWindowShouldClose(gWindow))
	{

		display();

		TwDraw();

		updateUserInterface();

		glfwSwapBuffers(gWindow);

		glfwPollEvents();
	}

	destroy();

	return EXIT_SUCCESS;
}

void beginLoad(string path) {

	string aux = path;
	string extension = aux.erase(0, aux.find(".") + 1);

	/*if (extension == "soff" || extension == "SOFF") {
		CSOff* coff = new CSOff();
		if (!coff->load(path))
			return;
		models.push_back(coff);
	}
	else*/
	if (extension == "off" || extension == "OFF") {
		OffLoader* offLoader = new OffLoader();
		if (!offLoader->load(path))
			return;
		models.push_back(offLoader);
	}
	else if (extension == "obj" || extension == "OBJ") {
		ObjLoader* objLoader = new ObjLoader();
		if (!objLoader->load(path))
			return;
		models.push_back(objLoader);
	}
}