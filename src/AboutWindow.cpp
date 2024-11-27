#include "../include/AboutWindow.h"

void AboutWindow::Render(AppState& state) {
    ImGui::SetNextWindowPos(ImVec2(300, 200), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("About", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Bison Audio Converter");
        ImGui::Text("Developed by: Rambod Ghashghai");
        ImGui::Separator();
        ImGui::Text("Description:");
        ImGui::Text("A powerful tool for audio format conversion.\nSupports batch and single file conversions.");
        ImGui::Separator();
        ImGui::Text("Support Development:");
        ImGui::Text("Donate to support future features:");
        if (ImGui::Selectable("My Wallet Address: abc123xyz456", false)) {
            ImGui::SetClipboardText("abc123xyz456"); // Copies to clipboard
        }
        if (ImGui::Button("Close")) {
            state.show_about_window = false;
        }
    }
    ImGui::End();
}
