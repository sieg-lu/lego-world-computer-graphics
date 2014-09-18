#ifndef __LEGO_MANAGER__
#define __LEGO_MANAGER__

#include <iostream>
#include <list>
#include <vector>
#include "CgShaderLight.h"
#include "EyePosition.h"
#include "..\Models\ModelManager.h"
#include "..\Common\ObjectBase.h"
#include "..\UnitBlocks\UnitBlockBase.h"
#include "..\UnitBlocks\UnitBlock1x1x1.h"
#include "..\UnitBlocks\UnitBlock1x2x1.h"
#include "..\UnitBlocks\UnitBlock2x1x1.h"
#include "..\UnitBlocks\UnitBlock2x2x1.h"
#include "..\UnitBlocks\UnitBlock3x1x1.h"
#include "..\UnitBlocks\UnitBlock3x1x2.h"
#include "..\UnitBlocks\UnitBlock4x1x1.h"
#include "..\UnitBlocks\UnitBlock4x1x2.h"
#include "..\UnitBlocks\LegoGround.h"
#include "..\UnitBlocks\LegoSaber.h"
using namespace std;

#define SPACE_SIZE					20
#define EYE_POSITION_COUNT_HORI		4
#define EYE_POSITION_COUNT_VERT		4
//#define MAX_BLOCK_COUNT				1000

enum eBlockType;

class LegoManager {
private:
	LegoManager();
	~LegoManager();

	eGameStatus							mGameStatus;

	bool								IsAddable(UnitBlockBase *block);

	static LegoManager					*mInstance;

	ModelManager						mModelManager;

	int									mIdAssigner;
	int									mVirtualIdAssigner;

// 	list<UnitBlockBase*>				mUnitBlockList;
// 	list<UnitBlockBase*>				mVirtualUnitBlockList;
	vector<UnitBlockBase*>				mUnitBlockList;
	vector<UnitBlockBase*>				mVirtualUnitBlockList;

	UnitBlockBase						*mGround;
	int									mBlockCount;
	bool								mBlockMark[SPACE_SIZE][SPACE_SIZE][SPACE_SIZE];

	bool								mIsEyeMoving;
	EyePosition							mCurrentEyePosition;
	EyePosition							mDestEyePosition;
	EyePosition							mBackupEyePosition;
	EyePosition							mEyeMovingStep;
	float								mLookToPosition[3];

	bool								mKeys[256];
	bool								mIsKeyPressed[256];

	CgShaderLight						*mLight0;

	int									mEyePositionVerticalNumber;
	int									mEyePositionHorizontalNumber;

	EyePosition							mTestingEye;
	vector<EyePosition>					mPossibleEyePositionList;

	eRotateDegree						mGlobalRotateDegree;

	bool								Render();
	bool								ClearSelectedMark();
	bool								UpdateMark();

public:
	static LegoManager					*Instance();

	bool								Initialize();
	bool								Update();
	bool								Destroy();

//	bool								DeleteBlock();

	bool								SaveToFile(string filename);
	bool								LoadFromFile(string filename);

	bool								ProcessHit(GLint hits, GLuint buffer[], bool putting);
	UnitBlockBase						*FindBlockById(int id);
	float								Distance2FromBlockToEye(int id);

	bool								AddUnitBlock(eBlockType blocktype, int xindex, int yindex, int zindex, eRotateDegree deg = eDegree0, bool isVirual = false, int len = 5);
	bool								AddSaber(int xindex, int yindex, int zindex, int len = 5, eRotateDegree deg = eDegree0);

	bool								ChangeEyePosition(int vert, int hori);
	bool								MoveEyePosition();

	bool								StartPuttingBlock();
	bool								EndPuttingBlock();

	inline void							PressKey(int key)						{ mKeys[key] = true; }
	inline void							ReleaseKey(int key)						{ mKeys[key] = false; }
	inline bool							IsKeyPressed(int key)					{ return mKeys[key]; }

	inline float						getLookToPositionX() const				{ return mLookToPosition[0]; }
	inline void							setLookToPositionX(float val)			{ mLookToPosition[0] = val; }
	inline float						getLookToPositionY() const				{ return mLookToPosition[1]; }
	inline void							setLookToPositionY(float val)			{ mLookToPosition[1] = val; }
	inline float						getLookToPositionZ() const				{ return mLookToPosition[2]; }
	inline void							setLookToPositionZ(float val)			{ mLookToPosition[2] = val; }

	inline eGameStatus					getGameStatus() const					{ return mGameStatus; }
	inline void							setGameStatus(eGameStatus val)			{ mGameStatus = val; }
	
	inline EyePosition					getCurrentEyePosition() const			{ return mCurrentEyePosition; }
	inline eRotateDegree				getGlobalRotateDegree() const			{ return mGlobalRotateDegree; }

};


#endif ///> end of __LEGO_MANAGER__