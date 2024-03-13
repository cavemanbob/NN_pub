#include "NNap.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <filesystem>
#include <random>
#include <time.h>

//from this to int main just func that for read photos not really interested with memory leak
namespace fs = std::filesystem;
struct dimg{
	int num;
	float* data;
};
std::vector<fs::path>* initvec[10];

/*
clock_t start_t = clock();
clock_t end_t = clock();
printf("Execution time: %f seconds\n", ((double)(end_t - start_t)) / CLOCKS_PER_SEC);
*/

fs::path getRandomFile(const fs::path& folderPath, int s) {
    
	std::vector<fs::path>* files = initvec[s];
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, files->size() - 1);
    int randomIndex = dis(gen);
    return files->at(randomIndex);
}



dimg GetImg(int s){
	
	dimg r;
	r.data = new float[28*28];
	r.num = s;

	std::string y = "MNIST Dataset JPG format/MNIST - JPG - testing/";
	y += std::to_string(s);
	y += "/";

	fs::path randomFile = getRandomFile(y,s);
	std::string str_path = randomFile.string();
	const char* path = str_path.c_str();
	//	std::cout << str_path << std::endl;
    int width, height, channels;
    unsigned char* imageData = stbi_load(path, &width, &height, &channels, STBI_grey);
	if (imageData == nullptr) {
	  // Handle error (unable to load image)
	  std::cerr << "Error loading image: " << stbi_failure_reason() << std::endl;
 } 
  	for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width * channels; ++j) {
//            unsigned char pixelValue = imageData[i * width * channels + j];
         	*(r.data + i * 28 + j) = imageData[i * width * channels + j];
		  }
   }
	
	 return r;
}
void printNum(float *r){
	std::cout << std::endl;
	for(int i=0; i<784; i++){
		if( i%28 == 0)std::cout << std::endl;
		(*(r + i)> 50) ? std::cout << "+" : std::cout<<".";
	}
}

int main(){
/* //neural network for hand writting digits 
	//second layer smaller than third cuz it dont get trained when 2 > 3 but i ll fix later np;
	NerualNetwork<float> n1(4,{784,12,16,10});

	//init image
	for(int i=0; i<10; i++){
		std::string y = "MNIST Dataset JPG format/MNIST - JPG - testing/";
		y += std::to_string(i);
		y += "/";
		std::vector<fs::path>* files = new std::vector<fs::path>;
		for (const auto& entry : fs::directory_iterator(y)) {
		  if (entry.is_regular_file()) {
				files->push_back(entry.path());
		  }
		}
		if (files->empty()) {
		  throw std::runtime_error("No files found in the folder.");
		}
		initvec[i] = files;
	}


	matrix<float> target(10,1);
	for(int epoch = 500; epoch>0; epoch--){
		std::cout << 5000-epoch << std::endl;
		for(int i=0; i<200; i++){
			dimg TestImg = GetImg(rand()%10);
			matrix<float> TestArr(784,1);
			TestArr.data = TestImg.data;
			target = 0;
			*(target.data + TestImg.num) = 1;
//			target.print();
			n1.BackPropagation(TestArr, target);
		}
		n1.ApplyGradients();
	}

	matrix<float> test(784,1);
	matrix<float> out(10,1);
	int correct = 0;
	int wrong = 0;
	for(int i=0; i< 2000; i++){
		dimg TestImg = GetImg(rand()%10);
		test.data = TestImg.data;
		out = n1.FeedForward(test);
		maxi(out) == TestImg.num ? correct++ : wrong++;

	}
	std::cout << "Correct: " << correct << std::endl << "Wrong: " << wrong;
	printNum(test.data);
	out.print();
*/

 //xor neural network 
	srand(time(NULL));
	NeuralNetwork<double> n1(4,{2,2,2,1});
	double inpar[4][2] = {{1,0},{0,1},{1,1},{0,0}};
	double intar[4][1] = {{1},{1},{0},{0}};
	matrix<double> inp(2,1); 	
	matrix<double> target(1,1);	
	matrix<double> out(1,1);	
	n1.lr /=10;
	n1.print();
	std::cout << "Before" << std::endl; 

	for(int i=0; i<4;i++){
		inp = inpar[i];
		out = n1.FeedForward(inp);
		std::cout << inpar[i][0]<<"- " << inpar[i][1] << " ->";
		out.print();
	}
	
clock_t start_t = clock();
	for(int epoch = 100000; epoch>0; epoch--){ 
		for(int i=0; i<4; i++){
			inp = inpar[i];
			target = intar[i];
			n1.train(inp, target);
		}		
		n1.ApplyGradients();
	}
	
clock_t end_t = clock();
printf("Execution time: %f seconds\n", ((double)(end_t - start_t)) / CLOCKS_PER_SEC);
	for(int i=0; i<4;i++){
		inp = inpar[i];
		out = n1.FeedForward(inp);
		std::cout << inpar[i][0]<<"- " << inpar[i][1] << " ->";
		out.print();
	}
	/*
	inp = {1,0};
	std::cout << "INP:";
	inp.print();
	out = n1.FeedForward(inp);
	std::cout << "1 - 0 ->";
	out.print();

	inp = {0,1};
	std::cout << "INP:";
	inp.print();
	out = n1.FeedForward(inp); 
	std::cout << "0 - 1 ->";
	out.print();

	inp = {1,1};
	std::cout << "INP:";
	inp.print();
	out = n1.FeedForward(inp);
	std::cout << "1 - 1 ->";
	out.print();

	inp = {0,0};
	std::cout << "INP:";
	inp.print();
	out = n1.FeedForward(inp);
	std::cout << "0 - 0 ->";
	out.print();*/
/*	
clock_t start_t = clock();
	for(int epoch = 15000; epoch>0; epoch--){ 
		inp = {1,0};
		target = {1};
		n1.BackPropagation(inp, target);

		inp = {0,1};
		target = {1};
		n1.BackPropagation(inp, target);

		inp = {0,0};
		target = {0};
		n1.BackPropagation(inp, target);

		inp = {1,1};
		target = {0};
		n1.BackPropagation(inp, target);
		
	//	n1.print();
		n1.ApplyGradients();
	}
	
clock_t end_t = clock();
printf("Execution time: %f seconds\n", ((double)(end_t - start_t)) / CLOCKS_PER_SEC);
	std::cout << "After" << std::endl;

	inp = {1,0};
	out = n1.FeedForward(inp);
	std::cout << "1 - 0 ->";
	out.print();

	inp = {0,1};
	out = n1.FeedForward(inp);
	std::cout << "0 - 1 ->";
	out.print();

	inp = {1,1};
	out = n1.FeedForward(inp);
	std::cout << "1 - 1 ->";
	out.print();

	inp = {0,0};
	out = n1.FeedForward(inp);
	std::cout << "0 - 0 ->";
	out.print();
	
	std::cout << "Bias Weights";
	for(int i=0; i<n1.LayerMaxSize -1; i++){
		std::cout << *(n1.LayersBiases + i) << "  ";
	}
*/


	return 0;
}
