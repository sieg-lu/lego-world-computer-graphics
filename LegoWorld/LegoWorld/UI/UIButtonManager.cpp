#include "..\Common\Global.h"
#include "..\Utility\Utility.h"
#include "UIButtonManager.h"
#include "..\Lego\LegoManager.h"

bool UIButtonManager::Initialize()
{
	mIdAssigner = 0;
	mCurrentSelectedOne = NULL;

	mCgContext = cgCreateContext();
	CheckForCgError("Creating Context", mCgContext);
	cgGLSetDebugMode(CG_FALSE);
	cgSetParameterSettingMode(mCgContext, CG_DEFERRED_PARAMETER_SETTING);

	mButtonFragmentProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);
	cgGLSetOptimalOptions(mButtonFragmentProfile);
	CheckForCgError("Selecting Fragment Profile", mCgContext);

	mButtonFragmentProgram =
		cgCreateProgramFromFile(
			mCgContext,
			CG_SOURCE,
			"button_pixel_t.cg",
			mButtonFragmentProfile,
			"fs_main",
			NULL);
	CheckForCgError("Creating Fragment Program From File", mCgContext);
	cgGLLoadProgram(mButtonFragmentProgram);
	CheckForCgError("Selecting Fragment Profile", mCgContext);

// 	UIControlButton *add1x1x1Button = new UIControlButton(mIdAssigner++, eButtonType::eAdding1x2x1, 10, 130, 100, 50, "Blue.bmp", &mCgContext, &mButtonFragmentProfile, &mButtonFragmentProgram);
// 	UIControlButton *add1x2x1Button = new UIControlButton(mIdAssigner++, eButtonType::eAdding1x1x1, 10, 10, 100, 50, "AddModel.bmp", &mCgContext, &mButtonFragmentProfile, &mButtonFragmentProgram);
// 	UIControlButton *add2x1x1Button = new UIControlButton(mIdAssigner++, eButtonType::eAdding2x1x1, 10, 70, 100, 50, "DelModel.bmp", &mCgContext, &mButtonFragmentProfile, &mButtonFragmentProgram);
// 
// 	add1x1x1Button->Initialize();
// 	add1x2x1Button->Initialize();
// 	add2x1x1Button->Initialize();
// 
// 	mBlocksButtonList.push_back(add1x2x1Button);
// 	mBlocksButtonList.push_back(add2x1x1Button);
// 	mBlocksButtonList.push_back(add1x1x1Button);

	UIControlButton *add1x1x1 = new UIControlButton(mIdAssigner++, eButtonType::eAdding1x1x1,  10, 50, 90, 90, "111_1.bmp", "111_2.bmp", &mCgContext, &mButtonFragmentProfile, &mButtonFragmentProgram);
	UIControlButton *add1x2x1 = new UIControlButton(mIdAssigner++, eButtonType::eAdding1x2x1, 110, 50, 90, 90, "112_1.bmp", "112_2.bmp", &mCgContext, &mButtonFragmentProfile, &mButtonFragmentProgram);
	UIControlButton *add2x1x1 = new UIControlButton(mIdAssigner++, eButtonType::eAdding2x1x1, 210, 50, 90, 90, "211_1.bmp", "211_2.bmp", &mCgContext, &mButtonFragmentProfile, &mButtonFragmentProgram);
	UIControlButton *add2x2x1 = new UIControlButton(mIdAssigner++, eButtonType::eAdding2x2x1, 310, 50, 90, 90, "212_1.bmp", "212_2.bmp", &mCgContext, &mButtonFragmentProfile, &mButtonFragmentProgram);
	UIControlButton *add3x1x1 = new UIControlButton(mIdAssigner++, eButtonType::eAdding3x1x1, 410, 50, 90, 90, "311_1.bmp", "311_2.bmp", &mCgContext, &mButtonFragmentProfile, &mButtonFragmentProgram);
	UIControlButton *add3x1x2 = new UIControlButton(mIdAssigner++, eButtonType::eAdding3x1x2, 510, 50, 90, 90, "321_1.bmp", "321_2.bmp", &mCgContext, &mButtonFragmentProfile, &mButtonFragmentProgram);
	UIControlButton *add4x1x1 = new UIControlButton(mIdAssigner++, eButtonType::eAdding4x1x1, 610, 50, 90, 90, "411_1.bmp", "411_2.bmp", &mCgContext, &mButtonFragmentProfile, &mButtonFragmentProgram);
	UIControlButton *add4x1x2 = new UIControlButton(mIdAssigner++, eButtonType::eAdding4x1x2, 710, 50, 90, 90, "421_1.bmp", "421_2.bmp", &mCgContext, &mButtonFragmentProfile, &mButtonFragmentProgram);

	add1x1x1->Initialize();
	add1x2x1->Initialize();
	add2x1x1->Initialize();
	add2x2x1->Initialize();
	add3x1x1->Initialize();
	add3x1x2->Initialize();
	add4x1x1->Initialize();
	add4x1x2->Initialize();

	mBlocksButtonList.push_back(add1x1x1);
	mBlocksButtonList.push_back(add1x2x1);
	mBlocksButtonList.push_back(add2x1x1);
	mBlocksButtonList.push_back(add2x2x1);
	mBlocksButtonList.push_back(add3x1x1);
	mBlocksButtonList.push_back(add3x1x2);
	mBlocksButtonList.push_back(add4x1x1);
	mBlocksButtonList.push_back(add4x1x2);

	UIControlButton *saving = new UIControlButton(mIdAssigner++, eButtonType::eSaving, 910, 100, 90, 45, "save.bmp", "save.bmp", &mCgContext, &mButtonFragmentProfile, &mButtonFragmentProgram);
	UIControlButton *loading = new UIControlButton(mIdAssigner++, eButtonType::eLoading, 1010, 100, 90, 45, "load.bmp", "load.bmp", &mCgContext, &mButtonFragmentProfile, &mButtonFragmentProgram);

	saving->Initialize();
	loading->Initialize();

	mBlocksButtonList.push_back(saving);
	mBlocksButtonList.push_back(loading);

	UIControlButton *deleting = new UIControlButton(mIdAssigner++, eButtonType::eDeleting, 940, 50, 90, 45, "delete.bmp", "delete.bmp", &mCgContext, &mButtonFragmentProfile, &mButtonFragmentProgram);

	deleting->Initialize();
	mBlocksButtonList.push_back(deleting);

	UIControlButton *saber = new UIControlButton(mIdAssigner++, eButtonType::eAddingSaber, 1050, 600, 100, 100, "ui_p.bmp", "ui_p.bmp", &mCgContext, &mButtonFragmentProfile, &mButtonFragmentProgram);
	saber->Initialize();
	mBlocksButtonList.push_back(saber);

	return true;
}

bool UIButtonManager::Render()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0f, WINDOW_WIDTH, 0.0f, WINDOW_HEIGHT, -20, 20);
	glMatrixMode(GL_MODELVIEW);

	for (int i = 0; i < mBlocksButtonList.size(); i++) {
		mBlocksButtonList[i]->Update();
	}

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	return true;
}

bool UIButtonManager::Update()
{
	Render();
	return true;
}

bool UIButtonManager::Destroy()
{
	for (int i = 0; i < mBlocksButtonList.size(); i++) {
		if (mBlocksButtonList[i]) {
			mBlocksButtonList[i]->Destroy();
			delete mBlocksButtonList[i];
			mBlocksButtonList[i] = NULL;
		}
	}

	return true;
}

bool UIButtonManager::LeftClickDown(int xpos, int ypos)
{
	for (int i = 0; i < mBlocksButtonList.size(); i++) {
		if (mBlocksButtonList[i]->LeftClickDown(xpos, ypos)) {
			return true;
		}
	}
	return false;
}

bool UIButtonManager::LeftClickUp(int xpos, int ypos)
{
	UIControlButton *current = NULL;
	int index = -1;
	for (int i = 0; i < mBlocksButtonList.size(); i++) {
		if (mBlocksButtonList[i]->LeftClickUp(xpos, ypos)) {
			current = mBlocksButtonList[i];
			index = i;
			break;
		}
	}
	if (current == NULL) {
		return false;
	}
	LegoManager::Instance()->EndPuttingBlock();
	LegoManager::Instance()->setGameStatus(eGameStatus::eNormal);
	if (mCurrentSelectedOne == NULL || current != mCurrentSelectedOne) {
		ResetButtonsExcept(index);
		switch (current->getButtonType())
		{
		case eBlock1x1x1:
			{
				LegoManager::Instance()->setGameStatus(eAddingBlock1x1x1);
				LegoManager::Instance()->StartPuttingBlock();
			} break;
		case eAdding1x2x1:
			{
				LegoManager::Instance()->setGameStatus(eAddingBlock1x2x1);
				LegoManager::Instance()->StartPuttingBlock();
			} break;
		case eAdding2x1x1:
			{
				LegoManager::Instance()->setGameStatus(eAddingBlock2x1x1);
				LegoManager::Instance()->StartPuttingBlock();
			} break;
		case eAdding2x2x1:
			{
				LegoManager::Instance()->setGameStatus(eAddingBlock2x2x1);
				LegoManager::Instance()->StartPuttingBlock();
			} break;
		case eAdding3x1x1:
			{
				LegoManager::Instance()->setGameStatus(eAddingBlock3x1x1);
				LegoManager::Instance()->StartPuttingBlock();
			} break;
		case eAdding3x1x2:
			{
				LegoManager::Instance()->setGameStatus(eAddingBlock3x1x2);
				LegoManager::Instance()->StartPuttingBlock();
			} break;
		case eAdding4x1x1:
			{
				LegoManager::Instance()->setGameStatus(eAddingBlock4x1x1);
				LegoManager::Instance()->StartPuttingBlock();
			} break;
		case eAdding4x1x2:
			{
				LegoManager::Instance()->setGameStatus(eAddingBlock4x1x2);
				LegoManager::Instance()->StartPuttingBlock();
			} break;
		case eAddingSaber:
			{
				LegoManager::Instance()->setGameStatus(eAddingBlockSaber);
				LegoManager::Instance()->StartPuttingBlock();
			} break;
		case eSaving:
			{
				cout << "saving.\n";
				LegoManager::Instance()->SaveToFile("default.sav");
				current->setIsOn(false);
			} break;
		case eLoading:
			{
				cout << "loading.\n";
				LegoManager::Instance()->LoadFromFile("default.sav");
				current->setIsOn(false);
			} break;
		case eDeleting:
			{
				LegoManager::Instance()->setGameStatus(eGameStatus::eDeletingBlock);
			} break;
		}
	}
	if (current->getButtonType() != eSaving && current->getButtonType() != eLoading) {
		if (current == mCurrentSelectedOne) {
			mCurrentSelectedOne = NULL;
			LegoManager::Instance()->setGameStatus(eNormal);
		} else {
			mCurrentSelectedOne = current;
		}
	}

	return true;
}

bool UIButtonManager::ResetAllButtons()
{
	for (int i = 0; i < mBlocksButtonList.size(); i++) {
		mBlocksButtonList[i]->TurnButtonStatus(false);
	}
	return true;
}

bool UIButtonManager::ResetButtonsExcept(int id)
{
	for (int i = 0; i < mBlocksButtonList.size(); i++) {
		if (id == i) {
			continue;
		}
		mBlocksButtonList[i]->TurnButtonStatus(false);
	}
	return true;
}

UIControlButton	*UIButtonManager::GetButtonByType(eButtonType ty)
{
	for (int i = 0; i < mBlocksButtonList.size(); i++) {
		if (mBlocksButtonList[i]->getButtonType() == ty) {
			return mBlocksButtonList[i];
		}
	}
	return NULL;
}

