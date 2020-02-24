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
	cont.setMinAreaRadius(20);
	//cont.setMaxAreaRadius(150);
	bLearnBackground = true;
}

//--------------------------------------------------------------
void ofApp::update(){
	//ofxOscMessage message;
	grab.update();
	if (grab.isFrameNew()) {
		//cont.setTargetColor(color);
		cont.setThreshold(ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 255));
		temp.setFromPixels(grab.getPixels());
		if (bLearnBackground == true) {
			background = temp;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBackground = false;
		}
		difference.absDiff(background, temp);
		cont.findContours(difference); //look into settings chnages for cont
		cont.setFindHoles(true);
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
		bLearnBackground = true;
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