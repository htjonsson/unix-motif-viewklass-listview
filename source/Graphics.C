#include "Graphics.h"

#include <Vk/VkPixmap.h>

Graphics::Graphics()
{

}

Graphics::~Graphics()
{
    // Remove GC
    if (_gc != NULL && _display != NULL)
        XFreeGC(_display, _gc);

    // Clean up font map
    for(auto font : _fontMap)
    {
        if (font.second != NULL)
        {
            delete font.second;
            font.second = NULL;
        }
    } 
    _fontMap.clear();

    // Clear up color map
    for(auto color : _colorMap) 
        delete color.second;
    _colorMap.clear();    
} 

void 
Graphics::setWidget(Widget widget)
{
    _widget = widget;
    _display = XtDisplay(widget);
    _window = XtWindow(widget);

    if (!(_gc = XCreateGC(_display, _window, NULL, 0)))
    {
        XtError("Can't create gc.");
    }
}

Widget
Graphics::widget()
{
    return _widget;
}

GC
Graphics::gc()
{
    return _gc;
}

Window
Graphics::window()
{
    return _window;
}

Display*
Graphics::display()
{
    return _display;
}

void 
Graphics::clearWindow()
{
    XClearWindow(_display, _window);
}

Colormap
Graphics::getColormap()
{
    return DefaultColormap(_display, DefaultScreen(_display));
}

// ---------------------------------------------------------------------------------------
//
//      XFT STRING LOGIC - TRUE TYPE FONTS
//      https://github.com/jsynacek/xft-example/tree/master
//
// ---------------------------------------------------------------------------------------

XftColor* 
Graphics::getColorByNameXft(std::string colorName)
{
    XftColor* color = (XftColor*) XtMalloc((sizeof(XftColor)));

    if (_xftColorMap.count(colorName) == 0)
    {
        Colormap colormap = getColormap(); 
        Visual* visual = DefaultVisual(_display, DefaultScreen(_display));

        if (!XftColorAllocName(_display, visual, colormap, colorName.c_str(), color))
            return NULL;

        _xftColorMap.insert(std::pair<std::string, XftColor*>(colorName, color)); 

        return color;
    }
    
    return _xftColorMap.at(colorName);
}

XftFont* 
Graphics::getFontByNameXft(std::string fontName)
{
    if (_xftFontMap.count(fontName) == 0)
    {
        XftFont* font = XftFontOpenName(_display, DefaultScreen(_display), fontName.c_str());

        if (!font)
        {
            std::string warning("Font " + fontName + " not found");
            XtWarning(warning.c_str());
            delete font;
            return NULL;
        }
        _xftFontMap.insert(std::pair<std::string, XftFont*>(fontName, font));

        // std::cout << "[getXftFontByName] " << fontName << " added to _xftFontMap" << std::endl;

        return font;

    }

    XftFont* font = _xftFontMap.at(fontName);

    // std::cout << "[getXftFontByName] " << fontName << " font already in _xftFontMap" << std::endl;

    return font;
}

bool
Graphics::drawString(std::string fontName, std::string colorName, Dimension x, Dimension y, std::string text)
{
    XftFont* font = getFontByNameXft(fontName);
    XftColor* color = getColorByNameXft(colorName);

    if (color != NULL && font != NULL)
    {
        Colormap colormap = getColormap();
        Visual* visual = DefaultVisual(_display, DefaultScreen(_display));

        XftDraw* draw = XftDrawCreate(_display, _window, visual, colormap);

        XftDrawStringUtf8(draw, color, font, x, y, (const FcChar8 *)text.c_str(), text.length());

        XftDrawDestroy(draw);
    }      
}

// ---------------------------------------------------------------------------------------
//
//      LINE  LOGIC
//
// ---------------------------------------------------------------------------------------

void 
Graphics::drawLine(int x1, int y1, int x2, int y2, std::string colorName)
{
    setForegroundColor(colorName);
    XDrawLine(_display, _window, _gc, x1, y1, x2, y2);
}

void 
Graphics::drawHorizontalLine(int x1, int x2, int y, std::string colorName)
{
    drawLine(x1, y, x2, y, colorName);
}

// ---------------------------------------------------------------------------------------
//
//      RECTANGLE  LOGIC
//
// ---------------------------------------------------------------------------------------

void
Graphics::drawRectangle(XRectangle rectangle, std::string colorName)
{
    setForegroundColor(colorName);
    drawRectangle(rectangle);
}

void
GraphicsGraphics::drawRectangle(Dimension x, Dimension y, Dimension width, Dimension height)
{
    XDrawRectangle(_display, _window, _gc, x, y, width, height);
}

void
Graphics::drawRectangle(XRectangle rectangle)
{
    XDrawRectangle(_display, _window, _gc, rectangle.x, rectangle.y, rectangle.width, rectangle.height);
}

void
Graphics::fillRectangle(XRectangle rectangle, std::string colorName)
{
    setForegroundColor(colorName);
    fillRectangle(rectangle);
}

void
Graphics::fillRectangle(XRectangle rectangle)
{
    XFillRectangle(_display, _window, _gc, rectangle.x, rectangle.y, rectangle.width, rectangle.height);
}

void
Graphics::fillRectangle(Position x, Position y, Dimension width, Dimension height)
{
    XFillRectangle(_display, _window, _gc, x, y, width, height);
}

// ---------------------------------------------------------------------------------------
//
//      COLOR HANDLING
//
// ---------------------------------------------------------------------------------------

XColor* 
Graphics::getColorByName(std::string colorName)
{
    XColor* color = (XColor*) XtMalloc((sizeof(XColor)));

    if (_colorMap.count(colorName) == 0)
    {
        Colormap colormap = getColormap();     

        XParseColor(_display, colormap, colorName.c_str(), color);
        XAllocColor(_display, colormap, color);

        _colorMap.insert(std::pair<std::string, XColor*>(colorName, color)); 
    }
    else
    {
        color = _colorMap.at(colorName);
    }

    return color;
}

void
Graphics::setForegroundColor(XColor* color)
{
    setForegroundColor(color->pixel);
} 

void 
Graphics::setForegroundColor(Pixel pixel)
{
    XSetForeground(_display, _gc, pixel);
}

void 
Graphics::setForegroundColor(std::string colorName)
{
    XColor* color = getColorByName(colorName);

    setForegroundColor(color);
}

void
Graphics::setBackgroundColor(XColor* color)
{
    setBackgroundColor(color->pixel);
} 

void 
Graphics::setBackgroundColor(Pixel pixel)
{
    XSetBackground(_display, _gc, pixel);
}

void 
Graphics::setBackgroundColor(std::string colorName)
{
    XColor* color = getColorByName(colorName);

    setBackgroundColor(color);
}

// ---------------------------------------------------------------------------------------
//
//      PIXMAP HANDLING
//
// ---------------------------------------------------------------------------------------

Pixmap 
Graphics::getPixmapByName(std::string pixmapName, const char** xpmPixmapDesc)
{
    if (_pixmapMap.count(pixmapName) == 0)
    {
        std::cout << "Name not found" << std::endl;

        Pixmap pixmap = VkCreateXPMPixmap(_widget, xpmPixmapDesc, NULL);

        if (pixmap == 0)
            return 0;

        _pixmapMap.insert(std::pair<std::string, Pixmap>(pixmapName, pixmap)); 

        std::cout << "pixmap " << pixmap  << std::endl;

        return pixmap;
    }
    std::cout << "Name found" << std::endl;

    return _pixmapMap.at(pixmapName);
}

Pixmap 
Graphics::getPixmap(std::string pixmapName)
{
    if (_pixmapMap.count(pixmapName) == 0)
        return 0;

    return _pixmapMap.at(pixmapName);
}

void 
Graphics::setPixmap(std::string pixmapName, Pixmap pixmap)
{
    if (_pixmapMap.count(pixmapName) == 0)
        _pixmapMap.insert(std::pair<std::string, Pixmap>(pixmapName, pixmap)); 
}

void 
Graphics::draw(std::string pixmapName, unsigned int width, unsigned int height, int dest_x, int dest_y)
{
    Pixmap pixmap = getPixmap(pixmapName);

    if (pixmap != 0)
        draw(pixmap, width, height, dest_x, dest_y);
}

void 
Graphics::draw(Pixmap pixmap, unsigned int width, unsigned int height, int dest_x, int dest_y)
{
    XCopyArea(_display, pixmap, _window, _gc, 0, 0, width, height, dest_x, dest_y);
}