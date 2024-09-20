#include "LinearRegression.h"
#include <vector>

// Yap�c� fonksiyon (constructor)
LinearRegression::LinearRegression(double lr, int iter) : w(0), b(0), learning_rate(lr), iterations(iter) {}

// Modeli e�itme fonksiyonu
void LinearRegression::fit(const std::vector<double>& X, const std::vector<double>& y) {
    int n = X.size();

    // Gradient Descent
    for (int i = 0; i < iterations; i++) {
        double dw = 0, db = 0;

        // T�revleri hesapla
        for (int j = 0; j < n; j++) {
            double prediction = w * X[j] + b; // Tahmin edilen y
            dw += (prediction - y[j]) * X[j]; // A��rl�k i�in t�rev
            db += (prediction - y[j]); // Bias i�in t�rev
        }

        dw /= n;
        db /= n;

        // A��rl�klar� ve bias� g�ncelle
        w -= learning_rate * dw;
        b -= learning_rate * db;
    }
}

// Tahmin fonksiyonu
double LinearRegression::predict(double X) const {
    return w * X + b;
}
