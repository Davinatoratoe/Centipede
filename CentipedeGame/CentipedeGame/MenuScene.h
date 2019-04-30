/*
	File: MenuScene.h
	Contains: MenuScene
*/

#pragma once
#include "Scene.h"

/// <summary>
/// The MenuScene is a scene for the main menu.
/// Allows loading the main game and container tests.
/// </summary>
class MenuScene : public Scene
{
public:
	MenuScene();	//Overloaded constructor
	~MenuScene();	//Deconstructor

	void OnStart() override;	//Called when the scene starts
	void OnClose() override;	//Called when the scene closes

	void Update(float deltaTime, Input* input) override;	//Called once per frame
	void Draw(Renderer2D* renderer) override;				//Called to draw the graphics

private:
	/// <summary>
	/// A class to draw a word that bobs.
	/// </summary>
	class Word
	{
	private:
		/// <summary>
		/// Struct for a floating letter used to display the title.
		/// </summary>
		class Letter
		{
		public:
			/// <summary>
			/// Default constructor.
			/// </summary>
			Letter()
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
			Letter(const char _letter, float _x, float _y)
			{
				letter = _letter;
				x = _x;
				y = _y;
			}

			float x;		//x-position to display the letter
			float y;		//y-position to display the letter

			/// <summary>
			/// Get the letter as a printable object.
			/// </summary>
			/// <returns>The letter as a printable object.</returns>
			const char* GetLetter()
			{
				return &letter;
			}

		private:
			char letter;	//Letter to be displayed
		};

	public:
		const unsigned int LETTER_SPACING = 40;		//The spacing between letters

		/// <summary>
		/// Overloaded constructor.
		/// </summary>
		/// <param name="_word">The word.</param>
		/// <param name="_length">The number of characters in the word.</param>
		/// <param name="_font">The font to use.</param>
		/// <param name="_x">The x-position of the word.</param>
		/// <param name="_y">The y-position of the word.</param>
		Word(const char* _word, unsigned int _length, Font* _font, float _x, float _y)
		{
			counter = 0;
			x = _x;
			y = _y;
			font = _font;
			length = _length;

			//Allocate memory for the letters
			word = new Letter[length + 1];
			
			//Add an extra empty letter to the end to avoid displaying trash memory
			memset(word + length, 0, sizeof(Letter));
			
			//Create the letters
			for (unsigned int i = 0; i < length; ++i)
				word[i] = Letter(_word[i], x + (LETTER_SPACING * i), y);
		}

		~Word()
		{
			delete[] word;
		}

		/// <summary>
		/// Update the word to bob.
		/// </summary>
		/// <param name="deltaTime">Time that has passed since last frame.</param>
		void Update(float deltaTime)
		{
			//Increase the counter
			counter += 0.02F;

			//Move the letters up and down, alternating
			int flipFlag = 1;
			for (unsigned int i = 0; i < length; ++i)
			{
				word[i].y += (sin(counter * 2.0F) * 0.2F) * flipFlag;
				flipFlag *= -1;
			}
		}

		/// <summary>
		/// Draw the word.
		/// </summary>
		/// <param name="renderer">The renderer to draw the word.</param>
		void Draw(Renderer2D* renderer)
		{
			for (unsigned int i = 0; i < length; ++i)
				renderer->drawText(font, word[i].GetLetter(), word[i].x, word[i].y);
		}

	private:
		Font* font;				//Font to use to draw
		float counter;			//Counter for the sin wave
		float x;				//x-position of the word
		float y;				//y-position of the word
		unsigned int length;	//Length of the word
		Letter* word;			//The word as letters
	};

	Word* title;	//Title displayed on-screen
};

