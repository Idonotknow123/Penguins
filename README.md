# README

## Player Program Overview

This program implements a player for a strategy game. It has been designed with compatibility in mind to ensure it works seamlessly across various platforms and environments. The source files are compiled into an executable using the `gcc` compiler, and the program accepts several runtime parameters to control its behavior.

## Compilation

To compile the program, use the following command:

```bash
gcc main.c -lm grid.c play.c -lm print.c valid_check.c -lm autonomous_mode.c unit_test.c autonomous_output.c algorithm.c -o NAME_OF_THE_PLAYER
```

Replace `NAME_OF_THE_PLAYER` with the desired name of the executable, which should match the name of your player.

## Running the Program

To run the compiled executable, use the following format:

```bash
/path/to/NAME_OF_THE_PLAYER(.out or .exe) phase=<placement|movement> [penguins=<int>] input_file=<input_file.txt> output_file=<output_file.txt>
```

### Parameters

- **phase**: Specifies the phase of the game. Must be either:
  - `placement`: Indicates the penguin placement phase. Requires the additional parameter `penguins`.
  - `movement`: Indicates the penguin movement phase. The `penguins` parameter is not required.
- **penguins**: (Only for `placement` phase) Specifies the number of penguins to place on the grid. Must be an integer.
- **input\_file**: Specifies the path to the input file containing the game state.
- **output\_file**: Specifies the path to the output file where the program will write its results.

### Displaying the Player Name

If the program is executed with an additional parameter `=name` (e.g., as the last argument in the command), it will print the name of the player. This name corresponds to the name of the compiled executable.

## Examples

### Placement Phase

```bash
./MyPlayer.out phase=placement penguins=3 input.txt output.txt
```

### Movement Phase

```bash
./MyPlayer.out phase=movement input.txt output.txt
```

### Display Player Name

```bash
./MyPlayer.out name
```

The program will print:

```
MyPlayer
```

## Notes

- Ensure that all required files (`input_file.txt` and `output_file.txt`) are accessible at runtime.
- For `placement` phase, the `penguins` parameter is mandatory.
- If the `name` parameter is provided, no other operation is performed.

## Compatibility

This program has been developed with portability and compatibility in mind. It should work across most systems where `gcc` is available for compilation. If you encounter any compatibility issues, please report them to the development team.
