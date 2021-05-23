<h1><img src="https://github.com/eerick1997/vNCASimulator/blob/72e7c3d97f79d0696684a508712bfc53bfbd02de/res/img/logo.jpg" alt="vNCASimulator" width="48" height="48"/>vNCASimulator</h1>

The name of the program stands for "von Neumann Cellular Automata Simulator". It was developed by using the C++ programming language and the QT framework with the OOP (Object Oriented Programming) paradigm. This simulator is only a tool for a research done on this type of Cellular Automata.

## Objective
Nowadays, Cellular Automata (CA) of the von Neumann type have not been studied in depth, so there is no classification process that allows making groups using the characteristics of this particular type of CA.

To solve this problem, it is proposed to perform different explorations of the rules on two-dimensional CAs, in order to analyze patterns and behaviors according to the initial conditions, as well as to obtain the polynomial of each rule. With the idea of facilitating the classification of the rules obtained, we developed a system that allows modifying different characteristics of a CA and observing the simulation in real time, obtaining the polynomial and classifying each fixed point in a multiplatform environment, i.e. this software runs on different operating systems such as Linux, Mac OS and Windows.

If you are interested about this investigation you can find the complete report [here](../vNCASimulator/doc/vNCASimulatorDocumentation.pdf). Aditionally, [here](../vNCASimulator/doc/vNCASimulatorManual.pdf) you have a user manual about the developed simulator. The information is only available in Spanish at this time.

## Features
The current version of this program allows to:

- Set up an evolution rule 
- Modify the initial conditions of the CA 
- Choose between a semi-totalistic rule or a complete totalistic rule 
- Display in real time the simulation of the evolution space
- Display in real time the current population and Shannon's entropy 
- Calculate the polynomial of each rule 
- Classify each fixed point of the polynomial 
- Make a 3D projection of the evolution space 
- Export and import binary files that contains the state of an specific simulation
- Generate a random evolution space
- Generate a random complete totalistic rule 
- Choose between a Von Neumann or Moore neighboor to evaluate the CA 
- And more...
## Future work
- [ ] Change the current algorithm to clasify the fixed points in order to get a better precision 
- [ ] Analyse more rules
- [ ] Implement different types of entrophy 
- [ ] Improve the current color gradient 

### Fix bugs
- [ ] Some times the program calculates two generations at the same time and the program does not correctly display the current generation.

## Installation (repository cloning)
```bash
git clone https://github.com/eerick1997/vNCASimulator/
```

## Usage and development
There is a step-by-step guide for each operating system to run/develop the program. Please follow the corresponding link to read the instructions.
- <a href="https://github.com/eerick1997/vNCASimulator/blob/ad3dc024b3c088fb949d5affab796d7229fcc9c0/doc/WindowsUsers.md" target="_blank"><img src="https://raw.githubusercontent.com/FortAwesome/Font-Awesome/master/svgs/brands/windows.svg" alt="windows" width="16" height="16"/>Windows</a>
- <a href="https://github.com/eerick1997/vNCASimulator/blob/main/doc/LinuxUsers.md" target="_blank"><img src="https://raw.githubusercontent.com/FortAwesome/Font-Awesome/master/svgs/brands/linux.svg" alt="linux" width="16" height="16"/>Linux</a> 
- <a href="https://github.com/eerick1997/vNCASimulator/blob/92918579a7c3b2fc91f45f32299fa7e33152bb40/doc/MacOSUsers.md" target="_blank"><img src="https://raw.githubusercontent.com/FortAwesome/Font-Awesome/master/svgs/brands/apple.svg"  alt="macOS" width="16" height="16"/>macOS</a>

There is also a user-manual which applies for the 3 operating systems mentioned above. You can find it [here](https://github.com/eerick1997/vNCASimulator/blob/6f6c4e8e7c765411ed5a7d3192e1c02ec3af637b/doc/vNCASimulatorManual.pdf).

## Languages and Tools
- [C++](http://www.cplusplus.com/)
- [QT Framework](https://www.qt.io/)

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Versioning
The vNCASimulator will be mantained under the Semantic Versioning guidelines as much as possible. Releases will be numbered with the following format:
`<major>.<minor>.<patch>`

For more information on SemVer, please visit [http://semver.org](http://semver.org).

This is a program that includes many file types and technologies. Therefore, we deviate from the SemVer standard with the following versioning rules:

* A **major** version when we have developed a completely new process, which will be previously defined in the BPMN diagram,
* a **minor** version when we have added functionality in a backward compatible way in any of the sub-processes, and
* a **patch** version when we have made backward compatible bug fixes.

## License [![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://github.com/eerick1997/vNCASimulator/blob/deb8f0ecfe75fb25988eda5b7d30d783680c5a9e/LICENSE)
You can checkout the full license [here](https://github.com/eerick1997/vNCASimulator/blob/deb8f0ecfe75fb25988eda5b7d30d783680c5a9e/LICENSE).
The vNCASimulator code is licensed under the terms of the [GPL license](https://github.com/eerick1997/vNCASimulator/blob/deb8f0ecfe75fb25988eda5b7d30d783680c5a9e/LICENSE).

## Attribution
In order to make the development of this system possible, we used icons and tools whose authors and works are mentioned below.
### Development
- [QT Framework](https://www.qt.io/).

### Design (icons)
- Icons used in the program were made by [Kiranshastry](https://www.flaticon.com/authors/kiranshastry) from [Flaticon](https://www.flaticon.com/).
- Icons used in this repository were made by [Fontawesome](https://github.com/FortAwesome/Font-Awesome). CC BY 4.0 License.

## Team
* [eerick1997](https://github.com/eerick1997/)
* [aesquivelv](https://github.com/aesquivelv/)
* [lalo1017](https://github.com/lalo1017/)
