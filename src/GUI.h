#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class App : public wxApp {
public:
  bool OnInit() override;
};

class Frame : public wxFrame {
public:
  Frame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
  wxMenu *menu_file;
  wxMenu *menu_help;
  wxMenuBar *menu_bar;
  wxBoxSizer *sizer;
  wxBoxSizer *row_sizer1;
  wxBoxSizer *row_sizer2;
  wxBoxSizer *row_sizer3;
  wxBoxSizer *sizer_buttons;
  wxBoxSizer *sizer_images;
  wxBoxSizer *sizer_input_image;
  wxBoxSizer *sizer_output_image;
  wxButton *button_submit;
  wxButton *button_select_file;
  wxButton *button_get_output;
  wxStaticText *label_scale_input;
  wxStaticText *label_input_min_dist;
  wxStaticText *label_sorting_range;
  wxStaticText *label_input_image;
  wxStaticText *label_output_image;
  wxStaticText *label_input_image_size;
  wxStaticText *label_output_image_size;
  wxStaticText *label_input_image_resolution;
  wxStaticText *label_output_image_resolution;
  wxComboBox *combo_box_scale;
  wxComboBox *combo_box_sorting_range;
  wxTextCtrl *min_dist_ctrl;
  wxStaticBitmap *input_image;
  wxStaticBitmap *output_image;

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
