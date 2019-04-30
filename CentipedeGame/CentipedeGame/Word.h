#pragma once
#include <Renderer2D.h>
#include <Font.h>

using namespace aie;

/// <summary>
/// Class for displaying an individual letter. Used by the Word class.
/// </summary>
class Letter
{
private:
	char letter;	//Letter to be displayed

public:
	float x;		//x-position to display the letter
	float y;		//y-position to display the letter

	//Default constructor
	Letter();

	//Overloaded constructor
	Letter(const char _letter, float _x, float _y);

	//Draw the letter
	void Draw(Renderer2D* renderer, Font* font);
};

/// <summary>
/// Used for displaying an animated word.
/// </summary>
class Word
{
private:
	Font* font;				//Font to use to draw
	float counter;			//Counter for the sin wave
	float x;				//x-position of the word
	float y;				//y-position of the word
	unsigned int length;	//Length of the word
	unsigned int letterSpacing;	//The spacing between the letters
	Letter* word;			//The word as letters

public:
	float speed;	//The speed that the word bobs
	float scale;	//The scale at which the word bobs

	//Default constructor
	Word();

	//Overloaded constructor
	Word(const char* _word, unsigned int _length, Font* _font, unsigned int _letterSpacing, float _x, float _y);
	
	//Deconstructor
	~Word();

	//Called once per frame
	void Update(float deltaTime);

	//Draws graphics
	void Draw(Renderer2D* renderer);
};

