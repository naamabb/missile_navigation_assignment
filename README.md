# missile_navigation_assignment

The program is a simulation of a rocket chasing targets.
Arguments:
supply 1 input configuration file in the following format:
t // time step
ts // missile's start time
n // number of objects
x0 y0 ang0 v0 x1 y1 ang1 v1.....xn yn angn vn // start points, direction(deg) and speed [m/s] for each objects
xm ym vm aMax // missile launch point, missile velocity [m/s], max lateral acceleration
dk // distance from object where the object is marked as destroyed


The program will output two files:
1. history.txt - indicates event like destroying target and find new target
2. events.txt -  indicates locations and statuses of all the objects during the run, 
also indicates missile location and lateral acceleration.


assumptions:
vm >> vm // the missile is faster then all objects
the objects are place infront of the missile.
ts - is multiple of the time step
