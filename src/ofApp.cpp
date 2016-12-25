#include "ofApp.h"

void DrawResultLine(int GameResult);

//--------------------------------------------------------------
void ofApp::setup() {
	float x = ofGetWidth() / 3;
	float y = ofGetHeight() / 3;

	for (int i(0), k = 0; i < 3; i++)
		for (int j(0); j < 3; j++)
			button[k++].ButtonSetup(x * j + 25, y * i + 25, x - 35, y - 35, k);                    //change

	Ximg.load("X.bmp");
	Oimg.load("O.bmp");
	Gridimg.load("Grid.bmp");
	im.load("MenuFon.jpg");

	font.loadFont("font.otf", 32);

	for (int i(9), k(y * 2), kk(-35); i < 13; i++, kk += 35)
	{
		if (i < 12)
			button[i].ButtonSetup(x, k + kk, x, 32, i + 1);
		button[i].ChangeColorWhileMouseMovedIn(ofColor::green, true);
		button[i].ChangeColorWhileMousePressed(ofColor::red, true);
		button[i].setButtonColor(ofColor::blue);
		button[i].setTextFont(font);
	}

	button[12].ButtonSetup(x, y * 2 + 70, x, 35, 13);

	button[9].setText("Player vs Player");
	button[10].setText("Player vs Machine");
	button[11].setText("Machine vs Machine");
	button[12].setText("Play Again");

	msg1 = "Win Player ";
	msg2 = "Press ESC to exit";

	Mode = 1;
	GameResult = 0;
	GameMode = buttonPressed = -1;
	TeachMode = false;
	LoopMvsMMode = false;
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	//*
	switch (Mode)
	{
	case 1:
		im.draw(0, 0);
		for (int i(9); i < 12; i++) button[i].DrawButton();
		if (buttonPressed != -1) { GameMode = buttonPressed - 9; Mode = 2; buttonPressed = -1; }
		break;
	case 2:
		Gridimg.draw(0, 0);
		for (int i(0); i < 9; i++) {
			if (game.GetMasCell(i) == 0) { button[i].isImage = false; button[i].DrawButton(); }
			if (game.GetMasCell(i) == 1) { button[i].setTexture(Ximg); button[i].DrawButton(); }
			if (game.GetMasCell(i) == 2) { button[i].setTexture(Oimg); button[i].DrawButton(); }
		}
		if (buttonPressed != -1)
		{
			cout << buttonPressed << endl;
			GameResult = game.GameMain(GameMode, buttonPressed - 1);
		}
		if (GameMode == 3) GameResult = game.GameMain(GameMode);
		if (GameResult) {
			if (LoopMvsMMode) { Mode = 1; GameResult = 0; GameMode = 3; buttonPressed = 12; game.Clear(); TeachMode = false; }
			else
				Mode = 3;
		}
		break;
	case 3:
		Gridimg.draw(0, 0);
		for (int i(0); i < 9; i++) {
			if (game.GetMasCell(i) == 0) { button[i].isImage = false; button[i].DrawButton(); }
			if (game.GetMasCell(i) == 1) { button[i].setTexture(Ximg); button[i].DrawButton(); }
			if (game.GetMasCell(i) == 2) { button[i].setTexture(Oimg); button[i].DrawButton(); }
		}
		DrawResultLine(GameResult);
		break;
	case 4:
		im.draw(0, 0);
		button[12].DrawButton();
		font.drawString(msg1, ofGetWidth() / 3, ofGetHeight() / 3 * 2 - 35);
		font.drawString(msg2, ofGetWidth() / 3, ofGetHeight() / 3 * 2 + 35);
		if (buttonPressed != -1) { Mode = 1; GameResult = 0; GameMode = buttonPressed = -1; game.Clear(); TeachMode = false; }
		break;
	}
	//*/
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (Mode == 1)
	{
		if (key == OF_KEY_CONTROL)
			TeachMode = true;
		if (key == OF_KEY_F3)
		{
			LoopMvsMMode = true;
			buttonPressed = 12;
		}
	}
	if (TeachMode && Mode == 2)
	{
		if (key == OF_KEY_DOWN)
			game.Teach(-1);
		if (key == OF_KEY_UP)
			game.Teach(1);
	}
	if (Mode == 2)
	{
		if (key == OF_KEY_BACKSPACE)
			game.ReturnStep();
		if (key == OF_KEY_RIGHT_SHIFT)
		{
			Mode = 1; GameResult = 0; GameMode = buttonPressed = -1; game.Clear(); TeachMode = false;
		}

	}

	if (key == OF_KEY_F4 && LoopMvsMMode)
		LoopMvsMMode = false;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	for (int i(0); i < 13; i++) button[i].mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	if (Mode == 3) { buttonPressed = -1; Mode = 4; }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int _button) {
	for (int i(0); i < 13; i++) {
		buttonPressed = button[i].mousePressed(x, y, _button);
		if (buttonPressed != -1)
			return;
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int _button) {
	for (int i(0); i < 13; i++) button[i].mouseReleased(x, y, _button);
	buttonPressed = -1;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	im.resize(w, h);
	Gridimg.resize(w, h);
	for (int i(0); i < 13; i++) button[i].windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

void DrawResultLine(int GameResult)
{
	switch (GameResult)
	{
	case 0:
		break;
	case 1:
		ofSetColor(255, 0, 0);
		ofLine(0, ofGetHeight() * 0.15625, ofGetWidth(), ofGetHeight() * 0.15625);
		ofSetColor(255, 255, 255);
		break;
	case 2:
		ofSetColor(255, 0, 0);
		ofLine(0, ofGetHeight() / 2, ofGetWidth(), ofGetHeight() / 2);
		ofSetColor(255, 255, 255);
		break;
	case 3:
		ofSetColor(255, 0, 0);
		ofLine(0, ofGetHeight() * 0.83333, ofGetWidth(), ofGetHeight() * 0.83333);
		ofSetColor(255, 255, 255);
		break;
	case 4:
		ofSetColor(255, 0, 0);
		ofLine(ofGetWidth() * 0.15212, 0, ofGetWidth() * 0.15212, ofGetHeight());
		ofSetColor(255, 255, 255);
		break;
	case 5:
		ofSetColor(255, 0, 0);
		ofLine(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight());
		ofSetColor(255, 255, 255);
		break;
	case 6:
		ofSetColor(255, 0, 0);
		ofLine(ofGetWidth() * 0.83164, 0, ofGetWidth() * 0.83164, ofGetHeight());
		ofSetColor(255, 255, 255);
		break;
	case 7:
		ofSetColor(255, 0, 0);
		ofLine(0, 0, ofGetWidth(), ofGetHeight());
		ofSetColor(255, 255, 255);
		break;
	case 8:
		ofSetColor(255, 0, 0);
		ofLine(0, ofGetHeight(), ofGetWidth(), 0);
		ofSetColor(255, 255, 255);
		break;
	}
}