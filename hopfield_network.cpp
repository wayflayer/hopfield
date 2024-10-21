#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace::std;

class Neuron {
private:
    int state;
public:
    Neuron(int value) {
        if (abs(value) == 1)
            state = value;
        else throw "Invalid neuron value. Can be '1' or '-1'.";
    }

    int get_state() { return state; }

    void set_state(int value) {
        if (abs(value) == 1)
            state = value;
        else throw "Invalid neuron value. Can be '1' or '-1'.";
    }
};

class Neural_Network {
private:
    vector<vector<float>> J;
    int N;
    int width;
    int height;
public:
    Neural_Network(pair<vector<vector<float>>, int> p) {
        J = p.first;
        width = p.second;
        N = J.size();
        height = N / width;
    }
    bool step(vector<Neuron>& working_line) {
        vector<Neuron> previous_line = working_line;

        for (int i = 0; i < N; i++) {
            float v = 0;
            for (int j = 0; j < N; j++) {
                v += J[i][j] * working_line[j].get_state();
            }
            working_line[i].set_state(v > 0 ? 1 : -1);
        }

        bool changed = false;
        for (int i = 0; i < N; i++) {
            if (previous_line[i].get_state() != working_line[i].get_state())
                changed = true;
            break;
        }

        return changed;
    }


    void start(string path) {
        ifstream fin; fin.open(path);

        vector<Neuron> working_line;

        string line;
        while (getline(fin, line) && line != "") {
            if (line.size() != width) throw "Non-matching image dimensions.";

            for (int i = 0; i < width; i++) {
                working_line.push_back(line[i] == '*' ? Neuron(1) : Neuron(-1));
            }
        }
        if (working_line.size() != N) throw "Non-matching image dimensions.";

        //Итерации шагов
        bool unstable = true;
        int iterations = 0;
        while (unstable && iterations < 999) {
            unstable = step(working_line);
            iterations += 1;
        }

        ofstream fout(path, ios::app);

        fout << "\n\nDiscerned image:\n";
        for (int i = 0; i < working_line.size(); i++) {
            working_line[i].get_state() == 1 ? fout << "*" : fout << "-";
            if ((i + 1) % width == 0) fout << "\n";
        }

        fout.close();
    }
};

pair<vector<vector<float>>, int> network_learn(string path) {
    ifstream fin; fin.open(path);

    string line; getline(fin, line);

    int width; int height;

    string a;
    for (int i = 0; i < line.size(); i++) {
        a += line[i];
        if (line[i] == ' ') { width = stoi(a); a = ""; }
    }
    height = stoi(a);

    int N = width * height;

    vector<vector<int>> images;

    images.push_back(vector<int> {});
    int img_index = 0;
    while (getline(fin, line)) {
        if (line == "") {
            img_index += 1;
            images.push_back(vector<int> {});
            }
        else {
            for (int i = 0; i < width; i++) {
                images[img_index].push_back(line[i] == '*' ? 1 : -1);
            }
        }
    }

    fin.close();

    vector<vector<float>> J;
    for (int i = 0; i < N; i++) {
        J.push_back(vector<float>(N, 0.0));
    }

    for (int k = 0; k < images.size(); k++) {
        float v;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < i; j++) {
                v = images[k][i] * images[k][j];
                J[i][j] += v;
                J[j][i] += v;
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            J[i][j] /= N;
            J[j][i] /= N;
        }
    }

    return pair<vector<vector<float>>, int>(J, width);
}

int main() {
    Neural_Network network(network_learn("images.txt"));

    network.start("discern_image.txt");
}
