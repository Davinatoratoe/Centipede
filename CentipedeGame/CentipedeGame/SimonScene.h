#pragma once
#include "Scene.h"
#include "Point2D.h"
#include "Colour.h"
#include "LinkedList.h"

/// <summary>
/// Simon Scene used for the Simon Game.
/// </summary>
class SimonScene : public Scene
{
private:
	typedef LinkedList<Colour>::LinkedListIterator<Colour> Iterator;
	
	/// <summary>
	/// Colours class that holds a library of colours that the Simon game uses.
	/// </summary>
	class SimonColours 
	{ 
	private:
		Colour colours[4];	//The colours available

	public:
		/// <summary>
		/// Default constructor.
		/// </summary>
		SimonColours()
		{
			//Sets up the colours
			colours[0] = { 255, 0, 0 };		//Red
			colours[1] = { 0, 255, 0 };		//Green
			colours[2] = { 0, 0, 255 };		//Blue
			colours[3] = { 255, 0, 255 };	//Pink
		}

		//Enum to make it easier to find colours
		enum COLOUR { RED, GREEN, BLUE, PINK, NUMBER_OF_COLOURS };

		/// <summary>
		/// Retrieve a colour using an index (or COLOUR enum value).
		/// Overloads the subscript operator.
		/// </summary>
		/// <param name="index">The index of a colour (or COLOUR enum value).</param>
		/// <returns>A colour.</returns>
		Colour operator[] (unsigned int index)
		{
			if (index >= 0 && index < NUMBER_OF_COLOURS)
				return colours[index];
			else
				throw out_of_range("Index not in range.");
		}
		
		/// <summary>
		/// Get a random colour.
		/// </summary>
		/// <returns>A random colour.</returns>
		Colour GetRandom() const { return colours[rand() % NUMBER_OF_COLOURS]; }
	};

	/// <summary>
	/// Class for a button for the Simon game.
	/// </summary>
	class Button
	{
	public:
		Point2D position;	//Position of the button
		Colour colour;		//Colour of the button

		/// <summary>
		/// Default constructor.
		/// </summary>
		Button() { position = Point2D(); colour = { 0, 0, 0 }; }

		/// <summary>
		/// Overloaded constructor to set the initial values.
		/// </summary>
		/// <param name="_position">The position of the button.</param>
		/// <param name="_colour">The colour of the button.</param>
		Button(Point2D _position, Colour _colour) { position = _position; colour = _colour; }

		/// <summary>
		/// Check if a given point is within the bounds of the button.
		/// </summary>
		/// <param name="point">The point.</param>
		/// <returns>True if the point is within the bounds of the button.</returns>
		bool IsOver(Point2D point) const
		{
			return point.x > position.x && point.x < position.x + SimonScene::BUTTON_WIDTH &&
				point.y < position.y && point.y > position.y - SimonScene::BUTTON_HEIGHT;
		}
	};

	SimonColours colours;			//The colours that the Simon game can use
	Button* buttons;				//The buttons to click in the Simon game
	unsigned int numberOfButtons;	//The number of buttons
	LinkedList<Colour> sequence;	//The sequence of colours to memorise
	LinkedList<Colour> pressed;		//A list of the colours that have been pressed (in order)
	
	static const unsigned int BUTTON_WIDTH = 120;	//The width of a button
	static const unsigned int BUTTON_HEIGHT = 120;	//The height of a button
	const unsigned int BUTTON_SPACING = 10;			//The spacing between buttons
	const unsigned int BUTTON_PER_ROW = 2;			//The number of buttons to be positioned per row

	unsigned int mouseIsOver;			//The index of the button that has the mouse over it
	unsigned int buttonClicked;			//The index of the button that mouse is currently clicking
	unsigned int score;					//The number of consequent sequences guessed

	bool flashSequence;					//Whether to flash the sequence to memorise
	Iterator flashIterator;				//Iterator used to iterate through the sequence of colours to flash
	float flashTimer;						//Timer used to show how long each button should be flashed
	const float FLASH_DELAY = 1.75F;		//The time per button when flashing
	const float FLASH_SHOW_TIME = 1.25F;	//The timer to visually flash the button when flashing

	//Enum for which guessing state the user is in
	enum GUESS_STATE { GUESS_ALL, GUESSING, GUESS_WRONG };

	GUESS_STATE guessState;		//Which guessing state is the user in?

	//Adds a new colour to the end of the sequence
	void AddToSequence();

	//Check for a new guess state
	unsigned int CheckNewState() const;

	//Starts flashing through the sequence
	void StartFlashingSequence();

	//Logic for flashing the sequence
	void FlashSequence(float deltaTime);

	void UpdateGuessingLogic(Input* input);

	//Show the game over menu
	void ShowGameOverMenu();

public:
	//Constructor
	SimonScene();

	//Deconstructor
	~SimonScene();

	//Called when the game starts
	void OnStart() override;

	//Called when the game ends
	void OnClose() override;

	//Update the game logic
	void Update(float deltaTime, Input* input) override;

	//Draw the game
	void Draw(Renderer2D* renderer) override;
};

