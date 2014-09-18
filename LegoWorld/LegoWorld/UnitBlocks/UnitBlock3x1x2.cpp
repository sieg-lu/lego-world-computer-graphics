#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <iostream>
#include "..\Common\Global.h"
#include "..\Models\MilkshapeModel.h"
#include "UnitBlock3x1x2.h"
using namespace std;

UnitBlock3x1x2::UnitBlock3x1x2(int id, int xindex, int yindex, int zindex, Model *modellower, Model *modelupper, bool vir)
	: UnitBlockBase(id, (float)xindex * 1.0f, (float)yindex * 0.5f, (float)zindex * 1.0f, modellower, modelupper, vir)
{
	mIndexLengthX = 3;
	mIndexLengthY = 1;
	mIndexLengthZ = 2;

	mIndexStepX = 1;
	mIndexStepY = 1;
	mIndexStepZ = 1;

	mIndexStartX = xindex;
	mIndexStartY = yindex;
	mIndexStartZ = zindex;
}

UnitBlock3x1x2::~UnitBlock3x1x2()
{

}

bool UnitBlock3x1x2::Initialize()
{
	return true;
}

bool UnitBlock3x1x2::Update()
{
	Render();
	return true;
}

bool UnitBlock3x1x2::Destroy()
{
	return true;
}

eBlockType UnitBlock3x1x2::getType()
{
	return eBlock3x1x2;
}

bool UnitBlock3x1x2::Rotate(eRotateDegree deg)
{
	switch(deg)
	{
	case eDegree0:
		{
			mIndexLengthX = 3;
			mIndexLengthZ = 2;

			mIndexStepX = 1;
			mIndexStepZ = 1;

		} break;
	case eDegree90:
		{
			mIndexLengthX = -2;
			mIndexLengthZ = 3;

			mIndexStepX = -1;
			mIndexStepZ = 1;
		} break;
	case eDegree180:
		{
			mIndexLengthX = -3;
			mIndexLengthZ = -2;

			mIndexStepX = -1;
			mIndexStepZ = -1;
		} break;
	case eDegree270:
		{
			mIndexLengthX = 2;
			mIndexLengthZ = -3;

			mIndexStepX = 1;
			mIndexStepZ = -1;
		} break;
	}
	return UnitBlockBase::Rotate(deg);
}