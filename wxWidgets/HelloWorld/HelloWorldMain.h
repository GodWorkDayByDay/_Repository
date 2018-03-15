#ifndef HELLOWORLDMAIN_H
#define HELLOWORLDMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class HelloWorldFrame: public wxFrame
{
    public:
        HelloWorldFrame(wxFrame *frame, const wxString& title);
        ~HelloWorldFrame();

    private:
        enum { idMenuQuit = 1000, idMenuAbout };
        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};

#endif // HELLOWORLDMAIN_H
