#ifndef LIST_VIEW_DELEGATE_H
#define LIST_VIEW_DELEGATE_H

#include "Graphics.h"
#include <Xm/Xm.h>

class ListViewDelegate
{
public:
    ListViewDelegate();
    virtual ~ListViewDelegate();

private:
    int _numberOfRows;

public:
    virtual int numberOfRows();
    void setNumberOfRows(int numberOfRows);

private:
    int _heightOfRow;

public:
    int heightOfRow();
    void setHeightOfRow(int heightOfRow);

public:
    void rowSelected(int rowId);

public:
    virtual void draw(int rowId, Graphics* graphics, XRectangle rectangle);
};

#endif // LIST_VIEW_DELEGATE_H