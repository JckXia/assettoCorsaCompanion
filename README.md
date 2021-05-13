# Assetto Corsa Companion


It is a Qt Application capable of displaying real time racing sim telemetry data. 

## Motivation behind this project
If you are someone like me , who got really into sim racing during the lockdown then you must be familar the pain of not being able to put out consistent lap times. This tool is aimed to solve that problem. By being able to visualize your braking zones and speed in crucial sectors, you will become more consistent and a better driver overall. This is very much a work in progress, and any feedback will be greatly appreciated! 
## Installation

Under windows, make sure microsoft visual studio 2019 is installed. Then, using the x86_64 terminal type

```bash
qmake && nmake clean && nmake install
```
To run this application, in the root project run
```bash
cd release && build.exe
```

## Features

![Screenshot (3)](https://user-images.githubusercontent.com/32422811/117744129-121de980-b1d6-11eb-8617-0eba7828185e.png)
Currently support braking pressure, rpm, speed and gear data

## How to use
While the telemetry app is running, start up assetto corsa and start driving. You will see the data points being displayed accordingly.

## Performance (To be improved)
![memoryUsage](https://user-images.githubusercontent.com/32422811/118061152-60f88a00-b362-11eb-8954-05636d4faa91.PNG)
Data recorded using DataDog tracing agent. Running on AMD Ryzen 5 3600 CPU and GTX 1660 GPU 

## License
[MIT](https://choosealicense.com/licenses/mit/)
