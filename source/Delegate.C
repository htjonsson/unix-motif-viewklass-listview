#include "Delegate.h"

#include "EZ.h"
#include "images/sgi.xpm"
#include "images/sparc.xpm"
#include "images/mips.xpm"
#include "images/apple.xpm"
#include "images/pc.xpm"
#include "images/ibm.xpm"
#include "images/monitor.xpm"
#include "images/unix.xpm"

#include <Vk/VkPixmap.h>
#include <Xm/Xm.h>
#include <X11/Xlib.h>
#include <string>
#include <iostream>
#include <ostream>
#include <sstream>

using namespace std;

Delegate::Delegate()
    : ListViewDelegate()
{}

Delegate::~Delegate()
{}

// --------------------------------------------------------------------------------------------------------------------------

const string Delegate::_titlefontName = "Verdan:style=Bold:pixelsize=10:antialias=true";
const string Delegate::_titleColorName = "black";
const string Delegate::_textfontName = "Verdan:pixelsize=10:antialias=true";
const string Delegate::_textColorName = "gray55";

// --------------------------------------------------------------------------------------------------------------------------

int 
Delegate::numberOfRows()
{
    return 18;
}

// --------------------------------------------------------------------------------------------------------------------------

std::string
Delegate::getTitle(int rowId)
{
    stringstream ss;
    ss << "[" << rowId << "] - Ant Design Title 2"; 

    return ss.str();
}

std::string
Delegate::getText(int rowId)
{
    return "Ant Design, a design language for background apllications, is refined by Ant UED Team";
}

std::string
Delegate::getImageName(int rowId, Graphics* g)
{
    g->getPixmapByName("sun", _workstation_sparc);
    g->getPixmapByName("sgi", _workstation_sgi);

    return "sgi";
}

// --------------------------------------------------------------------------------------------------------------------------

void 
Delegate::draw(int rowId, Graphics* g, XRectangle rectangle)
{
    // title
    XRectangle rect = EZ::ofRectangle(rectangle, 60, 18, 300, 11);
    g->drawString(  _titlefontName, 
                    _titleColorName, 
                    rect,
                    getTitle(rowId));

    // text
    rect = EZ::ofRectangle(rectangle, 60,44, 300, 11);
    g->drawString(  _textfontName, 
                    _textColorName, 
                    rect,
                    getText(rowId));

    // image
    rect = EZ::ofRectangle(rectangle, 6, 15, 48, 48);
    g->draw(getImageName(rowId, g), rect);    
}
