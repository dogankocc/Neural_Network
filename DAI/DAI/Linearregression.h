#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H

#include <vector>

class LinearRegression {
public:
    // Yapýcý fonksiyon (constructor)
    LinearRegression(double lr, int iter);

    // Modeli eðitme fonksiyonu
    void fit(const std::vector<double>& X, const std::vector<double>& y);

    // Tahmin fonksiyonu
    double predict(double X) const;

private:
    double w; // Aðýrlýk (weight)
    double b; // Bias (sabit terim)
    double learning_rate; // Öðrenme oraný
    int iterations; // Ýterasyon sayýsý
};

#endif // LINEARREGRESSION_H
