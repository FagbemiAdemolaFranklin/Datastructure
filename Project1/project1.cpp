#include <iostream>
#include <iomanip>
#include <string>
#include <ctype.h>
#include <cstdlib>
#include <time.h>
#include <fstream>

using namespace std;

int chosen_option;

class Game {
    
    char game_array[9];
    int nop, location_on_game_array; // nop means number of plays
    char player;
    public:
        Game();
        Game(char );
        char checkTable();
        void showTable();
        void countTable();
        void countPlays();
        void playGame(char, int);
        friend void gameMenu();
        friend void execute_option(int);
        friend void execute_option_one();
        friend void execute_option_two();

};

void execute_option(int a){ // a is just an argument for the function
    
    switch (a)
    {
    case 1:
        execute_option_one();
        break;
    case 2:
        execute_option_two();
        break;
    case 3:

        break;
    case 4:

        break;
    case 5:

        break;
    
    default:
        cout << "Choose a valid option." <<endl;
        gameMenu();
        break;
    }
}

void execute_option_one(){
    ofstream file_opener;
    file_opener.open("backup.txt");
    if(!file_opener.is_open()){
        cout << "Error finding specified file"<<endl;
    }else{
        
    }
    Game game;
    game.showTable();
    srand(time(0));
    game.playGame('X', rand()%10);
}

void execute_option_two(){
    Game game2;
    cout << "Choose who starts the game" <<endl;
    cout << "1 - You";
    cout << "2 - Computer";
    game2.showTable();
    cout << "Enter your symbol and a number between 0-9 starting from the top-left corner horizontally."<<endl;
    cout <<"Specified format : X9"<<endl;
    cin >> game2.player>>game2.location_on_game_array;
    game2.playGame(game2.player, game2.location_on_game_array);
}

void gameMenu(){ // Lists the options available to the user;
    cout << "Tic Toe Toe." << endl;
    cout << "Menu:" << endl;
    cout <<"Please choose any of the following "<<endl;
    cout << "1- Start or Continue game"<<endl;
    cout << "2- Choose who plays first" <<endl;
    cout << "3- Difficulty"<<endl;
    cout << "4- Pause game"<<endl;
    cout << "5- Statistics"<<endl;
    cout << "6- Exit"<<endl;
    cin >> chosen_option;
    execute_option(chosen_option);
}

void Game::playGame(char C, int n) {
    /*C is the current players chosen alphabet(X or O) 
    and n is the index on the board intended to play.*/
    
    if(C != 'X' || C != 'O'){
        cout <<"Please input a valid alphabet" <<endl;
    }else if(n>9){
        cout <<"Input a number between 1-9" <<endl;
    }else if(game_array[n] != ' '){
        cout << "The chosen location is occupied, choose another." << endl;
    }else{
        game_array[n] = C ; 
    }
    countPlays();
    cout << "0 - Pause or Exit to Menu" << endl;
}
void Game::countPlays() {
    nop>=6?checkTable():main();
}
char Game::checkTable(){ 
    // statements to check the equality in the table in case there is a winner 
    if(game_array[0] == game_array[1] && game_array[1] == game_array[2]){
        return game_array[0];
    }else if(game_array[3] == game_array[4] && game_array[4] == game_array[5]){
        return game_array[3];
    }else if(game_array[6] == game_array[7] && game_array[7] == game_array[8]){
        return game_array[6];
    }else if(game_array[0] == game_array[3] && game_array[3] == game_array[6]){
        return game_array[0];
    }else if(game_array[1] == game_array[4] && game_array[4] == game_array[7]){
        return game_array[1];
    }else if(game_array[2] == game_array[5] && game_array[5] == game_array[8]){
        return game_array[2];
    }else if(game_array[0] == game_array[4] && game_array[4] == game_array[7]){
        return game_array[0];
    }else if(game_array[2] == game_array[4] && game_array[4] == game_array[6]){
        return game_array[2];
    }else{
        return 'N'; //N stands for no winner
    }
}

void Game::showTable(){
    int array_size = (sizeof(game_array)/sizeof(char)) - 1;
    for(int i=0; i<=array_size; i++){
        cout <<left << setw(20) <<setfill(' ') << game_array[i] << endl;
    }
}
int main(){

    
    return 0;
}