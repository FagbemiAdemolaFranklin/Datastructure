#include <iostream>
#include <iomanip>
#include <string>
#include <ctype.h>
#include <cstdlib>
#include <time.h>
#include <fstream>

using namespace std;

int chosen_option;

class Game{
    char game_array[9];
    int nop, location_on_game_array, starter, array_size = (sizeof(game_array)/sizeof(char)) - 1; // nop means number of plays
    char players_sign, computers_sign, human, computer, inputed_character;
    unsigned long stats, victories, defeats, ties;
    string exit_confirmation, difficulty;

    public:
        Game(){
            
        };
        Game(char );
        char checkTable();
        void showTable();
        void countTable();
        void countPlays();
        void playGame();
        // void playGame(char, int);
        void gameMenu();
        void execute_option(int);
        void execute_option_one(),execute_option_two();
        void execute_option_three();
        void treat_errors();
        void restart_game();
        void checkAndComputeStats();
        int saveGame();
        void exit();

};

void Game::execute_option(int a){ // a is just an argument for the function
    
    switch (a)
    {
    case 1:
        execute_option_one();
        break;
    case 2:
        execute_option_two();
        break;
    case 3:
        execute_option_three();
        break;
    case 4:

        break;
    case 5:

        break;
    case 6:
        exit();
        break;
    default:
        cout << "Choose a valid option." <<endl;
        gameMenu();
        break;
    }
}

void Game::execute_option_one(){
    ofstream file_opener;
    file_opener.open("backup.txt");
    if(!file_opener.is_open()){
        cout << "Error finding specified file"<<endl;
    }else{
        
    }
    this->showTable();
    this->playGame();
}

void Game::execute_option_two(){
    cout << "Choose who starts the game" <<endl;
    cout << "1 - You ";
    cout << " 2 - Computer"<<endl<<flush;
    cin >> this->starter;
    cout << starter;
    cout <<"Sucess";
    if(this->starter == '2'){
        this->showTable();
        computer = 'X';
        human = 'O';
        cout<< "Your symbol is O"<<endl<<flush;
        this->playGame();
    }else if(starter == '1'){
        showTable();
        cout << "Enter your symbol and a number between 0-9 starting from the top-left corner horizontally."<<endl;
        cout <<"Specified format : X9 or O9"<<endl;
        cin >> this->inputed_character>>this->location_on_game_array;
        if(this->inputed_character == 'X' || this->inputed_character == 'O' && this->nop<=9){
            // this->playGame(this->inputed_character, this->location_on_game_array);
            human=inputed_character;
            this->playGame();
        }else{
            cout<< "Please check input value";
        }
        
    }
    
}

void Game::execute_option_three(){
    //You have to input a code here to clear the current game and start a new game.
    cout << "Select difficulty "<<endl;
    cout <<left << setw(20) << setfill(' ')<<"Elementary" <<endl;
    cout <<left << setw(20) << setfill(' ')<<"Basic" <<endl;
    cout <<left << setw(20) << setfill(' ')<<"Medium" <<endl;
    cin >> difficulty; 
    cout << difficulty << " " << "selected" <<endl;
    this->gameMenu();
}

// void execute_option_five(){

// }
void Game::gameMenu(){ // Lists the options available to the user;
    cout << "Tic Tac Toe." << endl;
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

void Game::playGame() {
    /*C is the current players_signs chosen alphabet(X or O) 
    and n is the index on the board intended to play.*/
    cout << "0 - Pause or Exit to Menu" << endl;
    if(this ->computer == ' '){
        human =='X'?computer='O': computer='X';
    }
    srand(time(0));
    cout << "Your turn" <<endl;
    cin >> inputed_character;
    cin >> location_on_game_array;
    if(inputed_character != 'O' && inputed_character != 0){
        cout <<"Please input a valid alphabet" <<endl;
        cout<< "Reminder : Your symbol is O"<<endl <<flush;
        playGame();
    }else if(location_on_game_array>9){
        cout <<"Input a number between 1-9" <<endl<<flush;
        playGame();
    }else if(game_array[location_on_game_array] != ' '){
        cout << "The chosen location is occupied, choose another." << endl<<flush;
        playGame();
    }else if(inputed_character == '0'){
        this->gameMenu();
    }else{
        game_array[location_on_game_array] = human;
        game_array[rand()%10] = computer;
        nop++;
    }
    // countPlays();
    
}
void Game::checkAndComputeStats(){
    if((checkTable() == 'X' && computer == 'X') || (checkTable() == 'O' && computer == 'O')){
        cout << "Computer wins"<<endl;
        victories++;
    }else if((checkTable() == 'X' && human == 'X') || (checkTable() == 'O' && human == 'O')){
        cout << "Human wins"<<endl;
    }else if(checkTable() == 'N'){
        cout << "It's a tie.!!"<<endl;
    }else{
        playGame();
    };
}

// void Game::playGame(char C, int n){
//     if(this->human == ' ' && this ->computer == ' '){
//         inputed_character=human;
//         C=='X'?computer='O':computer='X';
//     }
    
//     if(n>9|| this->human!=inputed_character){
//         cout << "Please check inputed values"<<endl;
//     }else if(game_array[location_on_game_array] != ' '){
//         cout << "The chosen location is occupied, choose another."<<endl;
//     }else{
//         game_array[location_on_game_array] = human;
//         game_array[rand()%10] = computer;
//         nop++;
//         if(checkTable() == 'X'){
//             cout << "Computer wins"<<endl;
//         }else if(checkTable() == 'O'){
//             cout << "Human wins"<<endl;
//         }else if(checkTable() == 'N'){
//             cout << "It's a draw!!"<<endl;
//         }else{
//             cout << "Your Turn"<<endl;
//             cin >> this->inputed_character>>this->location_on_game_array;
//             playGame(inputed_character, location_on_game_array);
//         };
//     }
//     // game_array[n] = C;
// }
// void Game::countPlays() {
//     nop>=6?checkTable():main();
// }
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
    }else if(nop == 9){
        return 'N'; //N stands for no winner
    }
    return 't';
}

void Game::showTable(){
    
    for(int i=0; i<=array_size; i++){
        cout << setw(20) <<setfill('/') << game_array[i] << endl;
    }

    // playGame(players_sign, location_on_game_array);
}

void Game::restart_game(){
    delete this;
    // nop=0;
    // for(int j = 0; j<=array_size; j++){
    //     game_array[j] = ' ';
    // }
}

void Game::exit(){
    cout << "Is the game over?. Are you sure that you wan to exit ? Yes or No" <<endl;
    cin >> exit_confirmation;
    if(exit_confirmation == "Yes") {
        this->restart_game();
    }else if(exit_confirmation == "No"){
        this->playGame();
    }else{
        cout << "Please input a valid expression" <<endl;
    }
}

int Game::saveGame(){
    char game_array[9],players_sign, computers_sign, human, computer, inputed_character;
    int nop, location_on_game_array, starter, array_size = (sizeof(game_array)/sizeof(char)) - 1; // nop means number of plays
    unsigned long stats, victories, defeats, ties;
    string exit_confirmation, difficulty;
    ofstream myfile;
    myfile.open("backup.txt");
    if(!myfile.is_open()){
        cout << "Error opening backup file" <<endl;
        return -1;
    }
    myfile.clear();
    myfile.skipws;
    struct Backup{
        char table_backup[9],players_sign_backup, computers_sign_backup, human_backup, computer_backup, inputed_character_backup;
        int nop_backup, location_backup,array_size_backup;
        unsigned long stats_backup, victories_backup, defeats_backup, ties_backup;
        string exit_confirmation_backup, difficulty_backup;
    };
    // myfile.write();
return 0 ;

}
int main(){
    Game game1;
    game1.gameMenu();
    
    return 0;
}