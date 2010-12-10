#include "RoomsEngine.h"
#include "RoomsManager.h"
#include "DrawDevice.h"

RoomsEngine *RoomsEngine::_engine = 0;

RoomsEngine::RoomsEngine()
{
    //ctor
    _rooms_mgr = new RoomsManager(this);
}

RoomsEngine::~RoomsEngine()
{
    //dtor
    delete _rooms_mgr;
}

RoomsEngine *RoomsEngine::CreateEngine()
{
    if (_engine == 0)
    {
        _engine = new RoomsEngine();
    }
    return _engine;
}

int RoomsEngine::initialize()
{
    /*if (!loadWorld("test_world.rooms"))
        throw;  //TODO: handle exception*/
    loadWorld("test_world.rooms");
}

void RoomsEngine::setDevice(DrawDevice *device)
{
    device != 0 ? _device = device : throw; //TODO: handle error!
}

void RoomsEngine::click (int x, int y)
{

}


void RoomsEngine::loadGame(std::string filename)
{

}

bool RoomsEngine::loadWorld(std::string filename)
{
    //TODO: realize a better error management than ok &= true
    TiXmlDocument document(filename.c_str());
    bool ok = document.LoadFile();
    int width = 0, height = 0;
    if (ok)
    {
        TiXmlElement *root = document.RootElement();
        TiXmlNode *node = 0;
        //Load World attributes
        _rooms_mgr->name(root->Attribute("name") ? root->Attribute("name") : "");
        root->QueryIntAttribute("width", &width) == TIXML_SUCCESS ? ok &= true : ok = false;
        root->QueryIntAttribute("height", &height) == TIXML_SUCCESS ? ok &= true : ok = false;
        _rooms_mgr->size(width, height);
        //TODO: manage different screen resolutions
        //Load images
        (node = root->FirstChild("images")) != 0 ? ok &= true : ok = false;
        for (node = node->FirstChild("img"); node != 0; node = node->NextSibling("img"))
        {
            std::string id = "";
            std::string name = "";
            TiXmlElement *el = node->ToElement();
            id = el->Attribute("id") ? ok &= true : ok = false;
            name = el->Attribute("file") ? ok &= true : ok = false;
            if (ok)
                ok &= (_device->loadImage(id, name));
        }
        (node = root->FirstChild("rooms")) != 0 ? ok &= true : ok = false;
        for (node = node->FirstChild("room"); node != 0; node = node->NextSibling("room"))
        {
            std::string id = "";
            std::string bg = "";
            TiXmlElement *el = node->ToElement();
            id = el->Attribute("id") ? ok &= true : ok = false;
            bg = el->Attribute("bg") ? ok &= true : ok = false;
            if (ok)
                _rooms_mgr->addRoom(id, bg) ? ok &=true : ok = false;
        }
        return ok;
    } else {
        return ok;
    }
}

RoomsManager *RoomsEngine::getRoomsManager()
{
    return _rooms_mgr;
}
