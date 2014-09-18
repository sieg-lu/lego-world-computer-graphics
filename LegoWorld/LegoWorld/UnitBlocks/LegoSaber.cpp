#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <iostream>
#include "..\Common\Global.h"
#include "..\Models\MilkshapeModel.h"
#include "LegoSaber.h"
using namespace std;

LegoSaber::LegoSaber(int id, int xindex, int yindex, int zindex, int len, Model *standmodel, Model *leftmodel, Model *rightmodel)
	: UnitBlockBase(id, (float)xindex * 1.0f, (float)yindex * 0.5f, (float)zindex * 1.0f, NULL, NULL, false)
	, mStandModel(standmodel), mLeftModel(leftmodel), mRightModel(rightmodel)
{
	mOrigIndexLengthX = mIndexLengthX = len;
	mOrigIndexLengthY = mIndexLengthY = 3;
	mOrigIndexLengthZ = mIndexLengthZ = 1;

	mIndexStepX = 1;
	mIndexStepY = 1;
	mIndexStepZ = 1;

	mIndexStartX = xindex;
	mIndexStartY = yindex;
	mIndexStartZ = zindex;
}

LegoSaber::~LegoSaber()
{

}

bool LegoSaber::Initialize()
{
	mDirection = mDegree0;
	mUpdateTimes = 0;
	mStep = 0.1f;
	mIsActive = true;

	return true;
}

bool LegoSaber::Render()
{
	glPushMatrix();
	unsigned int swi = mUpdateTimes % 60;
	glLoadName(-2);
	glColor3f(1.0f, 1.0f, 1.0f);
	glScalef(0.25f, 0.3f, 0.25f);
	glTranslatef(mIndexStartX * 3.0f + mCoordX - 2.0f, mIndexStartY * 3.0f + mCoordY - 1.0f, mIndexStartZ * 3.0f + mCoordZ - 2.0f);
	float rot = (float)(mDirection - mRotateDegree) + 90.0f;
	if (rot > 360.0f) {
		rot -= 360.0f;
	}
	if (rot < 0.0f) {
		rot += 360.0f;
	}
	glRotatef(rot, 0.0f, 1.0f, 0.0f);
	if ((swi >= 0 && swi < 15) || (swi >= 30 && swi < 45)) {
		mStandModel->draw();
	} else if (swi >= 15 && swi < 30) {
		mLeftModel->draw();
	} else {
		mRightModel->draw();
	}
	glPopMatrix();

	return true;
}

bool LegoSaber::Update()
{
	Render();

	if (mIsActive) {
		switch (mRotateDegree)
		{
		case eDegree0:
			{
				if (mDirection == mDegree0) {
					mCoordX += mStep;
					if (mCoordX >= (float)(mIndexStartX + 4 * (mIndexLengthX - 1))) {
						mCoordX = (float)(mIndexStartX + 4 * (mIndexLengthX - 1));
						mDirection = mDegree180;
					}
				} else {
					mCoordX -= mStep;
					if (mCoordX <= (float)(mIndexStartX)) {
						mCoordX = (float)(mIndexStartX);
						mDirection = mDegree0;
					}
				}
			} break;
		case eDegree90:
			{
				if (mDirection == mDegree0) {
					mCoordZ += mStep;
					if (mCoordZ >= (float)(mIndexStartZ + 4 * (mIndexLengthZ - 1))) {
						mCoordZ = (float)(mIndexStartZ + 4 * (mIndexLengthZ - 1));
						mDirection = mDegree180;
					}
				} else {
					mCoordZ -= mStep;
					if (mCoordZ <= (float)(mIndexStartZ)) {
						mCoordZ = (float)(mIndexStartZ);
						mDirection = mDegree0;
					}
				}
			} break;
		case eDegree180:
			{
				if (mDirection == mDegree0) {
					mCoordX -= mStep;
					if (mCoordX <= (float)(mIndexStartX + 4 * (mIndexLengthX + 1))) {
						mCoordX = (float)(mIndexStartX + 4 * (mIndexLengthX + 1));
						mDirection = mDegree180;
					}
				} else {
					mCoordX += mStep;
					if (mCoordX >= (float)(mIndexStartX)) {
						mCoordX = (float)(mIndexStartX);
						mDirection = mDegree0;
					}
				}
			} break;
		case eDegree270:
			{
				if (mDirection == mDegree0) {
					mCoordZ -= mStep;
					if (mCoordZ <= (float)(mIndexStartZ + 4 * (mIndexLengthZ + 1))) {
						mCoordZ = (float)(mIndexStartZ + 4 * (mIndexLengthZ + 1));
						mDirection = mDegree180;
					}
				} else {
					mCoordZ += mStep;
					if (mCoordZ >= (float)(mIndexStartZ)) {
						mCoordZ = (float)(mIndexStartZ);
						mDirection = mDegree0;
					}
				}
			} break;
		}

		mUpdateTimes++;
		if (mUpdateTimes > 6000) {
			mUpdateTimes = 0;
		}
	}

	return true;
}

bool LegoSaber::Destroy()
{
	return true;
}

eBlockType LegoSaber::getType()
{
	return eBlockSaber;
}

bool LegoSaber::Rotate(eRotateDegree deg)
{
	switch (deg)
	{
	case eDegree0:
		{
			mIndexLengthX = mOrigIndexLengthX;
			mIndexLengthZ = mOrigIndexLengthZ;

			mIndexStepX = 1;
			mIndexStepZ = 1;
		} break;
	case eDegree90:
		{
			mIndexLengthX = -mOrigIndexLengthZ;
			mIndexLengthZ = mOrigIndexLengthX;

			mIndexStepX = -1;
			mIndexStepZ = 1;
		} break;
	case eDegree180:
		{
			mIndexLengthX = -mOrigIndexLengthX;
			mIndexLengthZ = -mOrigIndexLengthZ;

			mIndexStepX = -1;
			mIndexStepZ = -1;
		} break;
	case eDegree270:
		{
			mIndexLengthX = mOrigIndexLengthZ;
			mIndexLengthZ = -mOrigIndexLengthX;

			mIndexStepX = 1;
			mIndexStepZ = -1;
		} break;
	}
	return UnitBlockBase::Rotate(deg);
}
