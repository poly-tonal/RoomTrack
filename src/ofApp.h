#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"

#define PORT 9001
#define HOST "localhost"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		//void keyReleased(int key);
		//void mouseMoved(int x, int y );
		//void mouseDragged(int x, int y, int button);
		//void mousePressed(int x, int y, int button);
		//void mouseReleased(int x, int y, int button);
		//void mouseEntered(int x, int y);
		//void mouseExited(int x, int y);
		//void windowResized(int w, int h);
		//void dragEvent(ofDragInfo dragInfo);
		//void gotMessage(ofMessage msg);
		void changeCam(int camera);
		//void message(Blob b);
		
		ofxOscSender osc;
		ofxCvGrayscaleImage background;
		ofxCvGrayscaleImage difference;
		ofxCvGrayscaleImage temp;
		bool bLearnBackground;
		float oscx = 0.0f;
		float oscy = 0.0f;
		bool playing = false;
		bool switched = false;
		ofVideoGrabber grab;
		ofxCv::ContourFinder cont;
		//ofColor color;
		int num = 1;
		int cam = 0;
};
