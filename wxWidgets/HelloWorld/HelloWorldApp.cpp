#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "HelloWorldApp.h"
#include "HelloWorldMain.h"

IMPLEMENT_APP(HelloWorldApp);

bool HelloWorldApp::OnInit()
{
    HelloWorldFrame* frame = new HelloWorldFrame(0L, _("wxWidgets Application Template"));
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show();

    return true;
}
