#pragma once
#include "Scene.h"
#include "Colour.h"

/// <summary>
/// Memory Scene used for the Memory Game.
/// </summary>
class MemoryScene : public Scene
{
private:
	static const unsigned int NUMBER_OF_PAIRS = 4;						//Number of pairs
	static const unsigned int NUMBER_OF_CARDS = NUMBER_OF_PAIRS * 2;	//Number of total cards

	Colour colours[NUMBER_OF_PAIRS];	//The colours to use for the memory game
	Colour cards[NUMBER_OF_CARDS];		//The coloured memory cards
	bool matched[NUMBER_OF_CARDS];		//Whether a pair has been matched

	const unsigned int CARD_WIDTH = 100;	//Width of a card
	const unsigned int CARD_HEIGHT = 150;	//Height of a card
	const unsigned int CARD_SPACING = 25;	//Spacing between the cards

	unsigned int numberOfMatches;		//Keep track of the number of pairs created
	unsigned int highlightedIndex;		//The index of the card that is highlighted
	unsigned int selectedFirstIndex;	//Index of the first card that was selected
	unsigned int selectedLastIndex;		//Index of the second card that was selected

	float showTimer;					//Timer used for showing the colours of two selected cards
	const float SHOW_DELAY = 1.75F;		//How long to show the colours for

	bool gameOver;	//Is the game over?
	
	//Shuffle the cards into a random order
	void ShuffleCards();

	//Check if two cards have matching colours
	bool CheckMatch(unsigned int a, unsigned int b) const;

	//Match two cards
	void Match(unsigned int a, unsigned int b);

	//Select a card
	void SelectCard(unsigned int a);

	//Move the highlighted index in a specific direction
	void MoveHighlighted(int horizontal, int vertical);

	//Update the timer for showing the selected cards
	void UpdateShowTimer(float deltaTime);

	//Handle user input to move the highlighted cards and select cards
	void HandleInput(Input* input);

	//Show the game over menu
	void ShowGameOverMenu();

public:
	//Default constructor
	MemoryScene();

	//Deconstructor
	~MemoryScene();

	//Called when the scene starts
	void OnStart();
	
	//Called when the scene closes
	void OnClose();

	//Update game logic
	void Update(float deltaTime, Input* input);

	//Draw stuff
	void Draw(Renderer2D* renderer);
};

