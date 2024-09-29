#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <X11/Xft/Xft.h>
#include <Xm/Xm.h>
#include <string>
#include <iostream>
#include <map>

class Graphics
{
private:
     Display* _display;
     GC _gc = NULL;
     Window _window;
     Widget _widget;

public:
     Graphics();
     ~Graphics();

public:
     void setWidget(Widget widget);
     Widget widget();
     GC gc();
     Window window();
     Display* display();
     
protected:     
     Colormap getColormap();  

public:
     void drawLine(int x1, int y1, int x2, int y2, std::string colorName);
     void drawHorizontalLine(int x1, int x2, int y, std::string colorName);

public:
     void drawRectangle(XRectangle rectangle, std::string colorName);  
     void drawRectangle(XRectangle rectangle);
     void drawRectangle(Dimension x, Dimension y, Dimension width, Dimension height);

public:
     void fillRectangle(XRectangle rectangle, std::string colorName);     
     void fillRectangle(XRectangle rectangle);
     void fillRectangle(Position x, Position y, Dimension width, Dimension height);

private:     
     std::map<std::string, XftFont*> _xftFontMap;
     std::map<std::string, XftColor*> _xftColorMap;

private:
     XftColor* getColorByNameXft(std::string colorName);
     XftFont* getFontByNameXft(std::string fontName);

public:
     bool drawString(std::string fontName, std::string colorName, XRectangle rect, std::string text);
     bool drawString(std::string fontName, std::string colorName, Dimension x, Dimension y, std::string text);

private:
     std::map<std::string, XColor*> _colorMap;

public:
     void setForegroundColor(XColor* color);
     void setForegroundColor(Pixel pixel);

public:     
     void setBackgroundColor(XColor* color);
     void setBackgroundColor(Pixel pixel);

public: 
     void setForegroundColor(std::string colorName);
     void setBackgroundColor(std::string colorName);

public:
     XColor* getColorByName(std::string colorName);

private:
     std::map<std::string, Pixmap> _pixmapMap;

public:
     Pixmap getPixmapByName(std::string pixmapName, const char** xpmPixmapDesc);
     Pixmap getPixmap(std::string pixmapName);
     void setPixmap(std::string pixmapName, Pixmap pixmap);

public:
     void draw(std::string pixmapName, XRectangle rect);
     void draw(std::string pixmapName, unsigned int width, unsigned int height, int dest_x, int dest_y);
     void draw(Pixmap pixmap, unsigned int width, unsigned int height, int dest_x, int dest_y); 
};

#endif // GRAPHICS_H