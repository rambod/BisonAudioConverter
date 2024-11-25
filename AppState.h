//
// Created by rambo on 11/25/2024.
//

#ifndef BISONAUDIOCONVERTER_APPSTATE_H
#define BISONAUDIOCONVERTER_APPSTATE_H

#include "imgui.h"
#include <string>

struct AppState {
    bool show_demo_window = false;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);

    // New State Variables
    std::string input_directory;
    std::string output_directory;
    bool is_converting = false;
    std::string log;
};

#endif //BISONAUDIOCONVERTER_APPSTATE_H
