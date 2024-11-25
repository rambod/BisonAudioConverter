#include "MainWindow.h"
#include "AudioConverter.h"
#include <nfd.h>
#include <filesystem>
#include <thread>  // For std::thread
#include <atomic>  // For std::atomic

void MainWindow::Render(AppState &state) {
    ImGui::Begin("Audio Converter");

    // Input Directory Selection
    if (!state.is_converting) {  // Only allow input selection when not converting
        if (ImGui::Button("Select Input Directory")) {
            nfdchar_t* outPath = nullptr;
            if (NFD_PickFolder(&outPath, nullptr) == NFD_OKAY) {
                state.input_directory = outPath;
                free(outPath);
            }
        }
    }
    ImGui::Text("Input Directory: %s", state.input_directory.c_str());

    // Output Directory Selection
    if (!state.is_converting) {  // Only allow output selection when not converting
        if (ImGui::Button("Select Output Directory")) {
            nfdchar_t* outPath = nullptr;
            if (NFD_PickFolder(&outPath, nullptr) == NFD_OKAY) {
                state.output_directory = outPath;
                free(outPath);
            }
        }
    }
    ImGui::Text("Output Directory: %s", state.output_directory.c_str());

    // Start Conversion Button
    if (state.is_converting) {
        ImGui::Text("Conversion in progress...");
    } else {
        if (ImGui::Button("Start Conversion")) {
            state.is_converting = true;
            state.log += "Conversion started...\n";

            // Start a thread to handle conversion
            std::thread([&state]() {
                auto audioFiles = AudioConverter::FindAudioFiles(state.input_directory);
                for (const auto& inputFile : audioFiles) {
                    std::string outputFile = state.output_directory + "/" + std::filesystem::path(inputFile).filename().string();
                    if (AudioConverter::ConvertAudio(inputFile, outputFile)) {
                        state.log += "Converted: " + inputFile + "\n";
                    } else {
                        state.log += "Failed: " + inputFile + "\n";
                    }
                }
                state.log += "Conversion completed.\n";
                state.is_converting = false;  // Mark conversion as complete
            }).detach();  // Detach the thread so it runs independently
        }
    }

    // Conversion Log
    ImGui::Text("Log:");
    ImGui::BeginChild("Log", ImVec2(0, 200), true);
    ImGui::TextUnformatted(state.log.c_str());
    ImGui::EndChild();

    ImGui::End();
}


