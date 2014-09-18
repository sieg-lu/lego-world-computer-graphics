#ifndef __UNIT_BLOCK_BASE__
#define __UNIT_BLOCK_BASE__

/*
 * This is the base unit block,
 * which contains most of the default behavior of the unit blocks.
 */

#include "..\Common\Global.h"
#include "..\Models\Model.h"
#include "..\Common\ObjectBase.h"

#define PREDEFINE_COLOR_COUNT			10

static float gPredefineColor[PREDEFINE_COLOR_COUNT][3] = {
	{ 1.0f, 0.5f, 0.5f },
	{ 0.5f, 1.0f, 0.5f },
	{ 0.5f, 0.5f, 1.0f },
	{ 0.8f, 0.8f, 0.8f },
	{ 0.5f, 0.7f, 0.9f },
	{ 0.5f, 0.9f, 0.7f },
	{ 0.7f, 0.5f, 0.9f },
	{ 0.7f, 0.9f, 0.5f },
	{ 0.9f, 0.5f, 0.7f },
	{ 0.9f, 0.7f, 0.5f },
};

class UnitBlockBase : public ObjectBase {
protected:
	int									mId;

	Model								*pModelLower;
	Model								*pModelUpper;
	float								mCoordX;
	float								mCoordY;
	float								mCoordZ;

	int									mIndexStartX;
	int									mIndexStartY;
	int									mIndexStartZ;

	int									mIndexStepX;
	int									mIndexStepY;
	int									mIndexStepZ;

	int									mIndexLengthX;
	int									mIndexLengthY;
	int									mIndexLengthZ;

	float								mRed;
	float								mGreen;
	float								mBlue;

	eRotateDegree						mRotateDegree;

	bool								mIsExisted;

	bool								mIsDrawingUpper;
	bool								mIsSelected;
	bool								mIsVirtual;
	bool								mIsActive;

	eBlockType							mType;

	virtual bool						Render();

public:
	UnitBlockBase(int id, float x, float y, float z, Model *modellower, Model *modelupper, bool vir);

	virtual ~UnitBlockBase() { }

	virtual bool						Initialize()					= 0;
	virtual bool						Update()						= 0;
	virtual bool						Destroy()						= 0;

	virtual eBlockType					getType()						= 0;

	virtual bool						Rotate(eRotateDegree deg);
	
	inline eRotateDegree				getRotateDegree() const			{ return mRotateDegree; }

	inline bool							getIsExisted() const			{ return mIsExisted; }
	inline void							setIsExisted(bool val)			{ mIsExisted = val; }

	inline int							getIndexStartX() const			{ return mIndexStartX; }
	inline void							setIndexStartX(int val)			{ mIndexStartX = val; }
	inline int							getIndexStartY() const			{ return mIndexStartY; }
	inline void							setIndexStartY(int val)			{ mIndexStartY = val; }
	inline int							getIndexStartZ() const			{ return mIndexStartZ; }
	inline void							setIndexStartZ(int val)			{ mIndexStartZ = val; }
	
	inline int							getIndexStepX() const			{ return mIndexStepX; }
	inline int							getIndexStepY() const			{ return mIndexStepY; }
	inline int							getIndexStepZ() const			{ return mIndexStepZ; }

	inline int							getIndexLengthX() const			{ return mIndexLengthX; }
	inline void							setIndexLengthX(int val)		{ mIndexLengthX = val; }
	inline int							getIndexLengthY() const			{ return mIndexLengthY; }
	inline void							setIndexLengthY(int val)		{ mIndexLengthY = val; }
	inline int							getIndexLengthZ() const			{ return mIndexLengthZ; }
	inline void							setIndexLengthZ(int val)		{ mIndexLengthZ = val; }

	inline int							getId() const					{ return mId; }
	inline void							setId(int val)					{ mId = val; }
	inline void							setIsDrawingUpper(bool val)		{ mIsDrawingUpper = val; }

	inline bool							getIsSelected() const			{ return mIsSelected; }
	inline void							setIsSelected(bool val)			{ mIsSelected = val; }

	inline float						getCoordX() const				{ return mCoordX; }
	inline float						getCoordY() const				{ return mCoordY; }
	inline float						getCoordZ() const				{ return mCoordZ; }
	
	inline void							setIsActive(bool val)					{ mIsActive = val; }

};


#endif ///> end of __UNIT_BLOCK_BASE__