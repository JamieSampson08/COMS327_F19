##Below Last Updated: 10/15

** serves as documentation for developers
** include a breakdown of the key data structures used
** a list of source files and what they contain
** a discussion of each function in the source code

# Part 1

## Data Structures
**struct config (as Config)**

- char turn[6] = black/red
- int redPawns = number of red pawns
- int reKings = number of red kings
- int blackPawns = number of black pawns
- int blackKings = number of black kings
- char jumpRule[15] = rule on jumps
- char captureRule[11] = rule on capturing
- bool isFlipped = if board is flipped
- char board[9][9] = layout of board

## Source Files
###config.c

- **void evaluateConfigFile()**
runs the functions to evaluate a config file .

- **bool skipCharacter(char c, int *currentLine, bool skipSpaces, bool skipNewLine)**
Skips comments and white spaces (spaces, new lines)
- **void validateRule(char c, int *currentLine)**
    Evaluates the rule keyword section for proper input

- **void validateTurn(char c, int *currentLine)**
    Evaluates the turn keyword section for proper input

- **void validateBoard(char c, int *currentLine)**
    Evaluates the board keyword section for proper input

- **void validateMoves(char c, int *currentLine)**
    Evaluates the moves keyword section for proper input
- **void printValidConfigInfo()**
    Prints valid config file information


###errors.c

- **void raiseFormattingError(int *lineNumber, char message[]);** .
    Error message for formatting errors

- **void raiseBoardError(int *lineNumber, char correctChar, char foundChar, int row, int col);**
    Error message for board errors

- **void raiseMoveError(int *lineNumber, char correctChar, char foundChar);**
    Error message for move errors

###**helpers.c**

- **int mapLetterToInt(char letter)**
    Maps a letter into its corresponding number

###**info.c**

- **int main()**
    calls function to evaluate config file and print response

# Part 2

## Data Structures
**ADDED struct config (as Config)**

-   Move *moves = array of moves
-   int numMovesProcssed = num of moves processed
-   int numMoves = total num of moves

**struct position (as Position)**

- int row = row coordinate
- int col = col coordinate

**struct files (as Files)**

- FILE ** files = list of files
- int numFiles = num o files in list

**struct moveFlags (as MoveFlags)**

- Files eFiles = files to print to for exchange files
- Files hFiles = files to print to for human files
- int movesToExecute = if value of N is given in switches

**struct move (as Move)**

- Position *positions = list of positions in move
- int numPositions = number of positions in list

## Source Files
###**change.c**

- **int main()**
    calls function to evaluate config file
    calls function to execute move and print response

###**moves.c**

- **bool executeMoves()**
	calls functions to handle executing moves

- **void exportFiles()**
	calls function execute moves, print stdout, and print to files

- **bool validPositionToMove(
	int startRow, int startCol, int endRow, int endCol,
	bool isRed, char* captureMoves, int numPositions);**
	determines if end positions is valid from start position

- **bool jumpPiece(bool isBlackKing, bool isRedKing, char jumpedPiece);**
	handles jumping a piece if possible

- **void exportMove(Move move, FILE *file);**
	prints to file a move

- ** void exportUnprocessedMoves(FILE *file, bool isValid);**
	prints all unprocessed moves to a file

- **void printMoveValidation(bool isValid);**
	prints to stdout final message after execution

- **void exportExchangeBoard(FILE *f);**
	prints exchange board to file

- **void exportExchangeFile(bool isValid);**
	prints details of exchange file

- **void exportHumanFile(bool isValid);**
	prints details of human file

- **void exportHumanBoard(FILE *f);**
	prints human board to file

- **char* findCapturePositions(int startRow, int startCol, bool isRed);**
	determines possible jump options based on start position and turn

- **void copyBoard();**    
  copies setup.board     

- **void revertBoard();**    
  copies boardCopy to setup.board    

###**helpers.c**

- **char mapIntToLetter(int num)**
	takes a row and converts to board letter row

- ** void deallocate()**
	deallocates all memory allocated while processing

- ** char* pieceToTurn (char piece);**
	based on piece, returns turn (red/black)

- **int rowToBoardRow(int row);**
	takes a row and converts to board num row

#Part 3

## Data Structures
**struct boardConfig (as BoardConfig)**   
Takes board related things from Config and splits it off
- char turn[6]   
- int redPawns   
- int redKings   
- int blackPawns   
- int blackKings   
- char board[8][8]   

**struct pm (as PossibleMoves)**   
- Move move   
- BoardConfig Config   
- int score   
- int depthLevel
- bool isJump   

**struct rs (as RankScore)**   
- PossibleMoves* possibleMoves   
- bool isVerbose   
- int depth   
- int numPossibleMoves   
- PossibleMoves* captureMoves;
- int numCaptureMoves;

## Old Function Updates
**Renamed:** "deallocate" -> "deallocateChangeInfo" in helpers.h  
**Deleted:** copyBoard in moves.h   
**Deleted:** revertBoard in moves.h   
**Updated:** jumpPiece - added param bool jump  
**Updated:** findCapturePositions - added param bool jump

## Source Files
###**rankmoves.c**

- **int main()**   
    calls function to evaluate config file
    calls function to calculate rank of moves

###**rank.c**
- **void calculateRank()**
  runner function to call finding moves, setting scores, and printing

- **void findOriginMove(int depth)**  
  recursive function to find possible moves

- **int calculateScore(Possible* possibleMove)**  
  finds the score for that move given its stored config

- **void findPossibleMoves(Position origin, char piece, int depth)**   
  Helper function for recursive function to find possible moves
  uses the isValid function from moves.c

- **void addPossibleMove(Position origin, Position dest, int depth, bool isJump)**   
  adds move to list of possible moves for the given game

- **void handleValidMove(Position origin, Position dest, char piece, bool isRedTurn)**  
  manages moving the piece once determined to be valid move

- **void printPossibleMoves()**    
  prints all moves formatted as directed

- **int maxScore(int* scores, int numScores)**   
  finds the max number out of a list of numbers and returns

- **void printPeriodMove(PossibleMoves possibleMove)**
  formats a move that starts with a `.`

- **void printQuestionMarkMove(PossibleMoves, possibleMove)**
  formats a move that starts with a `?`

- **void printNotPrintedList(int* notPrinted, int numNotPrinted)**   
  given a list of indexs of moves that haven't been printed, print them with their period formatting and score

- **void setDeepestScore()**   
  calculates scores for all moves at maxDepth and sets all others = 100

- **void setNonDeepestScores()**       
  look for scores = 100, calculate their scores based on depth level

- **void alphabetize(Position* piecePositions, int numPositions)**
  alphabetizes the list of positions (col then row)

- **void filterCaptureMoves()**   
  only takes jump moves if there is a single jump move at depth d

###**helpers.c**
- **void deallocateRankMoves()**      
  deallocates memory allocated when running rankmoves executable  

- **bool isRed(char* turn)**      
  given a string turn, convert to boolean if is 'red'

- **int boardRowToRow(int boardRow)**   
  converts a boardRow to a row in the board array

- **void copyBoardConfig(BoardConfig* src, BoardConfig* dest)**   
  copies all info from src to dest (ie. board, piece counts, turn)

- **void changeTurnRed(char* setTurn)**   
  given a string ('black'), switch to 'red'

- **void changeTurnBlack(char* setTurn)**   
  given a string ('red'), switch to 'black'

- **void alternateTurn(char* setTurn)**   
  given a string, determine which function to call to switch to opposite turn

- **bool inIntList(int* list, int size, int value)**   
  finds if value is in list

###**moves.c**
- **validCaptureMove(int row, int col)**  
  checks that end dest within bounds & epmty


# Part 4

## Old Function Updates
**Updated:** setup - added param int invalidMoveIndex  
**Updated:** setup - added param bool showMessages  
**Renamed:** "executeMoves()" -> executeMoves(int index, bool ignoreFlags, bool updateInvalidMove) in moves.h

## Source Files

###**edit.c**

- **int main()**   
    calls function to evaluate config file
    calls function to init termbox & render things
    calls functions to evaluateMoves

###**moves.c**
- **void exportAllMoves(FILE *file)**   
  exports all moves with 4 spaces between pairs followed by new line

###**render.c**
- **void renderBoard()**   
  renders checkerboard with pieces

- **void renderInstructions()**   
  renders hotkey key

- **void highlightMove(int cx, int cy, char* moveText, char type, bool reset)**  
  highlights/ un highlights the move at the given location

- **char getMoveType(int index)**  
  given a index for a move, determine the validity of the move

- **char* getMoveText(Move move, int index)**  
  converts a Move object to its formatted output (ie. a4->b3)

- **void renderMoveLocationFileName(int index)**  
  updates the index counter for what move the cursor is on

- **void renderMoves(int start, int end)**  
  shows a specific range of move indexes (enables scrolling)

- **void clearEditLine()**  
  helper to refresh editing so things are ensured to render correctly

- **void showEditMove(Move move, Position newPos, int editIndex)**  
  shows the current move to save, along with an editable position

- **void clearMoveLines()**    
  clears area of termbox where move list is shown

- **void updateInputFile()**   
  updates the input file with updated moves from appending/changing moves
