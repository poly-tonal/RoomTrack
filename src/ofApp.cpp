#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("roomTrack");
	ofSetBackgroundColor(0);
	osc.setup(HOST, PORT);
	grab.setDeviceID(1);
	grab.setup(1024, 768);
}

//--------------------------------------------------------------
void ofApp::update(){
	//ofxOscMessage message;
	grab.update();
	if (grab.isFrameNew()) {
		//cont.setTargetColor(color);
		cont.setThreshold(60);
		cont.findContours(grab); //look into settings chnages for cont
		//message.addBoolArg(playing);
		//oscx = ofMap(cont.getCentroid(0).x, 0, ofGetWidth(), 0.0f, 200.0f, true);
		//oscy = ofMap(cont.getCentroid(0).y, 0, ofGetHeight(), 1.0f, 0.0f, true);
		//message.addFloatArg(oscx);
		//message.addFloatArg(oscy);
	}
	//osc.sendMessage(message, false);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
	grab.draw(0, 0);
	cont.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (isdigit(key)) {
		num = ofMap(key, 48, 57, 0, 9);
		if (num != cam) {
			cam = num;
			changeCam(cam);
		}
	}
}

//--------------------------------------------------------------
void ofApp::changeCam(int cam) {
	grab.close();
	grab.setDeviceID(cam);
	grab.initGrabber(1024, 768);
}