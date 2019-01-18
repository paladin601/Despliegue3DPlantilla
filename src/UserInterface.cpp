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
	m_currentDeploy = GL_BEGIN_GL_END;
	TwDefine("Model refresh = '0.0001f'");
	TwDefine("Model resizable = false");
	TwDefine("Model fontresizable = false");
	TwDefine("Model movable = false");
	TwDefine("Model position = '20 20'");
	TwDefine("Model size = '220 320'");

	mModelTranslation[0] = 0.0f;
	mModelTranslation[1] = 0.0f;
	mModelTranslation[2] = 0.0f;


	TwEnumVal DeployType[] = { { GL_BEGIN_GL_END, "Gl Begin / Gl End" },{ DISPLAY_LIST, "Display List" },{ VERTEX_POINTER, "Vertex Pointer" },{ VBO, "VBO" } };
	TwType DeployTwType = TwDefineEnum("DeployType", DeployType, 4);

	TwAddVarRW(mUserInterface, "Deploy", DeployTwType, &m_currentDeploy, NULL);
	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "X", TW_TYPE_FLOAT, &mModelTranslation[0], " group='Translation' step=0.01 ");
	TwAddVarRW(mUserInterface, "Y", TW_TYPE_FLOAT, &mModelTranslation[1], " group='Translation' step=0.01 ");
	TwAddVarRW(mUserInterface, "Z", TW_TYPE_FLOAT, &mModelTranslation[2], " group='Translation' step=0.01 ");
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

string CUserInterface::getDeployType() {
	if (m_currentDeploy == GL_BEGIN_GL_END) return "glbeg";
	if (m_currentDeploy == DISPLAY_LIST) return "DL";
	if (m_currentDeploy == VERTEX_POINTER) return "VP";
	if (m_currentDeploy == VBO) return "VBO";
	return NULL;
}