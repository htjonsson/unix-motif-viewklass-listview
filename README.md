### Create a nice looking listview, that is simple to use 
- Using Motif/SGI ViewKit
- That works similar to to listview in iOS
- Use delegator pattern
- Use XFT font drawing

![alt text](screenshot.png)

### TODO
- Pixel scrolling
- Double buffer
- Mouse double click 
- Mouse scroll wheel
- Horizontal scrolling

#### main.C :
Starting point of application, creates windows, widgets, delegator and listview
#### Delegate.h/C :
Drawing of the list view, getting select command and telling the listview how many rows it has
#### DefaultResouces.h :
Default resources for motif
#### EZ.h/C :
Helper class, for X11 and Motif
#### Graphics.h/C :
Contains all drawing routines, and cashing of images/fonts
#### ListView.h/C :
UI Component class, contains motif widgets (drawing, scrollbar), handles callbacks
#### ListViewDelegate.h/C :
Delegation class for the ListView
