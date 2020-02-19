#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>

using namespace std;

class Perceptron
{
public :
    class Dendrit
    {
    public:
        Perceptron *input_perceptron;
        double weight;
    };

    double value;
    vector<Dendrit*> dendrites;

    Dendrit *createDendrit(const Perceptron * const &input_perceptron)
    {
        Dendrit *d = new Dendrit;
        d->input_perceptron = const_cast<Perceptron*>(input_perceptron);
        d->weight = 0;
        dendrites.push_back(d);
        return d;
    }

    double activate(bool recursive = false)
    {
        if (dendrites.size() == 0)
        {
            return value;
        }

        double sum = 0;
        for (Dendrit *d : dendrites)
        {
            if (recursive)
            {
                sum += d->input_perceptron->activate(true) * d->weight;
            } else
            {
                sum += d->input_perceptron->value * d->weight;
            }
        }
        value = relu(sum);
        return value;
    }


    double sigmoid(double x)
    {
        return 1 / (1 + pow(M_E, -x));
    }
    double linear(double x)
    {
        if (x > 1) return 1;
        else return x;
    }
    double relu(double x)
    {
        if (x < 0) return 0;
        else return x;
    }
};

int main()
{
    srand(time(nullptr));
    int neuralNetworkConfig[] {3, 5, 5, 3};

    vector <vector <Perceptron*>> neuralNetwork;

    for (int i = 0; i < sizeof(neuralNetworkConfig)/4; i++)
    {
        neuralNetwork.push_back(vector<Perceptron*>());
        for (int j = 0; j < neuralNetworkConfig[i]; j++)
        {
            Perceptron *p = new Perceptron;
            neuralNetwork[i].push_back(p);
            if (i > 0)
            {
                for (int k = 0; k < neuralNetworkConfig[i-1]; k++)
                {
                    Perceptron::Dendrit *d = p->createDendrit(neuralNetwork[i-1][k]);
                    d->weight = (rand() % 100) / 100.;
                }
            }
        }
    }

    neuralNetwork[0][0]->value = 0.4;
    neuralNetwork[0][1]->value = 0.7;
    neuralNetwork[0][2]->value = 0.1;

    cout<<neuralNetwork[3][0]->activate(true)<<endl;
    cout<<neuralNetwork[3][1]->activate(true)<<endl;
    cout<<neuralNetwork[3][2]->activate(true)<<endl;

    return 0;
}
