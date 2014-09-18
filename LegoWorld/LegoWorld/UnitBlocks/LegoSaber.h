#ifndef __LEGO_SABER_H__
#define __LEGO_SABER_H__

/*
 * This is the lego girl unit block,
 * which draw the girl in the specified position.
 */

#include <vector>
#include "..\Common\Global.h"
#include "..\Models\Model.h"
#include "UnitBlockBase.h"
using namespace std;

class LegoSaber : public UnitBlockBase {
protected:
	enum eFacingDirection {
		mDegree0 = 0,
		mDegree180 = 180,
	};

	virtual bool						Render();

	unsigned int						mUpdateTimes;

	int									mOrigIndexLengthX;
	int									mOrigIndexLengthY;
	int									mOrigIndexLengthZ;

	Model								*mStandModel;
	Model								*mLeftModel;
	Model								*mRightModel;

	eFacingDirection					mDirection;
	float								mStep;

public:
	LegoSaber(int id, int xindex, int yindex, int zindex, int len, Model *standmodel, Model *leftmodel, Model *rightmodel);
	virtual ~LegoSaber();

	virtual bool						Initialize();
	virtual bool						Update();
	virtual bool						Destroy();

	virtual bool						Rotate(eRotateDegree deg);

	virtual eBlockType					getType();

};


#endif ///> end of __LEGO_SABER_H__