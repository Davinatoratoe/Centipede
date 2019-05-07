#pragma once
#include "Scene.h"
#include "Point2D.h"
#include "LinkedList.h"

class SimonScene : public Scene
{
private:
	#define Iterator LinkedList<Colour>::LinkedListIterator<Colour>

	/// <summary>
	/// Struct to represent an RGBA colour value
	/// </summary>
	struct Colour { float r, g, b; float a = 1.0F; };

	/// <summary>
	/// Colours class that holds a library of colours that the Simon game uses.
	/// </summary>
	class Colours 
	{ 
	private:
		Colour colours[3];	//The colours available

	public:
		/// <summary>
		/// Default constructor.
		/// </summary>
		Colours()
		{
			//Sets up the colours
			colours[0] = { 255, 0, 0 };		//Red
			colours[1] = { 0, 255, 0 };		//Green
			colours[2] = { 0, 0, 255 };		//Blue
		}

		//Enum to make it easier to find colours
		enum COLOUR { RED, GREEN, BLUE, NUMBER_OF_COLOURS };

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
	};

	Colours colours;				//The colours that the Simon game can use
	Button* buttons;				//The buttons to click in the Simon game
	unsigned int numberOfButtons;	//The number of buttons
	LinkedList<Colour> sequence;	//The sequence of colours to memorise
	LinkedList<Colour> pressed;		//A list of the colours that have been pressed (in order)

	const unsigned int BUTTON_WIDTH = 60;	//The width of a button
	const unsigned int BUTTON_HEIGHT = 60;	//The height of a button
	const unsigned int BUTTON_SPACING = 10;	//The spacing between buttons
	const unsigned int BUTTON_PER_ROW = 3;	//The number of buttons to be positioned per row
	
	unsigned int mouseIsOver;	//The index of the button that has the mouse over it
	unsigned int score;			//The number of consequent sequences guessed

	bool flashSequence;					//Whether to flash the sequence to memorise
	Iterator flashIterator;				//Iterator used to iterate through the sequence of colours to flash
	float flashTimer;					//Timer used to show how long each button should be flashed
	const float FLASH_DELAY = 2.0F;		//The time per button when flashing
	const float FLASH_SHOW_TIME = 1.2F;	//The timer to visually flash the button when flashing

	//Enum for which guessing state the user is in
	enum GUESS_STATE { GUESS_ALL, GUESSING, GUESS_WRONG };

	GUESS_STATE guessState;	//Which guessing state is the user in?

	//Adds a new colour to the end of the sequence
	void GenerateSequence();

	//Starts flashing through the sequence
	void FlashSequence();

	//Check for a new guess state
	unsigned int CheckNewState() const;

	//Check if the mouse is over a region (used for buttons)
	bool IsMouseOver(int mouseX, int mouseY, float x, float y, float width, float height) const;

	//Check if two colours are the same
	bool CompareColour(Colour a, Colour b) const;

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

