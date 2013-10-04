#ifndef CSPARSER_H
#define CSPARSER_H

#include "TRexpp.h"
#include "gui.h"

#include <string>
#include <map>

typedef std::map<std::string, float> CsState;

struct CsObject {
    std::string name;
    std::string content;
    bool isText;
    CsState state;
};

struct CsStep {
    int duration;
    std::map<std::string, CsState > objStates;
    std::string next;
};

/**
 * \brief The CsParser class reads a cutscene file
 * It allows us to know if the file is correct and at the same time
 * it loads the cutscene objects and the animation steps
 *
 */
class CsParser
{
public:
    CsParser();

    /**
     * \brief parse the cutscene file
     * \param csPath the file path
     * \return true if the file is sintactically correct, otherwise false
     */
    bool parse(const std::string &csPath);

    /**
     * \brief getErrorMessage
     * \return if something went wrong it returns the error message
     */
    std::string getErrorMessage() const;

    /// Returns the list of the objects involved in the current cutscene
    std::vector<CsObject> objects() const;

    /// Returns the list of steps for the current cutscene
    std::map<std::string, CsStep> steps() const;

    /// Returns the names of the starting steps
    std::vector<std::string> startingSteps() const;

private:
    static std::string readline(std::istreambuf_iterator<char> &i);

    static void strip(std::string &string, const char expr);
    static std::string removeFirstSlice(std::string *in, const std::string &separator);

    static bool regexMatchSingle(const std::string &expression, const std::string &input, std::string *output);
    static bool parseInt(const std::string &in, int *out);
    static bool parseFloat(const std::string &in, float *out);
    static bool parseString(const std::string &in, std::string *out);
    static bool parseQuotedString(const std::string &in, std::string *out);
    static bool parseState(std::string *in, CsState *s);

    bool parseHeader(std::istreambuf_iterator<char> &i);

    bool parseDeclaration(std::string d_string, bool text);
    bool parseDeclarations(std::istreambuf_iterator<char> &i);

    bool parseStepContent(std::string &line, CsStep &step);
    bool parseAnimations(std::istreambuf_iterator<char> &i);

    void replaceWDefaults(std::string &string);
    bool parseDefaults();

    bool isObject(const std::string &name);

private:
    std::string _parsed_content;
    int _version;
    std::string _defaults_file_path;
    std::map<std::string, std::string> _defaults;
    std::vector<CsObject> _objects;
    std::map<std::string, CsStep> _steps;
    std::vector<std::string> _starting_steps;

    std::string _error_message;

};

size_t findUnquoted(const std::string &input, const std::string &toFind);

#endif // CSPARSER_H
