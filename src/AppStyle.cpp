//
// Created by rambod on 12/1/2024.
//

#include "../include/AppStyle.h"

void AppStyle::setStyle() {
    // Set rounded corners for windows
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 5.0f;
    style.WindowBorderSize = 1.0f;
    style.FrameRounding = 3.0f;
    style.FrameBorderSize = 1.0f;
    style.ScrollbarRounding = 5.0f;

    ImVec4* colors = style.Colors;

// Backgrounds
    colors[ImGuiCol_WindowBg] = ImVec4(0.07f, 0.07f, 0.1f, 1.0f);   // Main Background
    colors[ImGuiCol_ChildBg] = ImVec4(0.12f, 0.12f, 0.2f, 1.0f);   // Dim Background
    colors[ImGuiCol_PopupBg] = ImVec4(0.1f, 0.1f, 0.15f, 1.0f);    // Popup Background

// Headers
    colors[ImGuiCol_Header] = ImVec4(0.0f, 0.45f, 0.75f, 1.0f);    // Header
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.0f, 0.55f, 0.85f, 1.0f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.0f, 0.35f, 0.65f, 1.0f);

// Footer
    colors[ImGuiCol_Border] = ImVec4(0.0f, 0.6f, 0.6f, 1.0f);      // Footer

// Buttons
    colors[ImGuiCol_Button] = ImVec4(0.8f, 0.4f, 0.0f, 1.0f);      // Button Normal
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.9f, 0.55f, 0.1f, 1.0f); // Button Hover
    colors[ImGuiCol_ButtonActive] = ImVec4(0.7f, 0.35f, 0.0f, 1.0f);  // Button Active

// Text
    colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);        // Text
    colors[ImGuiCol_TextDisabled] = ImVec4(0.7f, 0.7f, 0.7f, 1.0f); // Dimmed Text

// Highlights
    colors[ImGuiCol_SliderGrab] = ImVec4(0.6f, 0.3f, 0.8f, 1.0f);  // Highlight
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.5f, 0.2f, 0.7f, 1.0f);

// Frame and Borders
    colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.15f, 0.2f, 1.0f);   // Frame Background
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.2f, 0.2f, 0.25f, 1.0f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.25f, 0.25f, 0.3f, 1.0f);
    colors[ImGuiCol_Border] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);      // Borders

    // Title Colors
    colors[ImGuiCol_TitleBg] = ImVec4(0.0f, 0.45f, 0.75f, 1.0f);         // Active Title
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.0f, 0.55f, 0.85f, 1.0f);   // Title Background Active
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.3f, 0.35f, 0.4f, 1.0f); // Dimmed Title

    //set button size
    style.FramePadding = ImVec2(10.0f, 10.0f);
    style.ItemSpacing = ImVec2(10.0f, 10.0f);
    style.ItemInnerSpacing = ImVec2(10.0f, 10.0f);

    //set window size
    style.WindowPadding = ImVec2(10.0f, 10.0f);
    style.WindowMinSize = ImVec2(300.0f, 300.0f);
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

    //set slider size
    style.GrabMinSize = 20.0f;

    return;
}
