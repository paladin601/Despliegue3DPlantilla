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
bool backFace = false;
bool camera = false;
bool ZBuffer = true;

void updateUserInterface()
{
	int a = userInterface->getPicked();
	bool abackFace = userInterface->getBackFaceCheck();
	bool aZBuffer = userInterface->getZBufferCheck();
	bool acamera = userInterface->getCameraCheck();
	if (abackFace != backFace || acamera != camera || aZBuffer != ZBuffer) {
		backFace = abackFace;
		camera = acamera;
		ZBuffer =aZBuffer;
		change_view();
	}

	if (a==picked) {
		models[picked]->setTranslation(userInterface->getTranslation());
		models[picked]->setScale(userInterface->getScale());
		models[picked]->setRotation(userInterface->getRotation());

		models[picked]->setWireCheck(userInterface->getWireCheck());
		models[picked]->setPointCheck(userInterface->getPointCheck());
		models[picked]->setFillCheck(userInterface->getFillCheck());
		models[picked]->setBoundingBoxCheck(userInterface->getBoundingBoxCheck());

		models[picked]->setColor(userInterface->getColor());
		models[picked]->setColorFill(userInterface->getColorFill());
		models[picked]->setColorPoint(userInterface->getColorPoint());
		models[picked]->setColorBoundingBox(userInterface->getColorBoundingBox());

		models[picked]->setNormalsFacesCheck(userInterface->getNormalsFacesCheck());
		models[picked]->setColorNormalsFaces(userInterface->getColorNormalsFaces());
		models[picked]->setNormalsVerticesCheck(userInterface->getNormalsVerticesCheck());
		models[picked]->setColorNormalsVertices(userInterface->getColorNormalsVertices());


		models[picked]->setDeployType(userInterface->getDeployType());

	}
	else {
		models[picked]->setBoundingBoxCheck(false);
		picked = a;
		userInterface->setTranslation(models[picked]->getTranslation());
		userInterface->setScale(models[picked]->getScale());
		userInterface->setRotation(models[picked]->getRotation());
		userInterface->setWireCheck(models[picked]->getWireCheck());
		userInterface->setPointCheck(models[picked]->getPointCheck());
		userInterface->setFillCheck(models[picked]->getFillCheck());
		userInterface->setBoundingBoxCheck(models[picked]->getBoundingBoxCheck());
		userInterface->setColor(models[picked]->getColor());
		userInterface->setColorFill(models[picked]->getColorFill());
		userInterface->setColorPoint(models[picked]->getColorPoint());
		userInterface->setColorBoundingBox(models[picked]->getColorBoundingBox());
		userInterface->setNormalsFacesCheck(models[picked]->getNormalsFacesCheck());
		userInterface->setColorNormalsFaces(models[picked]->getColorNormalsFaces());
		userInterface->setNormalsVerticesCheck(models[picked]->getNormalsVerticesCheck());
		userInterface->setColorNormalsVertices(models[picked]->getColorNormalsVertices());
		userInterface->setDeployType(models[picked]->getDeployType());
	}

}

void change_view() {
	if (camera) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-(float)gWidth / 100.0f, (float)gWidth / 100.0f, -(float)gHeight / 100.0f, (float)gHeight / 100.0f, 0.01f, 100.0f);

		glMatrixMode(GL_MODELVIEW);
	}
	else {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (float)gWidth / (float)gHeight, 1.0f, 1000.0f);

		glMatrixMode(GL_MODELVIEW);
	}

	if (backFace) {
		glEnable(GL_CULL_FACE);
	}
	else {
		glDisable(GL_CULL_FACE);
	}

	if (ZBuffer) {
		glEnable(GL_DEPTH_TEST);
	}
	else {
		glDisable(GL_DEPTH_TEST);
	}
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
		GLfloat matriz[16] = {
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
		};
		glPushMatrix();
		glScalef(scale.x, scale.y, scale.z);
		getMatriz4x4(rotation, matriz);
		glMultMatrixf(matriz);
		glTranslatef(translation.x, translation.y, translation.z);

		models[i]->display();
		glPopMatrix();
	}

}

void getMatriz4x4(glm::vec4 quat, float *mat)
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

	mat[0] = -yy2 - zz2 + 1.0f;
	mat[1] = xy2 + wz2;
	mat[2] = xz2 - wy2;
	mat[4] = xy2 - wz2;
	mat[5] = -xx2 - zz2 + 1.0f;
	mat[6] = yz2 + wx2;
	mat[8] = xz2 + wy2;
	mat[9] = yz2 - wx2;
	mat[10] = -xx2 - yy2 + 1.0f;

	mat[3] = mat[7] = mat[11] = mat[12] = mat[13] = mat[14] = 0;
	mat[15] = 1;
}

void reshape(GLFWwindow *window, int width, int height)
{
	gWidth = width;
	gHeight = height;

	glViewport(0, 0, gWidth, gHeight);

	userInterface->reshape();

	if (camera) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-(float)gWidth / 100.0f, (float)gWidth / 100.0f, -(float)gHeight / 100.0f, (float)gHeight / 100.0f, 0.01f, 100.0f);

		glMatrixMode(GL_MODELVIEW);
	}
	else {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (float)gWidth / (float)gHeight, 1.0f, 1000.0f);

		glMatrixMode(GL_MODELVIEW);
	}

	if (backFace) {
		glEnable(GL_CULL_FACE);
	}
	else {
		glDisable(GL_CULL_FACE);
	}
	if (ZBuffer) {
		glEnable(GL_DEPTH_TEST);
	}
	else {
		glDisable(GL_DEPTH_TEST);
	}

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
	if (!soff->load("../files/cube.soff"))
		return false;

	if (!offLoader->load("../files/Umbrella.obj"))
		return false;

	models.push_back(offLoader);
	return true;
}

int main(void)
{
	gWidth = 1600;
	gHeight = 900;
	picked = 0;

	if (!initGlfw() || !initScene() || !initUserInterface())
		return EXIT_FAILURE;

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