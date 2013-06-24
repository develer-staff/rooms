#include "pythonapi.h"
#include "engine.h"

Engine *engine = 0;

void apiInit(Engine *engine_)
{
    engine = engine_;
}

PyObject *apiPyLog(PyObject *, PyObject *args)
{
    char *message;
    if (!PyArg_ParseTuple(args, "s", &message))
        return 0;
    engine->getLogger()->write(message, Log::NOTE);
    Py_RETURN_NONE;
}

PyObject *apiPySaveGame(PyObject *, PyObject *args)
{
    char *filename;
    if (!PyArg_ParseTuple(args, "s", &filename))
        return 0;
    engine->saveGame(filename);
    Py_RETURN_NONE;
}

PyObject *apiPyLoadGame(PyObject *, PyObject *args)
{
    char *filename;
    if (!PyArg_ParseTuple(args, "s", &filename))
        return 0;
    engine->loadGame(filename);
    Py_RETURN_NONE;
}

PyObject *apiPyGotoRoom(PyObject *, PyObject *args)
{
    char *room;
    if (!PyArg_ParseTuple(args, "s", &room))
        return 0;
    engine->apiRoomGoto(room);
    Py_RETURN_NONE;
}

PyObject *apiPyMoveItem(PyObject *, PyObject *args)
{
    char *item, *dest;
    if (!PyArg_ParseTuple(args, "ss", &item, &dest))
        return 0;
    engine->apiItemMove(item, dest);
    Py_RETURN_NONE;
}

EngineMod::EngineMod() : PythonModule("engine")
{
    addMember("log", apiPyLog);
    addMember("saveGame", apiPySaveGame);
    addMember("loadGame", apiPyLoadGame);
    addMember("goto", apiPyGotoRoom);
    addMember("itemMove", apiPyMoveItem);
}

EngineMod::~EngineMod()
{
}

PyObject *apiPyRoomGetId(PyObject *, PyObject *args)
{
    if (!PyArg_ParseTuple(args, ""))
        return 0;
    Room *room = engine->getRoomsManager()->currentRoom();
    return Py_BuildValue("s", room->id.c_str());
}


RoomMod::RoomMod() : PythonModule("room")
{
    addMember("getName", apiPyRoomGetId);
}

RoomMod::~RoomMod()
{
}
