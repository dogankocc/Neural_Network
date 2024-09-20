#ifndef VOICEASSISTANT_H
#define VOICEASSISTANT_H

#include <string>

class VoiceAssistant {
public:
    VoiceAssistant();
    ~VoiceAssistant();

    void speak(const std::string& text);

    std::string recognizeSpeech(const std::string& audioFilePath);

private:
    void initializeSpeechRecognition();
    void cleanup();
};

#endif // VOICEASSISTANT_H
