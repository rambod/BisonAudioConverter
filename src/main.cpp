#include <iostream>
#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../include/AppState.h"
#include "../include/MainWindow.h"
#include "../include/LogWindow.h"
#include "../include/AboutWindow.h"
#include "../include/HelpWindow.h"
#include "../include/AppStyle.h"

int main() {
    // Initialize SFML window
    sf::RenderWindow window(sf::VideoMode(1300, 500), "Bison Audio Converter");

    // Set the window icon directly with SFML
    sf::Image icon;
    if (icon.loadFromFile("resources/icon.png")) {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    } else {
        std::cerr << "Failed to load icon image!" << std::endl;
    }

    // Check the result of ImGui-SFML initialization
    if (!ImGui::SFML::Init(window)) {
        std::cerr << "Failed to initialize ImGui-SFML!" << std::endl;
        return -1; // Exit the program if initialization fails
    }

    // App State and Windows
    AppState state;
    MainWindow mainWindow;
    LogWindow anotherWindow;
    SingleFileConverterWindow singleFileConverterWindow;
    AppStyle::setStyle();

    // Initialize the clock for delta time calculation
    sf::Clock deltaClock;

    // Main loop
    while (window.isOpen()) {
        // Calculate the delta time
        sf::Time deltaTime = deltaClock.restart();

        // Ensure deltaTime is always positive (this fixes the assertion failure)
        if (deltaTime.asSeconds() <= 0.0f) {
            deltaTime = sf::seconds(1.f / 60.f);  // Use a default value (e.g., 60 FPS) if deltaTime is non-positive
        }

        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Start a new ImGui frame
        ImGui::SFML::Update(window, deltaTime); // This should be first with deltaTime

        // Render ImGui UI
        if (state.show_demo_window) ImGui::ShowDemoWindow(&state.show_demo_window);

        // Menu bar rendering
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New", "Ctrl+N")) {
                    state.input_directory.clear();
                    state.output_directory.clear();
                    state.log.clear();
                }
                if (ImGui::MenuItem("Exit", "Ctrl+Q")) {
                    window.close();
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View")) {
                if (ImGui::MenuItem("Main Window", nullptr, state.show_main_window)) {
                    state.show_main_window = !state.show_main_window;
                }
                if (ImGui::MenuItem("Log Window", nullptr, state.show_log_window)) {
                    state.show_log_window = !state.show_log_window;
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Help")) {
                if (ImGui::MenuItem("About")) {
                    state.show_about_window = !state.show_about_window;
                }
                if (ImGui::MenuItem("Help")) {
                    state.show_help_window = !state.show_help_window;
                }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        // Render application windows
        if (state.show_main_window) {
            MainWindow::Render(state);
        }
        if (state.show_log_window) {
            anotherWindow.Render(state);
        }
        if (state.show_about_window) {
            AboutWindow::Render(state);
        }
        if (state.show_help_window) {
            HelpWindow::Render(state);
        }
        singleFileConverterWindow.Render(state);

        // Footer rendering
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + viewport->Size.y - 30));
        ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, 30));
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f)); // Dark background
        ImGui::Begin("Footer", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        ImGui::PopStyleColor();
        ImGui::Text("Bison Audio Converter © 2024 - All Rights Reserved Developed by: Rambod Ghashghai");
        ImGui::End();

        // Final rendering
        window.clear(sf::Color(state.clear_color.x * 255, state.clear_color.y * 255, state.clear_color.z * 255, state.clear_color.w * 255));

        // Render ImGui
        ImGui::Render();  // Ensure ImGui is rendered last
        ImGui::SFML::Render(window); // This finalizes the rendering for ImGui
        window.display(); // Swap buffers
    }

    // Cleanup
    ImGui::SFML::Shutdown();
    ImGui::DestroyContext();

    return 0;
}
