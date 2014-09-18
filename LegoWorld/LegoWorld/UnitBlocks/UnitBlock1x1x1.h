#ifndef __UNIT_BLOCK_1x1x1__
#define __UNIT_BLOCK_1x1x1__

/*
 * This is the 1x1x1 unit block,
 * which draw the 1x1x1 block in the specified position.
 */

#include "..\Models\Model.h"
#include "UnitBlockBase.h"

class UnitBlock1x1x1 : public UnitBlockBase {
protected:

public:
	UnitBlock1x1x1(int id, int xindex, int yindex, int zindex, Model *modellower, Model *modelupper, bool vir = false);
	virtual ~UnitBlock1x1x1();

	virtual bool						Initialize();
	virtual bool						Update();
	virtual bool						Destroy();

	virtual bool						Rotate(eRotateDegree deg);

	virtual eBlockType					getType();

};

#endif ///> end of __UNIT_BLOCK_1x1x1__