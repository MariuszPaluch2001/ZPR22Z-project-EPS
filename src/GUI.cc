#include <filesystem>

#include "GUI.h"
#include "GUIUtils.hpp"
#include "EPSFileTools.h"
#include "utils.hpp"
#include <wx/file.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/textdlg.h>

bool App::OnInit() {
  auto *frame = new Frame("EPS compression", wxPoint(50, 50), wxSize(800, 700));
  frame->Show(true);
  return true;
}

Frame::Frame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size) {

  initMenuBar();

  SetMenuBar(menu_bar.get());

  initComboBoxScale();

  initInputMinDist();

  initSortingRange();

  initButtonsRow();

  initImages();

  initButtonGetOutput();

  initSizer();

  SetSizer(sizer.get());

  setFontForLabels();

  Bind(wxEVT_CLOSE_WINDOW, &Frame::onExit, this);
}

wxBEGIN_EVENT_TABLE(Frame, wxFrame)
    EVT_MENU(wxID_EXIT, Frame::onExitMenu)
    EVT_MENU(wxID_ABOUT, Frame::onAbout)
wxEND_EVENT_TABLE()

void Frame::setFontForLabels() {
    wxFont font;
    font = label_output_image_size->GetFont();
    font.SetWeight(wxFONTWEIGHT_BOLD);
    label_output_image_size->SetFont(font);
    font = label_output_image_resolution->GetFont();
    font.SetWeight(wxFONTWEIGHT_BOLD);
    label_output_image_resolution->SetFont(font);
    font = label_input_image_size->GetFont();
    font.SetWeight(wxFONTWEIGHT_BOLD);
    label_input_image_size->SetFont(font);
    font = label_input_image_resolution->GetFont();
    font.SetWeight(wxFONTWEIGHT_BOLD);
    label_input_image_resolution->SetFont(font);
}

void Frame::initMenuBar() {
  menu_file->Append(wxID_EXIT);
  menu_help->Append(wxID_ABOUT);
  menu_bar->Append(menu_file.get(), "&File");
  menu_bar->Append(menu_help.get(), "&Help");
}

void Frame::initComboBoxScale() {

  for (int i = 1; i <= 5; i++) {
    combo_box_scale->Append(wxString::Format("%d", i));
  }

  combo_box_scale->SetSelection(0);

  row_sizer1->Add(label_scale_input.get(), 0, wxALIGN_CENTER_VERTICAL + wxRIGHT, 5);
  row_sizer1->Add(combo_box_scale.get(), 1, wxEXPAND);
}

void Frame::initInputMinDist() {

  row_sizer2->Add(label_input_min_dist.get(), 0, wxALIGN_CENTER_VERTICAL + wxRIGHT,
                  5);
  row_sizer2->Add(min_dist_ctrl.get(), 1, wxEXPAND);
}

void Frame::initSortingRange() {
  for (int i = 1; i <= 100; i++) {
    combo_box_sorting_range->Append(wxString::Format("%d", i));
  }

  combo_box_sorting_range->SetSelection(49);

  row_sizer3->Add(label_sorting_range.get(), 0, wxALIGN_CENTER_VERTICAL + wxRIGHT, 5);
  row_sizer3->Add(combo_box_sorting_range.get(), 1, wxEXPAND);
}

void Frame::initButtonsRow() {
  button_select_file->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Frame::chooseFile,
                           this);

  button_submit->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Frame::submit, this);
  sizer_buttons->Add(button_select_file.get(), 0, wxEXPAND + wxRIGHT + wxUP + wxDOWN,
                     5);
  sizer_buttons->Add(button_submit.get(), 0, wxEXPAND + wxALL, 5);
}

void Frame::initImages() {
  sizer_input_image->Add(label_input_image.get(), 0, wxEXPAND + wxALL, 5);
  sizer_input_image->Add(input_image.get(), 0, wxEXPAND + wxALL, 5);

  sizer_output_image->Add(label_output_image.get(), 0, wxEXPAND + wxALL, 5);
  sizer_output_image->Add(output_image.get(), 0, wxEXPAND + wxALL, 5);

  sizer_images->Add(sizer_input_image.get(), 0, wxEXPAND + wxRIGHT + wxUP + wxDOWN,
                    5);
  sizer_images->Add(sizer_output_image.get(), 0, wxEXPAND + wxALL, 5);
}

void Frame::initButtonGetOutput() {
  button_get_output->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Frame::save, this);
}

void Frame::initSizer() {
  sizer_left->Add(row_sizer1.get(), 0, wxALL, 10);
  sizer_left->Add(row_sizer2.get(), 0, wxALL, 10);
  sizer_left->Add(row_sizer3.get(), 0, wxALL, 10);
  sizer_left->Add(sizer_buttons.get(), 0, wxALL, 10);
  sizer_right->Add(sizer_images.get(), 0, wxALL, 10);
  sizer_left->Add(button_get_output.get(), 0, wxALL, 10);
  sizer_left->Add(label_input_image_size.get(), 0, wxALL, 10);
  sizer_left->Add(label_input_image_resolution.get(), 0, wxALL, 10);
  sizer_left->Add(label_output_image_size.get(), 0, wxALL, 10);
  sizer_left->Add(label_output_image_resolution.get(), 0, wxALL, 10);
  sizer->Add(sizer_left.get(), 0, wxALL, 10);
  sizer->Add(sizer_right.get(), 0, wxALL, 10);
}

void Frame::onExit(wxCloseEvent &e) {
    std::filesystem::remove(path_to_out_file_eps);
    std::filesystem::remove(path_to_image_buff);
    Destroy();
}

void Frame::onExitMenu(wxCommandEvent &event) {
    std::filesystem::remove(path_to_out_file_eps);
    std::filesystem::remove(path_to_image_buff);
    Destroy();
}

void Frame::onAbout(wxCommandEvent &event) {
  wxMessageBox("It's our EPS file compression app.", "About app",
               wxOK | wxICON_INFORMATION);
}

void Frame::chooseFile(wxCommandEvent &event) {
    wxBitmap newBitmap;
    std::unique_ptr<wxFileDialog> openFileDialog{new wxFileDialog(this, "Otwórz plik", "", "",
                                                                  "Pliki eps (*.eps)|*.eps", wxFD_OPEN | wxFD_FILE_MUST_EXIST)};

    if (openFileDialog->ShowModal() == wxID_CANCEL)
        return;

    path_to_input = openFileDialog->GetPath().ToStdString();
    convertEPSFileToPNG(path_to_input);
    newBitmap.LoadFile(path_to_image_buff, wxBITMAP_TYPE_PNG);
    input_image->SetBitmap(newBitmap);

    newBitmap.LoadFile(path_to_no_available, wxBITMAP_TYPE_PNG);
    output_image->SetBitmap(newBitmap);
    label_output_image_size->SetLabel("Rozmiar po: ");
    label_output_image_resolution->SetLabel("Rozdzielczosc po: ");

    label_input_image_size->SetLabel(updateSizeLabel("Rozmiar przed: ", path_to_input));
    label_input_image_resolution->SetLabel(updateResolutionLabel("Rozdzielczosc przed: ", path_to_input));
}

void Frame::submit(wxCommandEvent &event) {
    if(!path_to_input.empty()){
        mainFunction(path_to_input,
                     path_to_out_file_eps,
                     1 / stod(combo_box_scale->GetValue().ToStdString()),
                     stod(min_dist_ctrl->GetValue().ToStdString()),
                     stoi(combo_box_sorting_range->GetValue().ToStdString()));
    } else { return; }
    wxBitmap newBitmap;
    convertEPSFileToPNG(path_to_out_file_eps);
    newBitmap.LoadFile(path_to_image_buff, wxBITMAP_TYPE_PNG);
    output_image->SetBitmap(newBitmap);

    label_output_image_size->SetLabel(updateSizeLabel("Rozmiar po: ", path_to_out_file_eps));
    label_output_image_resolution->SetLabel(updateResolutionLabel("Rozdzielczosc po: ", path_to_out_file_eps));
}

void Frame::save(wxCommandEvent &event) {
    wxFileName source_file(path_to_out_file_eps);
    if (!source_file.FileExists())
    {
        wxMessageBox("Brak skompresowanego pliku.", "Error", wxOK | wxICON_ERROR);
        return;
    }
    wxFileDialog fileDialog(this, "Wybierz lokalizację docelową", "", "",
                            "Pliki eps (*.eps)|*.eps", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (fileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxFileName target_file(fileDialog.GetPath().ToStdString());

    if (wxCopyFile(source_file.GetFullPath(), target_file.GetFullPath()))
    {
        wxMessageBox("Plik został zapisany.", "Success", wxOK | wxICON_INFORMATION);
    } else
    {
        wxMessageBox("Nie udało się zapisać plików.", "Error", wxOK | wxICON_ERROR);
    }

}

wxString Frame::updateSizeLabel(const std::string& left_part_label, const std::string& path_to_file){
    std::stringstream s;
    s << left_part_label << getFileSize(path_to_file) << "kB";
    return { s.str() };
}

wxString Frame::updateResolutionLabel(const std::string& left_part_label, const std::string& path_to_file){
    std::stringstream s;
    std::ifstream f(path_to_file);
    EPSInFileStream EPSFs(f);
    Header h = EPSFs.getHeader();
    Resolution res = h.getResolution();
    s << left_part_label << res.getX() << 'x' << res.getY();
    f.close();
    return { s.str() };
}