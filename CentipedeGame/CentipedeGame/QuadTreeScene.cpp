#include "QuadTreeScene.h"
#include "imgui.h"
#include "CentipedeGameApp.h"

using namespace ImGui;

/// <summary>
/// Overloaded constructor.
/// </summary>
/// <param name="_font">The font to use.</param>
QuadScene::QuadScene()
{
	shipTexture = app->shipTexture;
	mushroomTexture = app->shroomTexture;
	selectedTexture = shipTexture;
	sprites = List<Sprite*>(100);
	quadTree = QuadTree();
}

/// <summary>
/// Deconstructor.
/// </summary>
QuadScene::~QuadScene()
{

}

/// <summary>
/// Called when the scene starts.
/// </summary>
void QuadScene::OnStart()
{
	
}

/// <summary>
/// Called when the scene closes.
/// </summary>
void QuadScene::OnClose()
{
	quadTree.Clear();
	sprites.Clear();
}

/// <summary>
/// Called once per frame.
/// </summary>
/// <param name="deltaTime">The time that passed since last frame.</param>
/// <param name="input">A pointer to the input handler.</param>
void QuadScene::Update(float deltaTime, Input* input)
{
	//Place a sprite if the right-mouse button is pressed
	if (input->wasMouseButtonPressed(1))
	{
		Sprite* sprite = new Sprite(selectedTexture, (float)input->getMouseX(), (float)input->getMouseY());
		sprites.Push(sprite);
		quadTree.Insert(sprite);
	}

	if (Button("Select ship texture", ImVec2(150, 0)))
		selectedTexture = shipTexture;

	if (Button("Select mushroom texture", ImVec2(150, 0)))
		selectedTexture = mushroomTexture;

	if (Button("Scatter sprites", ImVec2(150, 0)))
	{
		quadTree.Clear();
		sprites.Clear();
		for (unsigned int i = 0; i < 80; ++i)
		{
			Sprite* sprite = new Sprite(mushroomTexture, (float)app->RandomRange(0, app->getWindowWidth()), (float)app->RandomRange(0, app->getWindowHeight()));
			sprites.Push(sprite);
			quadTree.Insert(sprite);
		}
	}

	if (Button("Clear all", ImVec2(150, 0)))
	{
		sprites.Clear();
		quadTree.Clear();
	}

	if (Button("Menu", ImVec2(150, 0)))
		app->ChangeScene(app->menuScene);
}

/// <summary>
/// Draw the list to the screen.
/// </summary>
/// <param name="renderer">A pointer to the graphics renderer.</param>
void QuadScene::Draw(Renderer2D* renderer)
{
	//Draw text instructions and info
	renderer->drawText(app->font, "Right-click to place a sprite...", 20, 850);
	renderer->drawText(app->font, "Selected Sprite:", 20, 800);
	renderer->drawText(app->font, (selectedTexture == shipTexture ? "Ship" : "Mushroom"), 20, 750);

	//Draw the sprites
	for (unsigned int i = 0; i < sprites.Size(); ++i)
		sprites[i]->Draw(renderer);

	//Draw the quad tree
	quadTree.Draw(renderer);
}