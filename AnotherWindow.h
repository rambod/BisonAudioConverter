//
// Created by rambo on 11/25/2024.
//

#ifndef BISONAUDIOCONVERTER_ANOTHERWINDOW_H
#define BISONAUDIOCONVERTER_ANOTHERWINDOW_H

#include "AppState.h"
#include "imgui.h"

class AnotherWindow {
public:
    void Render(AppState& state) {
        if (state.show_another_window) {
            ImGui::Begin("Another Window", &state.show_another_window);
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me")) {
                state.show_another_window = false;
            }
            ImGui::End();
        }
    }
};


#endif //BISONAUDIOCONVERTER_ANOTHERWINDOW_H
