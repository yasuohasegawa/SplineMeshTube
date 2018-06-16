#include "Spline.h"

// constructor
Spline::Spline()
{
	for (int i = 0; i < sizeof(controlPoints); i++)
	{
		glm::vec3 pos = glm::vec3(0, 0, 0);
		pos.z = (float)i*2.0;
		controlPoints[i] = pos;
	}

	controlPoints[2].x = 1.5;

	controlPoints[5].x = 2;
	controlPoints[5].y = 0.5;

	controlPoints[7].x = -1;
	controlPoints[7].y = -1.2;

	for (int i = 0; i < NUM_OF_SEGMENTS; i++)
	{
		mats[i] = ofMatrix4x4();
	}
}

// destructor
Spline::~Spline()
{
	
}

void Spline::createAndUpdateHermitecurve() {
	// loop over segments of spline
	glm::vec3 p0;
	glm::vec3 p1;
	glm::vec3 m0;
	glm::vec3 m1;


	for (int i = 0; i < NUM_OF_SEGMENTS; i++)
	{
		mats[i].makeIdentityMatrix();
	}

	int last = MAX_POINTS - 1;

	int ind = 0;

	for (int j = 0; j < last; j++)
	{
		// determine control points of segment
		p0 = controlPoints[j];
		p1 = controlPoints[j + 1];
		if (j > 0)
		{
			m0 = 0.5f * (controlPoints[j + 1] - controlPoints[j - 1]);
		}
		else
		{
			m0 = controlPoints[j + 1] - controlPoints[j];
		}

		if (j < MAX_POINTS - 2)
		{
			m1 = 0.5f * (controlPoints[j + 2] - controlPoints[j]);
		}
		else
		{
			m1 = controlPoints[j + 1] - controlPoints[j];
		}

		// set points of Hermite curve
		glm::vec3 position;
		glm::vec3 derivertive;
		float t;
		float pointStep = 1.0f / (float)NUM_OF_POINTS;
		if (j == MAX_POINTS - 2)
		{
			pointStep = 1.0f / ((float)NUM_OF_POINTS - 1.0f);
			// last point of last segment should reach p1
		}

		for (int i = 0; i < NUM_OF_POINTS; i++)
		{
			t = i * pointStep;
			position = (2.0f * t * t * t - 3.0f * t * t + 1.0f) * p0
				+ (t * t * t - 2.0f * t * t + t) * m0
				+ (-2.0f * t * t * t + 3.0f * t * t) * p1
				+ (t * t * t - t * t) * m1;

			// derivertive of above calculation
			derivertive = (6.0f * t * t - 6.0f * t) * p0
				+ (3.0f * t * t - 4.0f * t + 1.0f) * m0
				+ (-6.0f * t * t + 6.0f * t) * p1
				+ (3.0f * t * t - 2.0f * t) * m1;

			glm::vec3 velocity = derivertive;
			glm::vec3 direction = glm::normalize(velocity);

			if (ind < sizeof(positions))
			{
				positions[ind] = position;
				lookAts[ind] = position + direction;

				mats[ind].glTranslate(positions[ind]*100);
				mats[ind].glScale(100, 100, 100);
				
				ofQuaternion q;
				q.makeRotate(ofVec3f(0, 0, 1) * 100, lookAts[ind] * 100);
				mats[ind].glRotate(q);

				ind++;
			}
		}
	}
}