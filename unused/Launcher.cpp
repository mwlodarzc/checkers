#include "Launcher.hh"

wxIMPLEMENT_APP(Launcher);

Launcher::Launcher()
{
}

Launcher::~Launcher()
{
    delete m_frame;
}

bool Launcher::OnInit()
{
    m_frame = new GameWindow();
    m_frame->Show();
    return true;
}
