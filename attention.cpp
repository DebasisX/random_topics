#include <bits/stdc++.h>
using namespace std;

// softmax
vector<float> softmax(vector<float> scores) {
    float sum = 0.0;
    for (float score : scores) {
        sum += exp(score);
    }
    for (float &score : scores) {
        score = exp(score) / sum;
    }
    return scores;
}

// compute attention
vector<float> attention(vector<vector<float>> Q, vector<vector<float>> K, vector<vector<float>> V) {
    int n = Q.size();  // (tokens)
    int d = Q[0].size();  // feature dimension

    vector<vector<float>> scores(n, vector<float>(n, 0.0));

    // Q·(K transpose) (dot product)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < d; k++) {
                scores[i][j] += Q[i][k] * K[j][k];  
            }
            scores[i][j] /= sqrt(d);  // scale 
        }
    }

    // Apply softmax to each row
    for (int i = 0; i < n; i++) {
        scores[i] = softmax(scores[i]);
    }

    // output: Attention Weights * V
    vector<float> output(n, 0.0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < d; k++) {
                output[i] += scores[i][j] * V[j][k];  
            }
        }
    }

    return output;
}

int main() {
// 	3 words (tokens), 2-dimensional embeddings
    vector<vector<float>> Q = {{1.0, 0.5}, {0.8, 0.3}, {0.2, 0.1}};  
    vector<vector<float>> K = {{1.0, 0.5}, {0.8, 0.3}, {0.2, 0.1}};  
    vector<vector<float>> V = {{1.0, 2.0}, {0.5, 1.5}, {0.3, 1.2}};  

    vector<float> result = attention(Q, K, V);

    cout << "Attention Output: ";
    for (float val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
