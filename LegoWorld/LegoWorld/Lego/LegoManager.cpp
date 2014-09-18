#include <iostream>
#include <fstream>
#include "..\Utility\Utility.h"

#include "LegoManager.h"
using namespace std;

static float gEyePosition[EYE_POSITION_COUNT_VERT][EYE_POSITION_COUNT_HORI][3] = {
	{
//		{  5, 15,  5 },
		{ -16,  5,   9 },
		{  9,   5,  34 },
		{  34,  5,   9 },
		{  9,   5, -16 },
	},

	{
		{ -16, 10,   9 },
		{  9,  10,  34 },
		{  34, 10,   9 },
		{  9,  10, -16 },
	},

	{
		{ -16, 20,   9 },
		{  9,  20,  34 },
		{  34, 20,   9 },
		{  9,  20, -16 },
	},

	{
		{ -16, 40,   9 },
		{  9,  40,  34 },
		{  34, 40,   9 },
		{  9,  40, -16 },
	},
};

LegoManager* LegoManager::mInstance = NULL;

LegoManager::LegoManager()
{

}

LegoManager::~LegoManager()
{
	if (mInstance) {
		delete mInstance;
	}
}

LegoManager *LegoManager::Instance()
{
	if (!mInstance) {
		mInstance = new	LegoManager();
	}
	return mInstance;
}

bool LegoManager::Initialize()
{
	if (!mModelManager.PreloadAllModels()) {
		return false;
	}

	memset(mBlockMark, 0, sizeof(mBlockMark));
	memset(mKeys, 0, sizeof(mKeys));
	memset(mIsKeyPressed, 0, sizeof(mIsKeyPressed));
	mIdAssigner = 1;
	mVirtualIdAssigner = SPACE_SIZE * SPACE_SIZE * SPACE_SIZE + 1;
	mBlockCount = 0;
	mEyePositionVerticalNumber = 0;
	mEyePositionHorizontalNumber = 0;
	mIsEyeMoving = false;

	mDestEyePosition.setPositionX(gEyePosition[0][0][0]);
	mDestEyePosition.setPositionY(gEyePosition[0][0][1]);
	mDestEyePosition.setPositionZ(gEyePosition[0][0][2]);

	mCurrentEyePosition.setPositionX(gEyePosition[0][0][0]);
	mCurrentEyePosition.setPositionY(gEyePosition[0][0][1]);
	mCurrentEyePosition.setPositionZ(gEyePosition[0][0][2]);

	mGameStatus = eGameStatus::eNormal;

	mLookToPosition[0] = 9.0f;
	mLookToPosition[1] = 0.0f;
	mLookToPosition[2] = 9.0f;

// 	mLookToPosition[0] = 0.0f;
// 	mLookToPosition[1] = 0.0f;
// 	mLookToPosition[2] = 0.0f;

	mGlobalRotateDegree = eDegree0;

	float pos[] = { 14.0f, 45.0f, 14.0f };
	float col[] = { 0.8f, 0.8f, 0.8f };
	float eye[] = { 
		mCurrentEyePosition.getPositionX(), 
		mCurrentEyePosition.getPositionY(), 
		mCurrentEyePosition.getPositionZ() 
	};
	mLight0 = new CgShaderLight(pos, col, eye);
	mLight0->InitLight();

// 	glLightfv(GL_LIGHT0, GL_POSITION, pos);
// 	glLightfv(GL_LIGHT0, GL_DIFFUSE, col);
// 	glLightfv(GL_LIGHT0, GL_AMBIENT, col);
// 	glLightfv(GL_LIGHT0, GL_EMISSION, col);
// 	glLightfv(GL_LIGHT0, GL_SPECULAR, col);
// 	glEnable(GL_LIGHTING);
// 	glEnable(GL_LIGHT0);

	mGround = new LegoGround();
	mGround->Initialize();

// 	AddSaber(0, 0, 0, 1);
// 	AddSaber(1, 0, 0, 1);
// 	AddSaber(1, 0, 1, 1);
// 	AddSaber(0, 0, 1, 1);
// 	AddSaber(0, 0, 0, 2, eDegree0);
// 	AddSaber(7, 0, 3, 5, eDegree180);
// 	AddSaber(1, 0, 5, 3, eDegree90);
// 	AddSaber(10, 0, 10, 5, eDegree270);

//	LoadFromFile("default.sav");

//	int cnt = 0;

// 	AddUnitBlock(eBlock1x1x1, 0, 0, 0);
// 	AddUnitBlock(eBlock1x2x1, 1, 0, 0);
// 	AddUnitBlock(eBlock2x1x1, 2, 0, 0);
//	AddUnitBlock(eBlock4x1x2, 0, 0, 0);

// 	for (int x = 0; x < 1; x++) {
// 		for (int z = 0; z < SPACE_SIZE; z++) {
// 			for (int y = 0; y < SPACE_SIZE; y++) {
// 				cout << mBlockMark[x][y][z] << ' ';
// 			}
// 			cout << endl;
// 		}
// 		cout << endl;
// 	}

	//---------------test---------------
// 	AddUnitBlock(eBlock3x1x2, 0, 0, 0, eDegree0);
// 	AddUnitBlock(eBlock3x1x2, 5, 0, 0, eDegree90);
// 	AddUnitBlock(eBlock3x1x2, 5, 0, 5, eDegree180);
// 	AddUnitBlock(eBlock3x1x2, 0, 0, 5, eDegree270);
	
// 	for (int i = 0; i < 30; i++) {
// 		if (AddUnitBlock(eBlock4x1x2, i, 0, 0, eDegree90, false)) {
// 			cnt++;
// 		}
// 	}
// 	cout << cnt << endl;
	
// 	for (int y = 0; y < 1; y++) {
// 		for (int z = 0; z < SPACE_SIZE; z++) {
// 			for (int x = 0; x < SPACE_SIZE; x++) {
// 				cout << mBlockMark[x][y][z] << ' ';
// 			}
// 			cout << endl;
// 		}
// 	}

// 	//---------test block4x1x1----------
// 	AddUnitBlock(eBlock2x1x1, 0, 0, 0);
// 	AddUnitBlock(eBlock1x1x1, 2, 0, 0);
// 	AddUnitBlock(eBlock1x2x1, 0, 1, 0);
// 	AddUnitBlock(eBlock2x2x1, 0, 0, 1);
// 	AddUnitBlock(eBlock3x1x1, 1, 1, 0);
// 	AddUnitBlock(eBlock3x1x2, 4, 0, 0);
// 	cnt = 0;
// 	for (int i = 0; i < 30; i++) {
// 		if (AddUnitBlock(eBlock4x1x1, i, 0, i)) {
// 			cnt++;
// 		}
// 	}
// 	cout << cnt << endl;
// 
// 
// 	//------test block 3x1x2------------
// 	AddUnitBlock(eBlock2x1x1, 0, 0, 0);
// 	AddUnitBlock(eBlock1x1x1, 2, 0, 0);
// 	AddUnitBlock(eBlock1x2x1, 0, 1, 0);
// 	AddUnitBlock(eBlock2x2x1, 0, 0, 1);
// 	AddUnitBlock(eBlock3x1x1, 1, 1, 0);
// 	cnt = 0;
// 	for (int i = 0; i < 30; i++) {
// 		if (AddUnitBlock(eBlock3x1x2, 2*i, 0, i*2)) {
// 			cnt++;
// 		}
// 	}
// 	cout << cnt << endl;
// 
// 	//--------test block 3x1x1----------
// 	AddUnitBlock(eBlock2x1x1, 0, 0, 0);
// 	AddUnitBlock(eBlock1x1x1, 2, 0, 0);
// 	AddUnitBlock(eBlock1x2x1, 0, 1, 0);
// 	AddUnitBlock(eBlock2x2x1, 0, 0, 1);
// 	cnt = 0;
// 	for (int i = 0; i < 30; i++) {
// 		if (AddUnitBlock(eBlock3x1x1, i, 0, i)) {
// 			cnt++;
// 		}
// 	}
// 	cout << cnt << endl;
// 
// //	--------test block2x2x1------
// 	AddUnitBlock(eBlock2x1x1, 0, 0, 0);
// 	AddUnitBlock(eBlock1x1x1, 2, 0, 0);
// 	AddUnitBlock(eBlock1x2x1, 0, 1, 0);
// 	AddUnitBlock(eBlock2x2x1, 0, 0, 1);



// 	for (int i = 0; i < 300; i++) {
// 		AddUnitBlock(eBlock1x2x1, 0, i, 0);
// 	}
// 
// 	AddUnitBlock(eBlock2x1x1, 0, 0, 0);
// 	AddUnitBlock(eBlock1x1x1, 2, 0, 0);
// 	AddUnitBlock(eBlock1x2x1, 0, 1, 0);
// 	AddUnitBlock(eBlock1x1x1, 0, 0, 1);
// 	int cnt = 0;
// 	for (int i = 0; i < 30; i++) {
// 		if (AddUnitBlock(eBlock2x1x1, rand() % 30, 0, rand() % 30)) {
// 			cnt++;
// 		}
// 	}
// 	cout << cnt << endl;
// 
// 	AddUnitBlock(eBlock1x1x1, 0, 0, 0);
// 	AddUnitBlock(eBlock1x1x1, 1, 0, 0);
// 	AddUnitBlock(eBlock1x2x1, 0, 1, 0);
// 
// 	/*int */cnt = 0;
// 	for (int i = 0; i < 3; i++) {
// 		if (AddUnitBlock(eBlock1x1x1, i, 0, 2)) {
// 			cnt++;
// 		}
// 	}
// 	cout << cnt << endl;
// 
// 	cnt = 0;
// 	for (int i = 0; i < 4; i++) {
// 		if (AddUnitBlock(eBlock1x2x1, i, 0, 1)) {
// 			cnt++;
// 		}
// 	}
// 	cout << cnt << endl;
// 	cnt = 0;
// 	for (int i = 0; i < 4; i++) {
// 		if (AddUnitBlock(eBlock1x2x1, i, 0, 1)) {
// 			cnt++;
// 		}
// 	}
// 	cout << cnt << endl;
// 	cnt = 0;
// 	for (int i = 0; i < 1; i++) {
// 		if (AddUnitBlock(eBlock1x2x1, i, 0, 0)) {
// 			cnt++;
// 		}
// 	}
// 	cout << cnt << endl;

// 	cnt = 0;
// 	for (int i = 0; i < 2; i++) {
// 		if (AddUnitBlock(eBlock1x1x1, i, 0, 0)) {
// 			cnt++;
// 		}
// 	}
// 	cout << cnt << endl;
	
// 	int cnt = 0;
// 	for (int i = 0; i < 30; i++) {
// 		for (int j = 0; j < 30; j++) {
// 			for (int k = 0; k < 30; k++) {
// 				if (AddUnitBlock(eBlock1x2x1, i, j, k)) {
// 					cnt++;
// 				}
// 			}
// 		}
// 	}
// 	cout << cnt << endl;

	return true;
}

bool LegoManager::Render()
{
	mLight0->TurnOnLight();

	bool flag;
//	for (list<UnitBlockBase*>::iterator it = mUnitBlockList.begin(); it != mUnitBlockList.end(); it++) {
	for (int i = 0; i < mUnitBlockList.size(); i++) {
		if (mUnitBlockList[i] == NULL) {
			continue;
		}
		UnitBlockBase *it = mUnitBlockList[i];
		flag = false;
		for (int x = 0, xStep = it->getIndexStepX(), xlen = it->getIndexLengthX(); x != xlen; x += xStep) {
			for (int z = 0, zStep = it->getIndexStepZ(), zlen = it->getIndexLengthZ(); z != zlen; z += xStep) {
				int xxx = it->getIndexStartX() + x;
				int yyy = it->getIndexStartY() + it->getIndexLengthY();
				int zzz = it->getIndexStartZ() + z;
				if (yyy < SPACE_SIZE) {
					if (!mBlockMark[xxx][yyy][zzz]) {
						flag = true;
						break;
					}
				} else {
					flag = true;
					break;
				}
			}
		}
		if (it->getIsExisted()) {
			it->setIsDrawingUpper(flag);
			it->Update();
		}
	}
//	for (list<UnitBlockBase*>::iterator it = mVirtualUnitBlockList.begin(); it != mVirtualUnitBlockList.end(); it++) {
	for (int i = 0; i < mVirtualUnitBlockList.size(); i++) {
		if (mVirtualUnitBlockList[i] == NULL) {
			continue;
		}
		mVirtualUnitBlockList[i]->setIsDrawingUpper(false);
		mVirtualUnitBlockList[i]->Update();
	}
	mGround->Update();

	mLight0->TurnOffLight();

	return true;
}

bool LegoManager::Update()
{
	Render();
	if (!MoveEyePosition()) {
		mGameStatus = eGameStatus::eNormal;
	}
	if (mKeys['W'] && !mIsKeyPressed['W']) {
		ChangeEyePosition(
			(mEyePositionVerticalNumber + 1) % EYE_POSITION_COUNT_VERT, 
			mEyePositionHorizontalNumber);
		mIsKeyPressed['W'] = true;
	} else if (!mKeys['W']) {
		mIsKeyPressed['W'] = false;
	}

	if (mKeys['S'] && !mIsKeyPressed['S']) {
		int vert = (mEyePositionVerticalNumber - 1) % EYE_POSITION_COUNT_VERT;
		if (vert < 0) {
			vert += EYE_POSITION_COUNT_VERT;
		}
		ChangeEyePosition(vert, mEyePositionHorizontalNumber);
		mIsKeyPressed['S'] = true;
	} else if (!mKeys['S']) {
		mIsKeyPressed['S'] = false;
	}

	if (mKeys['A'] && !mIsKeyPressed['A']) {
		int hori = (mEyePositionHorizontalNumber - 1) % EYE_POSITION_COUNT_HORI;
		if (hori < 0) {
			hori += EYE_POSITION_COUNT_HORI;
		}
		ChangeEyePosition(mEyePositionVerticalNumber, hori);
		mIsKeyPressed['A'] = true;
	} else if (!mKeys['A']) {
		mIsKeyPressed['A'] = false;
	}

	if (mKeys['D'] && !mIsKeyPressed['D']) {
		ChangeEyePosition(
			mEyePositionVerticalNumber, 
			(mEyePositionHorizontalNumber + 1) % EYE_POSITION_COUNT_HORI);
		mIsKeyPressed['D'] = true;
	} else if (!mKeys['D']) {
		mIsKeyPressed['D'] = false;
	}

	if (mKeys[' '] && !mIsKeyPressed[' ']) {
//		cout << mGlobalRotateDegree << endl;
		switch (mGlobalRotateDegree)
		{
		case eDegree0:
			mGlobalRotateDegree = eDegree90;
			break;
		case eDegree90:
			mGlobalRotateDegree = eDegree180;
			break;
		case eDegree180:
			mGlobalRotateDegree = eDegree270;
			break;
		case eDegree270:
			mGlobalRotateDegree = eDegree0;
			break;
		}
		mIsKeyPressed[' '] = true;
	} else if (!mKeys[' ']) {
		mIsKeyPressed[' '] = false;
	}

	if (mKeys['Z'] && !mIsKeyPressed['Z']) {
		SaveToFile("default.sav");
		cout << "Save Successfully.\n";
		mIsKeyPressed['Z'] = true;
	} else if (!mKeys['Z']) {
		mIsKeyPressed['Z'] = false;
	}

	return true;
}

bool LegoManager::Destroy()
{
//	for (list<UnitBlockBase*>::iterator it = mUnitBlockList.begin(); it != mUnitBlockList.end(); it++) {
	for (int i = 0; i < mUnitBlockList.size(); i++) {
		if (mUnitBlockList[i] == NULL) {
			continue;
		}
		UnitBlockBase *it = mUnitBlockList[i];
		it->Destroy();
		delete it;
		it = NULL;
	}

	for (int i = 0; i < mVirtualUnitBlockList.size(); i++) {
		if (mVirtualUnitBlockList[i] == NULL) {
			continue;
		}
		UnitBlockBase *it = mVirtualUnitBlockList[i];
		it->Destroy();
		delete it;
		it = NULL;
	}

	mModelManager.UnloadAllModels();

	if (mGround) {
		mGround->Destroy();
		delete mGround;
		mGround = NULL;
	}

	if (mLight0) {
		delete mLight0;
		mLight0 = NULL;
	}

	return true;
}

bool LegoManager::AddSaber(int xindex, int yindex, int zindex, int len /*= 5*/, eRotateDegree deg /*= eDegree0*/)
{
	return AddUnitBlock(eBlockSaber, xindex, yindex, zindex, deg, false, len);
}

bool LegoManager::AddUnitBlock(eBlockType blocktype, int xindex, int yindex, int zindex, eRotateDegree deg, bool isVirual, int len)
{
// 	if (mBlockCount > MAX_BLOCK_COUNT) {
// 		return false;
// 	}
	if (mUnitBlockList.size() > SPACE_SIZE * SPACE_SIZE * SPACE_SIZE) {
		cout << "Space Limit Exceeded...\n";
		return false;
	}
	if (!IsInLegalRange(xindex, 0, SPACE_SIZE) ||
		!IsInLegalRange(yindex, 0, SPACE_SIZE) ||
		!IsInLegalRange(zindex, 0, SPACE_SIZE)) {
			return false;
	}
	UnitBlockBase *block;
	switch(blocktype)
	{
	case eBlock1x1x1:
		{
			block = new UnitBlock1x1x1(mIdAssigner, xindex, yindex, zindex, mModelManager.GetModel(eBlock1x1x1, false), mModelManager.GetModel(eBlock1x1x1, true), isVirual);
		} break;
	case eBlock1x2x1:
		{
			block = new UnitBlock1x2x1(mIdAssigner, xindex, yindex, zindex, mModelManager.GetModel(eBlock1x2x1, false), mModelManager.GetModel(eBlock1x2x1, true), isVirual);
		} break;
	case eBlock2x1x1:
		{
			block = new UnitBlock2x1x1(mIdAssigner, xindex, yindex, zindex, mModelManager.GetModel(eBlock2x1x1, false), mModelManager.GetModel(eBlock2x1x1, true), isVirual);
		} break;
	case eBlock2x2x1:/*yakexi*/
		{
			block = new UnitBlock2x2x1(mIdAssigner, xindex, yindex, zindex, mModelManager.GetModel(eBlock2x2x1, false), mModelManager.GetModel(eBlock2x2x1, true), isVirual);			
		}break;
	case eBlock3x1x1:
		{
			block = new UnitBlock3x1x1(mIdAssigner, xindex, yindex, zindex, mModelManager.GetModel(eBlock3x1x1, false), mModelManager.GetModel(eBlock3x1x1, true), isVirual);
		} break;
	case eBlock3x1x2:
		{
			block = new UnitBlock3x1x2(mIdAssigner, xindex, yindex, zindex, mModelManager.GetModel(eBlock3x1x2, false), mModelManager.GetModel(eBlock3x1x2, true), isVirual);
		} break;
	case eBlock4x1x1:
		{
			block = new UnitBlock4x1x1(mIdAssigner, xindex, yindex, zindex, mModelManager.GetModel(eBlock4x1x1, false), mModelManager.GetModel(eBlock4x1x1, true), isVirual);
		} break;
	case eBlock4x1x2:
		{
			block = new UnitBlock4x1x2(mIdAssigner, xindex, yindex, zindex, mModelManager.GetModel(eBlock4x1x2, false), mModelManager.GetModel(eBlock4x1x2, true), isVirual);
		} break;
	case eBlockSaber:
		{
			block = new LegoSaber(mIdAssigner, xindex, yindex, zindex, len, mModelManager.GetSaberStand(), mModelManager.GetSaberLeft(), mModelManager.GetSaberRight());
			block->Initialize();
		} break;
	}
	block->Rotate(deg);
	if (isVirual) {
		block->setId(mVirtualIdAssigner++);
		block->Initialize();
		mVirtualUnitBlockList.push_back(block);
		return true;
	}

	if (!IsAddable(block)) {
		if (block) {
			delete block;
		}
		return false;
	}

	mIdAssigner++;
	mBlockCount++;
	for (int x = 0, xStep = block->getIndexStepX(); x != block->getIndexLengthX(); x += xStep) {
		for (int z = 0, zStep = block->getIndexStepZ(); z != block->getIndexLengthZ(); z += zStep) {
			for (int y = 0, yStep = block->getIndexStepY(); y != block->getIndexLengthY(); y += yStep) {
				int xxx = block->getIndexStartX() + x;
				int yyy = block->getIndexStartY() + y;
				int zzz = block->getIndexStartZ() + z;
				mBlockMark[xxx][yyy][zzz] = true;
			}
		}
	}
	block->Initialize();
	mUnitBlockList.push_back(block);

	return true;
}

bool LegoManager::UpdateMark()
{
	for (int x = 0; x < SPACE_SIZE; x++) {
		for (int z = 0; z < SPACE_SIZE; z++) {
			for (int y = 0; y < SPACE_SIZE; y++) {
				mBlockMark[x][y][z] = false;
			}
		}
	}
	for (int i = 0; i < mUnitBlockList.size(); i++) {
		UnitBlockBase *block = mUnitBlockList[i];
		for (int x = 0, xStep = block->getIndexStepX(); x != block->getIndexLengthX(); x += xStep) {
			for (int z = 0, zStep = block->getIndexStepZ(); z != block->getIndexLengthZ(); z += zStep) {
				for (int y = 0, yStep = block->getIndexStepY(); y != block->getIndexLengthY(); y += yStep) {
					int xxx = block->getIndexStartX() + x;
					int yyy = block->getIndexStartY() + y;
					int zzz = block->getIndexStartZ() + z;
					mBlockMark[xxx][yyy][zzz] = true;
				}
			}
		}
	}
	return true;
}

bool LegoManager::IsAddable(UnitBlockBase *block)
{
	for (int x = 0, xStep = block->getIndexStepX(); x != block->getIndexLengthX(); x += xStep) {
		for (int z = 0, zStep = block->getIndexStepZ(); z != block->getIndexLengthZ(); z += zStep) {
			for (int y = 0, yStep = block->getIndexStepY(); y != block->getIndexLengthY(); y += yStep) {
				int xxx = block->getIndexStartX() + x;
				int yyy = block->getIndexStartY() + y;
				int zzz = block->getIndexStartZ() + z;
				if (xxx >= SPACE_SIZE || yyy >= SPACE_SIZE || zzz >= SPACE_SIZE ||
					xxx < 0 || yyy < 0 || zzz < 0) {
					return false;
				}
				bool flag = mBlockMark[xxx][yyy][zzz];
				if (flag) {
					return false;
				}
			}
		}
	}

	return true;
}

bool LegoManager::ProcessHit(GLint hits, GLuint buffer[], bool putting)
{
	GLint names, *ptr;
//	printf("hits = %d\n", hits);
	ptr = (GLint *)buffer;

	int dest = 0xfffffff;
	int dist = 0xfffffff;
	for (int i = 0; i < hits; i++) {
		names = *ptr;
		ptr += 3;

		int tmp = -0xfffffff;
		for (int j = 0; j < names; j++) {
//			cout << "ptr: " << (*ptr) << endl;
// 			if ((*ptr) > 0 && (*ptr) <= SPACE_SIZE * SPACE_SIZE * SPACE_SIZE) {
// 				UnitBlockBase *base = FindBlockById(*ptr);
// 				cout << base->getId() << endl;
// 				cout << base->getIndexStartX() << ' ';
// 				cout << base->getIndexStartY() << ' ';
// 				cout << base->getIndexStartZ() << endl;
// 			}
			tmp = (*ptr);
			break;
			ptr++;
		}
		if (tmp < -1) {
//			dest = tmp;
			break;
		}
// 		if (tmp > -1) {
// 			dest = tmp;
// 			break;
// 		}
		float d = Distance2FromBlockToEye(tmp);
//		cout << tmp << ": " << d << endl;
		if (dist > d) {
			dist = d;
			dest = tmp;
		}
	}
//	cout << endl;
	ClearSelectedMark();
	if (dest > 0 && dest <= SPACE_SIZE * SPACE_SIZE * SPACE_SIZE) {
		mUnitBlockList[dest - 1]->setIsSelected(true);
		if (mGameStatus == eDeletingBlock) {
			mUnitBlockList[dest - 1]->setIsExisted(false);
			UnitBlockBase *block = mUnitBlockList[dest - 1];
			for (int x = 0, xStep = block->getIndexStepX(); x != block->getIndexLengthX(); x += xStep) {
				for (int z = 0, zStep = block->getIndexStepZ(); z != block->getIndexLengthZ(); z += zStep) {
					for (int y = 0, yStep = block->getIndexStepY(); y != block->getIndexLengthY(); y += yStep) {
						int xxx = block->getIndexStartX() + x;
						int yyy = block->getIndexStartY() + y;
						int zzz = block->getIndexStartZ() + z;
						mBlockMark[xxx][yyy][zzz] = false;
					}
				}
			}
		}
	} else if (dest > SPACE_SIZE * SPACE_SIZE * SPACE_SIZE && 
		dest <= SPACE_SIZE * SPACE_SIZE * SPACE_SIZE + mVirtualUnitBlockList.size()) {
			mVirtualUnitBlockList[dest - SPACE_SIZE * SPACE_SIZE * SPACE_SIZE - 1]->setIsSelected(true);
			if (putting) {
				UnitBlockBase *block = mVirtualUnitBlockList[dest - SPACE_SIZE * SPACE_SIZE * SPACE_SIZE - 1];
//				cout << mGlobalRotateDegree << endl;
				switch (mGameStatus)
				{
				case eAddingBlock1x1x1:
					{
						AddUnitBlock(eBlock1x1x1, block->getIndexStartX(), block->getIndexStartY(), block->getIndexStartZ(), mGlobalRotateDegree);
					} break;
				case eAddingBlock1x2x1:
					{
						AddUnitBlock(eBlock1x2x1, block->getIndexStartX(), block->getIndexStartY(), block->getIndexStartZ(), mGlobalRotateDegree);
					} break;
				case eAddingBlock2x1x1:
					{
						AddUnitBlock(eBlock2x1x1, block->getIndexStartX(), block->getIndexStartY(), block->getIndexStartZ(), mGlobalRotateDegree);
					} break;
				case eAddingBlock2x2x1:
					{
						AddUnitBlock(eBlock2x2x1, block->getIndexStartX(), block->getIndexStartY(), block->getIndexStartZ(), mGlobalRotateDegree);
					} break;
				case eAddingBlock3x1x1:
					{
						AddUnitBlock(eBlock3x1x1, block->getIndexStartX(), block->getIndexStartY(), block->getIndexStartZ(), mGlobalRotateDegree);
					} break;
				case eAddingBlock3x1x2:
					{
						AddUnitBlock(eBlock3x1x2, block->getIndexStartX(), block->getIndexStartY(), block->getIndexStartZ(), mGlobalRotateDegree);
					} break;
				case eAddingBlock4x1x1:
					{
						AddUnitBlock(eBlock4x1x1, block->getIndexStartX(), block->getIndexStartY(), block->getIndexStartZ(), mGlobalRotateDegree);
					} break;
				case eAddingBlock4x1x2:
					{
						AddUnitBlock(eBlock4x1x2, block->getIndexStartX(), block->getIndexStartY(), block->getIndexStartZ(), mGlobalRotateDegree);
					} break;
				case eAddingBlockSaber:
					{
						AddSaber(block->getIndexStartX(), block->getIndexStartY(), block->getIndexStartZ(), 5, mGlobalRotateDegree);
					} break;
				}
				EndPuttingBlock();
				StartPuttingBlock();
		}
	}

	return true;
}

UnitBlockBase *LegoManager::FindBlockById(int id)
{
	if (id == -1) {
		return mGround;
	} else if (id > 0 && id <= SPACE_SIZE * SPACE_SIZE * SPACE_SIZE) {
		return mUnitBlockList[id - 1];
	} else if (
		id > SPACE_SIZE * SPACE_SIZE * SPACE_SIZE && 
		id <= SPACE_SIZE * SPACE_SIZE * SPACE_SIZE + mVirtualUnitBlockList.size()) {
		return mVirtualUnitBlockList[id - SPACE_SIZE * SPACE_SIZE * SPACE_SIZE - 1];
	}
// 	for (list<UnitBlockBase*>::iterator it = mUnitBlockList.begin(); it != mUnitBlockList.end(); it++) {
// 		if ((*it)->getId() == id) {
// 			return *it;
// 		}
// 	}
// 	for (list<UnitBlockBase*>::iterator it = mVirtualUnitBlockList.begin(); it != mVirtualUnitBlockList.end(); it++) {
// 		if (id == (*it)->getId()) {
// 			return *it;
// 		}
// 	}

	return NULL;
}

bool LegoManager::ChangeEyePosition(int vert, int hori)
{
	switch (mGameStatus)
	{
	case eGameStatus::eNormal:
		{
			if (vert == mEyePositionVerticalNumber && hori == mEyePositionHorizontalNumber) {
				return false;
			}
			if (vert >= EYE_POSITION_COUNT_VERT || vert < 0) {
				return false;
			}
			if (hori >= EYE_POSITION_COUNT_HORI || hori < 0) {
				return false;
			}

			mDestEyePosition.setPositionX(gEyePosition[vert][hori][0]);
			mDestEyePosition.setPositionY(gEyePosition[vert][hori][1]);
			mDestEyePosition.setPositionZ(gEyePosition[vert][hori][2]);

			mEyePositionVerticalNumber = vert;
			mEyePositionHorizontalNumber = hori;

			mEyeMovingStep.setPositionX((mDestEyePosition.getPositionX() - mCurrentEyePosition.getPositionX()) / 60.0f);
			mEyeMovingStep.setPositionY((mDestEyePosition.getPositionY() - mCurrentEyePosition.getPositionY()) / 60.0f);
			mEyeMovingStep.setPositionZ((mDestEyePosition.getPositionZ() - mCurrentEyePosition.getPositionZ()) / 60.0f);

			mIsEyeMoving = true;
			mGameStatus = eGameStatus::eChangingView;
		} break;
	case eGameStatus::eChangingView:
		{

		} break;
	}

	return true;
}

bool LegoManager::MoveEyePosition()
{
	if (!mIsEyeMoving) {
		return true;
	}
	if (mCurrentEyePosition == mDestEyePosition) {
		mCurrentEyePosition.setPositionX(mDestEyePosition.getPositionX());
		mCurrentEyePosition.setPositionY(mDestEyePosition.getPositionY());
		mCurrentEyePosition.setPositionZ(mDestEyePosition.getPositionZ());

		mEyeMovingStep.setPositionX(0.0f);
		mEyeMovingStep.setPositionY(0.0f);
		mEyeMovingStep.setPositionZ(0.0f);

		mIsEyeMoving = false;

		return false;
	}

	mCurrentEyePosition.Move(
		mEyeMovingStep.getPositionX(), 
		mEyeMovingStep.getPositionY(), 
		mEyeMovingStep.getPositionZ());

	return true;
}

bool LegoManager::StartPuttingBlock()
{
	for (int x = 0; x < SPACE_SIZE; x++) {
		for (int z = 0; z < SPACE_SIZE; z++) {
			if (!mBlockMark[x][0][z]) {
				AddUnitBlock(eBlock1x1x1, x, 0, z, eDegree0, true);
			}
			for (int desty = 1; desty < SPACE_SIZE; desty++) {
				if (mBlockMark[x][desty - 1][z] && !mBlockMark[x][desty][z]) {
					AddUnitBlock(eBlock1x1x1, x, desty, z, eDegree0, true);
				}
			}
// 			int desty = 0;
// 			for (; desty < SPACE_SIZE; desty++) {
// 				if (!mBlockMark[x][desty][z]) {
// 					break;
// 				}
// 			}
// 			if (desty < SPACE_SIZE) {
// 				AddUnitBlock(eBlock1x1x1, x, desty, z, true);
// 			}
		}
	}
	for (int i = 0; i < mUnitBlockList.size(); i++) {
		if (mUnitBlockList[i]->getType() == eBlockSaber) {
			mUnitBlockList[i]->setIsActive(false);
		}
	}

	return true;
}

bool LegoManager::EndPuttingBlock()
{
//	for (list<UnitBlockBase*>::iterator it = mVirtualUnitBlockList.begin(); it != mVirtualUnitBlockList.end(); it++) {
	for (int i = 0; i < mVirtualUnitBlockList.size(); i++) {
		if (mVirtualUnitBlockList[i] != NULL) {
			mVirtualUnitBlockList[i]->Destroy();
			delete mVirtualUnitBlockList[i];
			mVirtualUnitBlockList[i] = NULL;
		}
	}
	mVirtualUnitBlockList.clear();
	mVirtualIdAssigner = SPACE_SIZE * SPACE_SIZE * SPACE_SIZE + 1;

	for (int i = 0; i < mUnitBlockList.size(); i++) {
		if (mUnitBlockList[i]->getType() == eBlockSaber) {
			mUnitBlockList[i]->setIsActive(true);
		}
	}

	return true;
}

float LegoManager::Distance2FromBlockToEye(int id)
{
	UnitBlockBase *block;
	block = FindBlockById(id);
	if (block == NULL) {
		return 0xfffffff;
	}
	float xxx = block->getCoordX() - mCurrentEyePosition.getPositionX();
	float yyy = block->getCoordY() - mCurrentEyePosition.getPositionY();
	float zzz = block->getCoordZ() - mCurrentEyePosition.getPositionZ();

	return (xxx * xxx + yyy * yyy + zzz * zzz);
}

bool LegoManager::ClearSelectedMark()
{
	for (int i = 0; i < mUnitBlockList.size(); i++) {
		mUnitBlockList[i]->setIsSelected(false);
	}
	for (int i = 0; i < mVirtualUnitBlockList.size(); i++) {
		mVirtualUnitBlockList[i]->setIsSelected(false);
	}
	return true;
}

bool LegoManager::SaveToFile(string filename)
{
	ofstream fout(filename);
	if (!fout) {
		cout << "File cannot be opened...\n";
		return false;
	}
	fout << mUnitBlockList.size() << endl;
	for (int i = 0; i < mUnitBlockList.size(); i++) {
		fout << mUnitBlockList[i]->getType() << ' ' << mUnitBlockList[i]->getRotateDegree() << ' ';
		fout << mUnitBlockList[i]->getIndexStartX() << ' ' << mUnitBlockList[i]->getIndexStartY() << ' ' << mUnitBlockList[i]->getIndexStartZ() << ' ';
//		fout << mUnitBlockList[i]->getIndexStepX() << ' ' << mUnitBlockList[i]->getIndexStepY() << ' ' << mUnitBlockList[i]->getIndexStepZ() << ' ';
//		fout << mUnitBlockList[i]->getIndexLengthX() << ' ' << mUnitBlockList[i]->getIndexLengthY() << ' ' << mUnitBlockList[i]->getIndexLengthZ() << ' ';
		fout << endl;
	}

	return true;
}

bool LegoManager::LoadFromFile(string filename)
{
	mIdAssigner = 1;
	mVirtualIdAssigner = SPACE_SIZE * SPACE_SIZE * SPACE_SIZE + 1;
	mBlockCount = 0;
	for (int i = 0; i < mUnitBlockList.size(); i++) {
		if (mUnitBlockList[i] == NULL) {
			continue;
		}
		UnitBlockBase *it = mUnitBlockList[i];
		it->Destroy();
		delete it;
		it = NULL;
	}
	memset(mBlockMark, 0, sizeof(mBlockMark));
	mUnitBlockList.clear();
	ifstream fin(filename);
	if (!fin) {
		cout << "File cannot be opened...\n";
		return false;
	}
	int T;
	fin >> T;
	int bt;
	int deg;
	int xxx, yyy, zzz;
	for (int i = 0; i < T; i++) {
		fin >> bt >> deg;
		fin >> xxx >> yyy >> zzz;
		AddUnitBlock((eBlockType)bt, xxx, yyy, zzz, (eRotateDegree)deg);
	}

	mGameStatus = eNormal;

	return true;
}
