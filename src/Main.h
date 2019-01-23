#define GLFW_INCLUDE_GLU
#include "../headers/glfw3.h"
#include "../headers/glm/glm.hpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void updateUserInterface();

void getMatriz4x4(glm::vec4, float*);

void display();

void change_view();

void reshape(GLFWwindow *window, int width, int height);

void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods);

void mouseButton(GLFWwindow* window, int button, int action, int mods);

void cursorPos(GLFWwindow* window, double x, double y);

void charInput(GLFWwindow* window, unsigned int scanChar);

void destroy();

bool initGlfw();

bool initUserInterface();

int main(void);