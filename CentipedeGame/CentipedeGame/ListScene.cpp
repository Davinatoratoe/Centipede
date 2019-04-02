#include "ListScene.h"
#include "imgui.h"

using namespace ImGui;

ListScene::ListScene(Font* _font)
{
	font = _font;
}

ListScene::~ListScene()
{

}

void ListScene::OnStart()
{
	list = List<int>();
	value = 0;
}

void ListScene::OnClose()
{
	
}

void ListScene::Update(float deltaTime, Input* input)
{
	InputInt("Value", &value);

	if (Button("Push", ImVec2(50, 0)))
		list.Push(value);
	
	if (Button("Pop", ImVec2(50, 0)))
		list.Pop();

	if (Button("Clear", ImVec2(50, 0)))
		list.Clear();

	if (Button("Reserve", ImVec2(50, 0)))
		list.Reserve(value);
}

void ListScene::Draw(Renderer2D* renderer)
{
	renderer->drawText(font, ("List: " + list.ToString()).c_str(), 20, 850);
	renderer->drawText(font, "Size: " + list.Size(), 20, 800);
}
