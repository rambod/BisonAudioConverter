#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "../include/AudioConverter.h"
#include <filesystem>
#include <iostream>
#include "lame/lame.h"

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

bool AudioConverter::ConvertAudio(const std::string& inputFile, const std::string& outputFile, const std::string& targetFormat) {
    if (targetFormat == "mp3") {
        return ConvertToMP3(inputFile, outputFile);
    } else if (targetFormat == "wav") {
        return ConvertToWAV(inputFile, outputFile);
    } else {
        std::cerr << "Unsupported target format: " << targetFormat << "\n";
        return false;
    }
}

bool AudioConverter::ConvertToMP3(const std::string& inputFile, const std::string& outputFile) {
    ma_decoder_config decoderConfig = ma_decoder_config_init(ma_format_s16, 2, 44100); // Force s16 format
    ma_decoder decoder;

    if (ma_decoder_init_file(inputFile.c_str(), &decoderConfig, &decoder) != MA_SUCCESS) {
        std::cerr << "Failed to initialize decoder for: " << inputFile << "\n";
        return false;
    }

    FILE* mp3File = fopen(outputFile.c_str(), "wb");
    if (!mp3File) {
        std::cerr << "Failed to open MP3 file for writing: " << outputFile << "\n";
        ma_decoder_uninit(&decoder);
        return false;
    }

    lame_t lame = lame_init();
    lame_set_num_channels(lame, decoder.outputChannels);
    lame_set_in_samplerate(lame, decoder.outputSampleRate);
    lame_set_brate(lame, 192);
    lame_set_quality(lame, 2);
    lame_set_mode(lame, STEREO);
    lame_set_VBR(lame, vbr_default);
    lame_set_VBR_quality(lame, 4);
    lame_init_params(lame);

    int16_t pcmBuffer[8192];
    unsigned char mp3Buffer[8192];
    ma_uint64 framesRead;
    size_t bufferSize = sizeof(pcmBuffer) / sizeof(int16_t) / decoder.outputChannels;

    while (ma_decoder_read_pcm_frames(&decoder, pcmBuffer, bufferSize, &framesRead) == MA_SUCCESS) {
        if (framesRead == 0) {
            std::cerr << "No frames read from the decoder.\n";
            break;
        }

        int mp3Size = lame_encode_buffer_interleaved(lame, pcmBuffer, framesRead, mp3Buffer, sizeof(mp3Buffer));
        if (mp3Size < 0) {
            std::cerr << "LAME encoding error: " << mp3Size << "\n";
            break;
        }

        if (mp3Size > 0) {
            fwrite(mp3Buffer, 1, mp3Size, mp3File);
        }
    }

    int mp3Size = lame_encode_flush(lame, mp3Buffer, sizeof(mp3Buffer));
    if (mp3Size > 0) {
        fwrite(mp3Buffer, 1, mp3Size, mp3File);
    }

    fclose(mp3File);
    lame_close(lame);
    ma_decoder_uninit(&decoder);
    return true;
}


bool AudioConverter::ConvertToWAV(const std::string& inputFile, const std::string& outputFile) {
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

std::string AudioConverter::CreateOutputPath(const std::string& inputRoot, const std::string& inputFile, const std::string& outputRoot, const std::string& targetFormat) {
    fs::path relativePath = fs::relative(inputFile, inputRoot);
    fs::path outputPath = fs::path(outputRoot) / relativePath;
    fs::create_directories(outputPath.parent_path());
    return outputPath.replace_extension("." + targetFormat).string();
}
