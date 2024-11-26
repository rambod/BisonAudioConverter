#include "../include/SingleFileConverterWindow.h"
#include <nfd.h>
#include <thread>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void SingleFileConverterWindow::Render(AppState& state) {
    ImGui::Begin("Single File Converter");

    static std::string inputFile;
    static std::string outputDirectory;
    static int selectedFormat = 0;
    const char* formats[] = { "wav", "mp3" };

    const nfdu8filteritem_t filterList[] = {
            {"Audio Files", "wav,mp3"}
    };
    nfdfiltersize_t filterCount = 1;

    // Input File Selection
    if (ImGui::Button("Select Input File")) {
        nfdchar_t* outPath = nullptr;
        if (NFD_OpenDialog(&outPath, filterList, filterCount, nullptr) == NFD_OKAY) {
            inputFile = outPath;
            free(outPath);
        }
    }
    ImGui::Text("Input File: %s", inputFile.c_str());

    // Output Directory Selection
    if (ImGui::Button("Select Output Directory")) {
        nfdchar_t* outPath = nullptr;
        if (NFD_PickFolder(&outPath, nullptr) == NFD_OKAY) {
            outputDirectory = outPath;
            free(outPath);
        }
    }
    ImGui::Text("Output Directory: %s", outputDirectory.c_str());

    // Format Selection
    ImGui::Combo("Output Format", &selectedFormat, formats, IM_ARRAYSIZE(formats));

    // Start Conversion Button
    if (ImGui::Button("Convert")) {
        if (!inputFile.empty() && !outputDirectory.empty()) {
            state.is_converting = true;
            state.log += "Starting single file conversion...\n";

            std::string localInputFile = inputFile;
            std::string localOutputDirectory = outputDirectory;
            int localSelectedFormat = selectedFormat;

            std::thread([&state, localInputFile, localOutputDirectory, formats, localSelectedFormat]() {
                // Create output file path
                fs::path inputPath = localInputFile;
                std::string outputFileName = inputPath.stem().string() + "." + formats[localSelectedFormat];
                std::string outputFile = (fs::path(localOutputDirectory) / outputFileName).string();

                // Perform conversion
                if (AudioConverter::ConvertAudio(localInputFile, outputFile, formats[localSelectedFormat])) {
                    state.log += "Successfully converted: " + localInputFile + " -> " + outputFile + "\n";
                } else {
                    state.log += "Failed to convert: " + localInputFile + "\n";
                }
                state.is_converting = false;
            }).detach();
        } else {
            state.log += "Error: Please select both input file and output directory.\n";
        }
    }

    ImGui::End();
}
