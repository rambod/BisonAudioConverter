//
// Created by rambo on 11/25/2024.
//

#ifndef BISONAUDIOCONVERTER_AUDIOCONVERTER_H
#define BISONAUDIOCONVERTER_AUDIOCONVERTER_H


#include <string>
#include <vector>

class AudioConverter {
public:
    // Recursively find all WAV files in a directory
    static std::vector<std::string> FindAudioFiles(const std::string& directory);

    // Convert audio files from one format to another
    static bool ConvertAudio(const std::string& inputFile, const std::string& outputFile);
};



#endif //BISONAUDIOCONVERTER_AUDIOCONVERTER_H
