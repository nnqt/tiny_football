#pragma once

#include <iostream>

struct Vector2f
{
	Vector2f():x(0), y(0)
	{}

	Vector2f(int p_x, int p_y)
		:x(p_x), y(p_y)
	{}

	void print()
	{
		std::cout << x << ", " << y << std::endl;
	}

	int x, y;
};

struct Circle
{
	int x, y;
	int r;
};

struct ColorRGB
{
	int red, green, blue;
	ColorRGB() :red(0), green(0), blue(0)
	{};
	ColorRGB(int p_red, int p_green, int p_blue)
	{
		red = p_red;
		green = p_green;
		blue = p_blue;
	}
};


