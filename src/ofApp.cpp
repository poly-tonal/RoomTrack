#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("roomTrack");
	ofSetBackgroundColor(0);
	osc.setup(HOST, PORT);
	grab.setDeviceID(0);
	grab.setup(1024, 768);
	background.allocate(ofGetWidth(), ofGetHeight());
	difference.allocate(ofGetWidth(), ofGetHeight());
	temp.allocate(ofGetWidth(), ofGetHeight());
	grab.videoSettings();
	
}

//--------------------------------------------------------------
void ofApp::update(){
	//ofxOscMessage message;
	grab.update();
	if (grab.isFrameNew()) {
		//cont.setTargetColor(color);
		cont.setThreshold(ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 255));
		temp = grab.getPixels();
		difference.absDiff(background, temp);
		cont.findContours(difference); //look into settings chnages for cont
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
	//will not draw in implimentation
	ofSetColor(255);
	grab.draw(0, 0);
	cont.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	//for camera change debuging
	if (isdigit(key)) {
		num = ofMap(key, 48, 57, 0, 9);
		if (num != cam) {
			cam = num;
			changeCam(cam);
		}
	}
	if (key == 's') {
		background = temp;
	}
}

//--------------------------------------------------------------
void ofApp::changeCam(int cam) {
	grab.close();
	grab.setDeviceID(cam);
	grab.initGrabber(1024, 768);
}


//TODO
//create message function to move stuff
//create blob object to contain each tracker
//work out how to track in room