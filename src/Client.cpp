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
#include "Client.hpp"

Client::~Client() {
}


void Client::initialize(unsigned int player, unsigned int board_size){
    if(player == 2) this->initialized = true;
    this->board_size = board_size;
    std:: string filename;
    if (player == 1){
        filename="player_1.action_board.json";
    }
    else{
        filename="player_2.action_board.json";
    }

    ofstream output (filename);
    string player_1_action_board= "{\n"
                                "    \"board\": [\n"
                                "        [\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0\n"
                                "        ],\n"
                                "        [\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0\n"
                                "        ],\n"
                                "        [\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0\n"
                                "        ],\n"
                                "        [\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0\n"
                                "        ],\n"
                                "        [\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0\n"
                                "        ],\n"
                                "        [\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0\n"
                                "        ],\n"
                                "        [\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0\n"
                                "        ],\n"
                                "        [\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0\n"
                                "        ],\n"
                                "        [\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0\n"
                                "        ],\n"
                                "        [\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0,\n"
                                "            0\n"
                                "        ]\n"
                                "    ]\n"
                                "}";
    output << player_1_action_board;

    this->player = 1;
}


void Client::fire(unsigned int x, unsigned int y) {
    std:: string filename;
    if(this-> player == 1) {
        filename = "player_1.shot.json";
    }
    else{
        filename="player_2.shot.json";
    }
    ofstream output (filename);
    string player_1_fire_message= "{\n"
                                  "    \"x\": " + to_string(x)+ ",\n"
                                  "    \"y\": " + to_string(y)+ "\n"
                                  "}";
    output << player_1_fire_message;
}


bool Client::result_available() {

    std:: string filename;
    if(this->player == 1){
        filename= "player_1.result.json";
    }
    else{
        filename= "player_2.result.json";
    }
    ifstream input(filename);
    if(!input.is_open()){
        return false;
    }
    else{
        return true;
    }

}


int Client::get_result() {
    std::string line;
    std:: string filename;
    if (this->player == 1) {
        filename = "player_1.result.json";
    }
    else{
        filename= "player_2.result.json";
    }
    ifstream input(filename);
    getline(input, line);
    getline(input, line);

    input.close();
    remove("player_1.result.json");
    remove("player_2.result.json");

    if(line[14] == '0'){
        return 0;
    }
    else if(line[14] == '1'){
        return 1;
    } else if(line[14] == '-'){
        return -1;
    }
    else{
        throw(ClientException("Wrong!"));
    }
}


void Client::update_action_board(int result, unsigned int x, unsigned int y) {
    std:: string filename;
    if(this->player == 1) {
        filename = "player_1.action_board.json";
    }
    else{
        filename= "player_2.action.board.json";
    }
    ofstream output (filename);

    string data = "{\n    \"board\": [\n";

    for(int i = 0; i < this->board_size; i++) {
        data += "        [\n";
        for (int j = 0; j < this->board_size; j++) {
            if (x == j and i == y) {
                data += "            " + to_string(result) + ",\n";
            }
            else{
                if(j == this->board_size -1){
                    data += "            0\n";
                }
                else{
                    data += "            0,\n";
                }
            }
        }
        if(i == this->board_size -1){
            data += "        ]\n";
        }
        else{
            data += "        ],\n";
        }
    }
    data += "    ]\n";
    data += "}";
    output << data;
    output.close();

}


string Client::render_action_board(){
    return "";
}
