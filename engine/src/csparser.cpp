#include "csparser.h"

#include <fstream>
#include <cstring> //strtok
#include <iterator> //istreambuf_iterator
#include <cstdlib>
#include <algorithm> //ererase
#include <sstream>

CsParser::CsParser(const std::vector<std::string> &imagePaths) :
    _image_paths(imagePaths),
    _version(0),
    _defaults_file_path(""),
    _error_message("")
{
}

bool CsParser::parse(const std::string &csPath)
{
    std::ifstream file;
    file.open(csPath.c_str(), std::ios_base::in);
    std::istreambuf_iterator<char> i(file.rdbuf());
    if (!parseHeader(i)){
        _error_message = "error parsing header";
        return false;
    }
    if (_defaults_file_path != ""){
        if (!parseDefaults()){
            _error_message = "error parsing "+_defaults_file_path;
            return false;
        }
    }
    if (!parseDeclarations(i)){
        _error_message = "error parsing declarations";
        return false;
    }
    if (!parseAnimations(i)){
        _error_message = "error parsing animations";
        return false;
    }
    return true;
}

std::string CsParser::getErrorMessage() const
{
    return _error_message;
}

std::vector<CsObject> CsParser::objects() const
{
    return _objects;
}

std::map<std::string, CsStep> CsParser::steps() const
{
    return _steps;
}

std::vector<std::string> CsParser::startingSteps() const
{
    return _starting_steps;
}

bool CsParser::parseInt(const std::string &in, int *out)
{
    std::string found;
    if (!regexMatchSingle("[+-]?[0-9]+", in, &found))
        return false;
    *out = atoi(found.c_str());
    return true;
}

bool CsParser::parseFloat(const std::string &in, float *out)
{
    std::string found;
    if (!regexMatchSingle("[-+]?[0-9]*\\.?[0-9]*", in, &found))
        return false;
    char *endptr;
    *out = strtof(found.c_str(), &endptr);
    if (endptr != (found.c_str() + found.length()))
        return false;
    return true;
}

bool CsParser::parseString(const std::string &in, std::string *out)
{
    *out = "";
    std::string::const_iterator i;
    for (i = in.begin(); i != in.end(); ++i){
        if ((*i) == ' '){
            if ((i+1) != in.end() &&
                    *(i+1) != ' ' &&
                    *out != "")
                return false;
            continue;
        }
        *out += (*i);
    }
    if (*out == "")
        return false;
    return true;
}

bool CsParser::parseQuotedString(const std::string &in, std::string *out)
{
    if (!regexMatchSingle("\"[^\"]*\"", in, out))
        return false;
    strip(*out, '"');
    return true;
}

bool CsParser::parseState(std::string *in, CsState *s)
{
    strip(*in, ' ');
    while (in->length() > 0) {
        std::string token = removeFirstSlice(in, ",");
        std::string var;
        if (token == ""){
            token = *in;
            in->clear();
        }
        var = removeFirstSlice(&token, ":");

        if (var == "")
            break;
        if (var != "x" &&
                var != "y" &&
                var != "width" &&
                var != "height" &&
                var != "alpha"){
            return false;
        }
        std::string stateName = var;
        float stateValue;
        if (!parseFloat(token, &stateValue))
            return false;
        (*s)[stateName] = stateValue;
    }
    return true;
}

std::string CsParser::readline(std::istreambuf_iterator<char> &i)
{
    std::istreambuf_iterator<char> eof;
    std::string line = "";
    while (i != eof && (*i) != '\n'){
        line += (*i);
        ++i;
    }
    ++i;
    return line;
}

void CsParser::strip(std::string &string, const char expr)
{
    string.erase(std::remove(string.begin(), string.end(), expr), string.end());
}

std::string CsParser::removeFirstSlice(std::string *in, const std::string &separator)
{
    std::string result;
    size_t c_pos = findUnquoted(*in, separator);
    if (c_pos == std::string::npos)
        return "";
    result = in->substr(0, c_pos);
    *in = in->substr(c_pos + separator.length());
    return result;
}

bool CsParser::regexMatchSingle(const std::string &expression, const std::string &input, std::string *output)
{
    TRexpp regex;
    const char *found = "";
    const char *last = "";

    regex.Compile(expression.c_str());
    regex.Search(input.c_str(), &found, &last);

    std::string last_str(last);
    if (last_str.length() > 0){
        strip(last_str, ' ');
        if (last_str.length() > 0){
            return false;
        }
    }

    output->assign(found);
    if (output->length() > 0)
        return true;
    return false;
}

bool CsParser::parseHeader(std::istreambuf_iterator<char> &i)
{
    std::istreambuf_iterator<char> eof;
    std::string line = "";

    while (true){
        if (i == eof)
            return false;
        line = readline(i);
        if (line.substr(0,3) == "###")
            break;
    }
    //getting version number and definitions file
    line = line.substr(3);
    strip(line, ' ');
    std::string version = removeFirstSlice(&line, ",");
    if(version == ""){
        return parseInt(line, &_version);
    }
    if (!parseInt(version, &_version))
        return false;
    if (!parseQuotedString(line, &_defaults_file_path))
        return false;
    return true;
}

bool CsParser::parseDeclaration(std::string d_string)
{
    CsObject obj;
    if (!parseString(removeFirstSlice(&d_string, ":"), &(obj.name))){
        strip(d_string, ' ');
        if (d_string.length() > 0)
            return false;
        return true;
    }
    if (!parseQuotedString(removeFirstSlice(&d_string, ","), &(obj.content)))
        return false;
    obj.isText = false;
    std::vector<std::string>::const_iterator i = find(_image_paths.begin(), _image_paths.end(), obj.content);
    if (i == _image_paths.end())
        obj.isText = true;
    strip(d_string, ' ');
    replaceWDefaults(d_string);
    if (!parseState(&d_string, &(obj.state)))
        return false;
    if(d_string.length() > 0)
        return false;
    _objects.push_back(obj);
    return true;
}

bool CsParser::parseDeclarations(std::istreambuf_iterator<char> &i)
{
    std::string line  = "";
    std::istreambuf_iterator<char> eof;
    while(i != eof){
        line = readline(i);
        if (line.find("---") != std::string::npos)
            break;
        if (!parseDeclaration(line))
            return false;
    }
    return true;
}

bool CsParser::parseStepContent(std::string &line, CsStep &step)
{
    std::string objectName;
    if (!parseString(removeFirstSlice(&line, ":"), &objectName)){
        strip(line, ' ');
        if (line != "")
            return false;
        return true;
    }

    strip(line, ' ');
    replaceWDefaults(line);

    CsState s;
    if (!isObject(objectName))
        return false;
    if (!parseState(&line, &s))
        return false;
    step.objStates[objectName] = s;
    return true;
}

bool CsParser::parseSubSteps(std::istreambuf_iterator<char> &i,
                             std::string &line,
                             const std::string &name,
                             int *n)
{
    std::istreambuf_iterator<char> eof;
    line = readline(i);
    while(i != eof){
        CsStep step;
        step.duration = -1;
        if (line.find("->") != std::string::npos)
            break;
        if (line.find(":") != std::string::npos)
            return false;
        strip(line, ' ');
        if (line == ""){
            line = readline(i);
            continue;
        }
        if (!parseInt(line, &(step.duration)))
            return false;
        line = readline(i);
        while(i != eof &&
              line.find(":") != std::string::npos &&
              line.find("->") == std::string::npos){
            if (!parseStepContent(line, step))
                return false;
            line = readline(i);
        }
        if (*n > 0){
            _steps[name+intToString((*n)-1)].next.push_back(name+intToString(*n));
        }
        _steps[name+intToString(*n)] = step;
        (*n)++;
    }
    (*n)--;
    return true;
}

bool CsParser::parseAnimations(std::istreambuf_iterator<char> &i)
{
    std::istreambuf_iterator<char> eof;
    std::map<std::string, int> steps_length;
    std::string line = readline(i);
    while (i != eof){
        if (line.substr(0, 2) != "->"){
            strip(line, ' ');
            if (line != "")
                return false;
            line = readline(i);
            continue;
        }
        line = line.substr(2);

        //parsing step header
        std::string name_str = removeFirstSlice(&line, ",");
        std::string prev = "";
        if (name_str != ""){
            if(!parseString(line, &prev))
                return false;
        } else {
            name_str = line;
        }
        std::string name;
        if (!parseString(name_str, &name))
            return false;

        int stepNumber = 0;
        if (!parseSubSteps(i, line, name, &stepNumber))
            return false;
        steps_length[name] = stepNumber;

        if (prev != ""){
            std::map<std::string, CsStep>::iterator i =_steps.find(prev+intToString(steps_length[prev]));
            if (i == _steps.end())
                return false;
            (*i).second.next.push_back(name+"0");
        } else {
            _starting_steps.push_back(name+"0");
        }
    }
    return true;
}

void CsParser::replaceWDefaults(std::string &string)
{
    std::map<std::string, std::string>::iterator i;
    for (i = _defaults.begin(); i != _defaults.end(); ++i){
        size_t start_pos = 0;
        while((start_pos = string.find((*i).first, start_pos)) != std::string::npos)
            string.replace(start_pos, (*i).first.length(), (*i).second);
    }
}

bool CsParser::parseDefaults()
{
    std::ifstream file;
    file.open(_defaults_file_path.c_str(), std::ios_base::in);
    std::istreambuf_iterator<char> i(file.rdbuf());
    std::istreambuf_iterator<char> eof;

    std::string line = "";
    while (i != eof){
        line = readline(i);
        strip(line, ' ');
        size_t arrow_pos = line.find("=>");
        if (arrow_pos == std::string::npos){
            if (line.length() > 0)
                return false;
            continue;
        }

        std::string var = "";
        if (!parseString(line.substr(0, arrow_pos), &var))
            return false;
        _defaults[var] = line.substr(arrow_pos + 2);
    }
    return true;
}

bool CsParser::isObject(const std::string &name)
{
    std::vector<CsObject>::iterator i;
    for (i = _objects.begin(); i != _objects.end(); ++i){
        if ((*i).name == name)
            return true;
    }
    return false;
}


size_t findUnquoted(const std::string &input, const std::string &toFind)
{
    int n = input.length();
    int m = toFind.length();
    size_t i = 0;
    while (int(i) < n-m){
        if (input.at(i) == '"'){
            ++i;
            while (input.at(i) != '"' && int(i) < n-m)
                ++i;
        }
        int j = 0;
        while (j < m && input.at(i+j) == toFind.at(j))
            ++j;
        if (j == m)
            return i;
        i++;
    }
    return std::string::npos;
}


std::string intToString(int i)
{
    std::stringstream ss;
    std::string s;
    ss << i;
    s = ss.str();

    return s;
}
