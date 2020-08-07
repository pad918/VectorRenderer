#ifndef VECTORS_H
#define VECTORS_H


namespace ml {

	class Vector2F {
	public:
		Vector2F(float x_point, float y_point);
		Vector2F();
		float x, y;
	};
	class Vector2I {
	public:
		Vector2I(int x_point, int y_point);
		Vector2I();
		int x, y;
	};

}

#endif