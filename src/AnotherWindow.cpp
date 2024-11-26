//
// Created by rambo on 11/25/2024.
//

#include "../include/AnotherWindow.h"

void AnotherWindow::Render(AppState &state) {
    if (state.show_another_window) {
        ImGui::Begin("Another Window", &state.show_another_window);
        ImGui::Text("Hello from another window!");
        // Log Window
        static bool autoScroll = true;
        ImGui::BeginChild("Log", ImVec2(0, 200), true);
        ImGui::TextUnformatted(state.log.c_str());
        if (autoScroll) ImGui::SetScrollHereY(1.0f);
        ImGui::EndChild();

        if (ImGui::Button("Close Me")) {
            state.show_another_window = false;
        }
        ImGui::End();

    }
}
