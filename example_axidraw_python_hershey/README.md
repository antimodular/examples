# How to send plotting commands to Axidraw plotter via Python from inside Openframeworks


![](https://github.com/antimodular/examples/blob/master/example_axidraw_python_hershey/images/appInUse.png)
![](https://github.com/antimodular/examples/blob/master/example_axidraw_python_hershey/images/plotResult.jpg)

Using ` Py_Initialize();`  , `PyRun_SimpleString(python_str.c_str());` and `Py_Finalize();` we can utilize the [Axidraw python API](https://axidraw.com/doc/py_api/#functions-interactive) to plot any path from sinde [Openframeworks](https://openframeworks.cc/)

## Installation
- to make python 3 with axidraw work inside OF
- install python3 on macos
- install axidraw with pip3
- find install python.framework at Library/Frameworks/Python.framework
- in xcode got to targets -> build phases -> link binary libraries -> + sign -> add other -> now navigate to the framework as shown in the above line

## Screenshots
![Link to Python binary](https://github.com/antimodular/examples/blob/master/example_axidraw_python_hershey/images/linkTo_python.png)
