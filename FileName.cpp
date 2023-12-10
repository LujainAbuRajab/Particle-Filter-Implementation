#include<iostream>
#include <random>
#include<math.h>

using namespace std;
struct PFStruct {
	float x, y, theta;
	float w;
};

//-------------------------------------
//Lujain AbuRajab   211045
//Haya Tahboub       211072
//-------------------------------------

const int l = 100;
void normalize(PFStruct* S) {
	int sum = 0;

	//to sum the waght for all particols
	for (int i = 0; i < l; i++)
	{
		sum = sum + S[i].w;
	}

	//to div the waght for particols
	for (int i = 0; i < l; i++)
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

	return l - 1; // Default case (should not reach here if weights are�normalized)
}

void forWord(int steps, PFStruct S) {
	S.x = S.x + abs(steps * cos(S.theta));
	S.y = S.y + abs(steps * sin(S.theta));
}

void rotate(PFStruct S) {
	S.theta += 90;

}



void update(PFStruct S, char Z) {
	if (Z == 'B' || Z == 'b')
	{
		if ((0 <= S.x <= 50) && (0 <= S.y <= 50)) //black box Num1
			S.w = 0.9;
		if ((0 <= S.x <= 50) && (50 <= S.y <= 100)) //white box Num1
			S.w = 0.1;
		if ((50 <= S.x <= 100) && (50 <= S.y <= 100)) //black box Num2
			S.w = 0.9;
		if ((50 <= S.x <= 100) && (0 <= S.y <= 50)) //black box Num2
			S.w = 0.1;
	}

	if (Z == 'W' || Z == 'w')
	{
		if ((0 <= S.x <= 50) && (0 <= S.y <= 50)) //black box Num1
			S.w = 0.2;
		if ((0 <= S.x <= 50) && (50 <= S.y <= 100)) //white box Num1
			S.w = 0.8;
		if ((50 <= S.x <= 100) && (50 <= S.y <= 100)) //black box Num2
			S.w = 0.2;
		if ((50 <= S.x <= 100) && (0 <= S.y <= 50)) //white box Num2
			S.w = 0.8;
	}
}

void ParticleFilter(PFStruct* S, char Z, char U, PFStruct* NS) {
	int k = 0;
	int j;
	for (int i = 0; i < l; i++)
	{
		j = sample(S);          //sample a partile i based on its weight 
		if (U == 'F' || U == 'f') {
			int steps;
			cout << "Enter num of steps: " << endl;
			cin >> steps;
			forWord(steps, S[j]);
		}
		else if (U == 'R' || U == 'r') {
			rotate(S[j]);
		}
		update(S[j], Z);
		NS[k] = S[j];
		k++;
	}
	normalize(S);

}


void initi(PFStruct* S) {
	for (int i = 0; i < l; i++)
	{
		S[i].x = abs(rand() % 101); //between min and max of the environment
		S[i].y = abs(rand() % 101); //between min and max of the environment
		S[i].theta = fmod(abs(rand()), 360.0); // theta between 0 and 360 
		S[i].w = 0.01; //sum of particles =1
	}
}


void main() {
	PFStruct S[l];
	PFStruct NS[l];
	initi(S);
	char Z;
	char U;
	while (1)
	{
		cout << "Enter the value of U: " << endl;
		cin >> U;
		cout << "Enter the value of Z (W/B): " << endl;
		cin >> Z;
		ParticleFilter(S, Z, U, NS);
		int j = 0;
		for (int i = 0; i < l; i++)
		{
			S[i] = NS[j];
			j++;
		}
	}


}