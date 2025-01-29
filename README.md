# :world_map: **Particle Filter Implementation**

## :paperclips: **Overview**
This project focuses on implementing a Particle Filter for robot localization. Particle filters are a powerful technique
used in robotics and AI to estimate the state of a system based on noisy sensor measurements. In this project, we
demonstrate the effectiveness of particle filters in localizing a robot within a simulated environment.

The particle filter algorithm is implemented in C++ and simulates the process of estimating the robot's position and 
orientation using a set of particles. Each particle represents a possible state of the robot, and the algorithm updates the particles' weights based 
on sensor measurements and motion updates.


## :sparkles: **Features**

- **Particle Initialization:** Particles are initialized randomly across the environment.
- **Motion Model:** The robot's motion is simulated using a forward and rotation model.
- **Sensor Model:** The sensor model updates particle weights based on the robot's position in the environment.
- **Resampling:** Particles are resampled based on their weights to focus on the most likely states.
- **Localization:** The algorithm estimates the robot's position and orientation by computing the mean and variance of the particles.

## :spiral_notepad: **Implementation Details**
+ **Programming Language:** `C++`
+ **Number of Particles:** `100`
+ **Sensor Model:** Binary environment (Black/White regions)
       ![particals position: Black/White regions](https://github.com/LujainAbuRajab/Particle-Filter-Implementation/blob/5236147faf7be673809f2c8e5c038005ff0b62b8/particals_position.jpg)
+ **Motion Model:** `Forward` movement and `rotation`
+ **Resampling Method:** Importance Sampling

## :bookmark_tabs: **File Structure**

```bash

Particle-Filter-Implementation/
│── robot.csv             # CSV file containing robot motion data
│── particle_filter.cpp   # Main implementation file
│── README.md             # Project documentation

```

## :computer: **Code Overview**
**The code is structured as follows:**
1. **Particle Structure:** Each particle is represented by a struct `PFStruct` containing its position (`x`, `y`), orientation (`theta`), and weight (`w`).
2. **Normalization:** The `normalize` function ensures that the sum of all particle weights is 1.
3. **CSV Reading:** The `readCSVLine` function reads robot data (position, displacement, and angle) from `robot.csv` file.
4. **Sampling:** The `sample` function selects a particle based on its weight.
5. **Motion Update:** The `forward` and `rotate` functions simulate the robot's motion.
6. **Sensor Update:** The `update` function updates particle weights based on sensor measurements.
7. **Particle Filter:** The `particleFilter` function performs the core particle filter algorithm, including motion and sensor updates.
8. **Initialization:** The `initializeParticles` function initializes particles randomly.
9. **Reporting:** The `report` function computes and prints the mean and variance of the particles' positions.
10. **Sensor Simulation:** The `sensor` function simulates the robot's sensor readings based on its position.

## :paperclips: **Usage**
### Compilation
To compile the code, use the following command:
```
  ./particle_filter
```
The program will read the robot's data from `robot.csv`, simulate the particle filter algorithm, and output the estimated position and variance of the robot.

### :inbox_tray: Input File Format
The input file (`robot.csv`) should contain the following columns:
1. **x:** Robot's x-coordinate.
2. **y:** Robot's y-coordinate.
3. **displacement:** Robot's displacement.
4. **angle:** Robot's rotation angle.

Example `robot.csv`:
```
  x,y,displacement,angle
  10,20,5,30
  15,25,6,45
  ...
```

### :outbox_tray: Output
The program outputs the following for each step:
+ **Robot's true position:** `robotX`, `robotY`
+ **Estimated position:** `meanParticleX`, `meanParticleY`
+ **Variance:** `varParticleX`, `varParticleY`

Example output:
```
  10 20 12.5 22.3 1.2 0.8
  15 25 16.7 24.1 1.1 0.9
  ...
```

### Let me know if you need help with any specific part of this! 😊  
