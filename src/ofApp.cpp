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

	gui.setup();
	gui.add(ctlpointSliderX.setup("ctlpointSliderX", 0.0, 0, 3));
	gui.add(ctlpointSliderY.setup("ctlpointSliderY", 0.0, 0, 3));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableDepthTest();
	fbo.begin();
	ofClear(0, 0, 0, 0);

	ofSetColor(0);

	cam.begin();

	ofEnableLighting();

	// debug spline controll point
	t.sp.controlPoints[3].x = ctlpointSliderX;
	t.sp.controlPoints[3].y = ctlpointSliderY;

	// draw mesh tube
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
	ofSetColor(0, 0, 0);
	string msg = "fps: " + ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(msg, ofGetWidth()-100, 20);
	
	// GUI
	ofDisableDepthTest();
	gui.draw();
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
