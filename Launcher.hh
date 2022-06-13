#ifndef GW_HH
#define GW_HH
#include <wx/wx.h>
#include "GameWindow.hh"
class Launcher : public wxApp
{
private:
    GameWindow *m_frame = nullptr;

public:
    Launcher();
    ~Launcher();
    virtual bool OnInit();
};

#endif