//    Battleship game assignment for MSU CSCI 366
//    Copyright (C) 2020    Mike P. Wittie
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.


#include "common.hpp"
#include "Server.hpp"


/**
 * Calculate the length of a file (helper function)
 *
 * @param file - the file whose length we want to query
 * @return length of the file in bytes
 */
int get_file_length(ifstream *file){
    return 1;
}


void Server::initialize(unsigned int board_size, string p1_setup_board, string p2_setup_board){
    this-> board_size = board_size;
    if (BOARD_SIZE != board_size){
        throw(ServerException("Wrong!"));
    }

    if ((p1_setup_board.compare("player_1.setup_board.txt")) != 0){

        throw(ServerException("Wrong!"));
    }

    if ((p2_setup_board.compare("player_2.setup_board.txt")) != 0){

        throw(ServerException("Wrong!"));
    }

}


int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {

    if (x >= 10) {
        return 0;
    }
    if (y >= 10) {
        return 0;
    }

    if (player > 2){
        throw(ServerException("Wrong!"));
    } else if (player < 1){
        throw(ServerException("Wrong!"));
    }

    char map [BOARD_SIZE][BOARD_SIZE];
    ifstream fp;
    if(player == 1) {
        fp.open("player_2.setup_board.txt");
    }
    else{
        fp.open("player_1.set_board.txt");
    }

    for(int row = 0; row < BOARD_SIZE; row++) {
        for(int column = 0; column < BOARD_SIZE; column++){
            fp >> map[column][row];
            }
        }

    if (map[x][y] == '_') {
        return -1;
     }
    else {
        return 1;
    }
}


int Server::process_shot(unsigned int player) {

    int x, y;
    string coord;
    std::ifstream player_1_file;
    if(player == 1) {
        player_1_file.open("player_1.shot.json");
    }
    else if(player == 2){
        player_1_file.open("player_2.shot.json");
    }
    else{
        throw(ServerException("Wrong!"));
    }
    getline(player_1_file, coord);

    if ( coord[6] == '1' and coord[7] == '0') {
        x = 10;
        if( coord[14] == '1' and coord[15] == '0'){
            y = 10;
        }else{
            y = coord[14] - '0';
        }
    } else{
        x = coord[6] - '0';
        if( coord[13] == '1' and coord[14] == '0'){
            y = 10;
        }else{
            y = coord[13] - '0';
        }
    }

    int result = evaluate_shot(player, x, y);
    string result_str = "{\n"
                        "    \"result\": "+to_string(result)+"\n"
                                                             "}";

    ofstream result_file;
    if(player == 1){
        result_file.open("player_1.result.json");
    }
    else{
        result_file.open("player_2.result.json");
    }
    result_file << result_str;
    result_file.close();
    player_1_file.close();

    remove("player_1.shot.json");
    remove("player_2.shot.json");
   return NO_SHOT_FILE;
}
