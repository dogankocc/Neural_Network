#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <vector>

class NeuralNetwork {
public:
    NeuralNetwork(int input_size, int hidden_size, int output_size, double learning_rate);
    void train(const std::vector<std::vector<double>>& inputs, const std::vector<std::vector<double>>& targets, int epochs);
    std::vector<double> feedforward(const std::vector<double>& inputs);

private:
    int input_size;
    int hidden_size;
    int output_size;
    double learning_rate;

    std::vector<double> weights_input_hidden; // Girdi-gizli katman aðýrlýklarý
    std::vector<double> weights_hidden_output; // Gizli-çýktý katman aðýrlýklarý
    std::vector<double> bias_hidden; // Gizli katman bias'larý
    std::vector<double> bias_output; // Çýktý katmaný bias'larý

    double sigmoid(double x);
    double sigmoid_derivative(double x);
    void updateWeights(const std::vector<double>& inputs, const std::vector<double>& hidden_outputs, const std::vector<double>& output_errors);
};

#endif // NEURALNETWORK_H
