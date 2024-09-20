#include "VoiceAssistant.h"
#include <iostream>
#include <pocketsphinx.h>
#include <sphinxbase/cmd_ln.h>
#include <cstdlib>
VoiceAssistant::VoiceAssistant() {
    initializeSpeechRecognition();
}

VoiceAssistant::~VoiceAssistant() {
    cleanup();
}

void VoiceAssistant::initializeSpeechRecognition() {
    // PocketSphinx ayarlarý burada yapýlandýrýlabilir
    // Örneðin, model yollarý gibi
}

void VoiceAssistant::cleanup() {
    // Kaynaklarý temizle
}

void VoiceAssistant::speak(const std::string& text) {
    std::string command = "espeak \"" + text + "\"";
    system(command.c_str());
}

std::string VoiceAssistant::recognizeSpeech(const std::string& audioFilePath) {
    // Model dosyalarýnýn yollarý
    const char* hmm = "path/to/model/en-us/en-us";
    const char* lm = "path/to/model/en-us/en-us.lm.bin";
    const char* dict = "path/to/model/en-us/cmudict-en-us.dict";

    // Yapýlandýrma
    cmd_ln_t* config = cmd_ln_init(NULL, NULL, TRUE,
        "-hmm", hmm,
        "-lm", lm,
        "-dict", dict,
        NULL);

    if (config == NULL) {
        std::cerr << "Hata: Config yüklenemedi!" << std::endl;
        return "";
    }

    // Decoder oluþturma
    ps_decoder_t* decoder = ps_init(config);
    if (decoder == NULL) {
        std::cerr << "Hata: Decoder oluþturulamadý!" << std::endl;
        cmd_ln_free_r(config);
        return "";
    }

    // Ses dosyasýný tanýma
    FILE* fh = fopen(audioFilePath.c_str(), "rb");
    if (fh == NULL) {
        std::cerr << "Hata: Ses dosyasý açýlamadý!" << std::endl;
        ps_free(decoder);
        cmd_ln_free_r(config);
        return "";
    }

    // Tanýmaya baþla
    ps_start_utt(decoder);
    int16_t buf[512];
    int nread;
    while ((nread = fread(buf, sizeof(int16_t), 512, fh)) > 0) {
        ps_process_raw(decoder, buf, nread, FALSE, FALSE);
    }
    ps_end_utt(decoder);

    // Tanýnan metni al
    const char* hyp = ps_get_hyp(decoder, NULL);
    std::string recognizedText = hyp ? hyp : "";

    // Temizleme
    fclose(fh);
    ps_free(decoder);
    cmd_ln_free_r(config);

    return recognizedText;
}

