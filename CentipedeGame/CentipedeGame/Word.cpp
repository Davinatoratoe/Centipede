#include "Word.h"
#include <iostream>

/// <summary>
/// Default constructor
/// </summary>
Letter::Letter()
{
	letter = '\0';
	x = 0;
	y = 0;
}

/// <summary>
/// Overloaded constructor.
/// </summary>
/// <param name="_letter">The letter.</param>
/// <param name="_x">The x-position.</param>
/// <param name="_y">The y-position.</param>
Letter::Letter(const char _letter, float _x, float _y)
{
	letter = _letter;
	x = _x;
	y = _y;
}

/// <summary>
/// Draw the letter.
/// </summary>
/// <param name="renderer">Renderer to use to draw.</param>
/// <param name="font">The font to use to draw the letter.</param>
void Letter::Draw(Renderer2D* renderer, Font* font)
{
	renderer->drawText(font, &letter, x, y);
}

/// <summary>
/// Default constructor.
/// </summary>
Word::Word()
{
	letterSpacing = 40;
	speed = 2.0F;
	scale = 0.2F;
	counter = 0;
	x = 0;
	y = 0;
	font = nullptr;
	word = nullptr;
}

/// <summary>
/// Overloaded constructor.
/// </summary>
/// <param name="_word">The word.</param>
/// <param name="_length">The number of characters in the word.</param>
/// <param name="_font">The font to use.</param>
/// <param name="_x">The x-position of the word.</param>
/// <param name="_y">The y-position of the word.</param>
Word::Word(const char* _word, unsigned int _length, Font* _font, unsigned int _letterSpacing, float _x, float _y)
{
	//Set variables
	letterSpacing = _letterSpacing;
	speed = 2.0F;
	scale = 0.2F;
	counter = 0;
	x = _x;
	y = _y;
	font = _font;
	length = _length;

	//Allocate memory for the letters
	word = new Letter[length + 1];

	//Add an extra empty letter to the end to avoid displaying garbage memory
	memset(word + length, 0, sizeof(Letter));

	//Create the letters
	for (unsigned int i = 0; i < length; ++i)
		word[i] = Letter(_word[i], x + (letterSpacing * i), y);
}

/// <summary>
/// Deconstructor.
/// </summary>
Word::~Word()
{
	delete[] word;
}

/// <summary>
/// Update the word to bob.
/// </summary>
/// <param name="deltaTime">Time that has passed since last frame.</param>
void Word::Update(float deltaTime)
{
	if (word == nullptr)
		return;

	//Increase the counter
	counter += 0.02F;

	//Move the letters up and down, alternating
	int flipFlag = 1;
	for (unsigned int i = 0; i < length; ++i)
	{
		word[i].y += (sin(counter * speed) * scale) * flipFlag;
		flipFlag *= -1;
	}
}

/// <summary>
/// Draw the word.
/// </summary>
/// <param name="renderer">The renderer to draw the word.</param>
void Word::Draw(Renderer2D* renderer)
{
	if (renderer == nullptr || word == nullptr || font == nullptr)
		return;

	for (unsigned int i = 0; i < length; ++i)
		word[i].Draw(renderer, font);
}