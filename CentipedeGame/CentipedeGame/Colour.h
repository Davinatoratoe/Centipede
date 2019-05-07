#pragma once

/// <summary>
/// Class to represent an RGBA colour value
/// </summary>
class Colour
{
public:
	float r;	//Red component
	float g;	//Green component
	float b;	//Blue component
	float a;	//Alpha component

	/// <summary>
	/// Default constructor.
	/// </summary>
	Colour() { r = 0; g = 0; b = 0; a = 1.0F; }

	/// <summary>
	/// Overloaded constructor.
	/// </summary>
	/// <param name="_r">Red component.</param>
	/// <param name="_g">Green component.</param>
	/// <param name="_b">Blue component.</param>
	Colour(float _r, float _g, float _b) { r = _r; g = _g; b = _b; }

	/// <summary>
	/// Overloaded constructor.
	/// </summary>
	/// <param name="_r">Red component.</param>
	/// <param name="_g">Green component.</param>
	/// <param name="_b">Blue component.</param>
	/// <param name="_a">Alpha component.</param>
	Colour(float _r, float _g, float _b, float _a) { r = _r; g = _g; b = _b; a = _a; }

	/// <summary>
	/// Check if this colour is equal to another colour.
	/// </summary>
	/// <param name="o">The other colour.</param>
	/// <returns>True if the colour components are the same.</returns>
	bool operator == (const Colour& o) const { return r == o.r && g == o.g && b == o.b && a == o.a; }

	/// <summary>
	/// Check if this colour is not equal to another colour.
	/// </summary>
	/// <param name="o">The other colour.</param>
	/// <returns>True if the colour components don't match.</returns>
	bool operator != (const Colour& o) const { return !(*this == o); }
};