#ifndef ZPR_GUI_H
#define ZPR_GUI_H
#include <sstream>
#include <wx/wxprec.h>
#include <memory>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class App : public wxApp {
public:
  bool OnInit() override;
};

using PwxMenu = std::unique_ptr<wxMenu>;
using PwxMenuBar = std::unique_ptr<wxMenuBar>;
using PwxBoxSizer = std::unique_ptr<wxBoxSizer>;
using PwxButton = std::unique_ptr<wxButton>;
using PwxStaticText = std::unique_ptr<wxStaticText>;
using PwxComboBox = std::unique_ptr<wxComboBox>;
using PwxTextCtrl = std::unique_ptr<wxTextCtrl>;
using PwxStaticBitmap = std::unique_ptr<wxStaticBitmap>;


class Frame : public wxFrame {
public:
  Frame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
  PwxMenu menu_file{new wxMenu};
  PwxMenu menu_help{new wxMenu};
  PwxMenuBar menu_bar{new wxMenuBar};
  PwxBoxSizer sizer{new wxBoxSizer(wxHORIZONTAL)};
  PwxBoxSizer sizer_left{new wxBoxSizer(wxVERTICAL)};
  PwxBoxSizer sizer_right{new wxBoxSizer(wxVERTICAL)};
  PwxBoxSizer row_sizer1{new wxBoxSizer(wxHORIZONTAL)};
  PwxBoxSizer row_sizer2{new wxBoxSizer(wxHORIZONTAL)};
  PwxBoxSizer row_sizer3{new wxBoxSizer(wxHORIZONTAL)};
  PwxBoxSizer sizer_buttons{new wxBoxSizer(wxHORIZONTAL)};
  PwxBoxSizer sizer_images{new wxBoxSizer(wxVERTICAL)};
  PwxBoxSizer sizer_input_image{new wxBoxSizer(wxVERTICAL)};
  PwxBoxSizer sizer_output_image{new wxBoxSizer(wxVERTICAL)};
  PwxButton button_submit{new wxButton(this, wxID_ANY, "Potwierdz", wxDefaultPosition)};
  PwxButton button_select_file{new wxButton(this, wxID_ANY, "Wybierz plik", wxDefaultPosition)};
  PwxButton button_get_output{new wxButton(this, wxID_ANY, "Zapisz", wxDefaultPosition)};
  PwxStaticText label_scale_input{new wxStaticText(this, wxID_ANY, "Wybierz pomniejszenie obrazka:     ")};
  PwxStaticText label_input_min_dist{new wxStaticText(this, wxID_ANY, "Min odleglosc pomiedzy punktami:")};
  PwxStaticText label_sorting_range{new wxStaticText(this, wxID_ANY, "Wybierz zakres sortowania:                ")};
  PwxStaticText label_input_image{new wxStaticText(this, wxID_ANY, "Obrazek wejsciowy")};
  PwxStaticText label_output_image{new wxStaticText(this, wxID_ANY, "Obrazek wyjsciowy")};
  PwxStaticText label_input_image_size{new wxStaticText(this, wxID_ANY, "Rozmiar przed: ")};
  PwxStaticText label_output_image_size{new wxStaticText(this, wxID_ANY, "Rozmiar po: ")};
  PwxStaticText label_input_image_resolution{new wxStaticText(this, wxID_ANY, "Rozdzielczosc przed: ")};
  PwxStaticText label_output_image_resolution{new wxStaticText(this, wxID_ANY, "Rozdzielczosc po: ")};
  PwxComboBox combo_box_scale{new wxComboBox(this, wxID_ANY, "", wxDefaultPosition,
                                             wxSize(150, 30), 0, nullptr, wxCB_READONLY)};
  PwxComboBox combo_box_sorting_range{ new wxComboBox(this, wxID_ANY, "", wxDefaultPosition,
                                                      wxSize(150, 30), 0,nullptr, wxCB_READONLY)};
  PwxTextCtrl min_dist_ctrl{new wxTextCtrl(this, wxID_ANY, "0.0", wxDefaultPosition,
                                           wxSize(150, 30), wxTE_PROCESS_ENTER)};
  PwxStaticBitmap input_image{new wxStaticBitmap(this, wxID_ANY,
          wxBitmap("assets/no_eps_available.png", wxBITMAP_TYPE_PNG))};
  PwxStaticBitmap output_image{new wxStaticBitmap(this, wxID_ANY,
          wxBitmap("assets/no_eps_available.png", wxBITMAP_TYPE_PNG))};
  void initMenuBar();
  void initComboBoxScale();
  void initInputMinDist();
  void initSortingRange();
  void initButtonsRow();
  void initImages();
  void initButtonGetOutput();
  void initSizer();
  void onExit(wxCommandEvent &event);
  void onAbout(wxCommandEvent &event);
  void chooseFile(wxCommandEvent &event);
  void submit(wxCommandEvent &event);
  void save(wxCommandEvent &event);
  wxDECLARE_EVENT_TABLE();
};

#endif
