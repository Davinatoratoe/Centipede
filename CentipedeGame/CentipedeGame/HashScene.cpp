#include "HashScene.h"
#include "imgui.h"
#include "CentipedeGameApp.h"
#include "HashFunction.h"
#include <iostream>
#include <sstream>

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

	shroomTextureFileName = (unsigned char*)"./textures/mushroom.png";
	shroomTextureFileNameLength = 24;
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
	if (Button("Hash the shipTexture file name", ImVec2(250, 0)))
		hashToDisplay = BKDRHash(shipTextureFileName, shipTextureFileNameLength);

	if (Button("Hash the shroomTexture file name", ImVec2(250, 0)))
		hashToDisplay = BKDRHash(shroomTextureFileName, shroomTextureFileNameLength);

	if (Button("Input shipTexture hash into table", ImVec2(250, 0)))
		loadedTextures->insert(make_pair(BKDRHash(shipTextureFileName, shipTextureFileNameLength), app->shipTexture));

	if (Button("Input shroomTexture hash into table", ImVec2(250, 0)))
		loadedTextures->insert(make_pair(BKDRHash(shroomTextureFileName, shroomTextureFileNameLength), app->shroomTexture));

	if (Button("Retrieve texture using hash", ImVec2(250, 0)))
		textureToDisplay = GetTexture(hashToDisplay);

	if (Button("Menu", ImVec2(150, 0)))
		app->ChangeScene(app->menuScene);
}

/// <summary>
/// Draw the list to the screen.
/// </summary>
/// <param name="renderer">A pointer to the graphics renderer.</param>
void HashScene::Draw(Renderer2D* renderer)
{
	//Draw the hash value generated
	if (hashToDisplay > 0)
	{
		ostringstream stream;
		stream << "Hash Value: " << hashToDisplay;
		renderer->drawText(app->font, stream.str().c_str(), 20, 850);
	}

	//Draw the texture and its address
	if (textureToDisplay != nullptr)
	{
		renderer->drawSprite(textureToDisplay, app->getWindowWidth() / 2, (app->getWindowHeight() / 2) + (sin(app->getTime() * 0.5) * 50));

		ostringstream stream;
		stream << "Texture address: " << &textureToDisplay;
		renderer->drawText(app->font, stream.str().c_str(), 20, 800);
	}
}
