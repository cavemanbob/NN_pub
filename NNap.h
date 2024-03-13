#include "matvec.h"


template <typename T>
class NeuralNetwork{
public:
	matrix<T> **Weights;
	std::vector<T> Biases;
	std::vector<T> BiasesGradients;
	matrix<T> **Values;
	matrix<T> **Errors;
	matrix<T> **Gradients;
	int *LayerSize;
	int LayerCount;
	T lr;

	NeuralNetwork(int size, std::initializer_list<int> LayerScheme){
		LayerCount = size;
		LayerSize = new int[size];
		std::copy(LayerScheme.begin(), LayerScheme.end(), LayerSize);

		// arrays declaring
		Weights = new matrix<T>*[size-1];
		Values = new matrix<T>*[size];
		Errors = new matrix<T>*[size];
		Gradients = new matrix<T>*[size-1]; // n layer n-1 connection layer (weights) so gradients
		Biases.resize(size - 1); // no bias for output layer
		BiasesGradients.resize(size - 1);


		//weights and Biases randomization and gradient declare
		for(int i=0; i<size - 1; i++){
			Weights[i] = new matrix<T>(LayerSize[i+1],LayerSize[i]); // col is L1 row is L0
			Weights[i]->rand(30000,70000); // 0.3->0.7
			*Weights[i]/=1e5;
			Biases[i] = ((float)rand() / RAND_MAX) * 0.6f + 0.2f; // 0.2->0.8;
			
			Gradients[i] = new matrix<T>(LayerSize[i+1],LayerSize[i]);
			*Gradients[i] = (T)0.0;
		}
		//other arrays
		for(int i=0; i<size; i++){
			Values[i] = new matrix<T>(LayerSize[i],1);
			Errors[i] = new matrix<T>(LayerSize[i],1);
		}
		//learning rate
		lr = 0.01f;
		//biasgradients zeroing
		for(int i=0; i<size-1; i++){
			BiasesGradients[i] = 0.0;
		}	
	}

	void SetWeights(T x){
		for(int i=0; i<LayerCount; i++){
			*Weights[i] = x;
		}
	}

	void print(){
		for(int i=0; i<LayerCount - 1; i++){
			std::cout << "Layer" << i << std::endl; 
			Weights[i]->print();
			std::cout << "B " << Biases[i] << std::endl;
		}
	}
	
	matrix<T> FeedForward(matrix<T> r){
		*Values[0] = r; // first layer neurons <- inp
		for(int i=0; i<LayerCount - 1; i++){
			r = (*Weights[i] & r) + Biases[i];
			r.sig();
			*Values[i+1] = r;
		}
		return r; // last layer neurons ->out
	}

	void train(matrix<T> inp, matrix<T> target){ // operator~ for matrix transpose / operator& for matrix dot product
		*Errors[LayerCount - 1] = FeedForward(inp) - target; // Out layer error 
		for(int i=LayerCount - 1; i>0; i--){ //From last layer to second layer
			*Gradients[i-1] += *Errors[i] * (*Values[i]).Dsig() & ~*Values[i-1];
			BiasesGradients[i-1] += (*Errors[i] * (*Values[i]).Dsig()).average();
			*Errors[i-1] = ~*Weights[i-1] & *Errors[i]; // split current layer error to previous layer
		}
	}// last layer index is LayerCount - 1 for everything except weights for them is LayerCount - 2

	void ApplyGradients(){
		for(int i=0; i<LayerCount -1; i++){
			*Weights[i] -= *Gradients[i] * lr;
			*Gradients[i] = 0.0;
			Biases[i] -= BiasesGradients[i] * lr;
			BiasesGradients[i] = 0.0;
		}
	}
};
