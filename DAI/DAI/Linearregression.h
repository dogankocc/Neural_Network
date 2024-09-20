#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H

#include <vector>

class LinearRegression {
public:
    // Yap�c� fonksiyon (constructor)
    LinearRegression(double lr, int iter);

    // Modeli e�itme fonksiyonu
    void fit(const std::vector<double>& X, const std::vector<double>& y);

    // Tahmin fonksiyonu
    double predict(double X) const;

private:
    double w; // A��rl�k (weight)
    double b; // Bias (sabit terim)
    double learning_rate; // ��renme oran�
    int iterations; // �terasyon say�s�
};

#endif // LINEARREGRESSION_H
