#include "Delegate.h"

#include "EZ.h"
#include "images/mips.xpm"
#include "images/sparc.xpm"
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
    return 8;
}

// --------------------------------------------------------------------------------------------------------------------------

std::string
Delegate::getTitle(int rowId)
{
    switch(rowId)
    {
        case 0: return "Indy Mips 5000";
        case 1: return "SPARCstation 20";
        case 2: return "Macintosh Quadra";
        case 3: return "RISC System/6000";
        case 4: return "Trinitron";
        case 5: return "AlphaStation 255";
        case 6: return "OpenServer";
        default: return "MIPS Magnum R4000";
    } 
}

std::string
Delegate::getText(int rowId)
{
    switch(rowId)
    {
        case 0: return "Silicon Graphics Incorporated";
        case 1: return "Sun Microsystems Incorporated";
        case 2: return "Apple Incorporated";
        case 3: return "International Business Machines Corporation";
        case 4: return "Sony Group Corporation";
        case 5: return "Digital Equipment Corporation";
        case 6: return "Santa Cruz Operation Incorporated";
        default: return "MIPS Computer Systems Incorporated";
    }
}

std::string
Delegate::getImageName(int rowId, Graphics* g)
{
    switch(rowId)
    {
        case 0: return "mips";
        case 1: return "sparc";
        case 2: return "apple";
        case 3: return "ibm";
        case 4: return "monitor";
        case 5: return "pc";
        case 6: return "unix";
        default: return "mips";
    }
}

void
Delegate::initImages(Graphics* g)
{
    g->getPixmapByName("sparc", xpm_sparc);
    g->getPixmapByName("mips", xpm_mips);
    g->getPixmapByName("apple", xpm_apple);
    g->getPixmapByName("ibm", xpm_ibm);
    g->getPixmapByName("monitor", xpm_monitor);
    g->getPixmapByName("pc", xpm_pc);
    g->getPixmapByName("unix", xpm_unix);
}

// --------------------------------------------------------------------------------------------------------------------------

void 
Delegate::rowSelected(int rowId)
{
    std::cout << "rowSelected " << rowId << std::endl;
}

// --------------------------------------------------------------------------------------------------------------------------

void 
Delegate::draw(int rowId, Graphics* g, XRectangle rectangle)
{
    initImages(g);

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
