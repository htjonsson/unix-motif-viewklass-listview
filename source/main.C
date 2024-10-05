// Motif 
#include <Xm/Xm.h>
#include <Xm/PushB.h>
#include <Xm/Text.h>
#include <Xm/List.h>
// ViewKlass
#include <Vk/VkApp.h>
#include <Vk/VkSimpleWindow.h>
// Standard C/C++
#include <stdio.h>
#include <iostream>
#include <vector>

#include "ListView.h"
#include "Delegate.h"
#include "DefaultResources.h"

using namespace std;

// Application-specific setup
int main ( int argc, char **argv )
{
    VkApp* app = new VkApp("ListViewApp", &argc, argv);
    // Application-specific code
    app->setDefaultResources(app->baseWidget(), _defaultResources);

    VkSimpleWindow* win = new VkSimpleWindow("ListView");
    
    Delegate delegate;
    delegate.setNumberOfRows(8);

    ListView panel("list_view_panel", win->mainWindowWidget(), &delegate);
    win->addView(panel);

    // Set a default size of window as 800x600
    XtVaSetValues(win->mainWindowWidget(), XmNwidth, 800, XmNheight, 600, NULL);

    win->show();

    // Run the application
    app->run();  

    return 0;
}

