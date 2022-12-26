#include "GUI.h"

bool App::OnInit() {
  auto *frame = new Frame("EPS compression", wxPoint(50, 50), wxSize(800, 700));
  frame->Show(true);
  return true;
}

Frame::Frame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size) {

  initMenuBar();

  SetMenuBar(menu_bar);

  initComboBoxScale();

  initInputMinDist();

  initSortingRange();

  initButtonsRow();

  initImages();

  initButtonGetOutput();

  initSizer();

  SetSizer(sizer);
}

wxBEGIN_EVENT_TABLE(Frame, wxFrame) EVT_MENU(wxID_EXIT, Frame::onExit)
    EVT_MENU(wxID_ABOUT, Frame::onAbout) wxEND_EVENT_TABLE()

        void Frame::initMenuBar() {
  menu_file = new wxMenu();
  menu_file->Append(wxID_EXIT);

  menu_help = new wxMenu();
  menu_help->Append(wxID_ABOUT);

  menu_bar = new wxMenuBar();
  menu_bar->Append(menu_file, "&File");
  menu_bar->Append(menu_help, "&Help");
}

void Frame::initComboBoxScale() {
  label_scale_input =
      new wxStaticText(this, wxID_ANY, "Wybierz pomniejszenie obrazka:     ");
  combo_box_scale = new wxComboBox(this, wxID_ANY, "", wxDefaultPosition,
                                   wxSize(150, 30), 0, nullptr, wxCB_READONLY);

  for (int i = 1; i <= 5; i++) {
    combo_box_scale->Append(wxString::Format("%dx", i));
  }

  combo_box_scale->SetSelection(0);

  row_sizer1 = new wxBoxSizer(wxHORIZONTAL);
  row_sizer1->Add(label_scale_input, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
  row_sizer1->Add(combo_box_scale, 1, wxEXPAND);
}

void Frame::initInputMinDist() {
  label_input_min_dist =
      new wxStaticText(this, wxID_ANY, "Min odleglosc pomiedzy punktami:");
  min_dist_ctrl = new wxTextCtrl(this, wxID_ANY, "0.0", wxDefaultPosition,
                                 wxSize(150, 30), wxTE_PROCESS_ENTER);

  row_sizer2 = new wxBoxSizer(wxHORIZONTAL);
  row_sizer2->Add(label_input_min_dist, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT,
                  5);
  row_sizer2->Add(min_dist_ctrl, 1, wxEXPAND);
}

void Frame::initSortingRange() {
  label_sorting_range = new wxStaticText(
      this, wxID_ANY, "Wybierz zakres sortowania:                ");
  combo_box_sorting_range =
      new wxComboBox(this, wxID_ANY, "", wxDefaultPosition, wxSize(150, 30), 0,
                     nullptr, wxCB_READONLY);

  for (int i = 1; i <= 100; i++) {
    combo_box_sorting_range->Append(wxString::Format("%d", i));
  }

  combo_box_sorting_range->SetSelection(49);

  row_sizer3 = new wxBoxSizer(wxHORIZONTAL);
  row_sizer3->Add(label_sorting_range, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
  row_sizer3->Add(combo_box_sorting_range, 1, wxEXPAND);
}

void Frame::initButtonsRow() {
  sizer_buttons = new wxBoxSizer(wxHORIZONTAL);
  button_select_file =
      new wxButton(this, wxID_ANY, "Wybierz plik", wxDefaultPosition);
  button_select_file->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Frame::chooseFile,
                           this);
  button_submit = new wxButton(this, wxID_ANY, "Potwierdz", wxDefaultPosition);
  button_submit->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Frame::submit, this);
  sizer_buttons->Add(button_select_file, 0, wxEXPAND | wxRIGHT | wxUP | wxDOWN,
                     5);
  sizer_buttons->Add(button_submit, 0, wxEXPAND | wxALL, 5);
}

void Frame::initImages() {
  sizer_images = new wxBoxSizer(wxHORIZONTAL);

  sizer_input_image = new wxBoxSizer(wxVERTICAL);
  label_input_image = new wxStaticText(this, wxID_ANY, "Obrazek wejsciowy");
  input_image = new wxStaticBitmap(
      this, wxID_ANY,
      wxBitmap("assets/no_eps_available.png", wxBITMAP_TYPE_PNG));
  label_input_image_size = new wxStaticText(this, wxID_ANY, "Rozmiar przed: ");
  label_input_image_resolution =
      new wxStaticText(this, wxID_ANY, "Rozdzielczosc przed: ");

  sizer_input_image->Add(label_input_image, 0, wxEXPAND | wxALL, 5);
  sizer_input_image->Add(input_image, 0, wxEXPAND | wxALL, 5);
  sizer_input_image->Add(label_input_image_size, 0, wxEXPAND | wxALL, 5);
  sizer_input_image->Add(label_input_image_resolution, 0, wxEXPAND | wxALL, 5);

  sizer_output_image = new wxBoxSizer(wxVERTICAL);
  label_output_image = new wxStaticText(this, wxID_ANY, "Obrazek wyjsciowy");
  output_image = new wxStaticBitmap(
      this, wxID_ANY,
      wxBitmap("assets/no_eps_available.png", wxBITMAP_TYPE_PNG));
  label_output_image_size = new wxStaticText(this, wxID_ANY, "Rozmiar po: ");
  label_output_image_resolution =
      new wxStaticText(this, wxID_ANY, "Rozdzielczosc po: ");

  sizer_output_image->Add(label_output_image, 0, wxEXPAND | wxALL, 5);
  sizer_output_image->Add(output_image, 0, wxEXPAND | wxALL, 5);
  sizer_output_image->Add(label_output_image_size, 0, wxEXPAND | wxALL, 5);
  sizer_output_image->Add(label_output_image_resolution, 0, wxEXPAND | wxALL,
                          5);

  sizer_images->Add(sizer_input_image, 0, wxEXPAND | wxRIGHT | wxUP | wxDOWN,
                    5);
  sizer_images->Add(sizer_output_image, 0, wxEXPAND | wxALL, 5);
}

void Frame::initButtonGetOutput() {
  button_get_output = new wxButton(this, wxID_ANY, "Zapisz", wxDefaultPosition);
  button_get_output->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Frame::save, this);
}

void Frame::initSizer() {
  sizer = new wxBoxSizer(wxVERTICAL);
  sizer->Add(row_sizer1, 0, wxALL, 10);
  sizer->Add(row_sizer2, 0, wxALL, 10);
  sizer->Add(row_sizer3, 0, wxALL, 10);
  sizer->Add(sizer_buttons, 0, wxALL, 10);
  sizer->Add(sizer_images, 0, wxALL, 10);
  sizer->Add(button_get_output, 0, wxALL, 10);
}

void Frame::onExit(wxCommandEvent &event) { Close(true); }

void Frame::onAbout(wxCommandEvent &event) {
  wxMessageBox("It's our EPS file compression app.", "About app",
               wxOK | wxICON_INFORMATION);
}

void Frame::chooseFile(wxCommandEvent &event) {
  std::cout << "Choose file ..." << std::endl;
}

void Frame::submit(wxCommandEvent &event) {
  std::cout << "Submit ..." << std::endl;
}

void Frame::save(wxCommandEvent &event) {
  std::cout << "Save ..." << std::endl;
}