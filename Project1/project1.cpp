#include <iostream>
#include <iomanip>
#include <string>
#include <ctype.h>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;


int chosen_option;
char retrieve_decision;
int game_cheat_array_random_number, get_current_player=0;

struct PlayerStats {
    string name;
    int victories;
    int defeats;
    int ties;
};

class Game{
    bool game_state;
    char game_array[9]={'\0','\0','\0','\0','\0','\0','\0','\0','\0'};
    int nop, location_on_game_array, starter, array_size = (sizeof(game_array)/sizeof(char)) - 1; // nop means number of plays
    char players_sign, computers_sign, human, computer, inputed_character;
    unsigned long stats, victories=0, defeats=0, ties=0, computer_victories, human_victories, computer_defeats, human_defeats, computer_ties, human_ties;
    string exit_confirmation, difficulty,current_user;
    int game_cheat_array_row = 8,game_cheat_array_columns=3;
    int game_cheat_array[9][3] = {
                                {0,4,8},
                                {1,0,2},
                                {2,4,6},
                                {3,4,5},
                                {4,1,7},
                                {5,2,8},
                                {6,7,8},
                                {7,4,1},
                                {8,4,0}};

    public:
        Game(){
            
        };
        Game(char );
        char checkTable();
        void showTable();
        void countTable();
        void countPlays();
        void playGame();
        void playGame(char, int);
        void gameMenu();
        int checkRandomNumber();
        void playGreedy();
        void execute_option(int);
        void execute_option_one(),execute_option_two();
        void execute_option_three(),execute_option_four();
        void execute_option_five();
        void treat_errors();
        void restart_game();
        void retrievGame();
        Game startNewGame();
        int readAndWriteStats(string, string, string);
        int loadStats(string, string, string);
        void showStats();
        int save_current_stats();
        void saveCurrentGame();
        void resetStats();
        int saveStats();
        void writeStats(string);
        void checkAndComputeStats();
        void sortAndShowStats();
        int saveGame();
        int showTopPlayers(string, string);
        void exit();
        

};

void Game::sortAndShowStats(){
    int compareVictories(const void *player1, const void *player2) { // compare 2 players
        return (((PlayerStats *)player1)->victories) > (((PlayerStats *)player2)->victories); 
    }

    void imprimeTabela(const char *nameOfTable, PlayerStats tab[], int numElem) {
        cout << " Top 10 players " << endl; 
        for (int i=0; i <= 9; i++) { // percorre todos os elementos da tabela
            cout << "Nome: " << tab[i].name << setw(20) << "Victories" << tab[i].victories << " Defeats" << tab[i].defeats << "Ties" << tab[i].ties << endl;
        }
    }
    qsort((void *)player, 50, sizeof(PlayerStats), compareVictories);
}

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
        execute_option_four();
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

int Game::showTopPlayers(string text3_param, string diff3){
    fstream showStatsFile("temporary_stats.txt");
    string current_line;
    if (!showStatsFile.is_open())
    {
        cout << "File not found" <<endl;
        return -1;
    }
    while(getline(showStatsFile,current_line)){
        
        // string line_object = "Difficulty: " + diff3;
        size_t found_string = current_line.find("Difficulty: " + diff3);
        if(found_string>20 && diff3 == "Elementary"){
            current_line.begin();
            PlayerStats player[50];
            if(current_line.find("computer: computer")){
                player[get_current_player] = {  "computer", stoi(current_line.substr(current_line.find("Victories: ") +11)),
                                                stoi(current_line.substr(current_line.find("Defeats: ") +9)),
                                                stoi(current_line.substr(current_line.find("Ties: ") +6))
                                            };
                
                get_current_player++;
            }else{
                player[get_current_player] = {current_line.substr(current_line.find("current_user: ") +14), stoi(current_line.substr(current_line.find("Victories: ") +11)),
                                                stoi(current_line.substr(current_line.find("Defeats: ") +9)),
                                                stoi(current_line.substr(current_line.find("Ties: ") +6))
                                            };
                
                get_current_player++;
            }

        }else if(found_string<=16 && diff3 == "Medium"){
            current_line.begin();
            PlayerStats player[50];
            if(current_line.find("computer: computer")){
                player[get_current_player] = {  "computer", stoi(current_line.substr(current_line.find("Victories: ") +11)),
                                                stoi(current_line.substr(current_line.find("Defeats: ") +9)),
                                                stoi(current_line.substr(current_line.find("Ties: ") +6))
                                            };
                
                get_current_player++;
            }else{
                player[get_current_player] = {current_line.substr(current_line.find("current_user: ") +14), stoi(current_line.substr(current_line.find("Victories: ") +11)),
                                                stoi(current_line.substr(current_line.find("Defeats: ") +9)),
                                                stoi(current_line.substr(current_line.find("Ties: ") +6))
                                            };
                
                get_current_player++;
            }
        }else{
            current_line.begin();
            PlayerStats player[50];
            if(current_line.find("computer: computer")){
                player[get_current_player] = {  "computer", stoi(current_line.substr(current_line.find("Victories: ") +11)),
                                                stoi(current_line.substr(current_line.find("Defeats: ") +9)),
                                                stoi(current_line.substr(current_line.find("Ties: ") +6))
                                            };
                
                get_current_player++;
            }else{
                player[get_current_player] = {current_line.substr(current_line.find("current_user: ") +14), stoi(current_line.substr(current_line.find("Victories: ") +11)),
                                                stoi(current_line.substr(current_line.find("Defeats: ") +9)),
                                                stoi(current_line.substr(current_line.find("Ties: ") +6))
                                            };
                
                get_current_player++;
            }
        }
                
    }
    showStatsFile.close();
    return 0;
}
void Game::showStats(){
    cout <<right << "Difficulty: " <<difficulty<<endl;
    cout <<right << "Human_Victories: " <<human_victories<<endl;
    cout <<right << "Human_Defeats: " <<human_defeats<<endl;
    cout <<right << "Human_Ties: " <<human_ties<<endl;
    cout <<right << "Computer_Victories: " <<computer_victories<<endl;
    cout <<right << "Computer_Defeats: " <<computer_defeats<<endl;
    cout <<right << "Computer_Ties: " <<computer_ties<<endl;
}

int Game::loadStats(string text2_param, string user2, string diff2){
    fstream retrieveFile(text2_param);
    string current_line;
    if (!retrieveFile.is_open())
    {
        cout << "File not found" <<endl;
        return -1;
    }
    while(getline(retrieveFile,current_line)){
        string line_object = "Difficulty: " + diff2;
        if(current_line.find(user2) != string::npos){
            // current_line.replace(current_line.find(line_object), line_object.length()+3, );
            size_t symbol_find = current_line.find("Difficulty: " + diff2);

            if(symbol_find != string::npos){
                int read_victories, read_defeats, read_ties;
                if(user2 == "computer"){
                    symbol_find = current_line.find("Victories: ") + 11;
                    current_line.substr(symbol_find);
                    retrieveFile>>computer_victories;
                    symbol_find = current_line.find("Defeats: ") + 9;
                    current_line.substr(symbol_find);
                    retrieveFile>>computer_defeats;
                    // read_defeats = stoi(current_line.substr(symbol_find));
                    symbol_find = current_line.find("Ties: ") + 6;
                    current_line.substr(symbol_find);
                    retrieveFile>>computer_ties;
                    // read_ties = stoi(current_line.substr(symbol_find));
                    // computer_defeats += read_defeats;
                    // computer_ties += read_ties;
                    // // current_line.replace();
                    // writeStats(text_param);
                    retrieveFile.close();
                    return 0;
                }else{
                    symbol_find = current_line.find("Victories: ") + 11;
                    current_line.substr(symbol_find);
                    retrieveFile>>human_victories;
                    symbol_find = current_line.find("Defeats: ") + 9;
                    current_line.substr(symbol_find);
                    retrieveFile>>human_defeats;
                    // read_defeats = stoi(current_line.substr(symbol_find));
                    symbol_find = current_line.find("Ties: ") + 6;
                    current_line.substr(symbol_find);
                    retrieveFile>>human_ties;
                    // read_ties = stoi(current_line.substr(symbol_find));
                    // human_defeats += read_defeats;
                    // human_ties += read_ties;
                    // // current_line.replace();
                    // writeStats(text_param);
                    retrieveFile.close();
                    return 0;
                }
                
            }
        }else{
            cout <<"No data found for this user" <<endl;
            retrieveFile.close();
            resetStats();
            return 0;
        }
                
    }
    // retrieveFile >>current_user>> difficulty>>human_defeats>>human_defeats>>human_ties;
    // retrieveFile >> current_user >> human >>computer >>inputed_character >> nop >> location_on_game_array >> array_size >>difficulty;
    return 0;
}

Game Game::startNewGame(){
    Game *players  = new Game;
    players->playGame();
}

void Game::writeStats(string write_stats){
    ofstream write_stats_file(write_stats, ofstream::out | ofstream::trunc);
    if(! write_stats_file.is_open()){
        cout << "Error opening file"<<endl;
    }else{
        write_stats_file <<"current_user: " << current_user <<" " << " Difficulty: "<< difficulty<< " "<< "Victories: " << victories<< " "<< "Defeats: "  <<defeats << " " <<ties << " "<< endl;
        cout<< "Stats saved!"<<endl;
        write_stats_file.close();
    }

}

int Game::readAndWriteStats(string text_param, string user, string diff){
    fstream stats_file_read_and_write(text_param, ios::in | ios::out);
    string current_line;
    if(!stats_file_read_and_write.is_open()){
        cout <<"Error opening file"<<endl;
        return - 1;
    }
    while(getline(stats_file_read_and_write,current_line)){
        string line_object = "Difficulty: " + diff;
        if(current_line.find(user) != string::npos){
            // current_line.replace(current_line.find(line_object), line_object.length()+3, );
            size_t symbol_find = current_line.find("Difficulty: " + diff);
            if(user=="computer"){
                int read_victories, read_defeats, read_ties;
                if(symbol_find != string::npos){
                    symbol_find = current_line.find("Victories: ") + 11;
                    read_victories = stoi(current_line.substr(symbol_find));
                    computer_victories+=read_victories;
                    current_line.substr(symbol_find).assign(to_string(computer_victories));
                    symbol_find = current_line.find("Defeats: ") + 9;
                    read_defeats = stoi(current_line.substr(symbol_find));
                    computer_defeats += read_defeats;
                    current_line.substr(symbol_find).assign(to_string(computer_defeats));
                    // read_defeats = stoi(current_line.substr(symbol_find));
                    symbol_find = current_line.find("Ties: ") + 6;
                    read_ties = stoi(current_line.substr(symbol_find));
                    computer_ties += read_ties;
                    current_line.substr(symbol_find).assign(to_string(computer_ties));
                    // read_ties = stoi(current_line.substr(symbol_find));
                    // human_defeats += read_defeats;
                    // human_ties += read_ties;
                    // // current_line.replace();
                    // writeStats(text_param);
                    return 0;
                
                }
            }else{
                if(symbol_find != string::npos){
                    int read_victories, read_defeats, read_ties;
                    symbol_find = current_line.find("Victories: ") + 11;
                    read_victories = stoi(current_line.substr(symbol_find));
                    human_victories += read_victories;
                    current_line.substr(symbol_find).assign(to_string(human_victories));
                    symbol_find = current_line.find("Defeats: ") + 9;
                    read_defeats = stoi(current_line.substr(symbol_find));
                    human_defeats += read_defeats;
                    current_line.substr(symbol_find).assign(to_string(human_defeats));
                    // read_defeats = stoi(current_line.substr(symbol_find));
                    symbol_find = current_line.find("Ties: ") + 6;
                    read_ties = stoi(current_line.substr(symbol_find));
                    human_ties += read_ties;
                    current_line.substr(symbol_find).assign(to_string(human_ties));
                    // read_ties = stoi(current_line.substr(symbol_find));
                    // human_defeats += read_defeats;
                    // human_ties += read_ties;
                    // // current_line.replace();
                    // writeStats(text_param);
                    return 0;
                }
            }
            

            
        }else{ 
            if(user== "computer"){
                stats_file_read_and_write <<"computer: " << user <<" " << " Difficulty: "<< difficulty<< " "<< "Victories: " << computer_victories<< " "<< "Defeats: "  <<computer_defeats << " " <<computer_ties << " "<< endl;
                cout<< "Stats saved!"<<endl;
                stats_file_read_and_write.close();
                return 0;
            }else{
                stats_file_read_and_write <<"current_user: " << user <<" " << " Difficulty: "<< difficulty<< " "<< "Victories: " << human_victories<< " "<< "Defeats: "  <<human_defeats << " " <<human_ties << " "<< endl;
                cout<< "Stats saved!"<<endl;
                stats_file_read_and_write.close();
                return 0;
            }
            
            
        }
    }

    // ofstream stats_file_write(text_param);
    // if(!stats_file_write.is_open()){
    //     cout << "Error opening file"<<endl;
    //     return -1;
    // }else{
    //     stats_file_write <<"current_user: " << current_user <<" " << " Difficulty: "<< difficulty<< " "<< "Victories: " << victories<< " "<< "Defeats: "  <<defeats << " " <<ties << " "<< endl;
    //     cout<< "Stats saved!"<<endl;
    //     stats_file_write.close();
    //     return 0;
    // }
    stats_file_read_and_write.close();
    cout <<"Don't know"<<endl;
    return 0;
}

int Game::save_current_stats(){
    readAndWriteStats("temporary_stats.txt", current_user, difficulty);
}

// int Game::saveStats(){
    // ifstream stats_file_read("stats.txt");
    // string current_line;
    // if(!stats_file_read.is_open()){
    //     cout <<"Error opening file"<<endl;
    //     return - 1;
    // }
    // while(getline(stats_file_read,current_line)){
    //     if(current_line.find(current_user) != string::npos){
    //         size_t symbol_find = current_line.find("Difficulty: " + difficulty);
    //         if(symbol_find != string::npos){
    //             int read_victories, read_defeats, read_ties;
    //             symbol_find = current_line.find("Victories: ") + 11;
    //             read_victories = stoi(current_line.substr(symbol_find));
    //             symbol_find = current_line.find("Defeats: ") +9;
    //             read_defeats = stoi(current_line.substr(symbol_find));
    //             symbol_find = current_line.find("Ties: ")+6;
    //             read_ties = stoi(current_line.substr(symbol_find));

    //             human_victories += read_victories;
    //             human_defeats += read_defeats;
    //             human_ties += read_ties;
                
    //         }
            
    //     }else{
    //         stats_file_read.close();
    //     }
    // }

//     ofstream stats_file_write("stats.txt");
//     if(!stats_file_write.is_open()){
//         cout << "Error opening file"<<endl;
//         return -1;
//     }else{
//         stats_file_write <<"current_user: " << current_user <<" " << " Difficulty: "<< difficulty<< " "<< "Victories: " << victories<< " "<< "Defeats: "  <<defeats << " " <<ties << " "<< endl;
//         cout<< "Stats saved!"<<endl;
//         stats_file_write.close();
//         return 0;
//     }

// }

// void Game::saveCurrentGame(){
//     readAndWriteStats("temporary.txt");
    
// }

void Game::execute_option_one(){
    // ifstream file_opener;
    // file_opener.open("project_back_up.txt");
    // if(!file_opener.is_open()){
    //     cout << "Error finding specified file"<<endl;
    // }else{
    //     cout << "Do you want to retrieve previous game? Y or N "<<endl;
    //     cin >> retrieve_decision;
    //     if(retrieve_decision == 'Y'){
    //         file_opener >> human >> computer >> inputed_character
    //                >> nop >> location_on_game_array >> array_size
    //                >> stats >> victories >> defeats >> ties
    //                >> exit_confirmation >> difficulty;
    //         file_opener.close();
    //         cout << "Loaded" << endl;
    //     }else if(retrieve_decision == 'N'){
    //         file_opener.close();
    //         ofstream clear_file("project_back_up.txt", ofstream::out | ofstream::trunc);
    //         clear_file.close();
    //         startNewGame();
            
    //     }else{
    //         cout << "Please input a valid option"<<endl;
    //         execute_option_one();
    //     }
    // }
    // this->showTable();
    if(current_user==""){
        cout <<"Please enter your name"<<endl;
        cin >>current_user;
        this->playGame();
    }else{
        this->playGame();
    }
    
}

void Game::execute_option_two(){
    cout << "Choose who starts the game" <<endl;
    cout << "1 - You ";
    cout << " 2 - Computer"<<endl;
    cin >> this->starter;
    cout << starter;
    cout <<"Sucess"<<endl;
    if(this->starter == 2){
        showTable();
        computer = 'X';
        human = 'O';
        difficulty = "Elementary";
        cout<< "Your symbol is O"<<endl;
        srand(time(0));
        game_array[checkRandomNumber()%9] = 'X';
        playGame();
    }else if(starter == 1){
        showTable();
        cout << "Enter your symbol and a number between 0-9 starting from the top-left corner horizontally."<<endl;
        cout <<"Specified format : X9 or O9"<<endl;
        cin >> inputed_character>>location_on_game_array;
        playGame(inputed_character, location_on_game_array-1);
        cout << inputed_character <<endl;
        cout << location_on_game_array <<endl;
        if(inputed_character == 'X' || inputed_character == 'O' && location_on_game_array<=array_size){
            // this->playGame(this->inputed_character, this->location_on_game_array);
            human=inputed_character;
            game_array[location_on_game_array] = human;
            playGame();
        }else{
            cout<< "Please check input value";
        }
        
    }
    
}

void Game::resetStats(){
    human_defeats=0;
    human_ties = 0;
    human_victories = 0;
    computer_victories=0;
    computer_ties=0;
    computer_defeats=0;
}

void Game::execute_option_three(){
    //You have to input a code here to clear the current game and start a new game.
    cout << "Select difficulty "<<endl;
    cout <<left << setw(20) << setfill(' ')<<"Elementary" <<endl;
    cout <<left << setw(20) << setfill(' ')<<"Basic" <<endl;
    cout <<left << setw(20) << setfill(' ')<<"Medium" <<endl;
    cin >> difficulty; 
    cout << difficulty << " " << "selected" <<endl;
    resetStats();
    gameMenu();
}

void Game::execute_option_four(){
    saveGame();
    cout << "sucessfully saved"<<endl;
    exit();
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
    cout << chosen_option;
    execute_option(chosen_option);
}

void Game::playGreedy(){
    loadStats("temporary_stats.txt", "computer", difficulty);
    loadStats("temporary_stats.txt", current_user, difficulty);
    showStats();
    cout << "0 - Pause or Exit to Menu"<<endl;
    if(computer != 'X' && computer != 'O'){
        cout<<"Empty" <<endl;
        human =='X'?computer='O': computer='X';
        // game_array[checkRandomNumber()%9] = computer;
        nop++;
    }
    if(game_cheat_array_random_number<0){
        game_cheat_array_random_number = checkRandomNumber();
    }else{
        for(int k = 1; k<=3;) {
            if(game_array[game_cheat_array[game_cheat_array_random_number][k]] !='\0'){
                game_cheat_array_random_number=-1;
                playGreedy();
            }else{
                game_array[game_cheat_array[game_cheat_array_random_number][k]]=computer;
                showTable();
                cout << "Your turn" <<endl;
                cin >>inputed_character>>location_on_game_array;
                cout<<inputed_character<<endl;
                // cin >> location_on_game_array;
                playGame(inputed_character, location_on_game_array-1);
                if((inputed_character != human) && (inputed_character != 0)){
                    cout <<"Please input a valid alphabet" <<endl;
                    cout<< "Reminder : Your symbol is O"<<endl;
                    playGreedy();
                }else if(location_on_game_array>9){
                    cout <<"Input a number between 1-9" <<endl;
                    playGreedy();
                }else if(game_array[location_on_game_array]=='X' || game_array[location_on_game_array] == 'O'){
                    cout << "The chosen location is occupied, choose another." << endl;
                    playGreedy();
                }else if((inputed_character == '0') && location_on_game_array){
                    gameMenu();
                }else{
                    game_array[location_on_game_array] = human;
                    checkAndComputeStats();
                    // srand(time(0));
                    // game_array[checkRandomNumber()] = computer;
                    // showTable();
                    // checkAndComputeStats();
                    location_on_game_array=-1;
                    nop++;
                    playGreedy();
                }
            }
            
        }
        
    }
    
}

void Game::playGame() {
    /*C is the current players_signs chosen alphabet(X or O) 
    and n is the index on the board intended to play.*/
    loadStats("temporary_stats.txt", "computer", difficulty);
    loadStats("temporary_stats.txt", current_user, difficulty);
    showStats();
    cout << "0 - Pause or Exit to Menu"<<endl;
    if(computer != 'X' && computer != 'O'){
        cout<<"Empty" <<endl;
        human =='X'?computer='O': computer='X';
        game_array[checkRandomNumber()%9] = computer;
        nop++;
    }
    if(difficulty == "Elementary"){
        showTable();
        cout << "Your turn" <<endl;
        cin >>inputed_character>>location_on_game_array;
        cout<<inputed_character<<endl;

        // cin >> location_on_game_array;
        playGame(inputed_character, location_on_game_array-1);
        if((inputed_character != human) && (inputed_character != 0)){
            cout <<"Please input a valid alphabet" <<endl;
            cout<< "Reminder : Your symbol is O"<<endl;
            playGame();
        }else if(location_on_game_array>9){
            cout <<"Input a number between 1-9" <<endl;
            playGame();
        }else if(game_array[location_on_game_array]=='X' || game_array[location_on_game_array] == 'O'){
            cout << "The chosen location is occupied, choose another." << endl;
            playGame();
        }else if((inputed_character == '0') && location_on_game_array){
            gameMenu();
        }else{
            game_array[location_on_game_array] = human;
            checkAndComputeStats();
            srand(time(0));
            game_array[checkRandomNumber()] = computer;
            // showTable();
            checkAndComputeStats();
            location_on_game_array=-1;
            nop++;
            playGame();
        }
    
    }else if(difficulty == "Basic"){
        // loadStats("temporary_stats.txt", "computer", difficulty);
        // loadStats("temporary_stats.txt", current_user, difficulty);
        // showTable();
        // cout << "Your turn" <<endl;
        // cin >> inputed_character>>location_on_game_array;
        // // cin >> location_on_game_array;
        // cout<<inputed_character;
        // playGame(inputed_character, location_on_game_array-1);
        // if(inputed_character != human){
        //     cout <<"Please input a valid alphabet" <<endl;
        //     cout<< "Reminder : Your symbol is O"<<endl;
        //     playGame();
        // }else if(location_on_game_array>9){
        //     cout <<"Input a number between 1-9" <<endl;
        //     playGame();
        // }else if(game_array[location_on_game_array]=='X' || game_array[location_on_game_array] == 'O'){
        //     cout << "The chosen location is occupied, choose another." << endl<<flush;
        //     playGame();
        // }else if((inputed_character == '0')){
        //     gameMenu();
        // }else{
        //     game_array[location_on_game_array] = human;
        //     checkAndComputeStats();
        //     srand(time(0));
        //     game_array[checkRandomNumber()] = computer;
        //     // showTable();
        //     checkAndComputeStats();
        //     nop++;
        // }
        playGreedy();
    }
    
    // countPlays();
    
}

int Game::checkRandomNumber(){
    int random_number = rand()%9;
    if (game_array[random_number] != '\0')
    {
        return checkRandomNumber();
    }  
    return random_number;
}

void Game::checkAndComputeStats(){
    if((checkTable() == 'X' && computer == 'X') || (checkTable() == 'O' && computer == 'O')){
        cout << "Computer wins"<<endl;
        computer_victories++;
        readAndWriteStats("temporary.txt", "computer", difficulty);
        nop=0;
        game_state=true;
        gameMenu();
    }else if((checkTable() == 'X' && human == 'X') || (checkTable() == 'O' && human == 'O')){
        cout << "Human wins"<<endl;
        nop=0;
        human_victories++;
        readAndWriteStats("temporary.txt", current_user, difficulty);
        game_state=true;
        gameMenu();
    }else if(checkTable() == 'N'){
        cout << "It's a tie.!!"<<endl;
        nop=0;
        game_state=true;
        computer_ties++;
        human_ties++;
        gameMenu();
    }
}

void Game::playGame(char C, int n){
    inputed_character=C;
    location_on_game_array=n;
}
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
    }else if(game_array[0] == game_array[4] && game_array[4] == game_array[8]){
        return game_array[0];
    }else if(game_array[2] == game_array[4] && game_array[4] == game_array[6]){
        return game_array[2];
    }else if(nop == 9){
        return 'N'; //N stands for no winner
    }
    return 't';
}

void Game::showTable(){

    cout << right <<"No of plays: "<< nop << "  "<< "Difficulty :" << difficulty <<endl;
    cout << "|" << game_array[0] << "|" <<game_array[1] << "|" <<game_array[2]<<endl;
    cout << "-----"<<endl;
    cout << "|" << game_array[3] << "|" <<game_array[4] << "|" <<game_array[5]<< endl;
    cout << "------"<<endl;
    cout << "|" << game_array[6] << "|" <<game_array[7] << "|" <<game_array[8]<< endl;
    
    // for(int i=0; i<=array_size; i++){
    //     cout << setw(20) <<setfill('/') << game_array[i] << endl;
    // }

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
    if(nop==0){
        ::exit(0);
    }else{
        cout << "Is the game over?. Are you sure that you want to exit ? Yes or No" <<endl;
        cin >> exit_confirmation;
        if(exit_confirmation == "Yes") {
            readAndWriteStats("temporary_stats.txt", "computer", difficulty);
            readAndWriteStats("temporary_stats.txt", current_user, difficulty);
            saveGame();
            ::exit(0);
        }else if(exit_confirmation == "No"){
            playGame();
        }else{
            cout << "Please input a valid expression" <<endl;
        }   
    }
    
}

int Game::saveGame(){
    // char game_array[9],players_sign, computers_sign, human, computer, inputed_character;
    // int nop, location_on_game_array, starter, array_size = (sizeof(game_array)/sizeof(char)) - 1; // nop means number of plays
    // unsigned long stats, victories, defeats, ties;
    // string exit_confirmation, difficulty;
    ofstream myfile;
    myfile.open("project_back_up.txt");
    if(!myfile.is_open()){
        cout << "Error opening backup file" <<endl;
        return -1;
    }else{
        string exit_confirmation, difficulty;
        myfile << current_user << " " << human<< " "<<computer<< " "<<inputed_character << " " << nop << " "<<location_on_game_array << " "<<array_size
        << " "<< stats<< " "<<victories<< " "<<defeats<< " "<<ties
        << " "<<difficulty;
        myfile.close();
        return 0;
    }
    return 0 ;
}
int main(){
    Game game1;
    game1.gameMenu();
    
    return 0;
}