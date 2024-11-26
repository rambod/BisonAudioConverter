#include "../include/MainWindow.h"
#include "../include/AudioConverter.h"
#include <nfd.h>
#include <thread>

void MainWindow::Render(AppState &state) {
    ImGui::Begin("Audio Converter");

    // Input Directory
    if (!state.is_converting) {
        if (ImGui::Button("Select Input Directory")) {
            nfdchar_t* outPath = nullptr;
            if (NFD_PickFolder(&outPath, nullptr) == NFD_OKAY) {
                state.input_directory = outPath;
                free(outPath);
            }
        }
    }
    ImGui::Text("Input Directory: %s", state.input_directory.c_str());

    // Output Directory
    if (!state.is_converting) {
        if (ImGui::Button("Select Output Directory")) {
            nfdchar_t* outPath = nullptr;
            if (NFD_PickFolder(&outPath, nullptr) == NFD_OKAY) {
                state.output_directory = outPath;
                free(outPath);
            }
        }
    }
    ImGui::Text("Output Directory: %s", state.output_directory.c_str());

    // Output Format
    if (!state.is_converting) {
        const char* formats[] = { "wav", "mp3", "ogg" };
        static int current_format = 0;
        if (ImGui::Combo("Output Format", &current_format, formats, IM_ARRAYSIZE(formats))) {
            state.output_format = formats[current_format];
        }
    }

    // Conversion Progress
    if (state.is_converting) {
        ImGui::Text("Conversion in progress...");
        ImGui::ProgressBar(state.progress, ImVec2(-1.0f, 0.0f));
    } else {
        if (ImGui::Button("Start Conversion")) {
            state.is_converting = true;
            state.log += "Conversion started...\n";

            std::thread([&state]() {
                auto audioFiles = AudioConverter::FindAudioFiles(state.input_directory);
                float totalFiles = static_cast<float>(audioFiles.size());
                float processedFiles = 0.0f;

                for (const auto& inputFile : audioFiles) {
                    std::string outputFile = AudioConverter::CreateOutputPath(state.input_directory, inputFile, state.output_directory);
                    if (AudioConverter::ConvertAudio(inputFile, outputFile)) {
                        state.log += "Converted: " + inputFile + "\n";
                    } else {
                        state.log += "Skipped (unsupported): " + inputFile + "\n";
                    }
                    processedFiles += 1.0f;
                    state.progress = processedFiles / totalFiles;
                }

                state.log += "Conversion completed.\n";
                state.is_converting = false;
            }).detach();
        }
    }

    ImGui::End();
}

