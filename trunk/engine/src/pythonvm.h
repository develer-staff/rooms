/* 
 * File:   pythonvm.h
 * Author: gendoikari
 *
 * Created on 3 febbraio 2011, 10.34
 */

#ifndef PYTHONVM_H
#define	PYTHONVM_H

#include <python2.6/Python.h> //all python stuff
#include <string> //std::string
#include <map> //std::map

using std::string;

typedef PyObject *(*PyVMFunc)(PyObject *, PyObject *);
typedef std::map<string, PyVMFunc> PyVMMembersMap;

class PythonModule
{
public:
	void addMember(string name, PyVMFunc func);
	PyVMMembersMap &getMembers();
	string getName();
	virtual ~PythonModule();
protected:
	PythonModule(string name);
private:
	PyVMMembersMap members;
	string name;
};

class PythonVM
{
public:
	PythonVM();
	~PythonVM();
	void import(PythonModule &module);
	void reset();
	bool execute(string script);
private:
	PythonVM(const PythonVM &);
	void operator=(const PythonVM &);
};

#endif	/* PYTHONVM_H */

