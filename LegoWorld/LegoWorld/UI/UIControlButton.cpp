#include "..\Common\Global.h"
#include "..\Lego\LegoManager.h"
#include "..\Utility\Utility.h"
#include "UIControlButton.h"

UIControlButton::UIControlButton(int id, eButtonType ty, float xpos, float ypos, float width, float height, const char *filename1, const char *filename2, CGcontext *context, CGprofile *profile, CGprogram *prog)
	: mId(id), mButtonType(ty)
	, mCoordX(xpos), mCoordY(ypos)
	, mButtonWidth(width), mButtonHeight(height)
	, mIsClicked(false), mIsOn(false)
	, mpCgContext(context), mpButtonFragmentProfile(profile), mpButtonFragmentProgram(prog)
{
	mTextureFilename1 = filename1;
	mTextureFilename2 = filename2;
}

bool UIControlButton::Initialize()
{
	mButtonTexture1 = LoadGLTexture(mTextureFilename1.c_str());
	mButtonTexture2 = LoadGLTexture(mTextureFilename2.c_str());

	mCgParamDecal = cgGetNamedParameter(*mpButtonFragmentProgram, "decal");
	CheckForCgError("Getting Decal Parameter", *mpCgContext);

	mCgParamReverse = cgGetNamedParameter(*mpButtonFragmentProgram, "reverse");
	CheckForCgError("Getting Reverse Parameter", *mpCgContext);

	return true;
}

bool UIControlButton::Render()
{
	cgGLSetParameter1f(mCgParamReverse, (mIsOn ? 1.0f : 0.5f));
	CheckForCgError("Setting Reverse", *mpCgContext);

	cgGLBindProgram(*mpButtonFragmentProgram);
	CheckForCgError("Binding Fragment Program", *mpCgContext);

	cgGLEnableProfile(*mpButtonFragmentProfile);
	CheckForCgError("Enabling Fragment Profile", *mpCgContext);

	cgGLEnableTextureParameter(mCgParamDecal);
	CheckForCgError("Enable Decal Texture", *mpCgContext);

	if (LegoManager::Instance()->getGlobalRotateDegree() == eDegree0 ||
		LegoManager::Instance()->getGlobalRotateDegree() == eDegree180) {
		glBindTexture(GL_TEXTURE_2D, mButtonTexture1);
		cgGLSetTextureParameter(mCgParamDecal, mButtonTexture1);
		CheckForCgError("Setting Decal 2D Texture", *mpCgContext);
	} else {
		glBindTexture(GL_TEXTURE_2D, mButtonTexture2);
		cgGLSetTextureParameter(mCgParamDecal, mButtonTexture2);
		CheckForCgError("Setting Decal 2D Texture", *mpCgContext);
	}
	glPushMatrix();
	float halfX = mButtonWidth / 2.0f;
	float halfY = mButtonHeight / 2.0f;
	glTranslatef(mCoordX + halfX, mCoordY + halfY, 0);
	if (mIsClicked) {
		glScalef(0.98f, 0.98f, 0.98f);
	}
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, 0); glVertex3f(-halfX, -halfY, 0.0f);
		glTexCoord2d(1, 0); glVertex3f( halfX, -halfY, 0.0f);
		glTexCoord2d(1, 1); glVertex3f( halfX,  halfY, 0.0f);
		glTexCoord2d(0, 1); glVertex3f(-halfX,  halfY, 0.0f);
	}
	glEnd();
	glPopMatrix();

	cgGLDisableTextureParameter(mCgParamDecal);
	CheckForCgError("Disable Decal Texture", *mpCgContext);

	cgGLDisableProfile(*mpButtonFragmentProfile);
	CheckForCgError("Disabling Fragment Profile", *mpCgContext);

	return true;
}

bool UIControlButton::Update()
{
	Render();
	return true;
}

bool UIControlButton::Destroy()
{
	return true;
}

bool UIControlButton::LeftClickDown(int xpos, int ypos)
{
// 	cout << mTextureFilename << endl;
// 	cout << mCoordX << ' ' << xpos << ' ' << mCoordX + mButtonWidth << endl;
// 	cout << mCoordY << ' ' << ypos << ' ' << mCoordY + mButtonHeight << endl;
	if ((xpos >= mCoordX && xpos <= mCoordX + mButtonWidth) &&
		(ypos >= mCoordY && ypos <= mCoordY + mButtonHeight)) {
//			cout << mTextureFilename << " Clicked!.\n";
			mIsClicked = true;
			return true;
	}
	return false;
}

bool UIControlButton::LeftClickUp(int xpos, int ypos)
{
	bool flag = false;
	if (mIsClicked &&
		(xpos >= mCoordX && xpos <= mCoordX + mButtonWidth) &&
		(ypos >= mCoordY && ypos <= mCoordY + mButtonHeight)) {
		mIsOn = !mIsOn;
		flag = true;
	}
	mIsClicked = false;
	return flag;
// 	if (mIsOn) {
// 		return true;
// 	}
// 	return false;
}

void UIControlButton::TurnButtonStatus(bool status)
{
	mIsOn = status;
}

