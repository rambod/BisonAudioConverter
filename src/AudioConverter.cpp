#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "../include/AudioConverter.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

std::vector<std::string> AudioConverter::FindAudioFiles(const std::string& directory) {
    const std::vector<std::string> SUPPORTED_EXTENSIONS = {".wav"};
    std::vector<std::string> audioFiles;

    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (entry.is_regular_file() &&
            std::find(SUPPORTED_EXTENSIONS.begin(), SUPPORTED_EXTENSIONS.end(), entry.path().extension().string()) != SUPPORTED_EXTENSIONS.end()) {
            audioFiles.push_back(entry.path().string());
        }
    }
    return audioFiles;
}

bool AudioConverter::ConvertAudio(const std::string& inputFile, const std::string& outputFile) {
    ma_decoder decoder;
    ma_encoder encoder;

    if (ma_decoder_init_file(inputFile.c_str(), nullptr, &decoder) != MA_SUCCESS) {
        std::cerr << "Failed to initialize decoder for: " << inputFile << "\n";
        return false;
    }

    ma_encoder_config config = ma_encoder_config_init(ma_encoding_format_wav, ma_format_f32, decoder.outputChannels, decoder.outputSampleRate);

    if (ma_encoder_init_file(outputFile.c_str(), &config, &encoder) != MA_SUCCESS) {
        ma_decoder_uninit(&decoder);
        std::cerr << "Failed to initialize encoder for: " << outputFile << "\n";
        return false;
    }

    ma_uint8 buffer[4096];
    ma_uint64 framesRead;
    while (ma_decoder_read_pcm_frames(&decoder, buffer, sizeof(buffer) / ma_get_bytes_per_frame(decoder.outputFormat, decoder.outputChannels), &framesRead) == MA_SUCCESS) {
        ma_encoder_write_pcm_frames(&encoder, buffer, framesRead, nullptr);
    }

    ma_encoder_uninit(&encoder);
    ma_decoder_uninit(&decoder);
    return true;
}

std::string AudioConverter::CreateOutputPath(const std::string& inputRoot, const std::string& inputFile, const std::string& outputRoot) {
    fs::path relativePath = fs::relative(inputFile, inputRoot);
    fs::path outputPath = fs::path(outputRoot) / relativePath;
    fs::create_directories(outputPath.parent_path()); // Ensure directory structure exists
    return outputPath.replace_extension(".wav").string(); // Force WAV extension
}
