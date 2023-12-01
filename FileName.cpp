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



/* sampling
double cum_dist_funct::real_cdf_function(vec X, double x, int N, int Ndft, vec& T, vec& Z)
{
	Z.set_size(X.length());
	Z.zeros();
	vec V;
	V.set_size(N);
	V.zeros();
	double f0 = 0;
	T.set_size(X.length());
	T.zeros();
	T = X;
	for (int i = 0; i < Ndft; i++)
	{
		V = X.get(i * N, (i + 1) * N - 1);
		for (int j = 0; j < N; j++)
		{
			if (x < V[0]) f0 = 0;
			else if (V[j] <= x && x < V[j + 1]) f0 = j / N;
			else if (x >= V[N - 1])      f0 = 1;
			Z[i * N + j] = f0;
		}
	}
	return f0;
}
*/