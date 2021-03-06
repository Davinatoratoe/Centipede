#include "Scene.h"
#include "CentipedeGameApp.h"
#include "imgui.h"

using namespace ImGui;

/// <summary>
/// Constructor.
/// </summary>
Scene::Scene()
{
	app = CentipedeGameApp::instance;	//Static instance on the App class
}

/// <summary>
/// Deconstructor.
/// </summary>
Scene::~Scene() 
{
}

/// <summary>
/// Create a GUI menu with a custom title and parameters.
/// https://github.com/ocornut/imgui
/// </summary>
/// <param name="name">Name of the menu.</param>
/// <param name="sizeX">Size of the menu.</param>
/// <param name="sizeY">Size of the menu.</param>
void Scene::CreateGUI(const char* name, float width)
{
	//Create a new menu that will automatically resize to fit elements added
	Begin(name, (bool*)0, ImVec2(width, 0), -1.0F, ImGuiWindowFlags_AlwaysAutoResize);

	//Set the position of the window only for the first time in the program's lifetime
	SetWindowPos(ImVec2(app->getWindowWidth() - width - 20, 20), sceneStarted ? ImGuiSetCond_Always : ImGuiSetCond_Once);

	//Scene started flag no longer needed
	sceneStarted = false;
}