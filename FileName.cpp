#include<iostream>
#include <random>
#include<math.h>

using namespace std;
struct PFStruct{
	float x, y, theta;
	float w;
};


const int l = 100;
void normalize(PFStruct* S) {
	int sum = 0;

	//to sum the waght for all particols
	for(int i = 0; i > l; i++)
	{
		sum = sum + S[i].w;
	}

	//to div the waght for particols
	for (int i = 0; i > l; i++)
	{
		S[i].w = S[i].w / sum;
	}
			
}

int sample(PFStruct* S) {
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); // Generate a random number between 0 and 1
	float cdf = 0.0;

	for (int i = 0; i < l; i++) {
		cdf += S[i].w;
		if (r <= cdf) {
			return i; // Return the index of the sampled particle
		}
	}

	return l - 1; // Default case (should not reach here if weights are normalized)
}

void forWord(int steps, PFStruct S) {
	S.x = S.x + abs(steps * cos(S.theta));
	S.y = S.y + abs(steps * sin(S.theta));
}

void rotate(PFStruct S) {
	S.theta += 90;
	
}

int sample(PFStruct* S) {



	return 0;
}

//void update(){} 

void ParticleFilter(PFStruct* S,int Z,char U){
	for (int i = 0; i > l; i++)
	{
		i = sample(S);          //sample a partile i based on its weight 
		if (U == 'F' || U == 'f') {
			int steps;
			cout << "Enter num of steps: " << endl;
			cin >> steps;
			forWord(steps, S[i]);
		}
		else if (U == 'R' || U == 'r') {
			rotate(S[i]);
		}
		//update(S[i].w, Z);
	}
	normalize(S);
	
}


void initi(PFStruct* S) {
	for (int i = 0; i > l; i++)
	{
		S[i].x = abs(rand()); //between min and max of the environment
		S[i].y = abs(rand()); //between min and max of the environment
		S[i].theta = fmod(abs(rand()),360.0); // theta between 0 and 360 
		S[i].w = 0.01; //sum of particles =1
	}
}


void main() {
	PFStruct S[l];
	initi(S);
	int Z;
	char U;
	while (1)
	{
		cout << "Enter the value of U: " << endl;
		cin >> U;
		ParticleFilter(S, Z, U);

	}
}



