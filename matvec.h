#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
template <typename T>
class matrix{
public:
	std::vector<std::vector<T>> data;
	int col;
	int row;
	int size;
	matrix(int col, int row) : col(col), row(row), size(col * row){
		data.resize(col);
		for(int i=0; i<col; i++)  data[i].resize(row);
	}
	void print(){
		for(int i=0; i<col; i++){
			for(int j=0; j<row; j++){
				std::cout << data[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
	void operator=(const T& num){
		for(int i=0; i<col; i++)
			for(int j=0; j<row; j++)
				data[i][j] = num;
	}/*
	void operator=(const std::initializer_list<T>& other){
		int i=0;
		for(T x: other){
			this->data[0][i] = x;
			i++;
		}
	}*/
	void operator=(const T* ar){
		for(int i=0; i<col; i++){
			data[i][0] = ar[i];
		}
	}

	// Matrix to matrix operator
	matrix<T> operator+(matrix<T> other){
		matrix r(this->col,this->row);
		for(int i=0; i<col; i++)
			for(int j=0; j<row; j++)
				r.data[i][j] = this->data[i][j] + other.data[i][j];
		return r;
	}
	matrix<T> operator-(matrix<T> other){
		matrix r(this->col,this->row);
		for(int i=0; i<col; i++)
			for(int j=0; j<row; j++)
				r.data[i][j] = this->data[i][j] - other.data[i][j];
		return r;
	}
	matrix<T> operator*(matrix<T> other){
		matrix r(this->col,this->row);
		for(int i=0; i<col; i++)
			for(int j=0; j<row; j++)
				r.data[i][j] = this->data[i][j] * other.data[i][j];
		return r;
	}
	matrix<T> operator/(matrix<T> other){
		matrix r(this->col,this->row);
		for(int i=0; i<col; i++)
			for(int j=0; j<row; j++)
				r.data[i][j] = this->data[i][j] / other.data[i][j];
		return r;
	}
	void operator+=(matrix<T> other){
		for(int i=0; i<col; i++)
			for(int j=0; j<row; j++)
				this->data[i][j] += other.data[i][j];
	}
	void operator-=(matrix<T> other){
		for(int i=0; i<col; i++)
			for(int j=0; j<row; j++)
				this->data[i][j] -= other.data[i][j];
	}
	void operator*=(matrix<T> other){
		for(int i=0; i<col; i++)
			for(int j=0; j<row; j++)
				this->data[i][j] *= other.data[i][j];
	}
	void operator/=(matrix<T> other){
		for(int i=0; i<col; i++)
			for(int j=0; j<row; j++)
				this->data[i][j] /= other.data[i][j];
	}

	// Matrix to num operator
	matrix<T> operator+(T num){
		matrix<T> r(this->col,this->row);
		for(int i=0; i<col; i++)
			for(int j=0; j<row; j++)
				r.data[i][j] = this->data[i][j] + num;
		return r;
	}
	matrix<T> operator-(T num){
		matrix<T> r(this->col,this->row);
		for(int i=0; i<col; i++)
			for(int j=0; j<row; j++)
				r.data[i][j] = this->data[i][j] - num;
		return r;
	}
	matrix<T> operator*(T num){
		matrix<T> r(this->col,this->row);
		for(int i=0; i<col; i++)
			for(int j=0; j<row; j++)
				r.data[i][j] = this->data[i][j] * num;
		return r;
	}
	matrix<T> operator/(T num){
		matrix<T> r(this->col,this->row);
		for(int i=0; i<col; i++)
			for(int j=0; j<row; j++)
				r.data[i][j] = this->data[i][j] / num;
		return r;
	}
	void operator+=(T num){
		for(int i=0; i<col; i++)
			for(int j=0; j<row; j++)
				this->data[i][j] += num;
	}
	void operator-=(T num){
		for(int i=0; i<col; i++)
			for(int j=0; j<row; j++)
				this->data[i][j] -= num;
	}
	void operator*=(T num){
		for(int i=0; i<col; i++)
			for(int j=0; j<row; j++)
				this->data[i][j] *= num;
	}
	void operator/=(T num){
		for(int i=0; i<col; i++)
			for(int j=0; j<row; j++)
				this->data[i][j] /= num;
	}
	
	// Special funcs
	
	void rand(int Sv, int Fv){
		for(int i=0; i<col; i++)
			for(int j=0; j<row; j++)
				this->data[i][j] = std::rand() % (Fv - Sv + 1) + Sv;
	}

	matrix<T> operator~(){
		matrix<T> r(this->row,this->col);	
		for(int i=0; i<col; i++)
			for(int j=0; j<row; j++)
				r.data[j][i] = this->data[i][j];
		return r;
	}
	
	matrix<T> operator&(const matrix<T>& other){
		if(this->row != other.col){
			std::cout << "Error: row and col unmatched!! " <<this->col<<" "<<this->row << "x" << other.col <<" "<<other.row<< std::endl;
		}
		matrix<T> r(this->col,other.row);
		r = 0.0;
		for(int i=0; i<this->col; i++)
			for(int k=0; k<this->row; k++)
				for(int j=0; j<other.row; j++)
					r.data[i][j] += this->data[i][k] * other.data[k][j];
		return r;
	}

	T average(){
		T sum = 0;
		for(int i=0; i<col; i++)
			for(int j=0; j<row; j++)
				sum += data[i][j];
		return sum / size;
	}
	/*
	matrix<T> sig(){
		matrix<T> r(col,row);
		for(int i=0; i<col; i++)
			for(int j=0; j<row; j++)
				r.data[i][j] = 1 / (1 + exp(-data[i][j]));
		return r;
	}*/
	void sig(){
		for(int i=0; i<col; i++)
			for(int j=0; j<row; j++)
				data[i][j] = (T)(1 / (1 + exp(-data[i][j])));
	}
	
	matrix<T> Dsig(){
		matrix<T> r(col,row);
		for(int i=0; i<col; i++)
			for(int j=0; j<row; j++)
				r.data[i][j] = data[i][j] * (1 - data[i][j]);
		return r;
	}
	T sum(){
		T sum=0;
		for(int i=0; i<col; i++)
			for(int j=0; j<row; j++)
				sum += data[i][j];
		return sum;
	}
};
/*
template <typename T>
matrix<T> operator-(float value, const matrix& obj) {
	matrix<T> r(obj.col, obj.row);
	for(int i=0; i<obj.col; i++)
		for(int j=0; j<obj.row; j++)
			r.data[i][j] = value - ob.data[i][j];
	return r;
}

template <typename T>
matrix<T> operator+(float value, const matrix& obj) {
	matrix<T> r(obj.col, obj.row);
	for(int i=0; i<obj.col; i++)
		for(int j=0; j<obj.row; j++)
			r.data[i][j] = value + ob.data[i][j];
	return r;
}
*/

