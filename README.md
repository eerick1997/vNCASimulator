# vNCASimulator

## Objective
Nowadays the Cellular Automata (CA) of Von Neumann type has not been studied in depth, that is why does not exist a classification process that allows make groups using the characteristics of this particular type of CA.

To solve this problem we propose to make different explorations of the rules on bidimensional CA, in order to analyse patterns and behaviors according to the initial conditions, as well as obtaining the polynomial of each rule. With the idea to make easier to classify the rules obtained we developed a system that allows modify different characteristics of a CA and watch the simulation in real time, get the polynomial and classify each fixed point in a multiplatform environment it means that this software runs in different operative systems such as Linux, Mac OS and Windows.

If you are interested about this investigation you can find all about it [here](../vNCASimulator/doc/vNCASimulatorDocumentation.pdf), aditionally [here](../vNCASimulator/doc/vNCASimulatorManual.pdf) you have a user manual about the developed system, unfortunaly for now all this information it is only in Spanish.

## Features

The current version of this program allows:

- Stablish a evolution rule 
- Modify the initial condition of a CA 
- Choose between a semi- totalistic rule or complete totalistic rule 
- Display in real time the simulation of the evolution space 
- Display in real time the current population and Shannon's entropy 
- Calculate the polynomial of each rule 
- Classify each fixed of the polynomial 
- Make a 3D projection of the CA 
- Export and import binary files that contains the state of an specific simulation 
- Generate a random evolution space 
- Generate a random complete totalistic rule 
- Choose between a Von Neumann or Moore neighboor to evaluate the CA 

## Bugs

- Some times the program calculates two generations at the same time and the program does not display correctly the current generation 

## Future work

- Change the current algorithm to clasify the fixed points in order to get a better precision 
- Analyse more rules 
- Implement different types of entrophy 
- Improve the current color gradient 

## How to execute the program
### Windows
The first step is to download the corresponding [files]()
