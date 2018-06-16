#include "Tube.h"

// constructor
Tube::Tube()
{
	m.glScale(100, 100, 100);
	m.glRotate(20, 0, 0, 1);

	createMesh(&m);
}

// destructor
Tube::~Tube()
{
	
}

void Tube::createMesh(ofMatrix4x4 *mat) {

	sp.createAndUpdateHermitecurve();

	int faceCount = 0;

	float x = 0.0;
	float y = 0.0;
	float z = 0.1;

	float uvRad = 1.0;
	float uvRad2 = 1.2;
	vertices.push_back(ofVec3f(0,0,0));
	colors.push_back(ofFloatColor(1, 0, 0, 1));

	for (int i = 1; i <= verticesCount; i++)
	{
		float rad = (90.0 - (360.0 / (float)verticesCount) * (i - 1)) * PI / 180.0;
		x = cos(rad);
		y = sin(rad);
		vertices.push_back(ofVec3f(x, y, 0));
		colors.push_back(ofFloatColor(1 - (i*0.1), 0, 0, 1));
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i == verticesCount ? 1 : i + 1);
	}

	for (int i = 0; i < vertices.size(); i++) {
		offsetVertices.push_back(ofVec3f(vertices[i].x, vertices[i].y, vertices[i].z));
	}

	float centerY = 0.5f;
	float centerZ = 0.1f;

	for (int i = 0; i< NUM_OF_SEGMENTS- NUM_OF_POINTS; i++) {
		for (int j = 0; j< verticesCount; j++)
		{
			float x2 = 0.0;
			float y2 = 0.0;

			float rad = (90.0 - (360.0 / (float)verticesCount) * (j)) * PI / 180.0;
			float rad2 = (90.0 - (360.0 / (float)verticesCount) * (j + 1)) * PI / 180.0;
			x = cos(rad);
			y = sin(rad);
			x2 = cos(rad2);
			y2 = sin(rad2);

			vertices.push_back(ofVec3f(x2, y2, z - centerZ));
			vertices.push_back(ofVec3f(x, y, z - centerZ));
			vertices.push_back(ofVec3f(x, y, z + centerZ));
			vertices.push_back(ofVec3f(x2, y2, z + centerZ));

			offsetVertices.push_back(ofVec3f(x2, y2, z - centerZ));
			offsetVertices.push_back(ofVec3f(x, y, z - centerZ));
			offsetVertices.push_back(ofVec3f(x, y, z + centerZ));
			offsetVertices.push_back(ofVec3f(x2, y2, z + centerZ));

			colors.push_back(ofFloatColor(1 - (j*0.1), 0, 0, 1));
			colors.push_back(ofFloatColor(1 - (j*0.1), 0, 0, 1));
			colors.push_back(ofFloatColor(1 - (j*0.1), 0, 0, 1));
			colors.push_back(ofFloatColor(1 - (j*0.1), 0, 0, 1));

			indices.push_back((verticesCount + 1) + faceCount * 4); //1
			indices.push_back((verticesCount + 1) + faceCount * 4 + 1); //2
			indices.push_back((verticesCount + 1) + faceCount * 4 + 2); //3
			indices.push_back((verticesCount + 1) + faceCount * 4); //1
			indices.push_back((verticesCount + 1) + faceCount * 4 + 2); //3
			indices.push_back((verticesCount + 1) + faceCount * 4 + 3); //4

			faceCount++;
		}
	}

	updateMesh();

	vboMesh.addVertices(vertices);
	vboMesh.addColors(colors);
	vboMesh.addIndices(indices);

	calcNormals(vboMesh);
}

void Tube::updateMesh() {
	for (int i = 0; i < verticesCount + 1; i++) {
		vertices[i] = offsetVertices[i] * sp.mats[0];
	}

	for (int i = 0; i < NUM_OF_SEGMENTS - NUM_OF_POINTS; i++) {
		int start = (verticesCount + 1) + ((verticesCount * 4)*i);
		for (int j = 0; j < verticesCount; j++)
		{
			vertices[start + (j * 4)] = offsetVertices[start + (j * 4)] * sp.mats[i];
			vertices[start + (j * 4) + 1] = offsetVertices[start + (j * 4) + 1] * sp.mats[i];
			vertices[start + (j * 4) + 2] = offsetVertices[start + (j * 4) + 2] * sp.mats[i];
			vertices[start + (j * 4) + 3] = offsetVertices[start + (j * 4) + 3] * sp.mats[i];
		}
	}

	// connect between polygons
	for (int j = 0; j < verticesCount; j++) {
		int prev = 1;
		int now = (verticesCount + 1);
		vertices[now + (j * 4)] = vertices[prev + j + 1];
		vertices[now + (j * 4) + 1] = vertices[prev + j];
	}

	for (int i = 0; i < (NUM_OF_SEGMENTS - NUM_OF_POINTS) - 1; i++) {
		for (int j = 0; j < verticesCount; j++) {
			int prev = (verticesCount + 1) + ((verticesCount * 4)*i);
			int now = (verticesCount + 1) + ((verticesCount * 4)*(i + 1));

			vertices[now + (j * 4)] = vertices[prev + (j * 4) + 3];
			vertices[now + (j * 4) + 1] = vertices[prev + (j * 4) + 2];
		}
	}
}

// TODO:mesh animation
void Tube::drawMesh() {
	sp.createAndUpdateHermitecurve();

	vboMesh.drawWireframe();
	vboMesh.enableNormals();

	updateMesh();

	vector<glm::vec3> &verts = vboMesh.getVertices();
	for (int i = 0; i < verts.size(); i++) {
		verts[i] = vertices[i];
	}

	vboMesh.draw();
	//vboMesh.draw(OF_MESH_WIREFRAME);
}

void Tube::calcNormals(ofVboMesh &mesh) {
	for( int i=0; i < mesh.getVertices().size(); i++ ) mesh.addNormal(ofPoint(0,0,0));

	for( int i=0; i < mesh.getIndices().size(); i+=3 ){
		const int ia = mesh.getIndices()[i];
		const int ib = mesh.getIndices()[i+1];
		const int ic = mesh.getIndices()[i+2];

		ofVec3f e1 = mesh.getVertices()[ia] - mesh.getVertices()[ib];
		ofVec3f e2 = mesh.getVertices()[ic] - mesh.getVertices()[ib];
		ofVec3f no = e2.cross( e1 );

		// depending on your clockwise / winding order, you might want to reverse the e2 / e1 above if your normals are flipped.

		mesh.getNormals()[ia] += no;
		mesh.getNormals()[ib] += no;
		mesh.getNormals()[ic] += no;
	}
}
