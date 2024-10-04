#ifndef DELEGATE_H
#define DELEGATE_H

#include "ListViewDelegate.h"
#include "Graphics.h"

#include <Xm/Xm.h>

class Delegate : public ListViewDelegate
{
public:
    Delegate();
    ~Delegate();

private:
    static const std::string _titlefontName;
    static const std::string _titleColorName;

private:
    static const std::string _textfontName;
    static const std::string _textColorName;

private:
    std::string getTitle(int rowId);
    std::string getText(int rowId); 
    std::string getImageName(int rowId, Graphics* g);

public:
    int numberOfRows();

public:
    void rowSelected(int rowId);

public:
    void draw(int rowId, Graphics* graphics, XRectangle rectangle);
};

#endif // DELEGATE_H
