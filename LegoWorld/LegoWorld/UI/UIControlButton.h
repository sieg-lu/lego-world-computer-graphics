#ifndef __UI_CONTROL_BUTTON_H__
#define __UI_CONTROL_BUTTON_H__

/*
 * This is the button class
 * which draws the button on the screen.
 */

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <iostream>
#include <string>
#include <cg\cg.h>
#include <cg\cgGL.h>
#include "..\Common\ObjectBase.h"
using namespace std;

class UIControlButton : public ObjectBase {
//protected:
public:
	int									mId;
	eButtonType							mButtonType;

	GLuint								mButtonTexture1;
	GLuint								mButtonTexture2;
	string								mTextureFilename1;
	string								mTextureFilename2;

	float								mCoordX;
	float								mCoordY;
	float								mButtonWidth;
	float								mButtonHeight;

	bool								mIsClicked;
	bool								mIsOn;

	CGcontext							*mpCgContext;
	CGprofile							*mpButtonFragmentProfile;
	CGprogram							*mpButtonFragmentProgram;

	CGparameter							mCgParamDecal;
	CGparameter							mCgParamReverse;

	virtual bool						Render();

public:
	UIControlButton(int id, eButtonType ty, float xpos, float ypos, float width, float height, const char *filename1, const char *filename2, CGcontext *context, CGprofile *profile, CGprogram *prog);
	virtual ~UIControlButton() { }

	virtual bool						Initialize();
	virtual bool						Update();
	virtual bool						Destroy();

	bool								LeftClickDown(int xpos, int ypos);	// return if this button is clicked inside?
	bool								LeftClickUp(int xpos, int ypos);	// return if this button is clicked inside?

	void								TurnButtonStatus(bool status);

	inline eButtonType					getButtonType() const				{ return mButtonType; }
	inline bool							getIsOn() const						{ return mIsOn; }
	inline void							setIsOn(bool val)					{ mIsOn = val; }

};

#endif ///> end of __UI_CONTROL_BUTTON_H__