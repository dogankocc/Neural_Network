#include <iostream>
#include "LinearRegression.h"
#include "NeuralNetwork.h"
#include "VoiceAssistant.h"

int main() {
    // Eðitim verileri (X ve y)
    std::vector<double> X = { 1, 2, 3, 4, 5 }; // Girdiler
    std::vector<double> y = { 5, 7, 9, 11, 13 }; // Çýktýlar

    // Doðrusal regresyon modeli oluþtur ve eðit
    LinearRegression model(0.1, 1000);
    model.fit(X, y);

    // Yeni bir veri için tahmin yap
    double input = 6; // Yeni girdi deðeri
    double prediction = model.predict(input); // Tahmin edilen çýktý
    std::cout << "Input: " << input << ", Prediction: " << prediction << std::endl;

    // Yeni bir veri için tahmin yap
    double input2 = 7; // Yeni girdi deðeri
    double prediction2 = model.predict(input2); // Tahmin edilen çýktý
    std::cout << "Input2: " << input2 << ", Prediction2: " << prediction2 << std::endl;


    NeuralNetwork nn(3, 5, 1, 0.1); // 3 giriþ, 5 gizli nöron, 1 çýkýþ, öðrenme oraný 0.1

    // Eðitim verileri (örnek)
    std::vector<std::vector<double>> inputs = {
        {0.0, 0.0, 0.0},
        {0.0, 0.0, 1.0},
        {0.0, 1.0, 0.0},
        {0.0, 1.0, 1.0},
        {1.0, 0.0, 0.0},
        {1.0, 0.0, 1.0},
        {1.0, 1.0, 0.0},
        {1.0, 1.0, 1.0}
    };

    // Hedef veriler (örnek)
    std::vector<std::vector<double>> targets = {
        {0.0},
        {1.0},
        {1.0},
        {0.0},
        {1.0},
        {0.0},
        {0.0},
        {1.0}
    };

    nn.train(inputs, targets, 10000); // 10,000 epoch boyunca eðitim

    // Tahmin yapma
    std::vector<double> result = nn.feedforward({ 0.0, 0.0, 1.0 });
    std::cout << "Tahmin: " << result[0] << std::endl;


    //std::string audioFilePath = "path/to/audio/file.wav";
    //std::string recognizedText = VoiceAssistant::recognizeSpeech(audioFilePath);

    //std::cout << "Tanýnan Metin: " << recognizedText << std::endl;

    return 0;
}
