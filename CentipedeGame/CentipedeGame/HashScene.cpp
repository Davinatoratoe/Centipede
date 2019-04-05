#include "HashScene.h"
#include "imgui.h"
#include "CentipedeGameApp.h"
#include "HashFunction.h"

using namespace ImGui;
using namespace HashFunction;

/// <summary>
/// Overloaded constructor.
/// </summary>
HashScene::HashScene()
{
	loadedTextures = new map<unsigned int, Texture*>();
	textureToDisplay = nullptr;

	shipTextureFileName = (unsigned char*)"./textures/ship.png";
	shipTextureFileNameLength = 20;
}

/// <summary>
/// Deconstructor.
/// </summary>
HashScene::~HashScene()
{
	delete loadedTextures;
}

/// <summary>
/// Called when the scene starts.
/// </summary>
void HashScene::OnStart()
{
	value = 0;
	hashToDisplay = 0;
}

/// <summary>
/// Called when the scene closes.
/// </summary>
void HashScene::OnClose()
{
	loadedTextures->clear();
	textureToDisplay = nullptr;
}

/// <summary>
/// Get a texture from the hash table using the hash value.
/// </summary>
/// <param name="ID">The hash value to look up.</param>
/// <returns>The texture in the hash table found using the hash value.</returns>
Texture* HashScene::GetTexture(unsigned int ID)
{
	auto iter = loadedTextures->find(ID);
	if (iter == loadedTextures->end())
		return nullptr;
	else
		return iter->second;
}

/// <summary>
/// Called once per frame.
/// </summary>
/// <param name="deltaTime">The time that passed since last frame.</param>
/// <param name="input">A pointer to the input handler.</param>
void HashScene::Update(float deltaTime, Input* input)
{
	//InputInt("Value", &value);

	if (Button("Insert shipTexture file name into hash function", ImVec2(350, 0)))
		hashToDisplay = BKDRHash(shipTextureFileName, shipTextureFileNameLength);

	if (Button("Input shipTexture hash into table", ImVec2(350, 0)))
		loadedTextures->insert(make_pair(BKDRHash(shipTextureFileName, shipTextureFileNameLength), app->shipTexture));
	
	if (Button("Retrive shipTexture from hash function", ImVec2(350, 0)))
		textureToDisplay = GetTexture(BKDRHash(shipTextureFileName, shipTextureFileNameLength));

	if (Button("Menu", ImVec2(150, 0)))
		app->ChangeScene(app->menuScene);
}

/// <summary>
/// Draw the list to the screen.
/// </summary>
/// <param name="renderer">A pointer to the graphics renderer.</param>
void HashScene::Draw(Renderer2D* renderer)
{
	if (textureToDisplay != nullptr)
		renderer->drawSprite(textureToDisplay, app->getWindowWidth() / 2, app->getWindowHeight() / 2);

	renderer->drawText(app->font, "Hash Value: " + hashToDisplay, 20, 850);
}
