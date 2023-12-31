#include <vector>
#include <Eigen/Dense>
#include <iostream>
#ifndef  MLP_H
#define MLP_H
static float sigmoid(float x)
{
    return 1 / (1 + expf(-x));
}
static Eigen::MatrixXf sigmoid(Eigen::MatrixXf&& x)
{
    for (int i = 0; i < x.rows(); i++)
    {
        for (int j = 0; j < x.cols(); j++)
        {
            x(i, j) = sigmoid(x(i, j));
        }
    }
    return x;
}

struct MLP
{
    MLP(){}
    MLP(std::initializer_list<int> layers_) : layers(layers_)
    {
        int numberOfLayers = layers.size();
        biases.reserve(numberOfLayers - 1);
        weights.reserve(numberOfLayers - 1);
        for (int i = 1; i < numberOfLayers; i++)
        {
            Eigen::MatrixXf weight = Eigen::MatrixXf::Random(layers[i], layers[i - 1]);
            Eigen::MatrixXf bias = Eigen::MatrixXf::Random(layers[i], 1);
            biases.push_back(std::move(bias));
            weights.push_back(std::move(weight));
        }
    }
    Eigen::MatrixXf feedforward(const Eigen::MatrixXf& input)
    {
        Eigen::MatrixXf a(input);
        for (int i = 0; i < biases.size(); i++)
        {
            a = sigmoid((weights[i] * a) + biases[i]);
        }
        return a;
    }

    std::vector<int> layers;
    std::vector<Eigen::MatrixXf> weights;
    std::vector<Eigen::MatrixXf> biases;
};
#endif
