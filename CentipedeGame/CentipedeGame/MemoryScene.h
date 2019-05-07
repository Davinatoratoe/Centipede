#pragma once
#include "Scene.h"
#include "Colour.h"

class MemoryScene : public Scene
{
private:
	static const unsigned int NUMBER_OF_PAIRS = 4;
	static const unsigned int NUMBER_OF_CARDS = NUMBER_OF_PAIRS * 2;

	Colour colours[NUMBER_OF_PAIRS];
	Colour cards[NUMBER_OF_CARDS];
	bool matched[NUMBER_OF_CARDS];

	const unsigned int CARD_WIDTH = 100;
	const unsigned int CARD_HEIGHT = 150;
	const unsigned int CARD_SPACING = 25;

	unsigned int numberOfMatches;
	unsigned int highlightedIndex;
	unsigned int selectedFirstIndex;
	unsigned int selectedLastIndex;

	float showTimer;
	const float SHOW_DELAY = 1.75F;

	bool gameOver;

	void ShuffleCards();

	bool CheckMatch(unsigned int a, unsigned int b) const;

	void Match(unsigned int a, unsigned int b);

	void SelectCard(unsigned int a);

	void MoveHighlightedToFree();

	void MoveHighlighted(int horizontal, int vertical);

	void UpdateShowTimer(float deltaTime);

	void HandleInput(Input* input);

	void ShowGameOverMenu();

public:
	MemoryScene();
	~MemoryScene();

	void OnStart();
	
	void OnClose();

	void Update(float deltaTime, Input* input);

	void Draw(Renderer2D* renderer);
};

