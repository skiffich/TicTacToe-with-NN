#pragma once

#include "ofMain.h"
#include "..\MyGUI.h"
#include "..\GameTTT.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);


	MyButton button[13];

	ofImage Ximg;
	ofImage Oimg;
	ofImage Gridimg;
	ofImage im;

	GameTTT game;

	ofTrueTypeFont		font;

	string msg1;
	string msg2;

	int Mode, GameMode, GameResult;
	int buttonPressed;
	bool TeachMode;
	bool LoopMvsMMode;
};