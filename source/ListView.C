// https://www.oreilly.com/openbook/motif/vol6a/Vol6a_html/appa.html#28

#include "ListView.h"
#include "EZ.h"
#include "Graphics.h"

#include <Xm/ScrolledW.h>
#include <Xm/DrawingA.h>
#include <Xm/ScrollBar.h>
#include <string>
#include <iostream>

using namespace std;

ListView::ListView(const char *name, Widget parent, ListViewDelegate *delegate)
    : VkComponent(name)
{
    setDelegate(delegate);
    createWidget(name, parent);

    if (_delegate != NULL)
        setNumberOfRows(_delegate->numberOfRows());      
}

ListView::~ListViewPaListViewnel()
{
}

void ListView::createWidget(const char *name, Widget parent)
{
    _baseWidget = XtVaCreateManagedWidget(name,
                                          xmScrolledWindowWidgetClass, parent,
                                          XmNscrollingPolicy, XmAPPLICATION_DEFINED,
                                          XmNvisualPolicy, XmVARIABLE,
                                          XmNshadowThickness, 0,
                                          NULL);

    // --------------------------------------------------------------------------

    _drawingArea = XtVaCreateManagedWidget("list_view_panel_drawing_a",
                                           xmDrawingAreaWidgetClass, _baseWidget,
                                           // XmNwidth, Resrcs.view_width,
                                           // XmNheight, Resrcs.view_height,
                                           NULL);

    // --------------------------------------------------------------------------

    _verticalScrollbar = XtVaCreateManagedWidget("list_view_panel_vertical_scrollbar",
                                                 xmScrollBarWidgetClass, _baseWidget,
                                                 XmNorientation, XmVERTICAL,
                                                 XmNminimum, 0,
                                                 XmNmaximum, _numberOfRows,
                                                 // XmNsliderSize,  1,  // (int)(_numberOfRows/_numberOfRowsVisible),
                                                 NULL);

    // --------------------------------------------------------------------------

    _horizontalScrollbar = XtVaCreateManagedWidget("list_view_panel_horizontal_scrollbar",
                                                   xmScrollBarWidgetClass, _baseWidget,
                                                   XmNorientation, XmHORIZONTAL,
                                                   XmNmaximum, 1,
                                                   // XmNsliderSize,    min (Resrcs.view_width / cell_width, Resrcs.cols),
                                                   NULL);

    // --------------------------------------------------------------------------

    XmScrolledWindowSetAreas(_baseWidget, _horizontalScrollbar, _verticalScrollbar, _drawingArea);

    // --------------------------------------------------------------------------

    XtAddCallback(_drawingArea, XmNexposeCallback, exposeCallback, this);
    XtAddCallback(_drawingArea, XmNresizeCallback, resizeCallback, this);
    XtAddCallback(_drawingArea, XmNinputCallback, inputCallback, this);

    // --------------------------------------------------------------------------

    XtAddCallback(_verticalScrollbar, XmNvalueChangedCallback, valueChangedVerticalCallback, this);
    XtAddCallback(_verticalScrollbar, XmNdragCallback, dragVerticalCallback, this);

    // --------------------------------------------------------------------------

    XtAddCallback(_horizontalScrollbar, XmNvalueChangedCallback, valueChangedHorizontalCallback, this);
    XtAddCallback(_horizontalScrollbar, XmNdragCallback, dragHorizontalCallback, this);
}

// ------------------------------------------------------------------------------------------------------------------------
//
//      DELEGATE LOGIC
//
// ------------------------------------------------------------------------------------------------------------------------

void 
ListView::setDelegate(ListViewDelegate *delegate)
{
    _delegate = delegate;
}

Delegate *
ListView::delegate()
{
    return _delegate;
}

int 
ListView::numnberOfRows()
{
    return _numberOfRows;
}

void
ListView::setNumberOfRows(int numberOfRows)
{
    if (_numberOfRows != numberOfRows && numberOfRows > 1)
    {
        _numberOfRows = numberOfRows;

        XtVaSetValues(_verticalScrollbar, XmNmaximum, numberOfRows-1, NULL);
    }
}

// ------------------------------------------------------------------------------------------------------------------------
//
//      SELECTED ROW LOGIC
//
// ------------------------------------------------------------------------------------------------------------------------

void 
ListView::setSelectedRow(int id)
{
    if (_numberOfRows > id || id < 0)
        clearSelectionRow();

    _selectedRow = id;
}
    
int 
ListView::selectedRow()
{
    return _selectedRow;
}
    
void 
ListView::clearSelectionRow()
{
    _selectedRow = -1;
}

// ------------------------------------------------------------------------------------------------------------------------
//
//      DRAWING LOGIC
//
// ------------------------------------------------------------------------------------------------------------------------

void 
ListView::setRowsVisible(Dimension height)
{
    if (height > 0)
    {
        XtError("Can't calculate rows visible");
        return;
    }

    float rows = (float)height / (float)_rowHeight;
    _numberOfRowsVisible = (int)rows; //  + 1;
}

void 
ListView::redraw(Window window)
{
    // BAD NAME    
    graphics.setWidget(_drawingArea);

    std::cout << "draw()" << std::endl;

    // Clear the drawarea with white color
    XRectangle windowReact = EZ::makeRectangle(0, 0, 0, 0);
    XtVaGetValues(_drawingArea, XmNwidth, &windowReact.width, XmNheight, &windowReact.height, NULL);
    graphics.fillRectangle(windowReact, "white");

    if (_delegate == NULL)
    {
        XtError("Delegator not found");
        return;
    }

    int separator = 1;
    int hightOfRow = _delegate->heightOfRow();

    // std::cout << "[numberOfRows] " << _numberOfRows << std::endl;
    // std::cout << "[offsetRows] " << _offsetRows << std::endl;

    for (int i = 0; i < _numberOfRowsVisible; i++)
    {
        int rowId = i + (_offsetRows); 

        if (this->_numberOfRows > rowId)
        {   
            int offset = (hightOfRow + separator) * i;

            if (_numberOfRows > 1)
            {
                // Draw separator line
                graphics.drawHorizontalLine(6, _rowWidth-6, offset+hightOfRow, "gray94");
            }

            if (rowId == selectedRow())
            {
                XRectangle selectedRowReact = EZ::makeRectangle(6, offset, windowReact.width-12, hightOfRow-separator);
                graphics.fillRectangle(selectedRowReact, "gray98");
            }

            XRectangle rectangle = EZ::makeRectangle(6, offset, _rowWidth-12, hightOfRow-separator);
            _delegate->draw(rowId, &graphics, rectangle);
        }     
    }

    // Fix the slide size 
    // int slideSize = (_numberOfRows/_numberOfRowsVisible);
    // XtVaSetValues(_verticalScrollbar, XmNsliderSize, slideSize, NULL);
}

int
ListView::getRowIdByY(int y)
{
    if (_delegate == NULL)
        return -1;

    int separator = 1;
    int hightOfRow = _delegate->heightOfRow();

    for (int i = 0; i < _numberOfRowsVisible; i++)
    {
        int rowId = i + (_offsetRows); 

        if (this->_numberOfRows > rowId)
        {   
            int offset = (hightOfRow + separator) * i;

            if (y >= offset && y <= offset+hightOfRow)
            {
                return rowId;
            }
                
        }
    }

    return -1;
}

// ------------------------------------------------------------------------------------------------------------------------
//
//      HANDLER ACTIONS
//
// ------------------------------------------------------------------------------------------------------------------------

void 
ListView::handleScrolled(int orientation, int value)
{
    std::cout << "scrolled " << value << std::endl;

    _offsetRows = value;

    redraw(XtWindow(_drawingArea));
}

void 
ListView::handleExpose(Window window)
{
    std::cout << "expose()" << std::endl;

    redraw(window);
}

void 
ListView::handleResize(Window window)
{
    Dimension width, height;
    GC gc;

    XtVaGetValues(_drawingArea, XmNwidth, &width, XmNheight, &height, NULL);

    _rowWidth = width;

    // std::cout << "XmNwidth " << width << std::endl;
    // std::cout << "XmNheight " << height << std::endl;

    if (_delegate != NULL)
    {
        // Calculate how many rows are visible
        int heightOfRow =  _delegate->heightOfRow();

        std::cout << "heightOfRow " << heightOfRow << std::endl;

        _numberOfRowsVisible = (int)(height/heightOfRow) + 1;

        std::cout << "numberOfRowsVisible " << _numberOfRowsVisible << std::endl;
    }
}

void 
ListView::handleEvent(XEvent* event)
{
    cout << "type : " << event->type << endl;

    // https://stackoverflow.com/questions/35745561/how-can-i-convert-an-xevent-to-a-string
    switch(event->type)
    {
        
        // case 2: cout << "XKeyPressedEvent" << endl; break;
        // case 3: handleKeyReleased((XKeyReleasedEvent*)event); break;
        case 4: handleButtonPressed((XButtonPressedEvent*)event); break;
        // case 5: handleButtonReleased((XButtonReleasedEvent*)event); break;
        // case 6: cout << "XPointerMovedEvent" << endl; break;
        // case 7: cout << "XEnterWindowEvent" << endl; break;
        // case 8: cout << "XLeaveWindowEvent" << endl; break;
        // case 9: cout << "XFocusInEvent" << endl; break;
        // case 10: cout << "XFocusOutEvent" << endl; break;
        // case 11: cout << "XKeymapEvent" << endl; break;
        // case 12: cout << "XExposeEvent" << endl; break;
        // case 13: cout << "XGraphicsExposeEvent" << endl; break;
        default: break; // cout << "Undefined" << endl; break;
    }
}

void 
ListView::handleButton1Pressed(XButtonPressedEvent* event)
{
    cout << "handleButton1Pressed" << " y: " << event->y << endl;    

    int rowId = getRowIdByY(event->y);

    setSelectedRow(rowId);

    redraw(XtWindow(_drawingArea));
}

void 
ListView::handleButtonPressed(XButtonPressedEvent* event)
{
    // cout << "handleButtonPressed" << endl;
    // cout << "x: " << event->x << " y: " << event->y << endl;

    // https://tronche.com/gui/x/xlib/events/keyboard-pointer/keyboard-pointer.html
    switch(event->button)
    {
        case Button1: /*cout << "Button1" << endl;*/ handleButton1Pressed(event); break;
        case Button2: cout << "Button2" << endl; break;
        case Button3: cout << "Button3" << endl; break;
        case Button4: cout << "Button4" << endl; break;
        case Button5: cout << "Button5" << endl; break;
        default: break;
    }
}

// ------------------------------------------------------------------------------------------------------------------------
//
//      MOTIF CALLBACKS LOGIC
//
// ------------------------------------------------------------------------------------------------------------------------

void 
ListView::exposeCallback(Widget widget, XtPointer clientData, XtPointer callData)
{
    std::cout << "exposeCallback" << std::endl;

    XmDrawingAreaCallbackStruct *cbs = (XmDrawingAreaCallbackStruct *)callData;

    if (callData != NULL)
    {
        ListView *listView = (ListView*)clientData;
        listView->handleExpose(cbs->window);
    }
}

void ListView::inputCallback(Widget widget, XtPointer clientData, XtPointer callData)
{
    std::cout << "inputCallback" << std::endl;

    XmDrawingAreaCallbackStruct *cbs = (XmDrawingAreaCallbackStruct *)callData;

    if (clientData != NULL)
    {
        ListView *listView = (ListView*)clientData;
        listView->handleEvent(cbs->event); 
    }
}   

void ListView::resizeCallback(Widget widget, XtPointer clientData, XtPointer callData)
{
    std::cout << "resizeCallback" << std::endl;

    XmDrawingAreaCallbackStruct *cbs = (XmDrawingAreaCallbackStruct *)callData;

    if (callData != NULL)
    {
        ListView *listView = (ListView*)clientData;
        listView->handleResize(cbs->window);
    }
}

void ListView::valueChangedVerticalCallback(Widget widget, XtPointer clientData, XtPointer callData)
{
    std::cout << "valueChangedVerticalCallback" << std::endl;

    ListView *listView = (ListView*)clientData;

    if (callData != NULL)
    {
        ListView *listView = (ListView*)clientData;
        listView->handleScrolled(XmVERTICAL, ((XmScrollBarCallbackStruct *)callData)->value);
    }
}

void ListView::dragVerticalCallback(Widget widget, XtPointer clientData, XtPointer callData)
{
    std::cout << "dragVerticalCallback" << std::endl;

    if (callData != NULL)
    {
        ListView *listView = (ListView*)clientData;
        listView->handleScrolled(XmVERTICAL, ((XmScrollBarCallbackStruct *)callData)->value);
    }
}

void ListView::valueChangedHorizontalCallback(Widget widget, XtPointer clientData, XtPointer callData)
{
    std::cout << "valueChangedHorizontalCallback" << std::endl;

    if (callData != NULL)
    {
        ListView *listView = (ListView*)clientData;
        listView->handleScrolled(XmVERTICAL, ((XmScrollBarCallbackStruct *)callData)->value);
    }
}

void ListView::dragHorizontalCallback(Widget widget, XtPointer clientData, XtPointer callData)
{
    std::cout << "dragHorizontalCallbackWidget" << std::endl;

    if (callData != NULL)
    {
        ListView *listView = (ListView*)clientData;
        listView->handleScrolled(XmVERTICAL, ((XmScrollBarCallbackStruct *)callData)->value);
    }
}