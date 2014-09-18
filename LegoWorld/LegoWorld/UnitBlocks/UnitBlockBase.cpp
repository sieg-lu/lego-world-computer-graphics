#include "..\Common\Global.h"
#include "UnitBlockBase.h"

UnitBlockBase::UnitBlockBase(int id, float x, float y, float z, Model *modellower, Model *modelupper, bool vir)
	: mId(id)
	, mCoordX(x), mCoordY(y), mCoordZ(z), mRotateDegree(eDegree0)
	, pModelLower(modellower), pModelUpper(modelupper)
	, mIsDrawingUpper(true), mIsSelected(false), mIsVirtual(vir), mIsExisted(true)
{
//	int index = rand() % PREDEFINE_COLOR_COUNT;
	int index = id % PREDEFINE_COLOR_COUNT;
	mRed = gPredefineColor[index][0];
	mGreen = gPredefineColor[index][1];
	mBlue = gPredefineColor[index][2];
}

bool UnitBlockBase::Render()
{
	glPushMatrix();
	if (mIsVirtual) {
		glEnable(GL_BLEND);
		if (mIsSelected) {
			glColor3f(mRed, mGreen, mBlue);
		} else {
			glColor4f(0.1f, 0.1f, 0.1f, 1.0f);
		}
	} else {
		if (mIsSelected) {
			glColor3f(1.0f - mRed, 1.0f - mGreen, 1.0f - mBlue);
		} else {
			glColor3f(mRed, mGreen, mBlue);
		}
	}
	int xTrans = abs(mIndexLengthX), zTrans = abs(mIndexLengthZ);
	if (mIndexLengthX < 0) {
		xTrans = -xTrans + 2;
	}
	if (mIndexLengthZ < 0) {
		zTrans = -zTrans + 2;
	}
	glTranslatef(
		mCoordX + UNIT_SIZE_OFFSET_X * (float)(xTrans - 2), 
		mCoordY - UNIT_SIZE_OFFSET_Y, 
		mCoordZ + UNIT_SIZE_OFFSET_Z * (float)(zTrans - 2));
	glRotatef((float)mRotateDegree, 0.0f, 1.0f, 0.0f);
	glLoadName(mId);
	pModelLower->draw();
	if (mIsDrawingUpper) {
		pModelUpper->draw();
	}
	if (mIsVirtual) {
		glDisable(GL_BLEND);
	}
	glPopMatrix();

	return true;
}

bool UnitBlockBase::Rotate(eRotateDegree deg)
{
	mRotateDegree = deg;
	return true;
}
