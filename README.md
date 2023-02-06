# missile_navigation_assignment

The program is a simulation of a rocket chasing targets.<br>
**Arguments**:<br>
supply 1 input configuration file in the following format:<br>
t // time step<br>
ts // missile's start time<br>
n // number of objects<br>
x0 y0 ang0 v0 x1 y1 ang1 v1.....xn yn angn vn // start points, direction(deg) and speed [m/s] for each objects<br>
xm ym vm aMax // missile launch point, missile velocity [m/s], max lateral acceleration<br>
dk // distance from object where the object is marked as destroyed<br>


**The program will output two files:**<br>
1. history.txt - indicates event like destroying target and find new target<br>
2. events.txt -  indicates locations and statuses of all the objects during the run, 
also indicates missile location and lateral acceleration.<br>


**assumptions:**<br>
vm >> vm // the missile is faster then all objects<br>
the objects are place infront of the missile.<br>
ts - is multiple of the time step<br>
