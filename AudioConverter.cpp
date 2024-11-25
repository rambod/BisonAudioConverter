//
// Created by rambo on 11/25/2024.
//
#include "AudioConverter.h"
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

std::vector<std::string> AudioConverter::FindAudioFiles(const std::string& directory) {
    std::vector<std::string> audioFiles;
    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".wav") {
            audioFiles.push_back(entry.path().string());
        }
    }
    return audioFiles;
}

bool AudioConverter::ConvertAudio(const std::string& inputFile, const std::string& outputFile) {
    ma_decoder decoder;
    ma_encoder encoder;

    // Initialize the decoder
    if (ma_decoder_init_file(inputFile.c_str(), nullptr, &decoder) != MA_SUCCESS) {
        return false;
    }

    // Initialize the encoder
    ma_encoder_config config = ma_encoder_config_init(
            ma_encoding_format_wav,
            ma_format_f32,
            decoder.outputChannels,
            decoder.outputSampleRate
    );

    if (ma_encoder_init_file(outputFile.c_str(), &config, &encoder) != MA_SUCCESS) {
        ma_decoder_uninit(&decoder);
        return false;
    }

    // Conversion loop
    ma_uint8 buffer[4096];
    ma_uint64 framesRead;

    while (ma_decoder_read_pcm_frames(&decoder, buffer, sizeof(buffer) / ma_get_bytes_per_frame(decoder.outputFormat, decoder.outputChannels), &framesRead) == MA_SUCCESS) {
        ma_encoder_write_pcm_frames(&encoder, buffer, framesRead, nullptr);
    }

    // Clean up
    ma_encoder_uninit(&encoder);
    ma_decoder_uninit(&decoder);

    return true;
}
