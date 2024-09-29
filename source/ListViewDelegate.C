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

void
ListViewDelegate::rowSelected(int rowId)
{
    std::cout << "ListViewDelegate::rowSelected " << rowId << std::endl;
}

// --------------------------------------------------------------------------------------------------------------------------

void 
ListViewDelegate::draw(int rowId, Graphics* g, XRectangle rectangle)
{}
 