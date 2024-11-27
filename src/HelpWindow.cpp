#include "../include/HelpWindow.h"

void HelpWindow::Render(AppState& state) {
    ImGui::SetNextWindowPos(ImVec2(400, 300), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Help", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("How to Use:");
        ImGui::BulletText("1. Select the input and output directories.");
        ImGui::BulletText("2. Choose the desired output format.");
        ImGui::BulletText("3. Click 'Start Conversion' to begin.");
        ImGui::Separator();
        ImGui::Text("For single file conversion:");
        ImGui::BulletText("1. Open 'Single File Converter' from the menu.");
        ImGui::BulletText("2. Follow the instructions in the window.");
        if (ImGui::Button("Close")) {
            state.show_help_window = false;
        }
    }
    ImGui::End();
}
