#include "GameWindow.hh"

// clang-format off

wxBEGIN_EVENT_TABLE(GameWindow, wxFrame)
    // EVT_BUTTON(10001,OnButtonClicked)
wxEND_EVENT_TABLE()

GameWindow::GameWindow() : wxFrame(nullptr, wxID_ANY, "Checkers game!", wxPoint(30, 30), wxSize(1000, 1000))
// clang-format on
{
    btn = new wxPanel *[nWidth * nHeight];
    wxGridSizer *grid = new wxGridSizer(nWidth, nHeight, 0, 0);
    for (int x = 0; x < nWidth; x++)
    {
        for (int y = 0; y < nHeight; y++)
        {
            btn[y * nWidth + x] = new wxPanel(this, 10000 + (y * nWidth + x), wxDefaultPosition, wxSize(100, 100));
            if (y % 2 == x % 2)
                btn[y * nWidth + x]->SetBackgroundColour(wxColor(255, 255, 255, 255));
            else
                btn[y * nWidth + x]->SetBackgroundColour(wxColor(0, 0, 0, 255));
            grid->Add(btn[y * nWidth + x], 1, wxEXPAND | wxALL);
        }
    }
    this->SetSizer(grid);
    grid->Layout();
    this->SetSizerAndFit(grid);
}
GameWindow::~GameWindow() {}
void GameWindow::OnButtonClicked(wxCommandEvent &evt)
{
    evt.Skip();
}