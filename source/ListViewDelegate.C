#include "ListViewDelegate.h"

#include "EZ.h"
#include "images/workstation_sgi.xpm"
#include "images/workstation_sparc.xpm"

#include <Vk/VkPixmap.h>
#include <Xm/Xm.h>
#include <X11/Xlib.h>
#include <string>
#include <iostream>
#include <ostream>
#include <sstream>

using namespace std;

ListViewDelegate::ListViewDelegate()
{
    _numberOfRows = 0;
    _heightOfRow = 72;
}

ListViewDelegate::~ListViewDelegate()
{

}

// --------------------------------------------------------------------------------------------------------------------------

int 
ListViewDelegate::numberOfRows()
{
    return _numberOfRows;
}

void
ListViewDelegate::setNumberOfRows(int numberOfRows)
{
    _numberOfRows =  numberOfRows;
}

int 
ListViewDelegate::heightOfRow()
{
    // std::cout << "ListViewDelegate::heightOfRow() " << _heightOfRow << endl; 

    return _heightOfRow;;
}

 void 
 ListViewDelegate::setHeightOfRow(int heightOfRow)
 {
    _heightOfRow = heightOfRow;
 }

// --------------------------------------------------------------------------------------------------------------------------

void 
ListViewDelegate::draw(int rowId, VkGraphics* g, XRectangle rectangle)
{
    // title
    XRectangle rect = EZ::ofRectangle(rectangle, 60, 18, 300, 13);

    stringstream ss;
    ss << "[" << rowId << "] - Ant Design Title 2"; 
    
    std::string fontName("Verdan:style=Bold:pixelsize=10:antialias=true");
    std::string colorName("black");

    g->drawStringXft(fontName, colorName, rect.x, rect.y+rect.height-2, ss.str());

    // text
    rect = EZ::ofRectangle(rectangle, 60,44, 300, 13);

    std::string fontName2("Verdan:pixelsize=10:antialias=true");
    std::string colorName2("gray55");

    g->drawStringXft(fontName2, colorName2, rect.x, rect.y+rect.height-2, "Ant Design, a design language for background apllications, is refined by Ant UED Team");

    // image
    rect = EZ::ofRectangle(rectangle, 6, 15, 48, 48);
    g->drawRectangle(rect, "green");

    g->getPixmapByName("sun", _workstation_sparc);

    g->draw("sun", 48, 48, rect.x, rect.y);    
}