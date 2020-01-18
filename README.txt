Last Updated: 11/9

** summarizes the submission, including which features have been implemented

Part 1
Description:
    Given a configuration file, ensure that the file contains the keywords
    "RULES:", "TURN:", "BOARD:", "MOVES:" along with valid input for each
    keyword section.

    Results, if file is valid, will return the specified rules, turn, and
    number of pawns/kings of both sides (red/black). If invalid, will return
    the line in which the error occurred and message pointing to what the
    error was.


Implementations
- Flipped Board Configuration Validity
- Normal Board Configuration Validity

Part 2
Description:
	Given a configuration file, do same checks from part 1, along with executing
	the moves given in the config file. Allow compatibility with various switches
	like -m (number of moves to execute) -h (print human readable file) -e (print
	file to be recycled into part 1 and part2).

	Results to stdout shows how many moves in file, the number of moves executed
	and if all moves were legal or if there was an illegal move, then what move
	it was. Also creates whatever files that were passed in as switches.

Implementations
- Flipped Board
- No Capture
- Capture
- Single Jumps
- Multiple Jumps

Part 3
Description:
	Given a game configuration, find all possible moves for a current player up to
	depth d, where d = number of turns looking ahead. For each possible move for
	either player, give each move a score that compounds together for a total score
	at each depth.

	Results are printed to stdout. If moves are provided in the config file, my
	program will exit with a warning (error). The executable can take two switches,
	-d <num> to pick depth/look ahead and -v to print out all sub moves vs move with
	scores at depth = 0 taking into account any depth d.

Implementations
- No Capture
- Single Jumps
- Capture

Not Implemented
- Multiple Jumps

Part 4
Description:
	Given an exchange file, ensure formatting (Part 1) and then render a visual
  (Termbox)of the checkerboard with a list of moves. Allow users to interact
	with the list of moves (edit, save, move, exit). Moves are color coded by
	if they are valid, invalid, or unknown. The board shows the location of pieces
	of the move BEFORE the current selected move. Move index and file name are listed
	at the top of the Termbox.

Implementations
- README file
- DEVELOPERS file
- working Makefile
- info executable
- change executable
- checkerboard display
- list of moves display
- hotkeys display
- moving cursor
- scrolling
- multiple jumps*
- forced capture
- ability to change or appendicitis's a move**
- ability to save edits***

* all backend logic works for multiple jumps (ie. the checkerboard
	will render multiple jumps longer than 4 positions, but the
	list of moves won't show more than the first 4 of the
  positions for that move. If more than 4 positions exist
  for the move, a `..` will follow the last position.)

** you can add as many positions to a move as you want, though only
	 the first 9 of them will show up on the last line of the
   screen and upon saving will default to the above scenario

*** bug where saving a move doesn't update the color coding of the moves
    correctly on the VM (works on my Mac), but the board still registers
    the location of the (if any) invalid move and if you close the file after saving
    and open it back up, the color coding will work properly.
