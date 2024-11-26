#ifndef BISONAUDIOCONVERTER_AUDIOCONVERTER_H
#define BISONAUDIOCONVERTER_AUDIOCONVERTER_H

#include <string>
#include <vector>

class AudioConverter {
public:
    static std::vector<std::string> FindAudioFiles(const std::string& directory);
    static bool ConvertAudio(const std::string& inputFile, const std::string& outputFile);

    // Create the output path with the same directory structure
    static std::string CreateOutputPath(const std::string& inputRoot, const std::string& inputFile, const std::string& outputRoot);
};

#endif //BISONAUDIOCONVERTER_AUDIOCONVERTER_H
