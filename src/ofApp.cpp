#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowShape(1920, 1080);
	ofBackground(255);

	ofEnableDepthTest();

	ofSetVerticalSync(true);
	ofEnableLighting();
	ofEnableAlphaBlending();
	ofEnableSmoothing();

	light.enable();
	light.setPointLight();
	light.setPosition(0, 0, 100);

	shader.load("shader/shader.vert", "shader/shader.frag");
	fbo.allocate(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	fbo.begin();
	ofClear(0, 0, 0, 0);

	ofSetColor(0);

	cam.begin();

	ofEnableLighting();

	t.drawMesh();

	ofDisableLighting();

	//ofSetColor(255, 255, 0);
	//light.draw();
	cam.end();
	fbo.end();

	shader.begin();
	shader.setUniformTexture("texture", fbo, 0);
	shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	shader.setUniform1f("time", ofGetElapsedTimef());

	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
	shader.end();

	fbo.draw(0, 0, ofGetWidth(), ofGetHeight());

	// FPS
	ofSetColor(255, 0, 0);
	string msg = "fps: " + ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(msg, 10, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
