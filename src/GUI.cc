#include "GUI.h"

bool App::OnInit()
{
  Frame* frame = new Frame("EPS compression", wxPoint(50, 50), wxSize(450, 400));
  frame->Show(true);
  return true;
}

Frame::Frame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{

  menuFile = new wxMenu();
  menuFile->Append(wxID_EXIT);

  menuHelp = new wxMenu();
  menuHelp->Append(wxID_ABOUT);

  menuBar = new wxMenuBar();
  menuBar->Append(menuFile, "&File");
  menuBar->Append(menuHelp, "&Help");

  SetMenuBar(menuBar);
  
  sizer = new wxBoxSizer(wxVERTICAL);
  
  label1 = new wxStaticText(this, wxID_ANY, "Wybierz pomniejszenie obrazka:     ");
  comboBox = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxSize(150, 30), 0, nullptr, wxCB_READONLY);

  for (int i = 1; i <= 5; i++)
  {
        comboBox->Append(wxString::Format("%dx", i));
  }

  comboBox->SetSelection(0);
  
  rowSizer1 = new wxBoxSizer(wxHORIZONTAL);
  rowSizer1->Add(label1, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
  rowSizer1->Add(comboBox, 1, wxEXPAND);
  
  label2 = new wxStaticText(this, wxID_ANY, "Min odleglosc pomiedzy punktami:");
  textCtrl = new wxTextCtrl(this, wxID_ANY, "0.0", wxDefaultPosition, wxSize(150, 30), wxTE_PROCESS_ENTER);
  
  rowSizer2 = new wxBoxSizer(wxHORIZONTAL);
  rowSizer2->Add(label2, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
  rowSizer2->Add(textCtrl, 1, wxEXPAND);
  
  sizerButtons = new wxBoxSizer(wxVERTICAL);
  buttonSelectFile = new wxButton(this, wxID_ANY, "Wybierz plik", wxDefaultPosition);
  buttonSubmit = new wxButton(this, wxID_ANY, "Potwierdz", wxDefaultPosition);
  
  sizerButtons->Add(buttonSelectFile, 0, wxEXPAND | wxALL, 5);
  sizerButtons->Add(buttonSubmit, 0, wxEXPAND | wxALL, 5);
  
  sizer->Add(rowSizer1, 0, wxALL, 10);
  sizer->Add(rowSizer2, 0, wxALL, 10);
  sizer->Add(sizerButtons, 0, wxALL, 10);
  
  SetSizer(sizer);

  CreateStatusBar();
  SetStatusText("Welcome to app!");
}

wxBEGIN_EVENT_TABLE(Frame, wxFrame)
    EVT_MENU(wxID_EXIT, Frame::OnExit)
    EVT_MENU(wxID_ABOUT, Frame::OnAbout)
wxEND_EVENT_TABLE()

void Frame::OnExit(wxCommandEvent& event) { Close(true); }

void Frame::OnAbout(wxCommandEvent& event)
{
  wxMessageBox("It's our EPS file compression app.", "About app",
               wxOK | wxICON_INFORMATION);
}
