#ifndef __EYE_POSITION_H__
#define __EYE_POSITION_H__

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <iostream>
using namespace std;

class EyePosition {
private:
	int									mId;
	float								mPosition[3];
	GLUquadricObj						*mSphere;
	int									mPosNumber;

public:
	EyePosition();
	~EyePosition();

	bool								Move(float stepx, float stepy, float stepz);
	bool								operator == (const EyePosition& b);

	bool								Render();

	inline float						getPositionX() const			{ return mPosition[0]; }
	inline void							setPositionX(float val)			{ mPosition[0] = val; }
	inline float						getPositionY() const			{ return mPosition[1]; }
	inline void							setPositionY(float val)			{ mPosition[1] = val; }
	inline float						getPositionZ() const			{ return mPosition[2]; }
	inline void							setPositionZ(float val)			{ mPosition[2] = val; }

	inline int							getId() const					{ return mId; }
	inline void							setId(int val)					{ mId = val; }

};


#endif ///> end of __EYE_POSITION_H__