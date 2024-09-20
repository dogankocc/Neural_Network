#include "NeuralNetwork.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

// Constructor
NeuralNetwork::NeuralNetwork(int input_size, int hidden_size, int output_size, double learning_rate)
    : input_size(input_size), hidden_size(hidden_size), output_size(output_size), learning_rate(learning_rate) {
    // Initialize weights and biases
    weights_input_hidden.resize(input_size * hidden_size);
    weights_hidden_output.resize(hidden_size * output_size);
    bias_hidden.resize(hidden_size);
    bias_output.resize(output_size);

    std::srand(std::time(0)); // Seed for random number generation

    // Randomly initialize weights and biases
    for (auto& w : weights_input_hidden) w = (double(std::rand()) / RAND_MAX);
    for (auto& w : weights_hidden_output) w = (double(std::rand()) / RAND_MAX);
    for (auto& b : bias_hidden) b = (double(std::rand()) / RAND_MAX);
    for (auto& b : bias_output) b = (double(std::rand()) / RAND_MAX);
}

// Sigmoid activation function
double NeuralNetwork::sigmoid(double x) {
    return 1 / (1 + std::exp(-x));
}

// Derivative of sigmoid function
double NeuralNetwork::sigmoid_derivative(double x) {
    return x * (1 - x);
}

// Train the neural network
void NeuralNetwork::train(const std::vector<std::vector<double>>& inputs, const std::vector<std::vector<double>>& targets, int epochs) {
    for (int epoch = 0; epoch < epochs; ++epoch) {
        for (size_t i = 0; i < inputs.size(); ++i) {
            // Forward pass
            std::vector<double> hidden_outputs(hidden_size);
            std::vector<double> final_outputs = feedforward(inputs[i]);

            // Calculate output errors
            std::vector<double> output_errors(targets[i].size());
            for (size_t j = 0; j < targets[i].size(); ++j) {
                output_errors[j] = targets[i][j] - final_outputs[j];
            }

            // Calculate hidden errors
            std::vector<double> hidden_errors(hidden_outputs.size());
            for (size_t j = 0; j < hidden_outputs.size(); ++j) {
                double error = 0.0;
                for (size_t k = 0; k < output_errors.size(); ++k) {
                    error += output_errors[k] * weights_hidden_output[j * output_size + k];
                }
                hidden_errors[j] = error * sigmoid_derivative(hidden_outputs[j]);
            }

            // Update weights and biases
            updateWeights(inputs[i], hidden_outputs, output_errors);
        }
    }
}

// Update weights
void NeuralNetwork::updateWeights(const std::vector<double>& inputs, const std::vector<double>& hidden_outputs, const std::vector<double>& output_errors) {
    // Update weights and biases for the output layer
    for (size_t j = 0; j < output_size; ++j) {
        for (size_t k = 0; k < hidden_outputs.size(); ++k) {
            weights_hidden_output[j * hidden_outputs.size() + k] += learning_rate * output_errors[j] * hidden_outputs[k];
        }
        bias_output[j] += learning_rate * output_errors[j];
    }

    // Update weights and biases for the hidden layer
    for (size_t j = 0; j < hidden_size; ++j) {
        double hidden_error = 0.0;
        for (size_t k = 0; k < output_size; ++k) {
            hidden_error += output_errors[k] * weights_hidden_output[k * hidden_size + j];
        }
        for (size_t k = 0; k < input_size; ++k) {
            weights_input_hidden[j * input_size + k] += learning_rate * hidden_error * sigmoid_derivative(hidden_outputs[j]) * inputs[k];
        }
        bias_hidden[j] += learning_rate * hidden_error * sigmoid_derivative(hidden_outputs[j]);
    }
}

// Feedforward function
std::vector<double> NeuralNetwork::feedforward(const std::vector<double>& inputs) {
    std::vector<double> hidden_outputs(hidden_size);
    std::vector<double> final_outputs(output_size);

    // Girdi-gizli katman iþlemi
    for (size_t i = 0; i < hidden_outputs.size(); i++) {
        hidden_outputs[i] = bias_hidden[i];
        for (size_t j = 0; j < inputs.size(); j++) {
            hidden_outputs[i] += inputs[j] * weights_input_hidden[i * input_size + j];
        }
        hidden_outputs[i] = sigmoid(hidden_outputs[i]);
    }

    // Gizli-çýktý katman iþlemi
    for (size_t i = 0; i < final_outputs.size(); i++) {
        final_outputs[i] = bias_output[i];
        for (size_t j = 0; j < hidden_outputs.size(); j++) {
            final_outputs[i] += hidden_outputs[j] * weights_hidden_output[i * hidden_outputs.size() + j];
        }
        final_outputs[i] = sigmoid(final_outputs[i]);
    }

    return final_outputs;
}
