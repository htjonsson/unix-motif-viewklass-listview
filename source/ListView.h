#ifndef LIST_VIEW_H
#define LIST_VIEW_H

#include <Vk/VkComponent.h>
#include <Xm/Xm.h>
#include "ListViewDelegate.h"

class ListView : public VkComponent
{
private:
    Widget _drawingArea;
    Widget _verticalScrollbar;
    Widget _horizontalScrollbar;

private:
    Graphics graphics;

private:
    Dimension _rowHeight = 30;
    Dimension _rowWidth = 0;

    int _numberOfRowsVisible = 1;
    int _numberOfRows = 1;
    int _offsetRows = 0;
    int _separatorHeight = 1;

private:
    ListViewDelegate* _delegate = NULL;

public:
    ListView(const char *name, Widget parent, ListViewDelegate *delegate);
    ~ListView();

private:
  void createWidget(const char *name, Widget parent);  

public:
    void setDelegate(ListViewDelegate* delegate);
    ListViewDelegate* delegate();

public:
    void setNumberOfRows(int numberOfRows);
    int numnberOfRows();

public:
    void setHeightOfRow(int heightOfRow);

private:
    void setupUserInterface(Widget w);

private:
    void redraw(Window window);

public:
    void setRowsVisible(Dimension height);
    int getRowIdByY(int y);

private:
    int _selectedRow = -1;

public:
    void setSelectedRow(int id);
    int selectedRow();
    void clearSelectionRow();

private:
    void handleScrolled(int orientation, int value);
    void handleExpose(Window window); 
    void handleResize(Window window);   
    void handleEvent(XEvent* event);  
    void handleButtonPressed(XButtonPressedEvent* event);
    void handleButton1Pressed(XButtonPressedEvent* event);

private:
    static void inputCallback(Widget widget, XtPointer clientData, XtPointer callData);
    static void exposeCallback(Widget widget, XtPointer clientData, XtPointer callData); 
    static void resizeCallback(Widget widget, XtPointer clientData, XtPointer callData);   
    static void valueChangedVerticalCallback(Widget widget, XtPointer clientData, XtPointer callData);   
    static void dragVerticalCallback(Widget widget, XtPointer clientData, XtPointer callData);   
    static void valueChangedHorizontalCallback(Widget widget, XtPointer clientData, XtPointer callData);   
    static void dragHorizontalCallback(Widget widget, XtPointer clientData, XtPointer callData);     
};

#endif // LIST_VIEW_H