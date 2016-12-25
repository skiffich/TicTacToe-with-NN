#include "MyGUI.h"


//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//------------------------------MyButton-----------------------------------------
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------

MyButton::MyButton()
{
	this->x = 0;
	this->y = 0;
	if (width < ofGetWidth() + x)
		this->width = 50;
	else
		this->width = 10;

	if (height < ofGetHeight() + x)
		this->height = 50;
	else
		this->height = 10;

	this->kWidth = ((x + width) * 100) / ofGetWidth();
	this->kHeight = ((y + height) * 100) / ofGetHeight();
	this->kx = x * 100 / ofGetWidth();
	this->ky = y * 100 / ofGetHeight();

	this->NoJoin2Window = 0;

	currentColor = ofColor::black;

	this->DrawFrame = 0;

	ReturningValue = -1;

	ReturningValue = 0;
}

MyButton::MyButton(float x, float y, float width, float height, int ButtonID, bool DrawFrame, bool NoJoin2Window)
{
	this->x = x;
	this->y = y;
	if (width < ofGetWidth() + x)
		this->width = width;
	else
		this->width = 10;

	if (height < ofGetHeight() + x)
		this->height = height;
	else
		this->height = 10;

	this->kWidth = ((x + width) * 100) / ofGetWidth();
	this->kHeight = ((y + height) * 100) / ofGetHeight();
	this->kx = x * 100 / ofGetWidth();
	this->ky = y * 100 / ofGetHeight();

	this->NoJoin2Window = NoJoin2Window;

	currentColor = defColor;

	this->DrawFrame = DrawFrame;

	ReturningValue = ButtonID;
}

MyButton::~MyButton()
{
}

void MyButton::ButtonSetup(float x, float y, float width, float height, int ButtonID, bool DrawFrame, bool NoJoin2Window)
{
	this->x = x;
	this->y = y;
	if (width < ofGetWidth() + x)
		this->width = width;
	else
		this->width = 10;

	if (height < ofGetHeight() + x)
		this->height = height;
	else
		this->height = 10;

	this->kWidth = width / ofGetWidth();
	this->kHeight = height / ofGetHeight();
	this->kx = x / ofGetWidth();
	this->ky = y / ofGetHeight();

	this->NoJoin2Window = NoJoin2Window;

	currentColor = defColor;

	this->DrawFrame = DrawFrame;

	ReturningValue = ButtonID;
}

void MyButton::setTexture(ofImage img)
{
	img.resize(this->width, this->height);
	this->isImage = true;
	this->texture = img;
}

void MyButton::setTexture(string Path2Img)
{
	ofImage img;
	img.load(Path2Img);
	this->setTexture(img);
}

void MyButton::setText(string text)
{
	this->isText = true;
	this->text = text;
}

void MyButton::setTextFont(ofTrueTypeFont font)
{
	this->font = font;
}

void MyButton::setTextFont(string Path2Font, int FontSize)
{
	ofTrueTypeFont	font;
	this->fontSize = FontSize;
	this->kFontSize = FontSize / ofGetHeight();
	font.load(Path2Font, FontSize);
	this->setTextFont(font);
}

void MyButton::setTextColor(float r, float g, float b)
{
	ofColor color;
	color.r = r;
	color.g = g;
	color.b = b;
	this->setTextColor(color);
}

void MyButton::setTextColor(ofColor color)
{
	this->TextColor = color;
}

void MyButton::setButtonColor(float r, float g, float b)
{
	ofColor color2;
	color2.r = r;
	color2.g = g;
	color2.b = b;
	setButtonColor(color2);
}

void MyButton::setButtonColor(ofColor color)
{
	this->defColor = color;
}

bool MyButton::ChangeColorWhileMouseMovedIn(float r, float g, float b, bool type)
{
	ofColor color2;
	color2.r = r;
	color2.g = g;
	color2.b = b;

	return ChangeColorWhileMouseMovedIn(color2, type);
}

bool MyButton::ChangeColorWhileMouseMovedIn(ofColor color2, bool type)
{
	this->MovedInColor = color2;
	this->ChangeMouseIn = type;
	return type;
}

bool MyButton::ChangeColorWhileMousePressed(float r, float g, float b, bool type)
{
	ofColor color2;
	color2.r = r;
	color2.g = g;
	color2.b = b;
	return ChangeColorWhileMousePressed(color2, type);
}

bool MyButton::ChangeColorWhileMousePressed(ofColor color2, bool type)
{
	this->PressedColor = color2;
	this->ChangeMouseePressed = type;
	return type;
}

void MyButton::DrawButton(ofColor MainWindowColor)
{
	if (this->DrawFrame)
	{
		ofSetColor(ofColor::black);
		ofDrawRectangle(this->x, this->y, this->width, this->height);
		ofSetColor(MainWindowColor);
	}
	if (this->isImage)
		this->texture.draw(this->x, this->y);
	if (this->isText)
	{
		ofSetColor(this->currentColor);
		this->font.drawString(this->text, this->x, this->y + 32);
		ofSetColor(MainWindowColor);
	}

	ButtonDrawed = true;
}

void MyButton::ButtonRemove()
{

}

void MyButton::windowResized(int w, int h)
{
	if (!NoJoin2Window)
	{
		x = ofGetWidth() * kx;
		y = ofGetHeight() * ky;
		width = ofGetWidth() * kWidth;
		height = ofGetHeight() * kHeight;

		texture.resize(width, height);

		font.setLineHeight(height);
	}
}

void MyButton::mouseMoved(int x, int y)
{
	if (x > this->x && y > this->y && x < this->width + this->x && y < this->height + this->y && this->ChangeMouseIn)
		currentColor = this->MovedInColor;
	else
		currentColor = defColor;
	ButtonDrawed = false;
}

int MyButton::mousePressed(int x, int y, int button)
{
	if (ButtonDrawed)
	{
		if (x > this->x && y > this->y && x < this->width + this->x && y < this->height + this->y && this->ChangeMouseePressed)
			currentColor = this->PressedColor;
		else
			currentColor = defColor;
		if (x > this->x && y > this->y && x < this->width + this->x && y < this->height + this->y)
		{
			ButtonPressed = true; return ReturningValue;
		}
		else return -1;
	}
	else ButtonPressed = false;
	return -1;
}

void MyButton::mouseReleased(int x, int y, int button)
{
	ButtonPressed = false;
}