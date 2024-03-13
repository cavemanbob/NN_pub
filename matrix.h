#include <iostream>
#include <cstdlib>
#include <cassert>
#include <initializer_list>
#include <math.h>

template <typename T>
class matrix{
public:
	T *data;
	int col;
	int row;
	int size;
	int temp;
	


	matrix(int col, int row) : col(col), row(row), size(col * row){
		this->data = new T[col * row];
		temp = 0;
	}
	//solution 1
/*	~matrix(){ //destructer have been tried but its breaks somethings
		delete[] data; 
	}*/
	void print(){
		for(int i=0; i<this->col; i++){
			for(int j=0; j<this->row; j++)
				std::cout << *(this->data + this->row * i + j ) << "  ";
			std::cout << std::endl;
		}
	}
	void operator=(const T& other){
		for(int i=0; i<this->size; i++){
			*(this->data + i) = (T)other;
		}
	}
	void operator=(const std::initializer_list<T>& other){
		int i=0;
		for(T x: other){
			*(this->data + i) = x;
			i++;
		}
	}

	void operator=(const matrix& other) { //solition 2
		if(other.temp){
			delete [] this->data;
			std::cout << "H";
		}	
		col = other.col;
		row = other.row;
		size = other.size;
		this->data = new T[other.size];
		for(int i=0; i<size; i++){
			*(this->data + i) = *(other.data + i);
		}
		if(other.temp){
			delete &other;
			std::cout << "H";
		}	
    }
	

	void rand(int Sv, int Fv){
		for(int i=0; i<this->size; i++){
			*(this->data + i) = ::rand() % (Fv - Sv + 1) + Sv;
		}
	}

	matrix<T> operator+(const matrix<T>& other){
//		matrix<T> *r = new matrix<T>(this->col, this->row);  //ptr type
		matrix<T> r(this->col, this->row);
		for(int i=0; i<this->size; i++){
			*(r.data + i) = *(this->data + i) + *(other.data + i);
		}
		r.temp = 1;
		return r;
	}

	void operator+=(const matrix<T>& other){
		matrix<T> r(this->col, this->row);
		for(int i=0; i<this->size; i++){
			*(this->data + i) += *(other.data + i);
		}
	}

	void operator-=(const matrix<T>& other){
		matrix<T> r(this->col, this->row);
		for(int i=0; i<this->size; i++){
			*(this->data + i) -= *(other.data + i);
		}
	}

	matrix<T> operator-(const matrix<T>& other){
		matrix<T> r(this->col, this->row);
		for(int i=0; i<this->size; i++){
			*(r.data + i) = *(this->data + i) - *(other.data + i);
		}
		return r;
	}

	matrix<T> operator*(const matrix<T>& other){
		matrix<T> r(this->col, this->row);
		for(int i=0; i<this->size; i++){
			*(r.data + i) = *(this->data + i) * *(other.data + i);
		}
		return r;
	}

	matrix<T> operator/(const matrix<T>& other){
		matrix<T> r(this->col, this->row);
		for(int i=0; i<this->size; i++){
			*(r.data + i) = *(this->data + i) / *(other.data + i);
		}
		return r;
	}

	void operator-=(const T& other){
		for(int i=0; i<this->size; i++)
			*(this->data + i) -= other;
	}

	void operator+=(const T& other){
		for(int i=0; i<this->size; i++)
			*(this->data + i) += other;
	}

	void operator*=(const T& other){
		for(int i=0; i<this->size; i++)
			*(this->data + i) *= other;
	}

	void operator/=(const T& other){
		for(int i=0; i<this->size; i++)
			*(this->data + i) /= other;
	}

	 matrix<T> operator-(const T& other){
		for(int i=0; i<this->size; i++){
			*(this->data + i) -= other;
		}
		return *this;
	}

	 matrix<T> operator+(const T& other){
		for(int i=0; i<this->size; i++){
			*(this->data + i) += other;
		}
		return *this;
	}
	matrix<T> operator*(const T& other){
		for(int i=0; i<this->size; i++){
			*(this->data + i) *= other;
		}
		return *this;
	}
	 matrix<T> operator/(const T& other){
		for(int i=0; i<this->size; i++){
			*(this->data + i) /= other;
		}
		return *this;
	}



	matrix<T> dot(const matrix<T>& other){
		if(this->row != other.col){
			std::cout << "Error: row and col unmatched!! " <<this->col<<" "<<this->row << "x" << other.col <<" "<<other.row<< std::endl;
			assert(0);
		}
		matrix<T> r(this->col, other.row);
		r = 0;	
		for(int i=0; i<this->col; i++)
			for(int k=0; k<this->row; k++)
				for(int j=0; j<other.row; j++)
					*(r.data + r.row * i + j) += *(this->data + this->row * i + k) * *(other.data + other.row * k + j);
		return r;
	}

	matrix<T> operator&(const matrix<T>& other){
		if(this->row != other.col){
			std::cout << "Error: row and col unmatched!! " <<this->col<<" "<<this->row << "x" << other.col <<" "<<other.row<< std::endl;
			assert(0);
		}
		matrix<T> r(this->col, other.row);
		r = 0;	
		for(int i=0; i<this->col; i++)
			for(int k=0; k<this->row; k++)
				for(int j=0; j<other.row; j++)
					*(r.data + r.row * i + j) += *(this->data + this->row * i + k) * *(other.data + other.row * k + j);
		return r;
	}

	matrix<T> operator~(){
		matrix <T> r(this->row, this->col);
		for(int i=0; i<this->col; i++)
			for(int j=0; j<this->row; j++)
				*(r.data + r.row * j + i) = *(this->data + this->row * i + j);
		return r;
	}

	T average(){
		T sum = 0;
		for(int i=0; i<this->size; i++){
			sum += *(this->data + i);
		}
		sum /= this->size;
		return sum;
	}

	void sig(){
		for(int i=0; i<this->size; i++)
			*(this->data + i) = 1 / (1 + exp(-*(this->data + i)));
	}
	matrix<T> Dsig(){
		matrix <T> r(this->col, this->row);
		for(int i=0; i<this->size; i++){
			*(r.data + i) = *(this->data + i) * (1 - *(this->data + i));
		}
		return r;
	}
};
