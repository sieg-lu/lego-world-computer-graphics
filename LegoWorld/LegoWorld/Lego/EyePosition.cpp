#include "..\Utility\Utility.h"

#include "EyePosition.h"

EyePosition::EyePosition()
{
	mSphere = gluNewQuadric();
}

EyePosition::~EyePosition()
{

}

bool EyePosition::Move(float stepx, float stepy, float stepz)
{
	mPosition[0] += stepx;
	mPosition[1] += stepy;
	mPosition[2] += stepz;

	return true;
}

bool EyePosition::operator==(const EyePosition& b)
{
	return (
		(FloatEquals(mPosition[0], b.mPosition[0])) &&
		(FloatEquals(mPosition[1], b.mPosition[1])) && 
		(FloatEquals(mPosition[2], b.mPosition[2])));
}

bool EyePosition::Render()
{
	glPushMatrix();
	glLoadName(mId);
	glTranslatef(mPosition[0], mPosition[1], mPosition[2]);
	gluSphere(mSphere, 0.5, 8, 16);
	glPopMatrix();

	return true;
}

