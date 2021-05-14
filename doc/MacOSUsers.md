<h1><img src="https://github.com/eerick1997/vNCASimulator/blob/72e7c3d97f79d0696684a508712bfc53bfbd02de/res/img/logo.jpg" alt="vNCASimulator" width="48" height="48"/>vNCASimulator</h1>

Before following the instructions, you must first clone this repository by typing the command shown below in your terminal (assuming you have git installed) or by copying the link into your git client.
```bash
git clone https://github.com/eerick1997/vNCASimulator/
```

## <img src="https://raw.githubusercontent.com/FortAwesome/Font-Awesome/master/svgs/brands/apple.svg" alt="macOS" width="16" height="16"/>MacOS users

These instructions apply for macOS users.

1. Locate the path were you have cloned the repository.
2. Find and move into the following directory:

> [/exe/macOS/vNCASimulator/](../vNCASimulator/exe/macOS/debug/)

3. Execute the file:

> [vNCASimulator.app](../vNCASimulator/exe/macOS/vNCASimulator/vNCASimulator.app)

1. You will be able to see the Settings window as shown below.

![Settings](https://github.com/eerick1997/vNCASimulator/blob/64b1404f7fcdd3fa331618bf672721e8c3173486/res/screens/macOS/Settings.jpg)

For more details on how to use the simulator, there is a user-manual [here](https://github.com/eerick1997/vNCASimulator/blob/6f6c4e8e7c765411ed5a7d3192e1c02ec3af637b/doc/vNCASimulatorManual.pdf).

## <img src="https://raw.githubusercontent.com/FortAwesome/Font-Awesome/master/svgs/brands/apple.svg" alt="macOS" width="16" height="16"/>C++ developers

These instructions apply for C++ developers who use macOS.

1. First, you need to download and install [QT Creator](https://www.qt.io/).

2. Add the Qt charts library by opening the Maintenance tool of QT. This tool must be in the directory where you have installed the IDE.

![Welcome](https://github.com/eerick1997/vNCASimulator/blob/64b1404f7fcdd3fa331618bf672721e8c3173486/res/screens/macOS/maintanenceToolLogin.png)

3. Once that you have logged in, you will see the next screen. There you must choose the first option to add the required dependencies.

![Setup-Qt](https://github.com/eerick1997/vNCASimulator/blob/64b1404f7fcdd3fa331618bf672721e8c3173486/res/screens/macOS/maintanenceToolChoose.png)

4. Search for the QT version installed in your computer.

![Select components](https://github.com/eerick1997/vNCASimulator/blob/64b1404f7fcdd3fa331618bf672721e8c3173486/res/screens/macOS/maintanenceToolChooseLibraries.png)

5. Add the library **Qt Charts**. It will allow you to see in a graph the entropy, the population and the CA polynomial.

![Component](https://github.com/eerick1997/vNCASimulator/blob/64b1404f7fcdd3fa331618bf672721e8c3173486/res/screens/macOS/maintanenceToolChooseLibrariesCharts.png)

6. Press *Next* and you will see the next screen.

![Update](https://github.com/eerick1997/vNCASimulator/blob/64b1404f7fcdd3fa331618bf672721e8c3173486/res/screens/macOS/maintanenceToolStartDownload.png)

7. Press *Update* and wait until the installation finishes.

![Wait](https://github.com/eerick1997/vNCASimulator/blob/64b1404f7fcdd3fa331618bf672721e8c3173486/res/screens/macOS/maintanenceToolWait.png)

8. Lastly, press *Finish*.

![Finish](https://github.com/eerick1997/vNCASimulator/blob/64b1404f7fcdd3fa331618bf672721e8c3173486/res/screens/macOS/maintanenceToolFinish.png)

Now you are able to correctly open the project in QT Creator and develop/contribute to the project.

For more details on how the simulator was developed, there is a technical-manual [here](https://github.com/eerick1997/vNCASimulator/blob/6f6c4e8e7c765411ed5a7d3192e1c02ec3af637b/doc/vNCASimulatorDocumentation.pdf).