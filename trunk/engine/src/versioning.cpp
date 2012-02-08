#include "versioning.h"
#include "roomsreader.h" // RRNode
#include "../lib/tinyxml/tinyxml.h" // TiXmlDocument

string Versioning::upgradeFrom1To2(string content)
{
    TiXmlDocument doc;
    doc.Parse(content.c_str());
    RRNode node(doc.RootElement());
    node.gotoElement("world");
    int w = node.attrInt("width");
    int h = node.attrInt("height");
    node.setAttr("version", "2");
    for (node.gotoElement("items")->gotoChild("item"); !node.isNull(); node.gotoNext())
    {
        node.setAttr("x", floatToStr(node.attrFloat("x") / w));
        node.setAttr("y", floatToStr(node.attrFloat("y") / h));
        node.setAttr("width", floatToStr(node.attrFloat("width") / w));
        node.setAttr("height", floatToStr(node.attrFloat("height") / h));
    }

    for (node.gotoElement("rooms")->gotoChild("room"); !node.isNull(); node.gotoNext())
    {
        for (node.gotoChild("area"); !node.isNull(); node.gotoNext())
        {
            node.setAttr("x", floatToStr(node.attrFloat("x") / w));
            node.setAttr("y", floatToStr(node.attrFloat("y") / h));
            node.setAttr("width", floatToStr(node.attrFloat("width") / w));
            node.setAttr("height", floatToStr(node.attrFloat("height") / h));
        }
        node.gotoParent();
    }
    TiXmlPrinter printer;
    doc.Accept(&printer);
    return printer.CStr();
}

string Versioning::upgradeFrom2To3(string content)
{
    TiXmlDocument doc;
    doc.Parse(content.c_str());
    RRNode node(doc.RootElement());
    node.gotoElement("world");
    node.setAttr("version", "3");

    for (node.gotoElement("rooms")->gotoChild("room"); !node.isNull(); node.gotoNext())
        node.setAttr("bgm", "");

    TiXmlPrinter printer;
    doc.Accept(&printer);
    return printer.CStr();
}

string Versioning::upgrade(int version, string content)
{
    for (int i = version; i < Versioning::VERSION; ++i)
    {
        logger.write("Updating from v." + floatToStr(i) + " to v." + floatToStr(i + 1), Log::NOTE);
        content = Versioning::upgrade_funcs[i - 1](content);
    }
    logger.write("Upgrade successful!", Log::WARNING);
    return content;
}
