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
int picked,pickedLight;
bool backFace = false;
bool camera = false;
bool ZBuffer = true;
bool light = false;
bool flat = false;


GLfloat no_mat[] =				{ 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat mat_ambient[] =			{ 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat mat_ambient_color[] =	{ 0.8f, 0.8f, 0.2f, 1.0f };
GLfloat mat_diffuse[] =			{ 0.1f, 0.5f, 0.8f, 1.0f };
GLfloat mat[] =					{ 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat mat_emission[] =		{ 0.3f, 0.2f, 0.2f, 0.0f };
GLfloat no_shininess[] =		{ 0.0f };
GLfloat low_shininess[] =		{ 5.0f };
GLfloat high_shininess[] =		{ 100.0f };

GLfloat ambient[] =  { 0.4f, 0.4f, 0.4f, 1.0f };
GLfloat diffuse[] =  { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat position[] = { 0.0f, 3.0f, 2.0f, 0.0f };

GLfloat ambient2[] = { 0.4f, 0.2f, 0.4f, 1.0f };
GLfloat diffuse2[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat specular2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat position2[] = { 2.0f, 3.0f, 0.0f, 0.0f };

GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat light_diffuse[] = { 0.6f, 0.6f, 0.6f, 1.0f };
GLfloat light_specular[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat light_position[] = { 15.0f, 15.0f, 15.0f, 10.0f };
GLfloat light_direction[] = { 0.0f, 0.0f, 0.0f };
GLfloat shininess =  15.0f;


void updateUserInterface()
{
	int a = userInterface->getPicked();
	bool abackFace = userInterface->getBackFaceCheck();
	bool aZBuffer = userInterface->getZBufferCheck();
	bool acamera = userInterface->getCameraCheck();
	bool alight = userInterface->getLightsCheck();
	bool aflat = userInterface->getFlatCheck();
	
	if (abackFace != backFace || acamera != camera || aZBuffer != ZBuffer || alight != light || aflat!=flat) {
		backFace = abackFace;
		camera = acamera;
		ZBuffer = aZBuffer;
		light = alight;
		flat = aflat;
		change_view();
	}
	int aux = userInterface->getLightPicked();
	if (aux != pickedLight) {
		pickedLight = aux;
		switch (pickedLight)
		{
		case 0:
			userInterface->setLightPosition(position);
			userInterface->setLightAmbient(ambient);
			userInterface->setLightDiffuse(diffuse);
			userInterface->setLightSpecular(specular);
			break;
		case 1:
			userInterface->setLightPosition(position2);
			userInterface->setLightAmbient(ambient2);
			userInterface->setLightDiffuse(diffuse2);
			userInterface->setLightSpecular(specular2);
			break;
		}
	}
	else {
		changeLight();
	}

	if (a == picked) {
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

void changeLight() {
	GLfloat *a;
	switch (pickedLight)
	{
	case 0:
		a =userInterface->getLightPosition();
		position[0] = a[0];
		position[1] = a[1];
		position[2] = a[2];
		a=userInterface->getLightAmbient();
		ambient[0] = a[0];
		ambient[1] = a[1];
		ambient[2] = a[2];
		a=userInterface->getLightDiffuse();
		diffuse[0] = a[0];
		diffuse[1] = a[1];
		diffuse[2] = a[2];
		a=userInterface->getLightSpecular();
		specular[0] = a[0];
		specular[1] = a[1];
		specular[2] = a[2];
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT0, GL_POSITION, position);
		glLightf(GL_LIGHT0, GL_SHININESS, shininess);
		break;
	case 1:
		a = userInterface->getLightPosition();
		position2[0] = a[0];
		position2[1] = a[1];
		position2[2] = a[2];
		a = userInterface->getLightAmbient();
		ambient2[0] = a[0];
		ambient2[1] = a[1];
		ambient2[2] = a[2];
		a = userInterface->getLightDiffuse();
		diffuse2[0] = a[0];
		diffuse2[1] = a[1];
		diffuse2[2] = a[2];
		a = userInterface->getLightSpecular();
		specular2[0] = a[0];
		specular2[1] = a[1];
		specular2[2] = a[2];
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient2);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse2);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular2);
		glLightfv(GL_LIGHT1, GL_POSITION, position2);
		glLightf(GL_LIGHT1, GL_SHININESS, shininess);
		break;
	}
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
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
	if (flat) {
		glShadeModel(GL_SMOOTH);
	}
	else {
		glShadeModel(GL_FLAT);
	}

	if (light) {

		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
	}
	else {
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHTING);
		glDisable(GL_COLOR_MATERIAL);
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
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
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

	change_view();
	changeLight();

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
	ObjLoader* objLoader = new ObjLoader();

	if (!objLoader->load("../files/Umbrella.obj"))
		return false;

	models.push_back(objLoader);
	return true;
}

int main(void)
{
	gWidth = 1600;
	gHeight = 900;
	picked = 0;
	pickedLight = 0;

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