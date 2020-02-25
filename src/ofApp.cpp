#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("roomTrack");
	ofSetBackgroundColor(0);
	osc.setup(HOST, PORT);
	grab.setVerbose(true);
	grab.setDeviceID(0);
	grab.setup(1024, 768);
	colorImg.allocate(ofGetWidth(), ofGetHeight());
	grayImage.allocate(ofGetWidth(), ofGetHeight());
	grayBg.allocate(ofGetWidth(), ofGetHeight());
	grayDiff.allocate(ofGetWidth(), ofGetHeight());

	bLearnBackground = true;
	threshold = 80;
}

//--------------------------------------------------------------
void ofApp::update(){
	bool bNewFrame = false;
	threshold = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, 255);
	
	grab.update();
	bNewFrame = grab.isFrameNew();

	if (bNewFrame) {
		colorImg.setFromPixels(grab.getPixels());
		grayImage = colorImg;
		if (bLearnBackground) {
			grayBg = grayImage;
			bLearnBackground = false;
		}

		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);

		cont.findContours(grayDiff, 20, ofGetWidth() * ofGetHeight(), 10, true);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//will not draw in implimentation
	ofSetColor(255);
	colorImg.draw(0, 0);
	for (int i = 0; i < cont.nBlobs; i++) {
		cont.blobs[i].draw();

		// draw over the centroid if the blob is a hole
		ofSetColor(255);
		if (cont.blobs[i].hole) {
			ofDrawBitmapString("hole",
				cont.blobs[i].boundingRect.getCenter().x,
				cont.blobs[i].boundingRect.getCenter().y);
		}
	}
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
	switch (key) {
	case ' ':
		bLearnBackground = true;
		break;
	case '+':
		threshold++;
		if (threshold > 255) threshold = 255;
		break;
	case '-':
		threshold--;
		if (threshold < 0) threshold = 0;
		break;
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