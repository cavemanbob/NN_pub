#include <iostream>

template <typename T>
class matrix{
public:
	T *data;
	int col;
	int row;
	int size;
	bool real;
	
	matrix(int col , int row){// declare matrix<T> r(40,40);
		this->data = new T[col * row];
		this->col = col;
		this->row = row;
		this->size = col * row;
		real = true;
	}
	 matrix(){ // declare matrix<T> r;
		this->data = nullptr;
		this->col = -1;
		this->row = -1;
		this->size = -1;
	 }
	void print(){
		for(int i=0; i<this->col; i++){
			for(int j=0; j<this->row; j++)
				std::cout << *(this->data + this->row * i + j ) << "  "; //note format is decided to *(data + i) cuz other format is confussing for me whenever 2d matrix. sry
			std::cout << std::endl;
		}
	}
	void operator=(const T& num){// fill
		for(int i=0; i<this->size; i++)
			*(this->data + i) = (T)num;
	}
	void operator=(matrix<T> other){ // mix
		if(other.real){ // copy
			col = other.col;
			row = other.row;
			size = other.size;
			data = new T[size];
			for(int i=0; i<size; i++)
				*(data + i) = *(other.data + i);
		}
		else{ //replace
			delete data;
			col = other.col;
			row = other.row;
			size = other.size;
			data = other.data;
		}
	}
	// SUM	
	matrix<T> operator+(const matrix<T>& other){
		if(this->real == 1 && other.real == 1){
			matrix<T> r(this->col, this->row);
			for(int i=0; i<this->size; i++)
				*(r.data + i) = *(this->data + i) + *(other.data + i);
			r.real = false;
			return r;
		}
		else if(this->real == 1 && other.real == 0){
			matrix<T> r = other;
			for(int i=0; i<this->size; i++)
				*(r.data + i) += *(this->data + i);
			r.real = false;
			return r;
		}
		else if(this->real == 0 && other.real == 1){
			matrix<T> *r = this;
			for(int i=0; i<this->size; i++)
				*(r->data + i) += *(this->data + i);
			r->real = false;
			return *r;
		}
		else{
			matrix<T> *r = this;
			for(int i=0; i<this->size; i++)
				*(r->data + i) += *(this->data + i);
			r->real = false;
			delete other.data;
			return *r;
		}
	}
};
template <typename T>
matrix<T> func(matrix<T> a){
	matrix<T> r = a;
	r.real = false; // while its false, gives error. also while its true, gives memory leak  
	r = 3;
	return r;
}



int main(){
	matrix<double> b(20,20);
	b = 2;
	matrix<double> k;
//	for(int i=0; i<1000000; i++)
	for(int i=0; i<10; i++)
		k = func(b);
	k.print();
	return 0;
}

//
// a = r; dont delete r delete a 
// a = b + c; delete a
//	c = b + c 
//
// bug
// c = f(a);
// c = f(a); second assigment gives error
//
//




/*
	void operator=(matrix other){ // replace
		delete data;
		col = other.col;
		row = other.row;
		size = other.size;
		data = other.data;
	}

	void operator=(matrix other){ // copy
		col = other.col;
		row = other.row;
		size = other.size;
		data = new T[size];
		for(int i=0; i<size; i++)
			*(data + i) = *(other.data + i);
	}*/
 /*   matrix(const matrix& a) { //initilaze matrix<T> r = a;
		std::cout << "M";
		std::cout << this->size;
		if(other.real){ // copy
			col = other.col;
			row = other.row;
			size = other.size;
			data = new T[size];
			for(int i=0; i<size; i++)
				*(data + i) = *(other.data + i);
		}
		else{ //replace
			delete data;
			col = other.col;
			row = other.row;
			size = other.size;
			data = other.data;
		}
	 }*/
