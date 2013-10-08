#ifndef CUTSCENES_DEFAULTS_H
#define CUTSCENES_DEFAULTS_H

#include <string>
#include <map>

using std::string;

struct Defaults {
    static std::map<string, string> create_map() {
        std::map<string, string> m;
        m["show"] = "alpha:1";
        m["hide"] = "alpha:0";
        m["fullscreen"] = "x:0, y:0, width:1, height:1";
        m["doubled"] = "width:2, height:2";
        m["text_in"] = "x:0.3, y:0.8, width:1, height:0.2, alpha:1";
        m["text_out"] = "x:0.3, y:1, width:1, height:0.2, alpha:1";
        return m;
    }
    static const std::map<string, string> declarations;
};

const std::map<string, string> Defaults::declarations = Defaults::create_map();

#endif // CUTSCENES_DEFAULTS_H
