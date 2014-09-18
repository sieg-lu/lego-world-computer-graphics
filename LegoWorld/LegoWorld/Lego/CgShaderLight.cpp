#include <Windows.h>
#include "..\Utility\Utility.h"

#include "CgShaderLight.h"

CgShaderLight::CgShaderLight(float pos[3], float color[3], float eye[3])
{
	mLightPosition[0] = pos[0];
	mLightPosition[1] = pos[1];
	mLightPosition[2] = pos[2];

	mLightColor[0] = color[0];
	mLightColor[1] = color[1];
	mLightColor[2] = color[2];

	mEyePosition[0] = eye[0];
	mEyePosition[1] = eye[1];
	mEyePosition[2] = eye[2];

	mGlobalAmbient[0] = 0.2f;
	mGlobalAmbient[1] = 0.2f;
	mGlobalAmbient[2] = 0.2f;

	for (int i = 0; i < 3; i++) {
		mKe[i] = mLightColor[i];
		mKa[i] = mLightColor[i];
		mKd[i] = mLightColor[i];
		mKs[i] = mLightColor[i];
	}

	mShininess = 20.0f;
}

CgShaderLight::~CgShaderLight()
{

}

bool CgShaderLight::InitLight()
{
	if (cgGLIsProfileSupported(CG_PROFILE_ARBVP1)) {
		mCGprofileVertex = CG_PROFILE_ARBVP1;
	} else if (cgGLIsProfileSupported(CG_PROFILE_VP40)) {
		mCGprofileVertex = CG_PROFILE_VP40;
	} else {
		MessageBox(NULL,"Failed to initialize vertex shader! Hardware doesn't "
			"support any of the required vertex shading extensions!",
			"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	//
	// Search for a valid pixel shader profile in this order:
	//
	// CG_PROFILE_ARBFP1 - GL_ARB_fragment_program
	// CG_PROFILE_FP30   - GL_NV_fragment_program
	// CG_PROFILE_FP20   - NV_texture_shader & NV_register_combiners
	//
	if (cgGLIsProfileSupported(CG_PROFILE_ARBFP1)) {
		mCGprofilePixel = CG_PROFILE_ARBFP1;
	} else if (cgGLIsProfileSupported(CG_PROFILE_FP30)) {
		mCGprofilePixel = CG_PROFILE_FP30;
	} else if (cgGLIsProfileSupported(CG_PROFILE_FP20)) {
		mCGprofilePixel = CG_PROFILE_FP20;
	} else {
		MessageBox(NULL,"Failed to initialize pixel shader! Hardware doesn't "
			"support any of the required pixel shading extensions!",
			"ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}
	// Create the context...
	mCGcontext = cgCreateContext();
	//
	// Create the vertex and pixel shader...
	//

	mCGvertex_t = 
		cgCreateProgramFromFile(
			mCGcontext,
			CG_SOURCE,
			"vertex_t.cg",
			mCGprofileVertex,
			"vs_main",
			NULL);
	CheckForCgError("", mCGcontext);
	mCGpixel_t = 
		cgCreateProgramFromFile( 
			mCGcontext,
			CG_SOURCE,
			"pixel_t.cg",
			mCGprofilePixel,
			"fs_main",
			NULL);
	CheckForCgError("", mCGcontext);
	//
	// Load the programs using Cg's expanded interface...
	//
	cgGLLoadProgram(mCGvertex_t);
	cgGLLoadProgram(mCGpixel_t);

	return true;
}

bool CgShaderLight::TurnOnLight()
{
	cgSetParameter3fv(cgGetNamedParameter(mCGpixel_t, "globalAmbient"), mGlobalAmbient);
	cgSetParameter3fv(cgGetNamedParameter(mCGpixel_t, "lightColor"), mLightColor);
	cgSetParameter3fv(cgGetNamedParameter(mCGpixel_t, "lightPosition"), mLightPosition);
	cgSetParameter3fv(cgGetNamedParameter(mCGpixel_t, "eyePosition"), mEyePosition);
	cgSetParameter3fv(cgGetNamedParameter(mCGpixel_t, "Ke"), mKe);
	cgSetParameter3fv(cgGetNamedParameter(mCGpixel_t, "Ka"), mKa);
	cgSetParameter3fv(cgGetNamedParameter(mCGpixel_t, "Kd"), mKd);
	cgSetParameter3fv(cgGetNamedParameter(mCGpixel_t, "Ks"), mKs);
	cgSetParameter1f(cgGetNamedParameter(mCGpixel_t, "shininess"), mShininess);
	cgGLBindProgram(mCGvertex_t);
	cgGLEnableProfile(mCGprofileVertex);
	cgGLBindProgram(mCGpixel_t);
	cgGLEnableProfile(mCGprofilePixel);

	return true;
}

bool CgShaderLight::TurnOffLight()
{
	cgGLDisableProfile(mCGprofilePixel);
	cgGLDisableProfile(mCGprofileVertex);

	return true;
}

