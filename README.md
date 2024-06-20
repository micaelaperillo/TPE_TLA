[![✗](https://img.shields.io/badge/Release-v1.0.0-ffb600.svg?style=for-the-badge)](https://github.com/micaelaperillo/CAL_9000/releases)

# CAL 9000 Compiler

A compiler based on the cal9k language detailed below.

* Installation
  * [Docker](docs/readme/Docker.md)
  * [Ubuntu](docs/readme/Ubuntu.md)

The compiler is not compatible with Windows, however programs like WSL can compile and execute it.

## Environment

Set the following environment variables to control and configure the behaviour of the application:

|Name|Default|Description|
|-|:-:|-|
|`LOG_IGNORED_LEXEMES`|`true`|When `true`, logs all of the ignored lexemes found with Flex at DEBUGGING level. To remove those logs from the console output set it to `false`.|
|`LOGGING_LEVEL`|`INFORMATION`|The minimum level to log in the console output. From lower to higher, the available levels are: `ALL`, `DEBUGGING`, `INFORMATION`, `WARNING`, `ERROR` and `CRITICAL`.|


# Cellular Automata Language 9000

This project aims to simplify the visual creation of cellular automatas by specifying the following values:
```
automata (A,D,B), grid (X,Y):
     check(M,N);
automatan't

rule:
     prop:property_name = (param1, param2)
rulen't
```

Where:
```
A: Minimum amount of neighbours needed for a cell to stay alive.
D: Minimum amount of neighbours needed for a cell to die of overpopulation.
B: Exact amount of neighbours needed for a cell to be born.

X, Y: Grid size.
M, N: Which cells should be considered neighbours. A value of (1, 1) will check the lower-right adjacent cell, a value of (-1, 1) will check the lower-left neighbour.
```

A list of properties can be found at [Properties](docs/Properties.md).

The output file can be found at out/automata.py. The following dependencies are required to run the program:

```
pip install pygame
pip install numpy
pip install tk
```
After compiling the code (instructions can be found at docs/readme), simply run:

```
python3 out/automata.py
```

# Controls:
Once the simulation is running:

- Left clicking a cell will toggle its state.
- Holding right click and moving your mouse across the grid will let you paint over the cells.
- Space will toggle pause.
  
The cells can only be interacted with while paused.
