#include "SimonScene.h"
#include "CentipedeGameApp.h"
#include "imgui.h"
#include <time.h>

/// <summary>
/// Constructor.
/// </summary>
SimonScene::SimonScene()
{
	//Seed the random number generator
	srand((unsigned int)time(NULL));

	//Create a new instance of the colours to be used in the game
	colours = SimonColours();
	
	//Create the buttons array
	numberOfButtons = colours.NUMBER_OF_COLOURS;
	buttons = new Button[numberOfButtons];

	//Determine that initial x-position of the first button
	float startX = (app->getWindowWidth() / 2.0F) - ((numberOfButtons < BUTTON_PER_ROW ? numberOfButtons : BUTTON_PER_ROW) * ((BUTTON_WIDTH + BUTTON_SPACING) / 2.0F));

	float startY = (app->getWindowHeight() / 2.0F) + (app->getWindowHeight() / 4.0F) + BUTTON_HEIGHT;

	//The x-position in the column to draw a button
	float colX = 0;

	//The y-position (row) to draw a button
	float rowY = 0;
	
	//Iterate through the buttons and set their positions
	for (unsigned int i = 0; i < numberOfButtons; ++i)
	{
		//If we have reached the maximum number of buttons for a row, move down and create a new row
		if (i % BUTTON_PER_ROW == 0)
		{
			colX = 0;
			++rowY;
		}

		//Calculate where to position this button
		float x = startX + (colX * (BUTTON_WIDTH + BUTTON_SPACING));
		float y = startY - (rowY * (BUTTON_HEIGHT + BUTTON_SPACING));
		
		//Instantiate the button
		buttons[i] = Button(Point2D(x, y), colours[i]);
		
		++colX;
	}

	//Set default values for the other variables

	sequence = LinkedList<Colour>();
	pressed = LinkedList<Colour>();
	
	mouseIsOver = numberOfButtons;
	buttonClicked = numberOfButtons;
	score = 0;

	flashSequence = false;
	flashIterator = sequence.Begin();
	flashTimer = 0.0F;

	guessState = GUESSING;
}

/// <summary>
/// Deconstructor.
/// </summary>
SimonScene::~SimonScene()
{
	delete[] buttons;
}

/// <summary>
/// Called when the scene starts.
/// </summary>
void SimonScene::OnStart()
{
	//Create a new sequence
	sequence.Clear();
	AddToSequence();

	//Set variables to default values
	pressed.Clear();
	score = 0;
	mouseIsOver = numberOfButtons;
	buttonClicked = numberOfButtons;

	//Flash the sequence and start the game!
	StartFlashingSequence();
	guessState = GUESSING;
}

/// <summary>
/// Called when the scene closes.
/// </summary>
void SimonScene::OnClose()
{

}

/// <summary>
/// Randomly add a colour to the end of the sequence.
/// </summary>
void SimonScene::AddToSequence()
{
	sequence.PushBack(colours.GetRandom());
}

/// <summary>
/// Determine what state the game is in.
/// </summary>
/// <returns>The state of the game. (GUESS_STATE)</returns>
unsigned int SimonScene::CheckNewState() const
{
	//Create iterator to allow us to iterate through the linked lists
	Iterator sequenceIterator = sequence.Begin();
	Iterator pressedIterator = pressed.Begin();

	//Loop until the sequence iterator hits the end of the sequence
	while (sequenceIterator != sequence.End())
	{
		//If we reach the end of the pressed list before the end of the sequence list, then keep guessing
		if (pressedIterator == pressed.End())
			return GUESSING;

		//If the colours don't match in the lists, then there was a wrong guess
		if (*sequenceIterator != *pressedIterator)
			return GUESS_WRONG;

		++sequenceIterator;
		++pressedIterator;
	}

	//Otherwise the entire sequence was guessed correctly - woo hoo!
	return GUESS_ALL;
}

/// <summary>
/// Start flashing the colours in the sequence.
/// </summary>
void SimonScene::StartFlashingSequence()
{
	flashSequence = true;
	flashIterator = sequence.Begin();
	flashTimer = FLASH_DELAY;
	mouseIsOver = numberOfButtons;
}

/// <summary>
/// Logic to flash the sequence.
/// </summary>
/// <param name="deltaTime">The time since last frame.</param>
void SimonScene::FlashSequence(float deltaTime)
{
	//Reduce the timer by deltaTime
	flashTimer -= deltaTime;

	//If the timer is below zero, then start flashing the next button in the sequence
	if (flashTimer < 0)
	{
		++flashIterator;
		flashTimer = FLASH_DELAY;

		//If there is no next button to flash, stop flashing and start guessing
		if (flashIterator == sequence.End())
		{
			flashSequence = false;
			guessState = GUESSING;
		}
	}
}

/// <summary>
/// Update the logic for when the player is guessing the sequence.
/// </summary>
/// <param name="input">Pointer to the input manager.</param>
void SimonScene::UpdateGuessingLogic(Input* input)
{
	mouseIsOver = numberOfButtons;
	buttonClicked = numberOfButtons;

	//Iterate through the buttons and check if any are being hovered over, or clicked
	for (unsigned int i = 0; i < numberOfButtons; ++i)
	{
		//Check if the button is being hovered over
		if (buttons[i].IsOver(Point2D((float)input->getMouseX(), (float)input->getMouseY())))
		{
			//Set the variable so it can be highlighted when drawn
			mouseIsOver = i;

			//Check if the mouse is still being clicked
			if (input->isMouseButtonDown(0))
				buttonClicked = i;

			//Check if the button is being clicked
			if (input->wasMouseButtonPressed(0))
			{
				//Push the colour of this button to the end of the pushed list
				pressed.PushBack(buttons[i].colour);

				//Check what the new state is
				guessState = (GUESS_STATE)CheckNewState();

				//Check if all the colours have been guessed correctly, then create a new sequence
				if (guessState == GUESS_ALL)
				{
					++score;
					pressed.Clear();
					AddToSequence();
					StartFlashingSequence();
				}
			}
		}
	}
}

/// <summary>
/// Show the game over menu.
/// </summary>
void SimonScene::ShowGameOverMenu()
{
	//Create the menu GUI
	CreateGUI("Game Over");

	//Button to play the game again
	if (ImGui::Button("Play again", ImVec2(150, 0)))
		app->ChangeScene(app->simonScene);

	//Button to return to the main menu
	if (ImGui::Button("Menu", ImVec2(150, 0)))
		app->ChangeScene(app->menuScene);

	ImGui::End();
}

/// <summary>
/// Called once per frame. Updates the game logic.
/// </summary>
/// <param name="deltaTime">The time that has passed since the last frame.</param>
/// <param name="input">Pointer to the input manager.</param>
void SimonScene::Update(float deltaTime, Input* input)
{
	//If the sequence is being flashed
	if (flashSequence)
		FlashSequence(deltaTime);
	//Otherwise, if the player is guessing the sequence
	else if (guessState == GUESSING)
		UpdateGuessingLogic(input);
	//Otherwise, if the player lost, open a menu
	else if (guessState == GUESS_WRONG)
		ShowGameOverMenu();

	//Check if a clicked button should be unclicked
	if (buttonClicked != numberOfButtons && (input->isMouseButtonUp(0) || !buttons[buttonClicked].IsOver(Point2D(input->getMouseX(), input->getMouseY()))))
		buttonClicked = numberOfButtons;
}

/// <summary>
/// Draw the game.
/// </summary>
/// <param name="renderer">Pointer to the graphics renderer.</param>
void SimonScene::Draw(Renderer2D* renderer)
{
	//Draw title text
	renderer->drawText(app->font, "SIMON GAME", 20.0F, app->getWindowHeight() - 50.0F);

	//Draw the score
	renderer->drawText(app->font, ("Score: " + to_string(score)).c_str(), app->getWindowWidth() / 2.0F, app->getWindowHeight() - 50.0F);

	//Draw text depending on the game state
	if (guessState == GUESSING)
		renderer->drawText(app->font, "Can you remember the sequence?...", 20.0F, app->getWindowHeight() - 100.0F);
	else if (guessState == GUESS_ALL)
		renderer->drawText(app->font, "All guessed! Memorise the new sequence...", 20.0F, app->getWindowHeight() - 100.0F);
	else if (guessState == GUESS_WRONG)
		renderer->drawText(app->font, "Incorrect! You must have a bad memory...", 20.0F, app->getWindowHeight() - 100.0F);

	//Iterate through the buttons and draw them
	for (unsigned int i = 0; i < numberOfButtons; ++i)
	{
		//Determine if this button should be highlighted
		// if it is being flashed, or is it being hovered over
		bool highlight = (flashSequence && flashTimer < FLASH_SHOW_TIME && buttons[i].colour == *flashIterator) || (!flashSequence && i == mouseIsOver);
		
		//Set the colour of the renderer to the colour of the button (and highlight if necessary)
		renderer->setRenderColour(buttons[i].colour.r, buttons[i].colour.g, buttons[i].colour.b, highlight ? 1.0F : 0.35F);
		
		//Determine the size of the button based on whether it is being clicked or not
		float sizeMod = (buttonClicked == i ? 0.8F : 1.0F);

		//Draw the button (not drawn at origin so that IsMouseOver() works properly)
		renderer->drawBox(buttons[i].position.x + (BUTTON_WIDTH / 2), buttons[i].position.y - (BUTTON_HEIGHT / 2), BUTTON_WIDTH * sizeMod, BUTTON_HEIGHT * sizeMod);
	}

	//Reset the renderer colour
	renderer->setRenderColour(0);
}
