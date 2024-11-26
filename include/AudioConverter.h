#ifndef BISONAUDIOCONVERTER_AUDIOCONVERTER_H
#define BISONAUDIOCONVERTER_AUDIOCONVERTER_H

#include <string>
#include <vector>

class AudioConverter {
public:
    static std::vector<std::string> FindAudioFiles(const std::string& directory);
    static bool ConvertAudio(const std::string& inputFile, const std::string& outputFile, const std::string& targetFormat);
    static std::string CreateOutputPath(const std::string& inputRoot, const std::string& inputFile, const std::string& outputRoot, const std::string& targetFormat);

private:
    static bool ConvertToMP3(const std::string& inputFile, const std::string& outputFile);
    static bool ConvertToWAV(const std::string& inputFile, const std::string& outputFile);
};

#endif //BISONAUDIOCONVERTER_AUDIOCONVERTER_H
