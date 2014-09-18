#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <iostream>
#include "..\Common\Global.h"
#include "..\Models\MilkshapeModel.h"
#include "UnitBlock1x2x1.h"
using namespace std;

UnitBlock1x2x1::UnitBlock1x2x1(int id, int xindex, int yindex, int zindex, Model *modellower, Model *modelupper, bool vir)
	: UnitBlockBase(id, (float)xindex * 1.0f, (float)yindex * 0.5f, (float)zindex * 1.0f, modellower, modelupper, vir)
{
	mIndexLengthX = 1;
	mIndexLengthY = 2;
	mIndexLengthZ = 1;

	mIndexStepX = 1;
	mIndexStepY = 1;
	mIndexStepZ = 1;

	mIndexStartX = xindex;
	mIndexStartY = yindex;
	mIndexStartZ = zindex;
}

UnitBlock1x2x1::~UnitBlock1x2x1()
{

}

bool UnitBlock1x2x1::Initialize()
{
	// 	pModelLower = new MilkshapeModel();
	// 	pModelUpper = new MilkshapeModel();
	// 	if (!pModelLower->loadModelData("1x2x1(Lower).ms3d")) {
	// 		cout << "Unable to load the 1x2x1(Lower).ms3d...\n";
	// 		return false;
	// 	}
	// 	if (!pModelUpper->loadModelData("1x2x1(Upper).ms3d")) {
	// 		cout << "Unable to load the 1x2x1(Upper).ms3d...\n";
	// 		return false;
	// 	}
	// 	pModelLower->reloadTextures();
	// 	pModelUpper->reloadTextures();

	return true;
}

bool UnitBlock1x2x1::Update()
{
	Render();
	return true;
}

bool UnitBlock1x2x1::Destroy()
{
	// 	if (pModelLower) {
	// 		delete pModelLower;
	// 		pModelLower = NULL;
	// 	}
	// 	if (pModelUpper) {
	// 		delete pModelUpper;
	// 		pModelUpper = NULL;
	// 	}
	return true;
}

eBlockType UnitBlock1x2x1::getType()
{
	return eBlock1x2x1;
}

bool UnitBlock1x2x1::Rotate(eRotateDegree deg)
{
	switch (deg)
	{
	case eDegree0:
		{
			mIndexLengthX = 1;
			mIndexLengthZ = 1;

			mIndexStepX = 1;
			mIndexStepZ = 1;
		} break;
	case eDegree90:
		{
			mIndexLengthX = -1;
			mIndexLengthZ = 1;

			mIndexStepX = -1;
			mIndexStepZ = 1;
		} break;
	case eDegree180:
		{
			mIndexLengthX = -1;
			mIndexLengthZ = -1;

			mIndexStepX = -1;
			mIndexStepZ = -1;
		} break;
	case eDegree270:
		{
			mIndexLengthX = 1;
			mIndexLengthZ = -1;

			mIndexStepX = 1;
			mIndexStepZ = -1;
		} break;
	}
	return UnitBlockBase::Rotate(deg);
}