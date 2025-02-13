#include <bits/stdc++.h>
using namespace std;

class Perceptron {
public:
    vector<float> w; 
    float b, alpha;

    Perceptron(int num_inputs, float learning_rate) {
        w.resize(num_inputs, 0.1);
        b = 0.1;
        alpha = learning_rate;
    }

    int activation(float x) {
        return x >= 0 ? 1 : 0;
    }

    int predict(const vector<float>& inputs) {
        float sum = b;
        for (size_t i = 0; i < w.size(); i++) {
            sum += w[i] * inputs[i];
        }
        return activation(sum);
    }

    void train(vector<vector<float>> dataset, vector<float> labels, int epochs) {
        for (int epoch = 0; epoch < epochs; epoch++) {
            float total_error = 0;
            for (size_t i = 0; i < dataset.size(); i++) {
                float y_true = labels[i];
                float y_pred = predict(dataset[i]);
                float error = y_true - y_pred;
                total_error += abs(error);

                for (size_t j = 0; j < w.size(); j++) {
                    w[j] += alpha * error * dataset[i][j];
                }
                b += alpha * error;
            }
            if (epoch % 100 == 0) {
                cout << "Epoch " << epoch << " | Error: " << total_error << endl;
            }
        }
    }
};

int main() {
    vector<vector<float>> dataset = {{0,0,0}, {0,0,1}, {0,1,0}, {0,1,1}};
    vector<float> labels = {1, 0, 1, 0};

    Perceptron perceptron(dataset[0].size(), 0.1);
    perceptron.train(dataset, labels, 1000);

    cout << "Predictions after training:\n";
    for (size_t i = 0; i < dataset.size(); i++) {
        cout << "Input: ";
        for (float x : dataset[i]) cout << x << " ";
        cout << "-> Output: " << perceptron.predict(dataset[i]) << endl;
    }

    while (true) {
        cout << "\nEnter test input (space-separated, same size as training data), or type 'exit' to quit:\n";
        string line;
        getline(cin, line);
        if (line == "exit") break;

        istringstream iss(line);
        vector<float> test_input;
        float value;
        while (iss >> value) test_input.push_back(value);

        if (test_input.size() != dataset[0].size()) {
            cout << "Invalid input size. Expected " << dataset[0].size() << " values.\n";
            continue;
        }

        cout << "Predicted output: " << perceptron.predict(test_input) << endl;
    }

    return 0;
}
