#ifndef PYTHONAPI_H
#define	PYTHONAPI_H

#include "pythonvm.h"

class Engine;

void apiInit(Engine *engine_);
PyObject *apiLog(PyObject *self, PyObject *args);

class EngineMod : public PythonModule
{
public:
	EngineMod();
	~EngineMod();
};

#endif	/* PYTHONAPI_H */

