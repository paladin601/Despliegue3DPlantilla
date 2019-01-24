#include "UserInterface.h"
#include "Windows.h"


extern int gWidth, gHeight;
void TW_CALL CallbackLoad(void *clientData);
string loadPath();
void beginLoad(string path);

// Global static pointer used to ensure a single instance of the class.
CUserInterface * CUserInterface::mInterface = NULL;

/**
* Creates an instance of the class
*
* @return the instance of this class
*/
CUserInterface * CUserInterface::Instance()
{
	if (!mInterface)   // Only allow one instance of class to be generated.
		mInterface = new CUserInterface();

	return mInterface;
}

CUserInterface::CUserInterface()
{
	pick = 0;
	mUserInterface = TwNewBar("Model");
	m_currentDeploy = DISPLAY_LIST;
	TwDefine("Model refresh = '0.0001f'");
	TwDefine("Model resizable = true");
	TwDefine("Model fontresizable = false");
	TwDefine("Model movable = false");
	TwDefine("Model position = '20 20'");
	TwDefine("Model size = '300 700'");
	mFillColor[0] = mFillColor[1] = mFillColor[2] = 1.0f;
	mPointColor[0] = mPointColor[1] = mPointColor[2] = 1.0f;
	mModelColor[0] = mModelColor[1] = mModelColor[2] = 1.0f;
	mNormalsFacesColor[0] = mNormalsFacesColor[1] = mNormalsFacesColor[2] = 1.0f;
	mNormalsVerticesColor[0] = mNormalsVerticesColor[1] = mNormalsVerticesColor[2] = 1.0f;
	mBoundingBoxColor[0] = 1.0f;
	mBoundingBoxColor[1] = mBoundingBoxColor[2] = 0.0f;
	mModelTranslation[0] = mModelTranslation[1] = mModelTranslation[2] = 0.0f;
	mModelScale[0] = mModelScale[1] = mModelScale[2] = 3;
	mModelRotation[0] = mModelRotation[1] = mModelRotation[2] = 0;
	mModelRotation[3] = 1;
	zBuffer = fillCheck = boundingBoxCheck = true;
	flat = light=camera = backFace = false;
	pickLight = 0;
	ambient[0] = ambient[1] = ambient[2] = 0.4f;
	diffuse[0]= diffuse[1]= diffuse[2]=diffuse[3] =ambient[3]= 1.0f;
	specular[0] = specular[1] = specular[2] = specular[3] =  1.0f;
	position[0] = position[3] = 0.0f;
	position[1] = 3.0f;
	position[2] = 2.0f;

	normalsFacesCheck = normalsVerticesCheck = pointCheck = wireCheck = false;

	TwEnumVal DeployType[] = { { GL_BEGIN_GL_END, "Gl Begin / Gl End" },{ DISPLAY_LIST, "Display List" },{ VERTEX_POINTER, "Vertex Pointer" },{ VBO, "VBO" } };
	TwType DeployTwType = TwDefineEnum("DeployType", DeployType, 4);
	TwAddVarRW(mUserInterface, "Deploy", DeployTwType, &m_currentDeploy, NULL);

	TwAddSeparator(mUserInterface, "", NULL);
	TwAddButton(mUserInterface, "Load", CallbackLoad, NULL, NULL);

	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "Figure", TW_TYPE_INT32, &pick, "group='Pick' min='0'");
	TwAddSeparator(mUserInterface, "", NULL);

	TwAddVarRW(mUserInterface, "Orthographic Camera", TW_TYPE_BOOLCPP, &camera, "group='Disabled - Enabled'");
	TwAddVarRW(mUserInterface, "BackFace", TW_TYPE_BOOLCPP, &backFace, "group='Disabled - Enabled'");
	TwAddVarRW(mUserInterface, "ZBuffer", TW_TYPE_BOOLCPP, &zBuffer, "group='Disabled - Enabled'");

	
	TwAddVarRW(mUserInterface, "Enabled", TW_TYPE_BOOLCPP, &light, "group='Lights'");
	TwAddVarRW(mUserInterface, "Flat", TW_TYPE_BOOLCPP, &flat, "group='Lights'");
	TwAddVarRW(mUserInterface, "Lights Select", TW_TYPE_INT32, &pickLight, "group='Lights' min='0' max='1'");
	TwAddSeparator(mUserInterface, "", " group='Lights'");
	TwAddVarRW(mUserInterface, "LX", TW_TYPE_FLOAT, &position[0], " group='Lights' step=0.01 min=-500.0 max=500.0");
	TwAddVarRW(mUserInterface, "LY", TW_TYPE_FLOAT, &position[1], " group='Lights' step=0.01 min=-500.0 max=500.0");
	TwAddVarRW(mUserInterface, "LZ", TW_TYPE_FLOAT, &position[2], " group='Lights' step=0.01 min=-500.0 max=500.0");
	TwAddSeparator(mUserInterface, "", " group='Lights'");
	TwAddVarRW(mUserInterface, "Ambient X", TW_TYPE_FLOAT, &ambient[0], " group='Lights' step=0.1 min=0 max=1");
	TwAddVarRW(mUserInterface, "Ambient Y", TW_TYPE_FLOAT, &ambient[1], " group='Lights' step=0.1 min=0 max=1");
	TwAddVarRW(mUserInterface, "Ambient Z", TW_TYPE_FLOAT, &ambient[2], " group='Lights' step=0.1 min=0 max=1");
	TwAddSeparator(mUserInterface, "", " group='Lights'");
	TwAddVarRW(mUserInterface, "Diffuse X", TW_TYPE_FLOAT, &diffuse[0], " group='Lights' step=0.1 min=0 max=1");
	TwAddVarRW(mUserInterface, "Diffuse Y", TW_TYPE_FLOAT, &diffuse[1], " group='Lights' step=0.1 min=0 max=1");
	TwAddVarRW(mUserInterface, "Diffuse Z", TW_TYPE_FLOAT, &diffuse[2], " group='Lights' step=0.1 min=0 max=1");
	TwAddSeparator(mUserInterface, "", " group='Lights'");
	TwAddVarRW(mUserInterface, "Specular X", TW_TYPE_FLOAT, &specular[0], " group='Lights' step=0.1 min=0 max=1");
	TwAddVarRW(mUserInterface, "Specular Y", TW_TYPE_FLOAT, &specular[1], " group='Lights' step=0.1 min=0 max=1");
	TwAddVarRW(mUserInterface, "Specular Z", TW_TYPE_FLOAT, &specular[2], " group='Lights' step=0.1 min=0 max=1");

	TwAddVarRW(mUserInterface, "Display Faces", TW_TYPE_BOOLCPP, &normalsFacesCheck, "group='Normals'");
	TwAddVarRW(mUserInterface, "Color Faces", TW_TYPE_COLOR3F, &mNormalsFacesColor, " group='Normals'");
	TwAddSeparator(mUserInterface, "", " group='Normals'");
	TwAddVarRW(mUserInterface, "Display Vertices", TW_TYPE_BOOLCPP, &normalsVerticesCheck, "group='Normals'");
	TwAddVarRW(mUserInterface, "Color Vertices", TW_TYPE_COLOR3F, &mNormalsVerticesColor, " group='Normals'");

	TwAddVarRW(mUserInterface, "Display", TW_TYPE_BOOLCPP, &boundingBoxCheck, "group='Bounding Box'");
	TwAddVarRW(mUserInterface, "Color", TW_TYPE_COLOR3F, &mBoundingBoxColor, " group='Bounding Box'");

	TwAddVarRW(mUserInterface, "Wire-frame Display", TW_TYPE_BOOLCPP, &wireCheck, "group='Wire-frame'");
	TwAddVarRW(mUserInterface, "Wire-frame Color", TW_TYPE_COLOR3F, &mModelColor, " group='Wire-frame'");

	TwAddVarRW(mUserInterface, "Points Display", TW_TYPE_BOOLCPP, &pointCheck, "group='Points'");
	TwAddVarRW(mUserInterface, "Points Color", TW_TYPE_COLOR3F, &mPointColor, " group='Points'");

	TwAddVarRW(mUserInterface, "Fill Display", TW_TYPE_BOOLCPP, &fillCheck, "group='Fill'");
	TwAddVarRW(mUserInterface, "Fill Color", TW_TYPE_COLOR3F, &mFillColor, " group='Fill'");

	TwAddVarRW(mUserInterface, "TX", TW_TYPE_FLOAT, &mModelTranslation[0], " group='Translation' step=0.01 min=-500.0 max=500.0");
	TwAddVarRW(mUserInterface, "TY", TW_TYPE_FLOAT, &mModelTranslation[1], " group='Translation' step=0.01 min=-500.0 max=500.0");
	TwAddVarRW(mUserInterface, "TZ", TW_TYPE_FLOAT, &mModelTranslation[2], " group='Translation' step=0.01 min=-500.0 max=500.0");

	TwAddVarRW(mUserInterface, "SX", TW_TYPE_FLOAT, &mModelScale[0], " group='Scale' step=0.1 min=-50.0 max=50.0");
	TwAddVarRW(mUserInterface, "SY", TW_TYPE_FLOAT, &mModelScale[1], " group='Scale' step=0.1 min=-50.0 max=50.0");
	TwAddVarRW(mUserInterface, "SZ", TW_TYPE_FLOAT, &mModelScale[2], " group='Scale' step=0.1 min=-50.0 max=50.0");

	TwAddVarRW(mUserInterface, "ModelR", TW_TYPE_QUAT4F, &mModelRotation, "group='Rotation'");
	TwAddVarRO(mUserInterface, "RX", TW_TYPE_FLOAT, &mModelRotation[0], " group='Rotation'");
	TwAddVarRO(mUserInterface, "RY", TW_TYPE_FLOAT, &mModelRotation[1], " group='Rotation'");
	TwAddVarRO(mUserInterface, "RZ", TW_TYPE_FLOAT, &mModelRotation[2], " group='Rotation'");
	TwAddVarRO(mUserInterface, "RW", TW_TYPE_FLOAT, &mModelRotation[3], " group='Rotation'");


}

void TW_CALL CallbackLoad(void *clientData)
{
	string path = loadPath();
	if (path != "")
		beginLoad(path);
}

CUserInterface::~CUserInterface()
{
}

void CUserInterface::reshape()
{
	TwWindowSize(gWidth, gHeight);
}

void CUserInterface::show()
{
	TwDefine("Figure visible = true");
}

void CUserInterface::hide()
{
	TwDefine("Figure visible = false");
}

void CUserInterface::setTranslation(glm::vec3 modelTranslation)
{
	mModelTranslation = modelTranslation;

}

glm::vec3 CUserInterface::getTranslation()
{
	return mModelTranslation;
}

void CUserInterface::setScale(glm::vec3  modelScale)
{
	mModelScale = modelScale;

}

glm::vec3 CUserInterface::getScale()
{
	return mModelScale;
}

void CUserInterface::setRotation(glm::vec4 modelRotation)
{
	mModelRotation = modelRotation;

}

glm::vec4 CUserInterface::getRotation()
{
	return mModelRotation;
}

string loadPath()
{
	OPENFILENAME ofn;
	char fileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "OBJ Files(.obj)\0*.obj\0OFF Files(.off)\0*.off";
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";
	string fileNameStr;
	if (GetOpenFileName(&ofn))
		fileNameStr = fileName;
	return fileNameStr;
}

int CUserInterface::getDeployType() {
	if (m_currentDeploy == GL_BEGIN_GL_END) return 0;
	if (m_currentDeploy == DISPLAY_LIST) return 1;
	if (m_currentDeploy == VERTEX_POINTER) return 2;
	if (m_currentDeploy == VBO) return 3;
	return NULL;
}

void CUserInterface::setDeployType(int a) {
	switch (a)
	{
	case 0:
		m_currentDeploy = GL_BEGIN_GL_END;
		break;
	case 1:
		m_currentDeploy = DISPLAY_LIST;
		break;
	case 2:
		m_currentDeploy = VERTEX_POINTER;
		break;
	case 3:
		m_currentDeploy = VBO;
		break;
	default:
		m_currentDeploy = DISPLAY_LIST;
		break;
	}
}

int CUserInterface::getPicked()
{
	return pick;
}

void CUserInterface::setColorFill(float *color)
{
	mFillColor[0] = color[0];
	mFillColor[1] = color[1];
	mFillColor[2] = color[2];
}

float * CUserInterface::getColorFill()
{
	return mFillColor;
}


void CUserInterface::setColorPoint(float *color)
{
	mPointColor[0] = color[0];
	mPointColor[1] = color[1];
	mPointColor[2] = color[2];
}

float * CUserInterface::getColorPoint()
{
	return mPointColor;
}


void CUserInterface::setColor(float *color)
{
	mModelColor[0] = color[0];
	mModelColor[1] = color[1];
	mModelColor[2] = color[2];
}

float * CUserInterface::getColor()
{
	return mModelColor;
}


void CUserInterface::setColorBoundingBox(float* color)
{
	mBoundingBoxColor[0] = color[0];
	mBoundingBoxColor[1] = color[1];
	mBoundingBoxColor[2] = color[2];
}

float * CUserInterface::getColorBoundingBox()
{
	return mBoundingBoxColor;
}

void CUserInterface::setColorNormalsFaces(float *color)
{
	mNormalsFacesColor[0] = color[0];
	mNormalsFacesColor[1] = color[1];
	mNormalsFacesColor[2] = color[2];
}

float * CUserInterface::getColorNormalsFaces()
{
	return mNormalsFacesColor;
}

void CUserInterface::setColorNormalsVertices(float *color)
{
	mNormalsVerticesColor[0] = color[0];
	mNormalsVerticesColor[1] = color[1];
	mNormalsVerticesColor[2] = color[2];
}

float * CUserInterface::getColorNormalsVertices()
{
	return mNormalsVerticesColor;
}

int CUserInterface::getLightPicked()
{
	return pickLight;
}

void CUserInterface::setLightPosition(GLfloat * a)
{
	position[0] = a[0];
	position[1] = a[1];
	position[2] = a[2];
}

GLfloat * CUserInterface::getLightPosition()
{
	return position;
}

void CUserInterface::setLightSpecular(GLfloat * a)
{
	specular[0] = a[0];
	specular[1] = a[1];
	specular[2] = a[2];
}

GLfloat * CUserInterface::getLightSpecular()
{
	return specular;
}

void CUserInterface::setLightDiffuse(GLfloat * a)
{
	diffuse[0] = a[0];
	diffuse[1] = a[1];
	diffuse[2] = a[2];
}

GLfloat * CUserInterface::getLightDiffuse()
{
	return diffuse;
}

void CUserInterface::setLightAmbient(GLfloat * a)
{
	ambient[0] = a[0];
	ambient[1] = a[1];
	ambient[2] = a[2];
}

GLfloat * CUserInterface::getLightAmbient()
{
	return ambient;
}


void CUserInterface::setBoundingBoxCheck(bool a)
{
	boundingBoxCheck = a;
}

bool CUserInterface::getBoundingBoxCheck()
{
	return boundingBoxCheck;
}

bool CUserInterface::getFillCheck()
{
	return fillCheck;
}

void CUserInterface::setFillCheck(bool a)
{
	fillCheck = a;
}

void CUserInterface::setPointCheck(bool a)
{
	pointCheck = a;
}

bool CUserInterface::getPointCheck()
{
	return pointCheck;
}

void CUserInterface::setWireCheck(bool a)
{
	wireCheck = a;
}

bool CUserInterface::getWireCheck()
{
	return wireCheck;
}

void CUserInterface::setNormalsFacesCheck(bool a)
{
	normalsFacesCheck = a;
}

bool CUserInterface::getNormalsFacesCheck()
{
	return normalsFacesCheck;
}

void CUserInterface::setNormalsVerticesCheck(bool a)
{
	normalsVerticesCheck = a;
}

bool CUserInterface::getNormalsVerticesCheck()
{
	return normalsVerticesCheck;
}

bool CUserInterface::getFlatCheck()
{
	return flat;
}

bool CUserInterface::getLightsCheck()
{
	return light;
}

bool CUserInterface::getBackFaceCheck()
{
	return backFace;
}

bool CUserInterface::getZBufferCheck()
{
	return zBuffer;
}

bool CUserInterface::getCameraCheck()
{
	return camera;
}
