#pragma once
#include <stdio.h>
#include "ofMain.h"
#include "Spline.h"

class Tube
{
private:
	void createMesh(ofMatrix4x4 * mat);
	void updateMesh();
public:
	Tube();
	~Tube();

	void drawMesh();
	void calcNormals(ofVboMesh &mesh);

	int verticesCount = 10;

	ofVboMesh vboMesh;
	ofMatrix4x4 m;

	vector<glm::vec3> vertices;
	vector<unsigned> indices;
	vector<ofFloatColor> colors;
	vector<ofVec3f> offsetVertices;

	Spline sp;
};