#include "pythonapi.h"
#include "engine.h"

Engine *engine = 0;

void apiInit(Engine *engine_)
{
	engine = engine_;
}

PyObject *apiLog(PyObject *self, PyObject *args)
{
	char *message;
	if (!PyArg_ParseTuple(args, "s", &message))
		return 0;
	engine->getLogger()->write(message, Log::NOTE);
	Py_RETURN_NONE;
}

EngineMod::EngineMod() : PythonModule("engine")
{
	addMember("log", apiLog);
}

EngineMod::~EngineMod()
{
}
