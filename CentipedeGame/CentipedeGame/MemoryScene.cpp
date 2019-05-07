#include "MemoryScene.h"
#include "CentipedeGameApp.h"
#include <math.h>
#include <algorithm>
#include "imgui.h"

MemoryScene::MemoryScene()
{
	colours[0] = Colour(255, 0, 0);
	colours[1] = Colour(0, 255, 0);
	colours[2] = Colour(0, 0, 255);
	colours[3] = Colour(255, 0, 255);

	unsigned int colourIndex = 0;
	for (unsigned int i = 0; i < NUMBER_OF_CARDS; i += 2)
	{
		cards[i] = colours[colourIndex];
		cards[i + 1] = colours[colourIndex];
		++colourIndex;
	}

	numberOfMatches = 0;
	highlightedIndex = 0;
	selectedFirstIndex = NUMBER_OF_CARDS;
	selectedLastIndex = NUMBER_OF_CARDS;

	gameOver = false;
}

MemoryScene::~MemoryScene()
{

}

void MemoryScene::OnStart()
{
	ShuffleCards();

	for (unsigned int i = 0; i < NUMBER_OF_CARDS; ++i)
		matched[i] = false;

	numberOfMatches = 0;
	highlightedIndex = 0;
	selectedFirstIndex = NUMBER_OF_CARDS;
	selectedLastIndex = NUMBER_OF_CARDS;

	gameOver = false;
}

void MemoryScene::OnClose()
{

}

void MemoryScene::ShuffleCards()
{
	std::random_shuffle(std::begin(cards), std::end(cards));
}

bool MemoryScene::CheckMatch(unsigned int a, unsigned int b) const
{
	return cards[a] == cards[b];
}

void MemoryScene::Match(unsigned int a, unsigned int b)
{
	matched[a] = true;
	matched[b] = true;
	++numberOfMatches;
	gameOver = numberOfMatches >= NUMBER_OF_PAIRS;
}

void MemoryScene::SelectCard(unsigned int a)
{
	if (selectedFirstIndex == NUMBER_OF_CARDS)
		selectedFirstIndex = a;
	else
	{
		selectedLastIndex = a;

		if (CheckMatch(selectedFirstIndex, selectedLastIndex))
		{
			Match(selectedFirstIndex, selectedLastIndex);
			selectedFirstIndex = NUMBER_OF_CARDS;
			selectedLastIndex = NUMBER_OF_CARDS;
		}
		else
			showTimer = SHOW_DELAY;
	}
}

void MemoryScene::MoveHighlightedToFree()
{
	int start = highlightedIndex;

	do
	{
		highlightedIndex = (highlightedIndex + 1) % NUMBER_OF_CARDS;

		if (!matched[highlightedIndex] && selectedFirstIndex != highlightedIndex && selectedLastIndex != highlightedIndex)
			break;
	}
	while (highlightedIndex != start);
}

void MemoryScene::MoveHighlighted(int horizontal, int vertical)
{
	highlightedIndex = (highlightedIndex + horizontal) % 4 + (highlightedIndex / 4) * 4;
	highlightedIndex = (highlightedIndex + (NUMBER_OF_PAIRS * vertical)) % NUMBER_OF_CARDS;
}

void MemoryScene::UpdateShowTimer(float deltaTime)
{
	showTimer -= deltaTime;

	if (showTimer <= 0)
	{
		selectedFirstIndex = NUMBER_OF_CARDS;
		selectedLastIndex = NUMBER_OF_CARDS;
	}
}

void MemoryScene::HandleInput(Input* input)
{
	int horizontal = input->wasKeyPressed(INPUT_KEY_LEFT) ? -1 : (input->wasKeyPressed(INPUT_KEY_RIGHT) ? 1 : 0);
	int vertical = input->wasKeyPressed(INPUT_KEY_DOWN) ? -1 : (input->wasKeyPressed(INPUT_KEY_UP) ? 1 : 0);
	
	MoveHighlighted(horizontal, vertical);	

	if (!matched[highlightedIndex] && selectedFirstIndex != highlightedIndex && input->wasKeyPressed(INPUT_KEY_ENTER))
		SelectCard(highlightedIndex);
}

void MemoryScene::ShowGameOverMenu()
{
	//Create the menu GUI
	CreateGUI("Game Over");

	//Button to play the game again
	if (ImGui::Button("Play again", ImVec2(150, 0)))
		app->ChangeScene(app->memoryScene);

	//Button to return to the main menu
	if (ImGui::Button("Menu", ImVec2(150, 0)))
		app->ChangeScene(app->menuScene);

	ImGui::End();
}

void MemoryScene::Update(float deltaTime, Input* input)
{
	if (showTimer > 0)
		UpdateShowTimer(deltaTime);
	else if (!gameOver)
		HandleInput(input);
	else
		ShowGameOverMenu();
}

void MemoryScene::Draw(Renderer2D* renderer)
{
	//Draw title text
	renderer->drawText(app->font, "MEMORY GAME", 20.0F, app->getWindowHeight() - 50.0F);

	//Draw instructions text
	renderer->drawText(app->font, "Use Arrow Keys to move...", 20.0F, app->getWindowHeight() - 100.0F);
	renderer->drawText(app->font, "Use ENTER to select...", 20.0F, app->getWindowHeight() - 150.0F);

	float colX = 0;
	float rowY = 0;

	for (unsigned int i = 0; i < NUMBER_OF_CARDS; ++i)
	{
		if (i % NUMBER_OF_PAIRS == 0)
		{
			colX = 0;
			++rowY;
		}

		float initX = (app->getWindowWidth() / 2.0F) - ((NUMBER_OF_PAIRS / 2) * (CARD_WIDTH + CARD_SPACING));
		float initY = (app->getWindowHeight() / 2.0F) + ((NUMBER_OF_PAIRS / 2) * CARD_WIDTH);

		float x = initX + ((CARD_WIDTH + CARD_SPACING) * colX) + (CARD_WIDTH / 2);
		float y = initY - ((CARD_HEIGHT + CARD_SPACING) * rowY);
		
		if (matched[i] || selectedFirstIndex == i || (showTimer > 0 && selectedLastIndex == i))
			renderer->setRenderColour(cards[i].r, cards[i].g, cards[i].b, cards[i].a);

		float sizeMod = highlightedIndex == i ? 1.15F : 1.0F;

		renderer->drawBox(x, y, CARD_WIDTH * sizeMod, CARD_HEIGHT * sizeMod);

		renderer->setRenderColour(255, 255, 255);

		++colX;
	}

	//Reset the renderer colour
	renderer->setRenderColour(255, 255, 255);
}