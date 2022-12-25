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
  wxBoxSizer* sizerImages;
  wxBoxSizer* sizerInputImage;
  wxBoxSizer* sizerOutputImage;
  wxButton* buttonSubmit;
  wxButton* buttonSelectFile;
  wxStaticText* label1;
  wxStaticText* label2;
  wxStaticText* labelInputImage;
  wxStaticText* labelOutputImage;
  wxComboBox* comboBox;
  wxTextCtrl* textCtrl;
  wxStaticBitmap* inputImage;
  wxStaticBitmap* outputImage;
  
  void OnExit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);

  wxDECLARE_EVENT_TABLE();
};
