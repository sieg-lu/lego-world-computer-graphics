#include "ModelManager.h"

bool ModelManager::PreloadModel(Model*& model, const char *filename)
{
	model = new MilkshapeModel();
	if (!model->loadModelData(filename)) {
		cout << "Unable to load the " << filename << endl;
		return false;
	}
	model->reloadTextures();

	return true;
}

bool ModelManager::UnloadModel(Model*& model)
{
	if (model) {
		delete model;
	}
	return true;
}

bool ModelManager::PreloadAllModels()
{
	if (!PreloadModel(pModelSaberStand, "saber_stand.ms3d")  ||
		!PreloadModel(pModelSaberLeft, "saber_left.ms3d")	 ||
		!PreloadModel(pModelSaberRight, "saber_right.ms3d")  ||
		!PreloadModel(pModel1x1x1Lower, "1x1x1(Lower).ms3d") ||
		!PreloadModel(pModel1x1x1Upper, "1x1x1(Upper).ms3d") ||
		!PreloadModel(pModel1x2x1Lower, "1x2x1(Lower).ms3d") ||
		!PreloadModel(pModel1x2x1Upper, "1x2x1(Upper).ms3d") ||
		!PreloadModel(pModel2x1x1Lower, "2x1x1(Lower).ms3d") ||
		!PreloadModel(pModel2x1x1Upper, "2x1x1(Upper).ms3d") ||
		!PreloadModel(pModel2x2x1Lower, "2x2x1(Lower).ms3d") ||/*yakei*/
		!PreloadModel(pModel2x2x1Upper, "2x2x1(Upper).ms3d") ||
		!PreloadModel(pModel3x1x1Lower, "3x1x1(Lower).ms3d") ||
		!PreloadModel(pModel3x1x1Upper, "3x1x1(Upper).ms3d") ||
		!PreloadModel(pModel3x1x2Lower, "3x1x2(Lower).ms3d") ||
		!PreloadModel(pModel3x1x2Upper, "3x1x2(Upper).ms3d") ||
		!PreloadModel(pModel4x1x1Lower, "4x1x1(Lower).ms3d") ||
		!PreloadModel(pModel4x1x1Upper, "4x1x1(Upper).ms3d") ||
		!PreloadModel(pModel4x1x2Lower, "4x1x2(Lower).ms3d") ||
		!PreloadModel(pModel4x1x2Upper, "4x1x2(Upper).ms3d")) {
			return false;
	}
	return true;
}

bool ModelManager::UnloadAllModels()
{
	UnloadModel(pModel1x1x1Lower);
	UnloadModel(pModel1x1x1Upper);

	UnloadModel(pModel1x2x1Lower);
	UnloadModel(pModel1x2x1Upper);

	UnloadModel(pModel2x1x1Lower);
	UnloadModel(pModel2x1x1Upper);

	UnloadModel(pModel2x2x1Lower);/*yakexi*/
	UnloadModel(pModel2x2x1Upper);

	UnloadModel(pModel3x1x1Lower);
	UnloadModel(pModel3x1x1Upper);

	UnloadModel(pModel3x1x2Lower);
	UnloadModel(pModel3x1x2Upper);

	UnloadModel(pModel4x1x1Lower);
	UnloadModel(pModel4x1x1Upper);

	UnloadModel(pModel4x1x2Lower);
	UnloadModel(pModel4x1x2Upper);

	UnloadModel(pModelSaberRight);
	UnloadModel(pModelSaberLeft);
	UnloadModel(pModelSaberStand);

	return true;
}

Model *ModelManager::GetModel(eBlockType bt, bool upp)
{
	switch (bt)
	{
	case eBlock1x1x1:
		{
			if (upp) {
				return pModel1x1x1Upper;
			}
			return pModel1x1x1Lower;
		} break;
	case eBlock1x2x1:
		{
			if (upp) {
				return pModel1x2x1Upper;
			}
			return pModel1x2x1Lower;
		} break;
	case eBlock2x1x1:
		{
			if (upp) {
				return pModel2x1x1Upper;
			}
			return pModel2x1x1Lower;
		} break;
	case eBlock2x2x1:/*yakexi*/
		{
			if (upp) {
				return pModel2x2x1Upper;
			}
			return pModel2x2x1Lower;
		}break;
	case eBlock3x1x1:
		{
			if (upp) {
				return pModel3x1x1Upper;
			}
			return pModel3x1x1Lower;
		} break;
	case eBlock3x1x2:
		{
			if (upp) {
				return pModel3x1x2Upper;
			}
			return pModel3x1x2Lower;
		} break;
	case eBlock4x1x1:
		{
			if (upp) {
				return pModel4x1x1Upper;
			}
			return pModel4x1x1Lower;
		} break;
	case eBlock4x1x2:
		{
			if (upp) {
				return pModel4x1x2Upper;
			}
			return pModel4x1x2Lower;
		} break;
	}

	return NULL;
}

