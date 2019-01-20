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
	mUserInterface = TwNewBar("Model");
	m_currentDeploy = DISPLAY_LIST;
	TwDefine("Model refresh = '0.0001f'");
	TwDefine("Model resizable = false");
	TwDefine("Model fontresizable = false");
	TwDefine("Model movable = false");
	TwDefine("Model position = '20 20'");
	TwDefine("Model size = '220 320'");

	mModelTranslation[0] = mModelTranslation[1] = 	mModelTranslation[2] = 0.0f;
	mModelScale[0] = mModelScale[1] = mModelScale[2] = 1;
	mModelRotation[0] = mModelRotation[1] = mModelRotation[2] = 0;
	mModelRotation[3] = 1;

	TwEnumVal DeployType[] = { { GL_BEGIN_GL_END, "Gl Begin / Gl End" },{ DISPLAY_LIST, "Display List" },{ VERTEX_POINTER, "Vertex Pointer" },{ VBO, "VBO" } };
	TwType DeployTwType = TwDefineEnum("DeployType", DeployType, 4);
	TwAddVarRW(mUserInterface, "Deploy", DeployTwType, &m_currentDeploy, NULL);

	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "TX", TW_TYPE_FLOAT, &mModelTranslation[0], " group='Translation' step=0.01 ");
	TwAddVarRW(mUserInterface, "TY", TW_TYPE_FLOAT, &mModelTranslation[1], " group='Translation' step=0.01 ");
	TwAddVarRW(mUserInterface, "TZ", TW_TYPE_FLOAT, &mModelTranslation[2], " group='Translation' step=0.01 ");
	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "SX", TW_TYPE_FLOAT, &mModelScale[0], " group='Scale' step=0.1 ");
	TwAddVarRW(mUserInterface, "SY", TW_TYPE_FLOAT, &mModelScale[1], " group='Scale' step=0.1 ");
	TwAddVarRW(mUserInterface, "SZ", TW_TYPE_FLOAT, &mModelScale[2], " group='Scale' step=0.1 ");	
	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "RX", TW_TYPE_FLOAT, &mModelRotation[0], " group='Rotation' step=1 min=-360 max=360");
	TwAddVarRW(mUserInterface, "RY", TW_TYPE_FLOAT, &mModelRotation[1], " group='Rotation' step=1 min=-360 max=360");
	TwAddVarRW(mUserInterface, "RZ", TW_TYPE_FLOAT, &mModelRotation[2], " group='Rotation' step=1 min=-360 max=360");
	TwAddSeparator(mUserInterface, "", NULL);
	TwAddButton(mUserInterface, "Load", CallbackLoad, NULL, NULL);
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

void CUserInterface::setModelTranslation(float *modelTranslation)
{
	mModelTranslation[0] = modelTranslation[0];
	mModelTranslation[1] = modelTranslation[1];
	mModelTranslation[2] = modelTranslation[2];
}

glm::vec3 CUserInterface::getModelTranslation()
{
	return mModelTranslation;
}

void CUserInterface::setModelScale(float * modelScale)
{
	mModelScale[0] = modelScale[0];
	mModelScale[1] = modelScale[1];
	mModelScale[2] = modelScale[2];
}

glm::vec3 CUserInterface::getModelScale()
{
	return mModelScale;
}

void CUserInterface::setModelRotation(float * modelRotation)
{
	mModelRotation[0] = modelRotation[0];
	mModelRotation[1] = modelRotation[1];
	mModelRotation[2] = modelRotation[2];
	mModelRotation[3] = modelRotation[3];
}

glm::vec4 CUserInterface::getModelRotation()
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

}