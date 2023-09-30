# Sudoku
Code for playing Sudoku, with an early implementation of a Sudoku Solver, for when I'm simply unable to solve my own sudokus😖. Here one can fill in the given digits of a Sudoku, 
press the "fix" button to make sure they can't be changed, and then fill in the remaining digits. Pressing "check?" will give feedback on whether the solution satisfies the rules
of Sudoku, and "Solve?" will trigger a stochastic algorithm for solving the sudoku, given that the board is not completely filled already. The algorithm is presented in the following 
article: https://www.mn.uio.no/math/english/research/projects/focustat/the-focustat-blog%21/sudokustory.html . The algorithm now appears to get stuck in some minimum, and I'll
hopefully find time sometime soon to figure out why this happens and fix this #fingerscrossed.

The graphical parts are built using code from the library in the class TDT4102 at NTNU.
