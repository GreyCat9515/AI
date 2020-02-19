#include <iostream>
#include <vector>
#include <cmath>
#include <iterator>

using namespace std;

class Perceptron
{
public :
    class Akson
    {
    private:
        Perceptron *p;
    public:
        Akson(){}
        Akson(const Perceptron * const &p)
        {
            this->p = const_cast<Perceptron*>(p);
        }
        double value = -1;
        double Value()
        {
            if (value == -1 && p != nullptr)
            {
                value = p->activate();
            } else return value;
        }
    };
    class Dendrit
    {
    public:
        Akson *inputAkson;
        double weight;
    };

    Akson akson = Akson(this);
    vector<Dendrit*> dendrites;

    Dendrit *createDendrit(const Perceptron * const &inputPerceptron)
    {
        Dendrit *d = new Dendrit;
        d->inputAkson = const_cast<Akson*>(&inputPerceptron->akson);
        d->weight = 0;
        dendrites.push_back(d);
        return d;
    }
    Dendrit *createDendrit(const Akson * const &inputAkson)
    {
        Dendrit *d = new Dendrit;
        d->inputAkson = const_cast<Akson*>(inputAkson);
        d->weight = 0;
        dendrites.push_back(d);
        return d;
    }

    double activate()
    {
        double sum = 0;
        for (Dendrit *d : dendrites)
        {
            sum += d->inputAkson->Value() * d->weight;
        }
        akson.value = sigmoid(sum);
        return akson.value;
    }

    double sigmoid(double x)
    {
        return 1 / (1 + pow(M_E, -x));
    }
};

int main()
{
    srand(time(nullptr));
    int neuralNetworkConfig[] {10, 5, 3, 5};

    vector <vector <Perceptron*>> neuralNetwork;
    vector <Perceptron::Akson*> input;

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
            } else
            {
                Perceptron::Akson *a = new Perceptron::Akson;
                input.push_back(a);
                Perceptron::Dendrit *d = p->createDendrit(a);
                d->weight = 1;
            }
        }
    }
    input[0]->value = 3;

    double res = neuralNetwork[3][0]->activate();
    return 0;
}
