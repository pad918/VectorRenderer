#include "Vectors.h"

ml::Vector2F::Vector2F(float x_point, float y_point)
{
	x = x_point;
	y = y_point;
}

ml::Vector2F::Vector2F()
{
	//INGET
}

ml::Vector2I::Vector2I(int x_point, int y_point)
{
	x = x_point;
	y = y_point;
}

ml::Vector2I::Vector2I()
{
	x = 0; y = 0;
}
