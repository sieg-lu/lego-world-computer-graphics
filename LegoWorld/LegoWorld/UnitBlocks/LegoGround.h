#ifndef __LEGO_GROUNG_H__
#define __LEGO_GROUNG_H__

/*
 * This is the ground unit block,
 * which draw the ground in the specified position.
 */

#include "..\Models\Model.h"
#include "UnitBlockBase.h"

class LegoGround : public UnitBlockBase {
protected:
	bool								Render();

public:
	LegoGround();
	virtual ~LegoGround();

	virtual bool						Initialize();
	virtual bool						Update();
	virtual bool						Destroy();

	virtual eBlockType					getType();

};


#endif ///> end of __LEGO_GROUNG_H__