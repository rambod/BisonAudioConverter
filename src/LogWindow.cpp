//
// Created by rambo on 11/25/2024.
//

#include "../include/LogWindow.h"

void LogWindow::Render(AppState &state) {
    if (state.show_another_window) {
        ImGui::Begin("Log Window", &state.show_another_window);
        ImGui::Text("Conversion Log!");
        // Log Window
        static bool autoScroll = true;
        ImGui::BeginChild("Log", ImVec2(0, 200), true);
        ImGui::TextUnformatted(state.log.c_str());
        if (autoScroll) ImGui::SetScrollHereY(1.0f);
        ImGui::EndChild();

        if (ImGui::Button("Close")) {
            state.show_another_window = false;
        }
        ImGui::End();

    }
}
