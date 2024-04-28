# Montion Control System
## Abstract
The barrier gate is quite common in the car park. In this project, we hope to model
the barrier gate by using a DC motor and design a closed-loop controller to make the
barrier gate more stable, accurate and safe in operation. Before the physical design,
we explore the control principle, characteristics and control mode of the DC motor
through Simulink simulation firstly, design the appropriate control algorithm and carry
out simulation for verification. Through the simulation, we can find out the parameters
of the controller more quickly and intuitively, which provides reference for the future
physical design.
![alt text](image.png)

## Contents
### Simulation part
You can see the simulation model in the folder - Simulink.

In this model, I try to use three diffenrent PID controller to realise the accurate control of a model of DC motor(parameters are specified by the real DC motor),
and compare the diffenrence and effectiveness between these controllers. The result is shown in Simulation Report.

The Report shows you:
* Simulation model
* Close loop control algorithm
* Trapezoidal and S-curve velocity profiles
* Analysis of P, I, and D
* Identification of the transfer function

### Codes for the microcontroller-ESP32
Base on the result of simulation, I compile the algorithm into a microcontroller-ESP32, and you can the the detail of the algorithm in the folder-MontionControl.

In this part, I realise:

* Design a closed-loop control algorithm, and utilize Pulse Width Modulation to control the
motor for generating Trapezoidal and S-curve velocity profiles.
* Display the velocity profiles in real-time on the OLED screen.
* Use Bluetooth to control the system remotely.
* Adjust the parameters of the controller to make the motor run smoothly with Trapezoidal
and S-curve velocity profiles.
