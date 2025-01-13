#pragma once

class Basis
{
public:
	Basis(int width, int height)
		: WIDTH(width), HEIGHT(height)
	{
	}

	float get_scale()
	{
		return scaleFactor;
	}

	float loc_to_window_x(float loc_x)
	{
		return (WIDTH / 2) + scaleFactor * (loc_x + centerTransX);
	}

	float loc_to_window_y(float loc_y)
	{
		return (HEIGHT / 2) - scaleFactor * (loc_y + centerTransY);
	}

	float window_to_loc_x(float window_x)
	{
		return (window_x - (WIDTH / 2)) / scaleFactor - centerTransX;
	}

	float window_to_loc_y(float window_y)
	{
		return ((HEIGHT / 2) - window_y) / scaleFactor - centerTransY;
	}

	void scale_up(float window_x, float window_y)
	{
		float x = window_to_loc_x(window_x);
		float y = window_to_loc_y(window_y);

		scaleFactor *= scaleAmount;

		centerTransX = _calc_x_trans_for_new_scale(x, window_x);
		centerTransY = _calc_y_trans_for_new_scale(y, window_y);
	}

	void scale_down(float window_x, float window_y)
	{
		if (scaleFactor > 0)
		{
			float x = window_to_loc_x(window_x);
			float y = window_to_loc_y(window_y);

			scaleFactor /= scaleAmount;

			centerTransX = _calc_x_trans_for_new_scale(x, window_x);
			centerTransY = _calc_y_trans_for_new_scale(y, window_y);
		}
	}



private:
	float scaleFactor = 1.0f;
	float scaleAmount = 1.3f;

	int centerTransX = 0;
	int centerTransY = 0;

	const int WIDTH;
	const int HEIGHT;

	float _calc_x_trans_for_new_scale(float loc_x, float window_x)
	{
		return (window_x - (WIDTH / 2)) / scaleFactor - loc_x;
	}

	float _calc_y_trans_for_new_scale(float loc_y, float window_y)
	{
		return ((HEIGHT / 2) - window_y) / scaleFactor - loc_y;
	}
};