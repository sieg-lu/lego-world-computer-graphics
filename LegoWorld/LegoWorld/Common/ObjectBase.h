#ifndef __OBJECT_BASE__
#define __OBJECT_BASE__

/*
 * This file contains some interfaces for the upper classes
 * Point and ObjectBase.
 */

class Point {
public:
	int									xCoord;
	int									yCoord;
	int									zCoord;

};

class ObjectBase {
protected:
	virtual bool						Render()						= 0;

public:
	ObjectBase() { }
	virtual ~ObjectBase() { }

	virtual bool						Initialize()					= 0;
	virtual bool						Update()						= 0;
	virtual bool						Destroy()						= 0;

};

#endif ///> end of __OBJECT_BASE__