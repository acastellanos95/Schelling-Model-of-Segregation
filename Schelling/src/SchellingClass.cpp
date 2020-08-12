/*
 * SchellingClass.cpp
 *
 *  Created on: Aug 10, 2020
 *      Author: andre
 */

#include "SchellingClass.h"

void SchellingClass::print(){
	for(auto &iter: this->game_array_){
	        std::cout << "[";
	        for (auto &row : iter)
	        {
	            std::cout << "[";
	            for (auto &&num : row)
	            {
	                std::cout << num << " , ";
	            }

	            std::cout << "]\n";

	        }

	        std::cout << "]\n";

	    }
}

void SchellingClass::display(){
    std::cout << "\x1b[2j";
    std::cout << "\x1b[H";
    while(true){
        for (size_t iter = 0; iter < this->game_array_.size(); iter++)
        {
            std::cout << "\n";
            for (size_t row = 0; row < this->game_array_[0].size(); row++)
            {
                std::cout << "\t";
                for (size_t col = 0; col < this->game_array_[0][0].size(); col++)
                {
                    if(this->game_array_[iter][row][col] == 0){
                    	std::cout << " @ ";
                    }else if(this->game_array_[iter][row][col] == 1){
                        std::cout << " # ";
                    }else{
                    	std::cout << " · ";
                    }
                }
                std::cout << std::endl;
            }

            std::cout << "\x1b[H";
            usleep(100000);
        }
        /* if(!repeat){
            timer += 100000;
            std::cout << timer << std::endl;
            break;
        } */
    }
}

void SchellingClass::shuffle(){
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0,2);

	for(auto &row: this->game_array_[0]){
		for(auto &num: row){
			num = distribution(generator);
		}
	}

}

bool SchellingClass::is_happy(std::vector<std::vector<int>> game_array, size_t row, size_t col){
	int count_similar = 0, count_different = 0;
//	positions
	int center = game_array[row][col];
	int up_left = game_array[(row-1)%this->num_side_][(col-1)%this->num_side_];
	int up = game_array[(row-1)%this->num_side_][col];
	int up_right = game_array[(row-1)%this->num_side_][(col+1)%this->num_side_];
	int left = game_array[row][(col-1)%this->num_side_];
	int right = game_array[row][(col+1)%this->num_side_];
	int down_left = game_array[(row+1)%this->num_side_][(col-1)%this->num_side_];
	int down = game_array[(row+1)%this->num_side_][col];
	int down_right = game_array[(row+1)%this->num_side_][(col+1)%this->num_side_];
	std::vector<int> positions {
		up_left, up, up_right,
		left,		 right,
		down_left, down, down_right
	};
	for(auto &position: positions){
		if(position == center){
			++count_similar;
		}else if(position == 0){
			continue;
		}else{
			++count_different;
		}
	}
	int total = count_similar + count_different;
	if(total == 0)
		return false;
	else if((double) count_similar/total < this->threshold_){
		return false;
	}else{
		return true;
	}
}

void SchellingClass::play(){
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0,this->num_side_-1);
	for (size_t iterations = 0; iterations < game_array_.size() - 1; iterations++)
	{
		for (size_t row = 0; row < game_array_[0].size(); row++)
		{
			for (size_t col = 0; col < game_array_[0][0].size(); col++)
			{
				if(game_array_[iterations][row][col] == 0)
					continue;
				else if(is_happy(game_array_[iterations], row, col)){
					bool find_new_position = true;
					while(find_new_position){
						size_t new_row = distribution(generator);
						size_t new_col = distribution(generator);
						if(game_array_[iterations][new_row][new_col] == 0){
							game_array_[iterations][new_row][new_col] = game_array_[iterations][row][col];
							game_array_[iterations][row][col] = 0;
							find_new_position = false;
						}
					}
				}
			}
		}
		game_array_[iterations+1] = game_array_[iterations];
	}
}

SchellingClass::SchellingClass(int num_side_, int num_iterations_, double threshold) :
	num_side_(num_side_), num_iterations_(num_iterations_), threshold_(threshold)
{
	game_array_ = std::vector<std::vector<std::vector<int>>>(num_iterations_, std::vector<std::vector<int>>(num_side_, std::vector<int>(num_side_, 0)));
}

SchellingClass::~SchellingClass() {
	// TODO Auto-generated destructor stub
}

