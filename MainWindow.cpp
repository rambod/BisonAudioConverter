#include "MainWindow.h"
#include "AudioConverter.h"
#include <nfd.h>
#include <filesystem>

void MainWindow::Render(AppState &state) {
    ImGui::Begin("Audio Converter");

    // Input Directory Selection
    if (ImGui::Button("Select Input Directory")) {
        nfdchar_t* outPath = nullptr;
        if (NFD_PickFolder(&outPath, nullptr) == NFD_OKAY) {
            state.input_directory = outPath;
            free(outPath);
        }
    }
    ImGui::Text("Input Directory: %s", state.input_directory.c_str());

    // Output Directory Selection
    if (ImGui::Button("Select Output Directory")) {
        nfdchar_t* outPath = nullptr;
        if (NFD_PickFolder(&outPath, nullptr) == NFD_OKAY) {
            state.output_directory = outPath;
            free(outPath);
        }
    }
    ImGui::Text("Output Directory: %s", state.output_directory.c_str());

    // Start Conversion
    if (ImGui::Button("Start Conversion") && !state.is_converting) {
        state.is_converting = true;

        auto audioFiles = AudioConverter::FindAudioFiles(state.input_directory);
        for (const auto& inputFile : audioFiles) {
            std::string outputFile = state.output_directory + "/" + std::filesystem::path(inputFile).filename().string();
            if (AudioConverter::ConvertAudio(inputFile, outputFile)) {
                state.log += "Converted: " + inputFile + "\n";
            } else {
                state.log += "Failed: " + inputFile + "\n";
            }
        }

        state.is_converting = false;
    }

    // Conversion Log
    ImGui::Text("Log:");
    ImGui::BeginChild("Log", ImVec2(0, 200), true);
    ImGui::TextUnformatted(state.log.c_str());
    ImGui::EndChild();

    ImGui::End();
}
