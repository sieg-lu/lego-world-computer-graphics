#ifndef __GLOBAL_H__
#define __GLOBAL_H__

/*
 * This file contains some global variables, definitions
 * and some enumerations.
 */

#include <windows.h>
#include <mmsystem.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <iostream>
using namespace std;

#define WINDOW_WIDTH					1200
#define WINDOW_HEIGHT					800

#define UNIT_SIZE_X						1.0f
#define UNIT_SIZE_OFFSET_X				(UNIT_SIZE_X / 2.0f)
#define UNIT_SIZE_Y						0.5f
#define UNIT_SIZE_OFFSET_Y				(UNIT_SIZE_Y / 2.0f)
#define UNIT_SIZE_Z						1.0f
#define UNIT_SIZE_OFFSET_Z				(UNIT_SIZE_Z / 2.0f)

enum eBlockType {
	eEmptyBlock = 0,
	eBlock1x1x1,
	eBlock1x2x1,
	eBlock2x1x1,
	eBlock2x2x1,
	eBlock3x1x1,
	eBlock3x1x2,
	eBlock4x1x1,
	eBlock4x1x2,
	eBlockGround,
	eBlockSaber,
};

enum eButtonType {
	eNull = 0,
	eAdding1x1x1,
	eAdding1x2x1,
	eAdding2x1x1,
	eAdding2x2x1,
	eAdding3x1x1,
	eAdding3x1x2,
	eAdding4x1x1,
	eAdding4x1x2,
	eAddingSaber,
	eSaving,
	eLoading,
	eDeleting,
	eSelecting,
};

#define FPS								60
static HDC								hDC = NULL;
static HGLRC							hRC = NULL;
static HWND								hWnd = NULL;
static HINSTANCE						hInstance;

static bool								active = TRUE;
static int								fps = 60;

enum eGameStatus {
	eNormal = 0,
	eChangingView,
	eAddingBlock1x1x1,
	eAddingBlock1x2x1,
	eAddingBlock2x1x1,
	eAddingBlock2x2x1,
	eAddingBlock3x1x1,
	eAddingBlock3x1x2,
	eAddingBlock4x1x1,
	eAddingBlock4x1x2,
	eAddingBlockSaber,
	eDeletingBlock,
};

enum eRotateDegree {
	eDegree0 = 0,
	eDegree90 = 90,
	eDegree180 = 180,
	eDegree270 = 270,
};

enum eSaberCommand {
	eStanding = 0,
	eMovingForward,
	eTurningLeft,
	eTurningRight,
};

#endif ///> end of __GLOBAL_H__