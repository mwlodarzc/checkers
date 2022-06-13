#ifndef GAME_WINDOW_HH
#define GAME_WINDOW_HH
#include <wx/wx.h>
#include <wx/event.h>
#include "ChceckerBoard.hh"

class GameWindow : public wxFrame
{
public:
    int nWidth = 10;
    int nHeight = 10;
    wxPanel **btn;

public:
    GameWindow();
    ~GameWindow();
    void OnButtonClicked(wxCommandEvent &evt);

    wxDECLARE_EVENT_TABLE();
};

#endif