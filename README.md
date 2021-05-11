# Assetto Corsa Companion


It is a Qt Application capable of displaying real time racing sim telemetry data. 

## Motivation behind this project
If you are someone like me , who got really into sim racing during the lockdown then you must be familar the pain of not being able to put out consistent lap times. This tool is aimed to solve that problem. By being able to visualize your braking zones and speed in crucial sectors, you will become more consistent and a better driver in races. This is very much a work in progress, and any feedback will be greatly appreciated! 
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

 

## License
[MIT](https://choosealicense.com/licenses/mit/)