#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

using namespace std;

struct PFStruct {
  float x, y, theta;
  float w;
};

const int NUMParticles = 100;

void normalize(PFStruct *S) {
  float sum = 0.0;

  // Sum the weights for all particles
  for (int i = 0; i < NUMParticles; i++) {
    sum += S[i].w;
  }

  // Divide the weights for each particle
  for (int i = 0; i < NUMParticles; i++) {
    S[i].w = S[i].w / sum;
  }
}

void readCSVLine(const string &filename, int lineNumber, float &x, float &y,
                 float &displacement, float &angle) {
  ifstream file(filename);
  string line;

  for (int i = 1; i <= lineNumber; ++i) {
    if (!getline(file, line)) {
      cout << "Out of scope\n";
      return;
    }
    if (i == lineNumber) {
      istringstream iss(line);
      string value;
      int count = 0;
      while (getline(iss, value, ',')) {
        count++;
        switch (count) {
        case 1:
          x = stof(value);
          break;
        case 2:
          y = stof(value);
          break;
        case 3:
          displacement = stof(value);
          break;
        case 4:
          angle = stof(value);
          break;
        }
      }
      break;
    }
  }
  file.close();
}

int sample(PFStruct *S) {
  float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  float cdf = 0.0;

  for (int i = 0; i < NUMParticles; i++) {
    cdf += S[i].w;
    if (r <= cdf) {
      return i;
    }
  }

  return NUMParticles - 1;
}

void forward(float steps, PFStruct &S) {
  S.x = S.x + abs(steps * cos(S.theta));
  S.y = S.y + abs(steps * sin(S.theta));
  if (S.x < 0 || S.x > 100) {
    S.x = fmod(abs(S.x), 100.0);
  }
  if (S.y < 0 || S.y > 100) {
    S.y = fmod(abs(S.y), 100.0);
  }
}

void rotate(float angle, PFStruct &S) { S.theta += angle; }

void update(PFStruct &S, char Z) {
  if ((0 <= S.x && S.x <= 50) && (0 <= S.y && S.y <= 50)) // Black box Num1
    S.w = (Z == 'B' || Z == 'b') ? 0.9 : 0.1;
  else if ((0 <= S.x && S.x < 50) && (50 < S.y && S.y <= 100)) // White box Num1
    S.w = (Z == 'B' || Z == 'b') ? 0.2 : 0.8;
  else if ((50 <= S.x && S.x <= 100) &&
           (50 <= S.y && S.y <= 100)) // Black box Num2
    S.w = (Z == 'B' || Z == 'b') ? 0.9 : 0.1;
  else if ((50 < S.x && S.x <= 100) && (0 <= S.y && S.y < 50)) // White box Num2
    S.w = (Z == 'B' || Z == 'b') ? 0.2 : 0.8;
}

void particleFilter(PFStruct *S, char Z, PFStruct *NS, float dis, float angle) {
  for (int i = 0; i < NUMParticles; i++) {
    int j = sample(S);
    forward(dis, S[j]);
    rotate(angle, S[j]);
    update(S[j], Z);
    NS[i] = S[j];
  }
  normalize(S);
}

void initializeParticles(PFStruct *S) {
  for (int i = 0; i < NUMParticles; i++) {
    S[i].x = fmod(abs(rand() % 101), 100.0);
    S[i].y = fmod(abs(rand() % 101), 100.0);
    S[i].theta = fmod(abs(rand()), 360.0);
    S[i].w = 0.01;
  }
}

void report(PFStruct *S, float robotX, float robotY) {
  float meanParticleX = 0.0, meanParticleY = 0.0, varParticleX = 0.0,
        varParticleY = 0.0;

  for (int i = 0; i < NUMParticles; i++) {
    meanParticleX += S[i].x;
    meanParticleY += S[i].y;
  }

  meanParticleX /= static_cast<float>(NUMParticles);
  meanParticleY /= static_cast<float>(NUMParticles);

  for (int i = 0; i < NUMParticles; i++) {
    varParticleX += pow(S[i].x - meanParticleX, 2);
    varParticleY += pow(S[i].y - meanParticleY, 2);
  }

  varParticleX /= static_cast<float>(NUMParticles);
  varParticleY /= static_cast<float>(NUMParticles);

  cout << robotX << " " << robotY << " " << meanParticleX << " "
       << meanParticleY << " " << varParticleX << " " << varParticleY << "\n";
}

char sensor(float x, float y) {
  if ((0 <= x && x <= 50 && 0 <= y && y <= 50) ||
      (50 <= x && x <= 100 && 50 <= y && y <= 100)) // Black
    return 'b';
  if ((0 <= x && x < 50 && 50 < y && y <= 100) ||
      (50 < x && x <= 100 && 0 <= y && y < 50)) // White
    return 'w';

  return ' ';
}

int main() {
  PFStruct S[NUMParticles];
  PFStruct NS[NUMParticles];
  initializeParticles(S);

  char Z;
  for (int i = 0; i <= 500; i++) {
    float robotX, robotY, displacement, angle;
    const string filePath =
        "C:/Users/user/source/repos/Particle-Filter-Implementation/robot.csv";
    readCSVLine(filePath, i + 2, robotX, robotY, displacement, angle);

    Z = sensor(robotX, robotY);
    particleFilter(S, Z, NS, displacement, angle);
    report(S, robotX, robotY);

    for (int i = 0; i < NUMParticles; i++) {
      S[i] = NS[i];
    }
  }

  return 0;
}
