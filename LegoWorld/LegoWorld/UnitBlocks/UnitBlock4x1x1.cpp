#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <iostream>
#include "..\Common\Global.h"
#include "..\Models\MilkshapeModel.h"
#include "UnitBlock4x1x1.h"
using namespace std;

UnitBlock4x1x1::UnitBlock4x1x1(int id, int xindex, int yindex, int zindex, Model *modellower, Model *modelupper, bool vir)
	: UnitBlockBase(id, (float)xindex * 1.0f, (float)yindex * 0.5f, (float)zindex * 1.0f, modellower, modelupper, vir)
{
	mIndexLengthX = 4;
	mIndexLengthY = 1;
	mIndexLengthZ = 1;

	mIndexStepX = 1;
	mIndexStepY = 1;
	mIndexStepZ = 1;

	mIndexStartX = xindex;
	mIndexStartY = yindex;
	mIndexStartZ = zindex;
}

UnitBlock4x1x1::~UnitBlock4x1x1()
{

}

bool UnitBlock4x1x1::Initialize()
{
	return true;
}

bool UnitBlock4x1x1::Update()
{
	Render();
	return true;
}

bool UnitBlock4x1x1::Destroy()
{
	return true;
}

eBlockType UnitBlock4x1x1::getType()
{
	return eBlock4x1x1;
}

bool UnitBlock4x1x1::Rotate(eRotateDegree deg)
{
	switch (deg)
	{
	case eDegree0:
		{
			mIndexLengthX = 4;
			mIndexLengthZ = 1;

			mIndexStepX = 1;
			mIndexStepZ = 1;
		} break;
	case eDegree90:
		{
			mIndexLengthX = -1;
			mIndexLengthZ = 4;

			mIndexStepX = -1;
			mIndexStepZ = 1;
		} break;
	case eDegree180:
		{
			mIndexLengthX = -4;
			mIndexLengthZ = -1;

			mIndexStepX = -1;
			mIndexStepZ = -1;
		} break;
	case eDegree270:
		{
			mIndexLengthX = 1;
			mIndexLengthZ = -4;

			mIndexStepX = 1;
			mIndexStepZ = -1;
		} break;
	}
	return UnitBlockBase::Rotate(deg);
}
