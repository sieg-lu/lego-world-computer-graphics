#ifndef __UI_MANAGER_H__
#define __UI_MANAGER_H__

/*
 * This is the button manager class
 * which take controls of all the buttons.
 */

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <iostream>
#include <vector>
#include <cg\cg.h>
#include <cg\cgGL.h>
#include "UIControlButton.h"
using namespace std;

class UIButtonManager : public ObjectBase {
protected:
	int									mIdAssigner;

	vector<UIControlButton*>			mBlocksButtonList;
	UIControlButton						*mCurrentSelectedOne;

	CGcontext							mCgContext;
	CGprofile							mButtonFragmentProfile;
	CGprogram							mButtonFragmentProgram;

	virtual bool						Render();

public:
	UIButtonManager() { }
	virtual ~UIButtonManager() { }

	virtual bool						Initialize();
	virtual bool						Update();
	virtual bool						Destroy();

	bool								LeftClickDown(int xpos, int ypos);
	bool								LeftClickUp(int xpos, int ypos);
	bool								ResetAllButtons();
	bool								ResetButtonsExcept(int id);

	UIControlButton						*GetButtonByType(eButtonType ty);

	inline UIControlButton				*getCurrentSelectedOne() const						{ return mCurrentSelectedOne; }

};

#endif ///> end of __UI_MANAGER_H__