/*
 Author	 : Nicholas Lau, Makara
 Student # : 000377939,
 Date		 : Nov. 20, 2015 Modified Nov. 22, 2015

 A Tic Tac Toe Game. Shows a TTT board which the player will select from.
 The AI will then choose an empty slot, and the first side to get
 three in a row wins. After, game will prompt to play again.
 Using function decomposition, all statements and operations hare handled
 in specialized functions, keeping main as clear as possible.
*/


#include <iostream>
#include <climits>
#include <limits>

using namespace std;


/* Constants for TTT game board symbols. */
const char EMPTY = ' ';
const char USER = 'O';
const char COMPUTER = 'X';


void initialize_board(char array[]);
void display_board(char array[]);
int computer(char array[]);
int player(char array[]);
void instructions();
void checkthree_inrow(char array[], int&);
void play_again(bool&, int&, int&, char&);
void draw_check(int&, const int, int&);
void TTT_controller(char array[], char&);
void endgamemessage(int);
void get_inputs(int&, int, char array[]);



const int boardsize = 9;

/*****************************************************
*****************************************************
****  Test driver / Test oracle for functions *******
****	DO NOT CHANGE THE CODE IN THE MAIN FUNCTION!!!**
*****************************************************
*****************************************************/
int main()
{
    char TTT_board[boardsize];
    bool quit = 0;
    int gamewon = 0; //endgame status
    int numberofmoves = 0;
    char playside = USER;
    int instructionsboard[boardsize];
    bool is_playingboard_or_instructions = false;

    cout << "Welcome to Tic Tac Toe" << endl;


    do
    {
        numberofmoves = 0;
        initialize_board(TTT_board);
        //display_board(TTT_board);
        while (gamewon == 0)
        {
            instructions();
            display_board(TTT_board);
            TTT_controller(TTT_board, playside); // Calls Player or Computer Functions
            checkthree_inrow(TTT_board, gamewon);
            draw_check(numberofmoves, boardsize, gamewon);
            endgamemessage(gamewon);
            display_board(TTT_board);

        }
        play_again(quit, gamewon, numberofmoves, playside);

    }
    while (quit == 0);

    cout << "Thanks for Playing! Closing..." << endl;

	return 0;
}


/* This function resets the board for playing.
Input: Array of TTT_board
Output: A blank array board.
*/
void initialize_board(char array[])
{
    int currentelement;
    char character;

    for (currentelement = 0; currentelement < boardsize; currentelement++)
    {
        array[currentelement] = ' ';
    }
    return;
}
 /* Controls which side is playing and calls upon the appropriate function. Allows for simpified and consolidated main function instead of repeating the function for both user and AI.
 Also switches the playing side so the other team can make a move.
 Input: The TTT_board array which is passed on to either the user or the comptuer.
 Output: Playside (who goes next) and the choice of slot on the TTT_board from their funciton.
 */
void TTT_controller(char array[], char& playside)
{
    if (playside == USER)
    {
        player(array);
        playside = COMPUTER;
    }
    else
    {
        computer(array);
        playside = USER;
    }
}


/* Displays the TTT_board in play.
Input: Array TTT_board from main
Output: A tic tac toe board is shown on screen.
*/
void display_board(char array[])
{
    cout << endl;

    //if (is_playingboard_or_instructions == false)
    {
        cout << " " << array[0]  << " | " << array[1] << " | " <<
        array[2] << " \n";
        cout << "___|___|___\n";
        cout << " " << array[3] << " | " << array[4] << " | " <<
        array[5] << " \n";
        cout << "___|___|___\n";
        cout << " " << array[6] << " | " << array[7] << " | " <<
        array[8] << " \n";
        cout << "   |   |   \n";
    }
    /*
    else if (is_playingboard_or_instructions == true)
    {
        cout << " " << instructionsboard[0]  << " | " << instructionsboard[1] << " | " <<
        instructionsboard[2] << " \n";
        cout << "___|___|___\n";
        cout << " " << instructionsboard[3] << " | " << instructionsboard[4] << " | " <<
        instructionsboard[5] << " \n";
        cout << "___|___|___\n";
        cout << " " << instructionsboard[6] << " | " << instructionsboard[7] << " | " <<
        instructionsboard[8] << " \n";
        cout << "   |   |   \n";
    }
*/


    //display_one_row(array[0],array[1],array[2]);
    //display_horizontal_line();
	//display_one_row(array[3],array[4],array[5]);
	//display_horizontal_line();
	//display_one_row(array[6],array[7],array[8]);

}

/* The computer AI which works by finding and then choosing the first available slot. The computer is X.
INput: The array TTT_board from main.
Output: The slot for which it chooses is switched to X.
*/
int computer(char array[])
{
    int currentelement = 0;

    for (currentelement = 0; currentelement < boardsize; currentelement++)
    {
        if (array[currentelement] == ' ')
        {
            array[currentelement] = 'X';
            break;
        }
    }
    return 0;
}

/* THe player controls. It first gets an input, then identifies if it is a valid integer input,
and then sees if it is an empty slot. If these tests fail, it will ask for a new input. The player is O.
INput: The TTT_board array and a user input for the slot that the player wants.
Output: The slot for which the player wants is occupied with an O.
*/
int player(char array[])
{
    int currentelement = 0;
    int sourceinput = 1;
    cout << "Input which slot you want" << endl;

    get_inputs(currentelement, sourceinput, array);


    array[currentelement] = 'O';
    //display_board(array);

}

/* Instructions and sample TTT board for referencing choice. Tells the player how to play and which numbers/selections correspond to whichever slot on the board.
Input: Boardsize constant from global.
OutPut: How to play and a sample TTT board with numbers to reference.
*/
void instructions()
{
    //char instructionboard[boardsize];
    //int array[boardsize]; // blank
    int currentelement;
    char number_in_board = 0;
    //bool is_playingboard_or_instructions = false;
    char instructionboard[boardsize] = {'0','1','2','3','4','5','6','7','8'};

    /*
    for (currentelement = 0, number_in_board = 0; currentelement < boardsize; currentelement++, number_in_board = (int) number_in_board + 1)
        {
            instructionboard[currentelement] = currentelement;
            //cout << instructionboard[currentelement]  << currentelement << endl;
            //cout << instructionboard[currentelement] << endl;
        }

    cout << "Score three letters in a row to win." << endl;
    cout << "Enter a number from the corresponding table below to select that slot." << endl;
    */
    display_board(instructionboard);

/*
    cout << " " << instructionboard[0]  << " | " << instructionboard[1] << " | " <<
    instructionboard[2] << " \n";
    cout << "___|___|___\n";
    cout << " " << instructionboard[3] << " | " << instructionboard[4] << " | " <<
    instructionboard[5] << " \n";
    cout << "___|___|___\n";
    cout << " " << instructionboard[6] << " | " << instructionboard[7] << " | " <<
    instructionboard[8] << " \n";
    cout << "   |   |   \n";
    */


}

/* Checks if a three in a row is achieved. THen checks which side won (computer or player).
Input: Array TTT_board, boardsize constant from global, gamewon (identifies whether the game has ended) by reference
OutPut: Outputs who wins and returns that the game has ended (gamewon).
*/


void checkthree_inrow(char array[], int& gamewon)
{
    cout << "Checking THree in row" << endl;


    /** Player Check **/
    if (array[0] == 'O' && array[1] == 'O' && array[2] == 'O') // top across
    {
            gamewon = 1;
            return;



        //testvalue = array[0];
        //checkwinner(array, boardsize, gamewon, testvalue);
    }
    else if (array[3] == 'O' && array[4] == 'O' && array[5] == 'O') // middle across
    {
            gamewon = 1;
            return;


        //testvalue = array[3];
        //checkwinner(array, boardsize, gamewon, testvalue);
    }
    else if (array[6] == 'O' && array[7] == 'O' && array[8] == 'O') // bottom across
    {
            gamewon = 1;
            return;


        //testvalue = array[6];
        //checkwinner(array, boardsize, gamewon, testvalue);
    }
    else if (array[0] == 'O' && array[3] == 'O' && array[6] == 'O') // left column

    {
            gamewon = 1;
            return;


        //testvalue = array[0];
        //checkwinner(array, boardsize, gamewon, testvalue);
    }
    else if (array[1] == 'O' && array[4] == 'O' && array[7] == 'O') // middle column

    {
            gamewon = 1;
            return;


       // testvalue = array[1];
        //checkwinner(array, boardsize, gamewon, testvalue);
    }
    else if (array[2] == 'O' && array[5] == 'O' && array[8] == 'O') // right column

    {
            gamewon = 1;
            return;

        //testvalue = array[2];
        //checkwinner(array, boardsize, gamewon, testvalue);
    }
    else if (array[0] == 'O' && array[4] == 'O' && array[8] == 'O') // diagonal to right (+ slope)

    {
            gamewon = 1;
            return;

        //testvalue = array[0];
        //checkwinner(array, boardsize, gamewon, testvalue);
    }
    else if (array[6] == 'O' && array[4] == 'O' && array[2] == 'O') // diagonal to left (- slope)

    {
            gamewon = 1;
            return;

        //testvalue = array[2];
        //checkwinner(array, boardsize, gamewon, testvalue);
    }

    /** COmputer Check **/
    if (array[0] == 'X' && array[1] == 'X' && array[2] == 'X') // top across
    {
            gamewon = 2;
            return;



        //testvalue = array[0];
        //checkwinner(array, boardsize, gamewon, testvalue);
    }
    else if (array[3] == 'X' && array[4] == 'X' && array[5] == 'X') // middle across
    {
            gamewon = 2;
            return;


        //testvalue = array[3];
        //checkwinner(array, boardsize, gamewon, testvalue);
    }
    else if (array[6] == 'X' && array[7] == 'X' && array[8] == 'X') // bottom across
    {
            gamewon = 2;
            return;


        //testvalue = array[6];
        //checkwinner(array, boardsize, gamewon, testvalue);
    }
    else if (array[0] == 'X' && array[3] == 'X' && array[6] == 'X') // left column

    {
            gamewon = 2;
            return;


        //testvalue = array[0];
        //checkwinner(array, boardsize, gamewon, testvalue);
    }
    else if (array[1] == 'X' && array[4] == 'X' && array[7] == 'X') // middle column

    {
            gamewon = 2;
            return;


       // testvalue = array[1];
        //checkwinner(array, boardsize, gamewon, testvalue);
    }
    else if (array[2] == 'X' && array[5] == 'X' && array[8] == 'X') // right column

    {
            gamewon = 2;
            return;

        //testvalue = array[2];
        //checkwinner(array, boardsize, gamewon, testvalue);
    }
    else if (array[0] == 'X' && array[4] == 'X' && array[8] == 'X') // diagonal to right (+ slope)

    {
            gamewon = 2;
            return;

        //testvalue = array[0];
        //checkwinner(array, boardsize, gamewon, testvalue);
    }
    else if (array[6] == 'X' && array[4] == 'X' && array[2] == 'X') // diagonal to left (- slope)

    {
            gamewon = 2;
            return;

        //testvalue = array[2];
        //checkwinner(array, boardsize, gamewon, testvalue);
    }
    cout << "gamewon = " << gamewon<< endl;

    return;
}

/* Checks if player wants to play again. 1 for yes, 0 for no.
Input: Whether player wants play again or not (1 or 0). quit (variable that enforces loop to play again) by reference, gamewon(boolean that checks whether the game has ended).
Numberofmoves (counter for function draw to see if a draw is reached)
Output: Quit is returned, which will either end the game loop (quit == true) and quit the game, or will start a new round (quit == false)
The playside user which will reset to the user so they can go first in the next round.
Gamewon is returned as false to start a new round if player wants to play again.
Numberofmoves returns 0 to reset counter for draw.
Playside is returned to the user.
*/
void play_again(bool& quit, int& gamewon, int& numberofmoves, char& playside)
{
    int response;
    char array_blanks[1]; // Blank array.
    int sourceinput = 2;
    cout << "Do you want to play again? 1 for Yes, 0 for No" << endl;
    get_inputs(response, sourceinput, array_blanks);

    if (response == 0)
    {
        quit = 1;
        return;
    }
    else if (response == 1)
    {
        gamewon = 0;
        numberofmoves = 0;
        playside = USER;
        return;
    }
    //cin >> response;

}
/* CHeck if a draw is reached by using a counter.
Input: Numberofmoves (counter), boardsize constant for the max number of moves, gamewon to return that game has ended
Output: Numberofmoves + 1 if game has not ended. Returns gamewon as true if numberofmoves has reached numberofmoves and boardsize condition (max moves reached/ board filled).
*/
void draw_check(int& numberofmoves, const int boardsize, int& gamewon)
{
    if (numberofmoves < boardsize)
    {
        numberofmoves++;
    }
    else
    {
        gamewon = 3;
    }
}
 /* Tells the player who won or if it is a draw.
 Input: The gamewon status
 Output: The result of who won.
 */
void endgamemessage(int gamewon)
{
    if (gamewon == 1)
    {
        cout << "Player Wins." << endl;
        return;
    }
    else if (gamewon == 2)
    {
        cout << "Computer Wins" << endl;
        return;
    }
    else if (gamewon == 3)
    {
        cout << "Tie. No one wins." << endl;
        return;
    }
    return;
}

/* Gets the input and validates it.
Input: The user input which will be returned to the respective funciton for use. The sourceinput number to identify where it came from and to use the appropriate coniditions, and thne array
to check against the current TTT board in play.
Output: THe user input currentelement
*/
void get_inputs(int& currentelement, int sourceinput, char array[])
{

    if (sourceinput == 1) // player input
    {

        cin.unsetf(ios::skipws);
        while (!(cin >> currentelement) || !(cin.get() == '\n') || (!(currentelement < 9) || !(currentelement >= 0) || !(array[currentelement] == ' ')))
        {
            if (!(currentelement < 9) || !(currentelement >= 0))
            {
                cout << "Not within range of values." << endl;
            }
            else if (!(array[currentelement] == ' '))
            {
                cout << "Slot taken." << endl;
            }
            cout << "Not a valid input. Please reenter." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        return;
    }
    else if (sourceinput == 2) // play again input
    {

        while (!(cin >> currentelement) || !(cin.get() == '\n') || (currentelement > 1) || (currentelement < 0))
        {
            cout << "Not a valid input. Please reenter." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        return;
    }

}
