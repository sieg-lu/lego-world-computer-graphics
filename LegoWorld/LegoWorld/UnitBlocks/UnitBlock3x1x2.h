#ifndef __UNIT_BLOCK_3x1x2_H__
#define __UNIT_BLOCK_3x1x2_H__

/*
 * This is the 3x1x2 unit block,
 * which draw the 3x1x2 block in the specified position.
 */

#include "..\Models\Model.h"
#include "UnitBlockBase.h"

class UnitBlock3x1x2 : public UnitBlockBase {
protected:

public:
	UnitBlock3x1x2(int id, int xindex, int yindex, int zindex, Model *modellower, Model *modelupper, bool vir = false);
	virtual ~UnitBlock3x1x2();

	virtual bool						Initialize();
	virtual bool						Update();
	virtual bool						Destroy();

	virtual bool						Rotate(eRotateDegree deg);

	virtual eBlockType					getType();

};

#endif ///> end of __UNIT_BLOCK_3x1x2_H__