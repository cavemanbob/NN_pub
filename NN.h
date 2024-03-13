#include "matvec.h"


template<typename Tn>
class NeuralNetwork{
public:
	matrix<Tn> **LayersWeights;
	Tn *LayersBiases;
	Tn *LayersBiasGradients;
	matrix<Tn> **LayersValues; //all of this a array that include pointers of matrixes 
	matrix<Tn> **LayersErrors;
	matrix<Tn> **LayersGradients;
	int *LayerSize;
	int LayerMaxSize;
	Tn lr;

	NeuralNetwork(int size, std::initializer_list<int> inp){ //init neural network
		// 5, {4,9,6,2,4}
		LayerMaxSize = size;
		int *n = new int[size + 1];
		std::copy(inp.begin(),inp.end(),n);
		LayerSize = n;
		// ptr arrays init
		LayersWeights = new matrix<Tn>*[size];
		LayersBiases = new Tn[size];
		LayersBiasGradients = new Tn[size];
		LayersValues = new matrix<Tn>*[size];
		LayersErrors = new matrix<Tn>*[size];
		LayersGradients = new matrix<Tn>*[size];
		
		// row -> L0  col -> L1
		// weights
		for(int i=0; i<size-1 ; i++){
			matrix<Tn>* m = new matrix<Tn>(*(n+1 + i),*(n + i));
			m->rand(30000,70000);
//			m->rand(50000,50000);
			*m /= 100000;
			*(LayersWeights + i) = m;
		}
		// biases
		for(int i=0; i<size-1 ; i++){
			*(LayersBiases + i) = ((float)rand() / RAND_MAX) * 0.6f + 0.2f; // 0.2-0.8  
		}
		// lr
		this->lr = 0.01f;
		//Gradient
		for(int i=0; i<size - 1; i++){ // array that include pointers of matrixes 
			*(LayersGradients + i) = new matrix<Tn>(*(n + i + +1), *(n + i));
			*LayersGradients[i] = 0.0;	
		}
		//BiasGradient
		for(int i=0; i<size; i++){
			*(LayersBiasGradients + i) = 0.0; 
		}
		//Values	
		for(int i=0; i<size; i++){
			*(LayersValues + i) = new matrix<Tn>(*(n + i), 1); 
		}
		//Errors	
		for(int i=0; i<size; i++){
			*(LayersErrors + i) = new matrix<Tn>(*(n + i), 1); 
		}
	}
	void SetWeights(Tn x){
		for(int i=0;i<LayerMaxSize -1; i++){
			**(LayersWeights + i) = x;
			*(LayersBiases + i) = x;	
		}
	}
	void print(){
		for(int i=0; i<LayerMaxSize - 1;i++){
			(*(LayersWeights + i))->print();
			std::cout << "  " << *(LayersBiases + i) <<	std::endl;
		}
	}
	~NeuralNetwork() {
    for (int i = 0; i < LayerMaxSize - 1; i++){
        delete LayersWeights[i];
        delete LayersGradients[i];
        delete LayersValues[i];
        delete LayersErrors[i];
    }
    delete[] LayersWeights;
    delete[] LayersGradients;
    delete[] LayersValues;
    delete[] LayersErrors;
    delete[] LayersBiases;
    delete[] LayersBiasGradients;
    delete[] LayerSize;
}
			

	matrix<Tn> FeedForward(matrix<Tn> r){ // r = inp
			**LayersValues = r;
			for(int i=0; i< LayerMaxSize-1; i++){
				r = (**(LayersWeights + i) & r) + *(LayersBiases + i);
				r.sig();
				**(LayersValues + i + 1) = r;
			}
			return r;
	}

	void train(matrix<Tn> inp, matrix<Tn> target){
		*LayersErrors[LayerMaxSize - 1] = FeedForward(inp) - target; // 
		for(int i=LayerMaxSize - 1; i > 0; i--){
			std::cout << i;
			*LayersErrors[i - 1] = ~*LayersWeights[i - 1]  & *LayersErrors[i];
			
			// lr       -> this->lr
			// L1 error -> (*(*(LayersErrors + i)))
			// L0 input -> (*(*(LayersValues + i - 1)))
			// L1 der   -> (*(*(LayersValues + i))).Dsig()
			
			//update gradient
			*LayersGradients[i - 1] += *LayersErrors[i] * (*LayersValues[i]).Dsig() & ~*(LayersValues[i-1]);
			//update biasgradient
			LayersBiasGradients[i - 1] += (*LayersErrors[i] * (*LayersValues[i]).Dsig()).average();
		}
		
	}
/*
	void BackPropagation(matrix<Tn> inp, matrix<Tn> target){
		**(LayersErrors + LayerMaxSize - 1) = this->FeedForward(inp) - target; // 
		for(int i=LayerMaxSize - 1; i > 0; i--){
			**(LayersErrors + i - 1) = (~(**(LayersWeights + i - 1)) ) & (**(LayersErrors + i));
			
			// lr       -> this->lr
			// L1 error -> (*(*(LayersErrors + i)))
			// L0 input -> (*(*(LayersValues + i - 1)))
			// L1 der   -> (*(*(LayersValues + i))).Dsig()
			
			//update gradient
			**(LayersGradients + i - 1) += (**(LayersErrors + i) * (**(LayersValues + i)).Dsig()) & ~(**(LayersValues + i - 1));
			//update biasgradient
			*(LayersBiasGradients + i - 1) += (**(LayersErrors + i) * (**(LayersValues + i)).Dsig()).average();
		}
		
	}*/
	/*void BackPropagation(matrix<Tn> inp, matrix<Tn> target){
		**(LayersErrors + LayerMaxSize - 1) = target - this->FeedForward(inp);
		for(int i=LayerMaxSize - 1; i > 0; i--){  
			**(LayersErrors + i - 1) = (~(**(LayersWeights + i - 1))) & (*(*(LayersErrors + i)));
			
			// lr       -> this->lr
			// L1 error -> (*(*(LayersErrors + i)))
			// L0 input -> (*(*(LayersValues + i - 1)))
			// L1 der   -> (*(*(LayersValues + i))).Dsig()
			
			//update gradient
			**(LayersGradients + i - 1) += (**(LayersErrors + i) * (**(LayersValues + i)).Dsig()  * lr) & ~(**(LayersValues + i - 1));
			//update biasgradient
			*(LayersBiasGradients + i - 1) += (**(LayersErrors + i) * (**(LayersValues + i)).Dsig()  * lr).average();
		}
		
	}*/

	void ApplyGradients(){
		for(int i=0; i<LayerMaxSize - 1; i++){
			**(LayersWeights + i) -= **(LayersGradients + i) * lr;
			**(LayersGradients + i) = 0.0;
			*(LayersBiases + i) -= *(LayersBiasGradients + i) * lr;
			*(LayersBiasGradients + i) = 0.0;
		}
	}
};






/*	void BackPropagation(matrix<Tn> inp , matrix<Tn> target){
		**(LayersErrors + LayerMaxSize - 1) = target - FeedForward(inp);
		for(int i=0; i<LayerMaxSize - 1;i++){
			**(LayersErrors + i - 1) = ~(**(LayersWeights + i - 1)) & **(LayersErrors + i);
			**(LayersGradients + i - 1) += (**(LayersErrors + i - 1) * (**(LayersValues + i)).Dsig() * lr) & ~(**(LayersValues + i - 1));
			*(LayersBiasGradients + i - 1) += (**(LayersErrors + i) * (**(LayersValues + i)).Dsig()  * lr).average();
		}
	}*/






