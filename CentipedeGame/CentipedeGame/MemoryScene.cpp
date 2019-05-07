#include "MemoryScene.h"
#include "CentipedeGameApp.h"
#include <math.h>
#include <algorithm>
#include "imgui.h"

/// <summary>
/// Default constructor.
/// </summary>
MemoryScene::MemoryScene()
{
	//Set up the colours
	colours[0] = Colour(255, 0, 0);
	colours[1] = Colour(0, 255, 0);
	colours[2] = Colour(0, 0, 255);
	colours[3] = Colour(255, 0, 255);

	//Assign pairs of cards
	unsigned int colourIndex = 0;
	for (unsigned int i = 0; i < NUMBER_OF_CARDS; i += 2)
	{
		cards[i] = colours[colourIndex];
		cards[i + 1] = colours[colourIndex];
		++colourIndex;
	}

	//Set default values

	numberOfMatches = 0;
	highlightedIndex = 0;
	selectedFirstIndex = NUMBER_OF_CARDS;
	selectedLastIndex = NUMBER_OF_CARDS;

	gameOver = false;
}

/// <summary>
/// Deconstructor.
/// </summary>
MemoryScene::~MemoryScene()
{

}

/// <summary>
/// Called when the scene starts.
/// </summary>
void MemoryScene::OnStart()
{
	//Shuffle the cards
	ShuffleCards();

	//Unmatch all cards
	for (unsigned int i = 0; i < NUMBER_OF_CARDS; ++i)
		matched[i] = false;

	//Set default values

	numberOfMatches = 0;
	highlightedIndex = 0;
	selectedFirstIndex = NUMBER_OF_CARDS;
	selectedLastIndex = NUMBER_OF_CARDS;

	gameOver = false;
}

/// <summary>
/// Called when the scene closes.
/// </summary>
void MemoryScene::OnClose()
{

}

/// <summary>
/// Shuffle the cards using random_shuffle from the algorithms library.
/// </summary>
void MemoryScene::ShuffleCards()
{
	std::random_shuffle(std::begin(cards), std::end(cards));
}

/// <summary>
/// Check to see if two cards have matching colours.
/// </summary>
/// <param name="a">Card A.</param>
/// <param name="b">Card B.</param>
/// <returns>True if both cards have the same colours.</returns>
bool MemoryScene::CheckMatch(unsigned int a, unsigned int b) const
{
	return cards[a] == cards[b];
}

/// <summary>
/// Match two cards.
/// </summary>
/// <param name="a">Card A.</param>
/// <param name="b">Card B.</param>
void MemoryScene::Match(unsigned int a, unsigned int b)
{
	//Match the cards
	matched[a] = true;
	matched[b] = true;
	++numberOfMatches;
	
	//End the game if all the cards have been matched
	gameOver = numberOfMatches >= NUMBER_OF_PAIRS;
}

/// <summary>
/// Select a card. Tries to match if selecting the second card.
/// </summary>
/// <param name="a">Card to select.</param>
void MemoryScene::SelectCard(unsigned int a)
{
	//If this is the first card selected then continue
	if (selectedFirstIndex == NUMBER_OF_CARDS)
		selectedFirstIndex = a;
	//Otherwise check for a match
	else
	{
		selectedLastIndex = a;

		//Check if there is a match
		if (CheckMatch(selectedFirstIndex, selectedLastIndex))
		{
			//Match the cards
			Match(selectedFirstIndex, selectedLastIndex);

			//Reset the selections
			selectedFirstIndex = NUMBER_OF_CARDS;
			selectedLastIndex = NUMBER_OF_CARDS;
		}
		//Otherwise they don't match, so show the colours
		else
			showTimer = SHOW_DELAY;
	}
}

/// <summary>
/// Move the highlighted index through the array.
/// Will wrap horizontally and vertically.
/// </summary>
/// <param name="horizontal">Horizontal direction.</param>
/// <param name="vertical">Vertical direction.</param>
void MemoryScene::MoveHighlighted(int horizontal, int vertical)
{
	highlightedIndex = (highlightedIndex + horizontal) % 4 + (highlightedIndex / 4) * 4;
	highlightedIndex = (highlightedIndex + (NUMBER_OF_PAIRS * vertical)) % NUMBER_OF_CARDS;
}

/// <summary>
/// Update the timer for showing the colours.
/// </summary>
/// <param name="deltaTime">Time that has passed since the last frame.</param>
void MemoryScene::UpdateShowTimer(float deltaTime)
{
	//Decrease the timer
	showTimer -= deltaTime;

	//If the timer has reached zero, then reset the selection
	if (showTimer <= 0)
	{
		selectedFirstIndex = NUMBER_OF_CARDS;
		selectedLastIndex = NUMBER_OF_CARDS;
	}
}

/// <summary>
/// Handle user input to move and select cards.
/// </summary>
/// <param name="input">Pointer to the input manager.</param>
void MemoryScene::HandleInput(Input* input)
{
	//Get which direction the highlighted card should be moved in
	int horizontal = input->wasKeyPressed(INPUT_KEY_LEFT) ? -1 : (input->wasKeyPressed(INPUT_KEY_RIGHT) ? 1 : 0);
	int vertical = input->wasKeyPressed(INPUT_KEY_DOWN) ? -1 : (input->wasKeyPressed(INPUT_KEY_UP) ? 1 : 0);
	
	//Move the highlighted card
	MoveHighlighted(horizontal, vertical);	

	//Check if the player selects this card
	if (!matched[highlightedIndex] && selectedFirstIndex != highlightedIndex && input->wasKeyPressed(INPUT_KEY_ENTER))
		SelectCard(highlightedIndex);
}

/// <summary>
/// Show the game over menu.
/// </summary>
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

/// <summary>
/// Called once per frame. Update the game logic.
/// </summary>
/// <param name="deltaTime">Time that has passed since last frame.</param>
/// <param name="input">Pointer to the input manager.</param>
void MemoryScene::Update(float deltaTime, Input* input)
{
	//If showing the colours then update the show timer
	if (showTimer > 0)
		UpdateShowTimer(deltaTime);
	//Otherwise if the game is not over, handle the input
	else if (!gameOver)
		HandleInput(input);
	//Otherwise if the game is over, show the game over menu
	else
		ShowGameOverMenu();
}

/// <summary>
/// Draw the cards and text.
/// </summary>
/// <param name="renderer">Pointer to the graphics renderer.</param>
void MemoryScene::Draw(Renderer2D* renderer)
{
	//Draw title text
	renderer->drawText(app->font, "MEMORY GAME", 20.0F, app->getWindowHeight() - 50.0F);

	//Draw instructions text
	renderer->drawText(app->font, "Use Arrow Keys to move...", 20.0F, app->getWindowHeight() - 100.0F);
	renderer->drawText(app->font, "Use ENTER to select...", 20.0F, app->getWindowHeight() - 150.0F);

	float colX = 0;	//x-position in a column
	float rowY = 0;	//y-position of a row

	//Calculate the initial position of the cards
	float initX = (app->getWindowWidth() / 2.0F) - ((NUMBER_OF_PAIRS / 2) * (CARD_WIDTH + CARD_SPACING));
	float initY = (app->getWindowHeight() / 2.0F) + ((NUMBER_OF_PAIRS / 2) * CARD_WIDTH);

	//Iterate through the cards and draw each one
	for (unsigned int i = 0; i < NUMBER_OF_CARDS; ++i)
	{
		//Check if we have reached the end of a row, and move down a row if so
		if (i % NUMBER_OF_PAIRS == 0)
		{
			colX = 0;
			++rowY;
		}

		//Calculate the position of the card
		float x = initX + ((CARD_WIDTH + CARD_SPACING) * colX) + (CARD_WIDTH / 2);
		float y = initY - ((CARD_HEIGHT + CARD_SPACING) * rowY);
		
		//If the card has been matched or has been selected, then show its colour
		if (matched[i] || selectedFirstIndex == i || (showTimer > 0 && selectedLastIndex == i))
			renderer->setRenderColour(cards[i].r, cards[i].g, cards[i].b, cards[i].a);

		//Change the size of the card if it is the one highlighted
		float sizeMod = highlightedIndex == i ? 1.15F : 1.0F;
		
		//Draw the card
		renderer->drawBox(x, y, CARD_WIDTH * sizeMod, CARD_HEIGHT * sizeMod);

		//Set the renderer colour back to white
		renderer->setRenderColour(255, 255, 255);

		++colX;
	}

	//Reset the renderer colour
	renderer->setRenderColour(255, 255, 255);
}