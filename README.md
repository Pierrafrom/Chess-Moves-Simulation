# Chess Moves Simulation

## Description

This project simulates the possible moves of various chess pieces on a standard 8x8 chessboard. The simulation takes into account the unique movement rules for each chess piece, such as pawns, rooks, knights, bishops, queens, and kings.

## Features

- **Initialize Chessboard**: The chessboard is initialized with `*` characters, indicating empty squares.
- **Display Chessboard**: The current state of the chessboard can be printed to the console.
- **Set Piece**: Place a specific chess piece on the board at a given position.
- **Possible Movements**: Determine the possible moves for a given chess piece from its current position.
  - **Pawn**: Takes into account the pawn's unique two-square initial move and its forward movement.
  - **Rook**: Can move horizontally or vertically across the board.
  - **Knight**: Moves in an "L" shape.
  - **Bishop**: Moves diagonally.
  - **Queen**: Combines the capabilities of a rook and a bishop.
  - **King**: Can move one square in any direction.

## How to Run

1. Compile the `main.c` file:
   ```
   gcc main.c -o chess_simulation
   ```

2. Execute the compiled program:
   ```
   ./chess_simulation
   ```

Upon execution, the program initializes a chessboard, places a black pawn at position (1,1), calculates its possible moves, and then displays the chessboard with the possible moves marked.

## Contributing

Contributions are welcome! Please ensure that any changes made are consistent with the existing code structure and style.

## License

This project is open-source. Feel free to use, modify, and distribute the code as you see fit.
