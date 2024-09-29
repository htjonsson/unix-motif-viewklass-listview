#ifndef LIST_VIEW_DELEGATE_H
#define LIST_VIEW_DELEGATE_H

#include "VkGraphics.h"
#include <Xm/Xm.h>

class ListViewDelegate
{
public:
    ListViewDelegate();
    ~ListViewDelegate();

private:
    int _numberOfRows;

public:
    int numberOfRows();
    void setNumberOfRows(int numberOfRows);

private:
    int _heightOfRow;

public:
    int heightOfRow();
    void setHeightOfRow(int heightOfRow);

public:
    void draw(int rowId, VkGraphics* graphics, XRectangle rectangle);
};

#endif // LIST_VIEW_DELEGATE_H