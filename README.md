### GOAL
To create a simple listview in Motif/SGI ViewKit (simular to listview in iOS), using delegator pattern.

![alt text](Screenshot_2020-06-26_16-04-41.png)

### TODO
- Pixel scrolling
- Mouse click
- Mouse double click 
- Mouse scroll wheel

#### main.C :
Starting point of application, creates windows, widgets, delegator and listview
####Delegate.h/C :
Drawing of the list view, getting select command and telling the listview how many rows it has
####DefaultResouces.h :
Default resources for motif
####EZ.h/C :
Helper class, for X11 and Motif
####Graphics.h/C :
Contains all drawing routines, and cashing of images/fonts
####ListView.h/C :
UI Component class, contains motif widgets (drawing, scrollbar), handles callbacks
####ListViewDelegate.h/C :
Delegation class for the ListView
