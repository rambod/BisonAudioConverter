//
// Created by rambo on 11/25/2024.
//

#ifndef BISONAUDIOCONVERTER_APPSTATE_H
#define BISONAUDIOCONVERTER_APPSTATE_H

#include "imgui.h"
#include <string>
#include <atomic>

struct AppState {
    bool show_demo_window = true;
    bool show_another_window = true;
    ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);

    std::string input_directory;
    std::string output_directory;
    std::atomic<bool> is_converting = false;
    std::string log;
    float progress = 0.0f; // Track progress
};


#endif //BISONAUDIOCONVERTER_APPSTATE_H
