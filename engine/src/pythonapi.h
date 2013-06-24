#ifndef PYTHONAPI_H
#define	PYTHONAPI_H

#include "pythonvm.h"

class Engine;

void apiInit(Engine *engine_);

class EngineMod : public PythonModule
{
public:
	EngineMod();
	~EngineMod();
};

class RoomMod : public PythonModule
{
public:
	RoomMod();
	~RoomMod();
};

#endif	/* PYTHONAPI_H */

