#ifndef __UNIT_BLOCK_2x2x1_H__
#define __UNIT_BLOCK_2x2x1_H__

/*
 * This is the 2x2x1 unit block,
 * which draw the 2x2x1 block in the specified position.
 */

#include "..\Models\Model.h"
#include "UnitBlockBase.h"

class UnitBlock2x2x1 : public UnitBlockBase {
protected:

public:
	UnitBlock2x2x1(int id, int xindex, int yindex, int zindex, Model *modellower, Model *modelupper, bool vir = false);
	virtual ~UnitBlock2x2x1();

	virtual bool						Initialize();
	virtual bool						Update();
	virtual bool						Destroy();

	virtual bool						Rotate(eRotateDegree deg);

	virtual eBlockType					getType();

};

#endif ///> end of __UNIT_BLOCK_2x2x1_H__