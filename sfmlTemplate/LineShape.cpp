#include "LineShape.h"
#include <algorithm>
#include <iostream>

ml::Vector2F spe::LineShape::getShapeSize()
{
	ml::Vector2F maxPoint(0,0);
	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].start.x > maxPoint.x) {
			maxPoint.x = lines[i].start.x;
		}
		if (lines[i].start.y > maxPoint.y) {
			maxPoint.y = lines[i].start.y;
		}
	}
	return maxPoint;
}

ml::Vector2F spe::LineShape::pixelToPointSpace(ml::Vector2I pixelPos)
{
	return ml::Vector2F(pixelPos.x/(float)pixelsPerPoint, pixelPos.y/(float)pixelsPerPoint);
}

void spe::LineShape::loadLinesFromPoints(std::vector<ml::Vector2F> points)
{
	if (lines.size() != 0) {
		std::cout << "Overwriting lines in lineshape" << std::endl;
		lines.clear();
	}
	if (points.size() < 3) {
		std::cout << "ERROR, cannot create shape from 3> points..." << std::endl;
		return;
	}

	for (int i = 1; i <= points.size(); i++) {
		if(i == points.size())
			lines.push_back(spe::Line(points[i - 1], points[0]));
		else
			lines.push_back(spe::Line(points[i-1], points[i]));
	}
}

ml::Vector2I spe::LineShape::getResolution()
{
	return resolution;
}

spe::LineShape::LineShape()
{

}

sf::Uint8 * spe::LineShape::render()
{
	
	ml::Vector2F tmp = getShapeSize();
	resolution.x = tmp.x * pixelsPerPoint; resolution.y = tmp.y * pixelsPerPoint;
	std::cout << "RESULOTION = " << resolution.x << " " << resolution.y << std::endl;
	sf::Uint8 * pixels = new sf::Uint8[resolution.x * resolution.y * 4]; //RGBA pixel array
	std::vector<spe::Line> collidingLines;
	for (int y = 0; y < resolution.y; y++) {
		for (int i = 0; i < lines.size(); i++) {
			float yPoint = (pixelToPointSpace(ml::Vector2I(0, y)).y); //(pixelToPointSpace(ml::Vector2I(0, resolution.y - y)).y);
			if (lines[i].isOnLine(yPoint)) {
				lines[i].colPos = lines[i].colDist(yPoint); // RÄKNA UT HÄR
				collidingLines.push_back(lines[i]);
			}
		}
		std::sort(collidingLines.begin(), collidingLines.end());
		bool isInside = false;
		int lastIntersection = 0;
		for (int i = 0; i < collidingLines.size()+1; i++) {
			if (i == 1)
				int hji = 0;
			if (i % 2 != 0)
				isInside = true;
			else
				isInside = false;
			bool restOfLine = false;
			if (i == collidingLines.size())
				restOfLine = true;
			//else
				//std::cout << "Line " << i << " | has dist of " << collidingLines[i].colPos << std::endl;
			float pixelLength = resolution.y;
			if(!restOfLine)
				pixelLength = collidingLines[i].colPos*pixelsPerPoint;
			for (int j = lastIntersection; j < pixelLength; j++) {
				int pixelPos = 4 * (y * resolution.x + j);
				if (j < resolution.x && y < resolution.y) {
					if (isInside) {
						pixels[pixelPos + 0] = 255 * ((i + 0) % 3 == 0);
						pixels[pixelPos + 1] = 255 * ((i + 1) % 3 == 0);
						pixels[pixelPos + 2] = 255 * ((i + 2) % 3 == 0);
						pixels[pixelPos + 3] = 255;
					}
					else {
						pixels[pixelPos + 0] = 0;
						pixels[pixelPos + 1] = 0;
						pixels[pixelPos + 2] = 0;
						pixels[pixelPos + 3] = 255;
					}
				}
			}
			lastIntersection = pixelLength;
		}

		collidingLines.clear();
	}

	return pixels;
}

float spe::Line::getLowestY(ml::Vector2F point1, ml::Vector2F point2)
{
	if (point1.y < point2.y)
		return point1.y;
	return point2.y;
}

spe::Line::Line(ml::Vector2F start_pos, ml::Vector2F end_pos)
{
	start = start_pos;
	end = end_pos;
}

bool spe::Line::isOnLine(float yLine)
{
	if ((start.y < yLine) != (end.y < yLine)) { // if they are on opposite sides of the line
		return true;
	}
	return false;
}

float spe::Line::colDist(float yPos)
{
	bool falling = false;
	ml::Vector2F points[2]; points[0] = start; points[1] = end;
	if (start.x > end.x) {
		points[0] = end; points[1] = start;
	}
	if (points[0].y > points[1].y) {
		falling = true;
	}
	float dY = std::abs(end.y - start.y);
	float dX = std::abs(start.x - end.x);
	float dist = points[0].x;
	float x1 = ((yPos - getLowestY(start, end)) / dY)*dX; // points[1].y
	if(falling)
		x1 = ((dY-(yPos - points[1].y)) / dY)*dX;
	return (dist+x1);
}
