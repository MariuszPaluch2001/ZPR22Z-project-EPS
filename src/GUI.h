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
  wxButton* buttonGetOutput;
  wxStaticText* labelScaleInput;
  wxStaticText* labelInputMinDist;
  wxStaticText* labelInputImage;
  wxStaticText* labelOutputImage;
  wxStaticText* labelInputImageSize;
  wxStaticText* labelOutputImageSize;
  wxStaticText* labelInputImageResolution;
  wxStaticText* labelOutputImageResolution;
  wxComboBox* comboBox;
  wxTextCtrl* textCtrl;
  wxStaticBitmap* inputImage;
  wxStaticBitmap* outputImage;
  
  void OnExit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);

  wxDECLARE_EVENT_TABLE();
};
