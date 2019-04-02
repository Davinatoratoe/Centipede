#include "Scene.h"
#include "CentipedeGameApp.h"

Scene::Scene()
{
	app = CentipedeGameApp::instance;	//Static instance on the App class
}

Scene::~Scene() {}