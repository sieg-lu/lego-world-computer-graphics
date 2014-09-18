#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <iostream>
#include "..\Common\Global.h"
#include "..\Models\MilkshapeModel.h"
#include "LegoGround.h"
using namespace std;

LegoGround::LegoGround()
	: UnitBlockBase(-1, 9.0f, -0.25f, 9.0f, NULL, NULL, false)
{
	mRed = mGreen = mBlue = 0.6f;
}

LegoGround::~LegoGround()
{

}

bool LegoGround::Initialize()
{
	pModelLower = new MilkshapeModel();
	if (!pModelLower->loadModelData("ground20x20.ms3d")) {
		cout << "Unable to load the ground.ms3d...\n";
		return false;
	}
	pModelLower->reloadTextures();

	return true;
}

bool LegoGround::Render()
{
	glPushMatrix();
	glColor3f(mRed, mGreen, mBlue);
	glLoadName(mId);
	glTranslatef(mCoordX, mCoordY, mCoordZ);
	pModelLower->draw();
	glPopMatrix();

	return true;
}

bool LegoGround::Update()
{
	Render();
	return true;
}

bool LegoGround::Destroy()
{
	if (pModelLower) {
		delete pModelLower;
		pModelLower = NULL;
	}
	return true;
}

eBlockType LegoGround::getType()
{
	return eBlockGround;
}
