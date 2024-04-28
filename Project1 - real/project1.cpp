#include <iostream>
#include <iomanip>
#include <string>
#include <ctype.h>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <algorithm>

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
PlayerStats players[50];

class Game{
    bool game_state;
    char game_array[9]={'\0','\0','\0','\0','\0','\0','\0','\0','\0'};
    int nop=0, location_on_game_array, starter, array_size = (sizeof(game_array)/sizeof(char)) - 1; // nop means number of plays
    char human='O', computer='X', inputed_character='\0';
    unsigned long stats, victories=0, defeats=0, ties=0, computer_victories=0, human_victories=0, computer_defeats=0, human_defeats=0, computer_ties=0, human_ties=0;
    string exit_confirmation, difficulty="Elementary",current_user;

    public:
        Game(){
            
        };
        Game(char );
        char checkTable();
        void showTable();
        void countTable();
        void countPlays();
        void playGame();
        void playGame(int);
        void gameMenu();
        void clearArray();
        int checkRandomNumber();
        void playElementary();
        void playGreedy();
        void playGreedyWinner();
        void playMedium();
        void playMediumWinner();
        void execute_option(int);
        void execute_option_one(),execute_option_two();
        void execute_option_three(),execute_option_four();
        void execute_option_five(struct PlayerStats playerss[], int);
        void treat_errors();
        void restart_game();
        void retrievGame();
        Game startNewGame();
        int retrievePreviousGame(string user);
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
        showTopPlayers("temporary_stats.txt", difficulty);
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
    
    ifstream showStatsFile(text3_param);
    string current_line;
    if (!showStatsFile.is_open())
    {
        cout << "File not found" <<endl;
        return -1;
    }
    while(getline(showStatsFile,current_line)){
        
        // string line_object = "Difficulty: " + diff3;
        size_t found_string = current_line.find("Difficulty: " + diff3);
        cout<< found_string<<endl;
        if(found_string>18 && diff3 == "Elementary"){
            current_line.begin();
            cout<< current_line.find("computer: computer&");
            if(current_line.find("computer: computer&")){
                cout<< "foundcomp"<<endl;
                players[get_current_player] = {  "computer", stoi(current_line.substr(current_line.find("Victories: ") +11)),
                                                stoi(current_line.substr(current_line.find("Defeats: ") +9)),
                                                stoi(current_line.substr(current_line.find("Ties: ") +6))
                                            };
                
                get_current_player++;
            }else{
                cout<< "found"<<endl;
                cout<< current_line.find("current_user: ")<< endl;
                players[get_current_player] = {current_line.substr(current_line.find("current_user: ") +14), stoi(current_line.substr(current_line.find("Victories: ") +11)),
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
    execute_option_five(players,10);
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
    string current_line="";
    size_t symbol_find;
    if (!retrieveFile.is_open())
    {
        cout << "File not found" <<endl;
        return -1;
    }
    while(getline(retrieveFile,current_line)){
        string line_object = "Difficulty: " + diff2;
        if(current_line.find(user2)){
            cout<<"Retrieving stats"<<endl;
            // current_line.replace(current_line.find(line_object), line_object.length()+3, );
            symbol_find = current_line.find("Difficulty: " + diff2);

            if(symbol_find){
                int read_victories, read_defeats, read_ties;
                if(user2 == "computer&"+ current_user){
                    symbol_find = current_line.find("Victories: ");
                    cout<< symbol_find<<endl;
                    // retrieveFile>> computer >> difficulty >> victories >> defeats >> ties;
                    computer_victories= stoi(current_line.substr(symbol_find+11));
                    // retrieveFile>>computer_victories;
                    symbol_find = current_line.find("Defeats: ");
                    current_line.substr(symbol_find);
                    computer_defeats= stoi(current_line.substr(symbol_find+9));
                    // retrieveFile>>computer_defeats;
                    // read_defeats = stoi(current_line.substr(symbol_find));
                    symbol_find = current_line.find("Ties: ");
                    current_line.substr(symbol_find);
                    computer_ties= stoi(current_line.substr(symbol_find+6));
                    // retrieveFile>>computer_ties;
                    // read_ties = stoi(current_line.substr(symbol_find));
                    // computer_defeats += read_defeats;
                    // computer_ties += read_ties;
                    // // current_line.replace();
                    // writeStats(text_param);
                    retrieveFile.close();
                    return 0;
                }else{
                    symbol_find = current_line.find("Victories: ");
                    human_victories= stoi(current_line.substr(symbol_find+11));
                    symbol_find = current_line.find("Defeats: ");
                    human_defeats= stoi(current_line.substr(symbol_find+9));
                    symbol_find = current_line.find("Ties: ");
                    human_ties= stoi(current_line.substr(symbol_find+6));
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

// int Game::readAndWriteStats(string text_param, string user, string diff) {
//     fstream stats_file_read_and_write(text_param, ios::in | ios::out);

//     if (!stats_file_read_and_write.is_open()) {
//         cerr << "Error opening file" << endl;
//         return -1;
//     }

//     string current_line;
//     bool user_found = false;

//     while (getline(stats_file_read_and_write, current_line)) {
//         if (current_line.find(user) != string::npos) {
//             user_found = true;

//             // Parse and update statistics
//             istringstream iss(current_line);
//             string token;
//             int victories, defeats, ties;
//             while (iss >> token) {
//                 if (token == "Victories:") {
//                     iss >> victories;
//                 } else if (token == "Defeats:") {
//                     iss >> defeats;
//                 } else if (token == "Ties:") {
//                     iss >> ties;
//                 }
//             }

//             // Update statistics based on user and difficulty
//             if (user == "computer") {
//                 computer_victories += victories;
//                 computer_defeats += defeats;
//                 computer_ties += ties;
//             } else {
//                 human_victories += victories;
//                 human_defeats += defeats;
//                 human_ties += ties;
//             }

//             // Move file pointer to the beginning of the line
//             stats_file_read_and_write.seekp(stats_file_read_and_write.tellg());

//             // Write updated statistics back to the file
//             stats_file_read_and_write << user << " Difficulty: " << diff << " Victories: " << computer_victories << " Defeats: " << computer_defeats << " Ties: " << computer_ties << endl;

//             stats_file_read_and_write.close();
//             return 0; // Exit after updating statistics
//         }
//     }

//     if (!user_found) {
//         // Append new statistics if user is not found
//         if (user == "computer") {
//             stats_file_read_and_write << "computer: " << user << " Difficulty: " << diff << " Victories: " << computer_victories << " Defeats: " << computer_defeats << " Ties: " << computer_ties << endl;
//         } else {
//             stats_file_read_and_write << "current_user: " << user << " Difficulty: " << diff << " Victories: " << human_victories << " Defeats: " << human_defeats << " Ties: " << human_ties << endl;
//         }
//     }

//     stats_file_read_and_write.close();
//     cout << "Operation completed" << endl;
//     return 0;
// }

int Game::readAndWriteStats(string text_param, string user, string diff){
    fstream stats_file_read_and_write(text_param, ios::in | ios::out);
    int read_victories=0, read_defeats=0, read_ties=0;
    string current_line="";
    size_t symbol_find;
    if(!stats_file_read_and_write.is_open()){
        cout <<"Error opening file"<<endl;
        return - 1;
    }else{
        while(getline(stats_file_read_and_write,current_line)){
            cout<<"Found"<<endl;
            string line_object = "Difficulty: " + diff;
            if(current_line.find(user) && current_line.find(diff)){
                // current_line.replace(current_line.find(line_object), line_object.length()+3, );
                if(user=="computer&" + current_user ){
                    cout<<"Found computer"<<endl;
                    symbol_find = current_line.find("Difficulty: " + diff);
                    // int read_victories, read_defeats, read_ties;
                    if(symbol_find != string::npos){
                        symbol_find = current_line.find("Victories: ") + 11;
                        cout<<symbol_find<<endl;
                        // read_victories = stoi(current_line.substr(symbol_find));
                        computer_victories+=read_victories;
                        current_line.substr(symbol_find).assign(to_string(computer_victories));
                        symbol_find = current_line.find("Defeats: ") + 9;
                        cout<<symbol_find<<endl;
                        // read_defeats = stoi(current_line.substr(symbol_find));
                        computer_defeats += read_defeats;
                        current_line.substr(symbol_find).assign(to_string(computer_defeats));
                        // read_defeats = stoi(current_line.substr(symbol_find));
                        symbol_find = current_line.find("Ties: ") + 6;
                        cout<<symbol_find<<endl;
                        // read_ties = stoi(current_line.substr(symbol_find));
                        computer_ties += read_ties;
                        current_line.substr(symbol_find).assign(to_string(computer_ties));
                        stats_file_read_and_write <<"computer: " << "computer&" + current_user <<" " << " Difficulty: "<< difficulty<< " "<< "Victories: " << computer_victories<< " "<< "Defeats: "  <<computer_defeats<< " "<< "Ties: " <<computer_ties << endl;
                        stats_file_read_and_write.close();
                        // read_ties = stoi(current_line.substr(symbol_find));
                        // human_defeats += read_defeats;
                        // human_ties += read_ties;
                        // // current_line.replace();
                        // writeStats(text_param);
                        return 0;
                    }
                    
                }else{
                    cout<<"Found human"<<endl;
                    size_t symbol_find = current_line.find("Difficulty: " + diff);
                    
                    if(symbol_find != string::npos){
                        symbol_find = current_line.find("Victories: ") + 11;
                        // read_victories = stoi(current_line.substr(symbol_find));
                        human_victories += read_victories;
                        current_line.substr(symbol_find).assign(to_string(human_victories));
                        symbol_find = current_line.find("Defeats: ") + 9;
                        // read_defeats = stoi(current_line.substr(symbol_find));
                        human_defeats += read_defeats;
                        current_line.substr(symbol_find).assign(to_string(human_defeats));
                        // read_defeats = stoi(current_line.substr(symbol_find));
                        symbol_find = current_line.find("Ties: ") + 6;
                        // read_ties = stoi(current_line.substr(symbol_find));
                        human_ties += read_ties;
                        current_line.substr(symbol_find).assign(to_string(human_ties));
                        stats_file_read_and_write <<"current_user: " << user <<" " << " Difficulty: "<< difficulty<< " "<< "Victories: " << human_victories<< " "<< "Defeats: "  <<human_defeats<< " " << "Ties: " <<human_ties << endl;
                        stats_file_read_and_write.close();
                        return 0;
                    }
                }
                

                
            }
        }

        fstream stats_file_read_and_write(text_param, ios::in | ios::out | ios::app);
        cout<<"Secondloop"<<endl;
        if(user== "computer"){
            cout<<"save dtat"<<endl;
            stats_file_read_and_write <<"computer: " << "computer&" + human <<" " << " Difficulty: "<< difficulty<< " "<< "Victories: " << computer_victories<< " "<< "Defeats: "  <<computer_defeats<< " "<< "Ties: " <<computer_ties << endl;
            cout<<"computer is saving"<<endl;
            cout<< "Stats saved!"<<endl;
            stats_file_read_and_write.close();
            return 0;
        }else{
            cout<<"save dtat"<<endl;
            stats_file_read_and_write <<"current_user: " << user <<" " << " Difficulty: "<< difficulty<< " "<< "Victories: " << human_victories<< " "<< "Defeats: "  <<human_defeats<< " " << "Ties: " <<human_ties << endl;
            cout<<"human is saving"<<endl;
            cout<< "Stats saved!"<<endl;
            stats_file_read_and_write.close();
            return 0;
        } 
        cout<<"Not found"<<endl;
    }
    

    // ofstream stats_file_write(text_param);
    // if(!stats_file_write.is_open()){
    //     cout << "Error opening file"<<endl;
    //     return -1;
    // }else{
    //     stats_file_write <<"current_user: " << user <<" " << " Difficulty: "<< difficulty<< " "<< "Victories: " << victories<< " "<< "Defeats: "  <<defeats << " " <<ties << " "<< ties<< endl;
    //     cout<< "Stats saved!"<<endl;
    //     stats_file_write.close();
    //     return 0;
    // }
    // stats_file_read_and_write.close();
    // cout <<"Don't know"<<endl;
    stats_file_read_and_write.close();
    cout <<"Opeartion completed" <<endl;
    return 0;
}

// int Game::save_current_stats(){
//     readAndWriteStats("temporary_stats.txt", current_user, difficulty);
// }

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

int Game::retrievePreviousGame(string user){
    cout<<"Retrieving..."<<endl;
    ifstream retriever("previous_game.txt");
    string current_line;
    size_t symbol_find;
    if(!retriever.is_open()){
        cout <<  "Error opening file" << endl;
        return -1;
    }else{
        // cout<<"I am here"<<endl;
        while(getline(retriever,current_line)){
            cout<<"Found"<<endl;
            if(current_line.find(user)){
                // current_line.replace(current_line.find(line_object), line_object.length()+3, );
                cout << "Do you want to retrieve previous game? Y or N "<<endl;
                cin >> retrieve_decision;
                if(retrieve_decision == 'Y'){
                    current_user=user;
                    symbol_find = current_line.find("human: ");
                    human=current_line.at(symbol_find+7);
                    symbol_find = current_line.find("nop: ");
                    nop=stoi(current_line.substr(symbol_find+5));
                    symbol_find = current_line.find("location_on_game_array: ");
                    location_on_game_array=stoi(current_line.substr(symbol_find+24));
                    symbol_find = current_line.find("array_size: ");
                    array_size=stoi(current_line.substr(symbol_find+12));
                    cout<<array_size<<endl;
                    symbol_find = current_line.find("difficulty: ");
                    difficulty=current_line.substr(symbol_find+12, '\0');
                    cout<<difficulty<<endl;
                    symbol_find = current_line.find("arrays: ");
                    cout<<current_line.substr(symbol_find)<<endl;
                    for (int i = 0; i < 9; i++) {
                        game_array[i] = current_line.substr(symbol_find+8)[i];
                    }
                    retriever.close();
                    cout<<"Finished"<<endl;
                    return 0; 
                }else if(retrieve_decision == 'N'){
                    current_line.erase();
                    retriever.close();
                    return 0;
                    
                }else{
                    cout << "Please input a valid option"<<endl;
                    retriever.close();
                    execute_option_one();
                }
                
            }else{
                cout << "Data not found for this user"<<endl;
                retriever.close();
                return -1;
            }
        }
        cout << "Data not found for this user"<<endl;
        retriever.close();
        return -1;
    }

}

void Game::execute_option_one(){
    if(current_user==""){
        cout <<"Please enter your name"<<endl;
        cin >>current_user;
        retrievePreviousGame(current_user);
        cout<<"yeah"<<endl;
        loadStats("temporary_stats.txt", "computer&"+current_user, difficulty);
        loadStats("temporary_stats.txt", current_user, difficulty);
        playGame();
    }else{
        retrievePreviousGame(current_user);
        loadStats("temporary_stats.txt", "computer&"+current_user, difficulty);
        loadStats("temporary_stats.txt", current_user, difficulty);
        playGame();
    }
}

void Game::execute_option_two(){
    cout << "Choose who starts the game" <<endl;
    cout << "1 - You ";
    cout << " 2 - Computer"<<endl;
    cin >> this->starter;
    if(this->starter == 2){
        // showTable();
        difficulty==""?difficulty="Elementary":difficulty;
        cout<< "Your symbol is O"<<endl;
        srand(time(0));
        game_array[checkRandomNumber()%9] = computer;
        nop++;
        gameMenu();
    }else if(starter == 1){
        difficulty==""?difficulty="Elementary":difficulty;
        // playGame(); 
        gameMenu();
    }
}

void Game::clearArray(){
    for(int i=0; i<=8; i++){
        game_array[i] = '\0';
    }
}

void Game::resetStats(){
    human_defeats=0;
    human_ties = 0;
    human_victories = 0;
    computer_victories=0;
    computer_ties=0;
    computer_defeats=0;
    nop=0;
    clearArray();
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

bool compareVictories(const PlayerStats& player1, const PlayerStats& player2) {
    cout<< player1.victories << player2.victories <<endl;
    return player1.victories > player2.victories;
}

void Game::execute_option_five(PlayerStats player[], int numPlayers){
    sort(player, player + numPlayers, compareVictories);

    // Display stats of the top 10 players
    cout << "Top 10 Players:" << endl;
    for (int i = 0; i < min(10, numPlayers); ++i) {
        cout << "Name: " << player[i].name << setw(10) << " Victories: " << player[i].victories 
             << setw(10) << " Defeats: " << player[i].defeats << setw(10) << " Ties: " << player[i].ties << endl;
    }
}


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

void Game::playElementary(){
    showStats();
    cout << "0 - Pause or Exit to Menu"<<endl;
    showTable();
    cout << "Your turn" <<endl;
    cin >> location_on_game_array;
    if(location_on_game_array == 0){
        gameMenu();

    }else{
        if(location_on_game_array>9){
            cout <<"Input a number between 1-9" <<endl;
            playElementary();
        }else if(game_array[location_on_game_array-1] != '\0'){
            cout << "The chosen location is occupied, choose another." << endl;
            playElementary();
        }else{
            game_array[location_on_game_array-1] = human;
            checkAndComputeStats();
            srand(time(0));
            game_array[checkRandomNumber()] = computer;
            // showTable();
            checkAndComputeStats();
            nop++;
            playElementary();
        }
    }
    // cin >> location_on_game_array;
    
}

void Game::playGreedyWinner(){
    for(int i = 0; i<=8; i++){
        if(game_array[i] == '\0'){
            game_array[i] == computer;
            if(checkTable() == computer) return;
            game_array[checkRandomNumber()] = computer;
            break;
        }
    }
}
void Game::playGreedy(){
    // loadStats("temporary_stats.txt", "computer", difficulty);
    // loadStats("temporary_stats.txt", current_user, difficulty);
    showStats();
    cout << "0 - Pause or Exit to Menu"<<endl;
    showTable();
    cout << "Your turn, input a number between 0-9" <<endl;
    cin >>location_on_game_array;
    cout << location_on_game_array<<endl;
    if(location_on_game_array==0){
        gameMenu();
    }else{
        if(location_on_game_array>9){
            cout <<"Input a number between 1-9" <<endl;
            playGreedy();
        }else if(game_array[location_on_game_array-1] != '\0'){
            cout << "The chosen location is occupied, choose another." << endl;
            playGreedy();
        }else{
            game_array[location_on_game_array-1] = human;
            checkAndComputeStats();
            // for(int i = 0; i<=8; i++){
            //     if(game_array[i] == '\0'){
            //         game_array[i] = computer;
            //         if(checkTable() == computer) {
            //             game_array[i] = computer;
            //         }else{
            //             game_array[i] = '\0';
            //         }

            //         if(i==8){
            //             game_array[checkRandomNumber()] = computer;
            //         }
                    
            //     }
            // }
            playGreedyWinner();
            checkAndComputeStats();
            nop++;
            playGreedy();
        } 
    }
    
}


void Game::playMediumWinner(){
    for(int i = 0; i<=8; i++){
        if(game_array[i] == '\0'){
            game_array[i] == computer;
            if(checkTable() == computer) return;
            game_array[checkRandomNumber()] = computer;
            break;
        }
    }

    for(int i = 0; i<=8; i++){
        if(game_array[i] == '\0'){
            game_array[i] == human;
            if(checkTable() == human){
                game_array[i] = computer;
                return;
            };
            game_array[checkRandomNumber()] = computer;
            break;
        }
    }
}

void Game::playMedium(){
    cout << "0 - Pause or Exit to Menu"<<endl;
    showTable();
    cout << "Your turn, input a number between 0-9" <<endl;
    cin >> location_on_game_array;
    if(location_on_game_array==0){
        gameMenu();
    }else{
        if(location_on_game_array>9){
            cout <<"Input a number between 1-9" <<endl;
            playMedium();
        }else if(game_array[location_on_game_array-1] != '\0'){
            cout << "The chosen location is occupied, choose another." << endl;
            playMedium();
        }else if(location_on_game_array == 0 ){
            gameMenu();
        }else{
            game_array[location_on_game_array-1] = human;
            checkAndComputeStats();
            playMediumWinner();
            nop++;
            playMedium();
        } 
    }
    
}

void Game::playGame() {
    /*C is the current players_signs chosen alphabet(X or O) 
    and n is the index on the board intended to play.*/
    difficulty==""?difficulty="Elementary":difficulty;
    if(difficulty == "Elementary"){
        playElementary();
    }else if(difficulty == "Basic"){
        playGreedy();
    }else if(difficulty == "Medium"){
        playMedium();
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
        human_defeats++;
        readAndWriteStats("temporary_stats.txt", "computer&" + current_user, difficulty);
        readAndWriteStats("temporary_stats.txt",  current_user, difficulty);
        nop=0;
        clearArray();
    }else if((checkTable() == 'X' && human == 'X') || (checkTable() == 'O' && human == 'O')){
        cout << "Human wins"<<endl;
        nop=0;
        human_victories++;
        computer_defeats++;
        readAndWriteStats("temporary_stats.txt", "computer&" + current_user, difficulty);
        readAndWriteStats("temporary_stats.txt", current_user, difficulty);
        game_state=true;
        clearArray();
    }else if(checkTable() == 'N'){
        cout << "It's a tie.!!"<<endl;
        nop=0;
        game_state=true;
        clearArray();
        computer_ties++;
        human_ties++;
        readAndWriteStats("temporary_stats.txt", "computer&"+ current_user, difficulty);
        readAndWriteStats("temporary_stats.txt", current_user, difficulty);
    }
}

void Game::playGame(int n){
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
    // loadStats("temporary_stats.txt", "computer", difficulty);
    // loadStats("temporary_stats.txt", current_user, difficulty);
    // showStats();
    cout << "|" << game_array[0] << "|" <<game_array[1] << "|" <<game_array[2]<<endl;
    cout << "-----"<<endl;
    cout << "|" << game_array[3] << "|" <<game_array[4] << "|" <<game_array[5]<<endl;
    cout << "------"<<endl;
    cout << "|" << game_array[6] << "|" <<game_array[7] << "|" <<game_array[8]<<endl;
    
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
            readAndWriteStats("temporary_stats.txt", "computer&"+current_user, difficulty);
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
    myfile.open("previous_game.txt");
    if(!myfile.is_open()){
        cout << "Error opening backup file" <<endl;
        return -1;
    }else{
        string exit_confirmation, difficulty;
        myfile <<"current_user: " << current_user<< " " << " human:  " << human<< " " <<  " computer:  "<<computer << " " << " nop: "<< nop << " " <<  " location_on_game_array: "<<location_on_game_array<< " " << " array_size: "<<array_size<< " " << " difficulty: "<<difficulty << " ";
        myfile << " arrays: ";
        for (int i = 0; i < 9; ++i) {
            myfile << game_array[i];
        }
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