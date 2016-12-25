#pragma once
#pragma once

#include "ofMain.h"

using namespace std;

class MyButton
{
private:
	bool NoJoin2Window;
	bool DrawFrame;
	ofImage texture;
	ofTrueTypeFont font;
	string text;
	float x, y, width, height;

	ofColor defColor = ofColor::whiteSmoke;
	ofColor MovedInColor;
	ofColor PressedColor;
	ofColor TextColor;
	ofColor currentColor;

	bool ChangeMouseIn, ChangeMouseePressed;

	float kx, kWidth;
	float ky, kHeight;

	float fontSize;
	float kFontSize;

public:
	MyButton();
	/* x,y - coord of left top corner
	** width, height - width, height of button
	** Join2Window = 1 - buttons will not resize after resizing window
	** default is joined */
	MyButton(float x, float y, float width, float height, int ButtonID, bool DrawFrame = 0, bool NoJoin2Window = 0);

	~MyButton();

	bool ButtonPressed;

	bool ButtonDrawed;

	bool isImage;

	bool isText;

	int ReturningValue;

	void ButtonSetup(float x, float y, float width, float height, int ButtonID = 0, bool DrawFrame = 0, bool NoJoin2Window = 0);

	void setTexture(ofImage img);
	void setTexture(string Path2Img);

	void setTextFont(ofTrueTypeFont font);
	void setTextFont(string Path2Font, int FontSize = 10);

	void setText(string text);

	void setTextColor(float r, float g, float b);
	void setTextColor(ofColor color);

	void setButtonColor(float r, float g, float b);
	void setButtonColor(ofColor color);

	//if type is true color will change
	bool ChangeColorWhileMouseMovedIn(float r, float g, float b, bool type = 0);
	bool ChangeColorWhileMouseMovedIn(ofColor color2, bool type = 0);
	bool ChangeColorWhileMousePressed(float r, float g, float b, bool type = 0);
	bool ChangeColorWhileMousePressed(ofColor color2, bool type = 0);

	void DrawButton(ofColor MainWindowColor = ofColor::white);

	void ButtonRemove();

	void windowResized(int w, int h);
	void mouseMoved(int x, int y);
	int mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
};