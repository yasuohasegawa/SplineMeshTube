#pragma once
#include <stdio.h>
#include "ofMain.h"

#define MAX_POINTS 10
#define NUM_OF_SEGMENTS 50
#define NUM_OF_POINTS 5

class Spline
{
private:
	
public:
	Spline();
	~Spline();

	void createAndUpdateHermitecurve();

	glm::vec3 const up = glm::vec3(0, 0, 1);
	glm::vec3 controlPoints[MAX_POINTS];
	glm::vec3 positions[NUM_OF_SEGMENTS];
	glm::vec3 lookAts[NUM_OF_SEGMENTS];
	ofMatrix4x4 mats[NUM_OF_SEGMENTS];
};