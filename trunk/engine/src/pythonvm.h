/**
 * \file
 * <!--
 * Copyright 2010,2011 Daniele Maccioni
 * All rights reserved.
 * -->
 *
 * \version $Id: pythonvm.h $
 * \author Daniele Maccioni <gendoikari@develer.com>
 */

#ifndef PYTHONVM_H
#define	PYTHONVM_H

#include <python2.6/Python.h> //all python stuff
#include <string> //std::string
#include <map> //std::map

using std::string;

typedef PyObject *(*PyVMFunc)(PyObject *, PyObject *);
typedef std::map<string, PyVMFunc> PyVMMembersMap;

/*! \brief Python module creator.
 *
 * This class permits to create a Python module. It must be imported into a
 * PythonVM to work. Best use: derive this class creating your module throught
 * addMember method.
 *
 * \code
#include "pythonvm.h"
#include <cstdlib>
#include <iostream>

PyObject *MyApi_Log(PyObject *self, PyObject *args)
{
	char *message;
	if (!PyArg_ParseTuple(args, "s", &message))
		return 0;
	std::cout << "LOG: " << message << std::endl;
	Py_RETURN_NONE;
}

class MyApiModule : public PythonModule
{
public:

	MyApiModule() : PythonModule("MyApi")
	{
		addMember("log", MyApi_Log);
	}

	~MyApiModule()
	{
	}
};

int main(int argc, char** argv)
{
	PythonVM vm;
	vm.import(new MyApiModule);
	return vm.execute("MyApi.log('Hello World!')") == 0;
}
 * \endcode
 */
class PythonModule
{
public:
	/// Adds a function to the module.
	void addMember(string name, PyVMFunc func);
	/// Gets all module's functions.
	PyVMMembersMap &getMembers();
	/// Gets module's name.
	string getName();
	virtual ~PythonModule();
protected:
	PythonModule(string name);
private:
	PyVMMembersMap members;
	string name;
};

/*! \brief Python virtual machine.
 *
 * This class wraps Python and permits to import modules and to execute scripts.
 */
class PythonVM
{
public:
	PythonVM();
	~PythonVM();
	/// Imports a PythonModule and loads it into the vm.
	void import(PythonModule &module);
	/// Reboots virual machine: deletes all modules and all python stuff.
	void reset();
	/// Makes python execute given script.
	bool execute(string script);
private:
	PythonVM(const PythonVM &);
	void operator=(const PythonVM &);
};

#endif	/* PYTHONVM_H */

