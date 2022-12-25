#include "GUI.h"

bool App::OnInit()
{
  Frame* frame = new Frame("EPS compression", wxPoint(50, 50), wxSize(800, 700));
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
  
  labelScaleInput = new wxStaticText(this, wxID_ANY, "Wybierz pomniejszenie obrazka:     ");
  comboBox = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxSize(150, 30), 0, nullptr, wxCB_READONLY);

  for (int i = 1; i <= 5; i++)
  {
        comboBox->Append(wxString::Format("%dx", i));
  }

  comboBox->SetSelection(0);
  
  rowSizer1 = new wxBoxSizer(wxHORIZONTAL);
  rowSizer1->Add(labelScaleInput, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
  rowSizer1->Add(comboBox, 1, wxEXPAND);
  
  labelInputMinDist = new wxStaticText(this, wxID_ANY, "Min odleglosc pomiedzy punktami:");
  textCtrl = new wxTextCtrl(this, wxID_ANY, "0.0", wxDefaultPosition, wxSize(150, 30), wxTE_PROCESS_ENTER);
  
  rowSizer2 = new wxBoxSizer(wxHORIZONTAL);
  rowSizer2->Add(labelInputMinDist, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
  rowSizer2->Add(textCtrl, 1, wxEXPAND);
  
  sizerButtons = new wxBoxSizer(wxHORIZONTAL);
  buttonSelectFile = new wxButton(this, wxID_ANY, "Wybierz plik", wxDefaultPosition);
  buttonSubmit = new wxButton(this, wxID_ANY, "Potwierdz", wxDefaultPosition);
  
  sizerButtons->Add(buttonSelectFile, 0, wxEXPAND | wxRIGHT | wxUP | wxDOWN, 5);
  sizerButtons->Add(buttonSubmit, 0, wxEXPAND | wxALL, 5);
  
  sizerImages = new wxBoxSizer(wxHORIZONTAL);
  
  sizerInputImage = new wxBoxSizer(wxVERTICAL);
  labelInputImage = new wxStaticText(this, wxID_ANY, "Obrazek wejsciowy");
  inputImage = new wxStaticBitmap(this, wxID_ANY, wxBitmap("assets/no_eps_available.png", wxBITMAP_TYPE_PNG));
  labelInputImageSize = new wxStaticText(this, wxID_ANY, "Rozmiar przed: ");
  labelInputImageResolution = new wxStaticText(this, wxID_ANY, "Rozdzielczosc przed: ");
  
  sizerInputImage->Add(labelInputImage, 0, wxEXPAND | wxALL, 5);
  sizerInputImage->Add(inputImage, 0, wxEXPAND | wxALL, 5);
  sizerInputImage->Add(labelInputImageSize, 0, wxEXPAND | wxALL, 5);
  sizerInputImage->Add(labelInputImageResolution, 0, wxEXPAND | wxALL, 5);
  
  sizerOutputImage = new wxBoxSizer(wxVERTICAL);
  labelOutputImage = new wxStaticText(this, wxID_ANY, "Obrazek wyjsciowy");
  outputImage = new wxStaticBitmap(this, wxID_ANY, wxBitmap("assets/no_eps_available.png", wxBITMAP_TYPE_PNG));
  labelOutputImageSize = new wxStaticText(this, wxID_ANY, "Rozmiar po: ");
  labelOutputImageResolution = new wxStaticText(this, wxID_ANY, "Rozdzielczosc po: ");
  
  sizerOutputImage->Add(labelOutputImage, 0, wxEXPAND | wxALL, 5);
  sizerOutputImage->Add(outputImage, 0, wxEXPAND | wxALL, 5);
  sizerOutputImage->Add(labelOutputImageSize, 0, wxEXPAND | wxALL, 5);
  sizerOutputImage->Add(labelOutputImageResolution, 0, wxEXPAND | wxALL, 5);
  
  sizerImages->Add(sizerInputImage, 0, wxEXPAND | wxRIGHT | wxUP | wxDOWN, 5);
  sizerImages->Add(sizerOutputImage, 0, wxEXPAND | wxALL, 5);
  
  buttonGetOutput = new wxButton(this, wxID_ANY, "Zapisz", wxDefaultPosition);
  
  sizer->Add(rowSizer1, 0, wxALL, 10);
  sizer->Add(rowSizer2, 0, wxALL, 10);
  sizer->Add(sizerButtons, 0, wxALL, 10);
  sizer->Add(sizerImages, 0, wxALL, 10);
  sizer->Add(buttonGetOutput, 0, wxALL, 10);
  
  SetSizer(sizer);
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
