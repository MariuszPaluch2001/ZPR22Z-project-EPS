#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class App : public wxApp
{
public:
  bool OnInit();
};

class Frame : public wxFrame
{
public:
  Frame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
  wxMenu* menuFile;
  wxMenu* menuHelp;
  wxMenuBar* menuBar;
  wxBoxSizer* sizer;
  wxBoxSizer* rowSizer1;
  wxBoxSizer* rowSizer2;
  wxBoxSizer* sizerButtons;
  wxButton* buttonSubmit;
  wxButton* buttonSelectFile;
  wxStaticText* label1;
  wxStaticText* label2;
  wxComboBox* comboBox;
  wxTextCtrl* textCtrl;
  
  void OnExit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);

  wxDECLARE_EVENT_TABLE();
};
