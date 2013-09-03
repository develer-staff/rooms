#include "pythonvm.h"

#include <Python.h>

PythonVM::PythonVM()
{
    Py_Initialize();
}

PythonVM::~PythonVM()
{
    Py_Finalize();
}

void PythonVM::import(PythonModule &module)
{
    PyVMMembersMap map = module.getMembers();
    PyMethodDef *module_methods = new PyMethodDef[map.size() + 1];
    int j = 0;
    for (PyVMMembersMap::iterator i = map.begin(); i != map.end(); ++i)
    {
        module_methods[j].ml_name = i->first.c_str();
        module_methods[j].ml_meth = i->second;
        module_methods[j].ml_flags = METH_VARARGS;
        module_methods[j].ml_doc = "Return the number of arguments received by the process.";
        ++j;
    }
    module_methods[j].ml_name = 0;
    module_methods[j].ml_meth = 0;
    module_methods[j].ml_flags = 0;
    module_methods[j].ml_doc = 0;
    Py_InitModule(module.getName().c_str(), module_methods);
    PyRun_SimpleString(("import " + module.getName() + '\n').c_str());
}

void PythonVM::reset()
{
    Py_Finalize();
    Py_Initialize();
}

bool PythonVM::execute(string script)
{
    return PyRun_SimpleString(script.c_str()) != -1;
}

PythonModule::PythonModule(string name) : name(name)
{
}

PythonModule::~PythonModule()
{
    members.clear();
}

void PythonModule::addMember(string name, PyVMFunc func)
{
    if (name != "" && func)
        members[name] = func;
}

PyVMMembersMap &PythonModule::getMembers()
{
    return members;
}

string PythonModule::getName()
{
    return name;
}
