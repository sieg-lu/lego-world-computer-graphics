#ifndef __CG_SHADER_LIGHT__
#define __CG_SHADER_LIGHT__

/*
 * This is the CgShaderLight class,
 * which mix the light and the color functions.
 */

#include <cg\cg.h>
#include <cg\cgGL.h>

class CgShaderLight {
private:
	CGprofile				mCGprofileVertex;
	CGprofile				mCGprofilePixel;
	CGcontext				mCGcontext;
	CGprogram				mCGvertex_t;
	CGprogram				mCGpixel_t;

	float					mLightColor[3];
	float					mKe[3];
	float					mKa[3];
	float					mKd[3];
	float					mKs[3];
	float					mShininess;
	float					mGlobalAmbient[3];
	float					mLightPosition[3];
	float					mEyePosition[3];

public:
	CgShaderLight(float pos[3], float color[3], float eye[3]);
	~CgShaderLight();

	bool					InitLight();

	bool					TurnOnLight();
	bool					TurnOffLight();

};

#endif ///> end of __CG_SHADER_LIGHT__