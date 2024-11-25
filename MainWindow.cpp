//
// Created by rambo on 11/25/2024.
//

#include "MainWindow.h"

void MainWindow::Render(AppState &state) {

        ImGui::Begin("Main Window");  // Main window title

        ImGui::Text("Welcome to the Audio Converter!");
        ImGui::Checkbox("Show Demo Window", &state.show_demo_window);
        ImGui::Checkbox("Show Another Window", &state.show_another_window);

        ImGui::End();

}
