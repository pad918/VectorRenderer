#ifndef LINESHAPE_H
#define LINESHAPE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Vectors.h"

namespace spe {

	class Line {
	private:
		float getLowestY(ml::Vector2F point1, ml::Vector2F point2);
	public:
		Line(ml::Vector2F start_pos, ml::Vector2F end_pos);
		ml::Vector2F start, end;
		bool isOnLine(float yLine);
		float colDist(float yPos);
		float colPos = 0.0f;

		bool operator< (const Line &other) const { // for sorting
			return colPos < other.colPos;
		}
	};

	class LineShape {
	private:
		ml::Vector2I resolution;
		ml::Vector2F getShapeSize();
		ml::Vector2F pixelToPointSpace(ml::Vector2I pixelPos);
		float pixelsPerPoint = 10.0f;
		
	public:
		LineShape();
		sf::Uint8 * render();
		std::vector<spe::Line> lines;
		void loadLinesFromPoints(std::vector<ml::Vector2F> points);
		ml::Vector2I getResolution();
	};

	

}

#endif
