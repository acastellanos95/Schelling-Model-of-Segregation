/*
 * SchellingClass.h
 *
 *  Created on: Aug 10, 2020
 *      Author: andre
 */

#ifndef SCHELLINGCLASS_H_
#define SCHELLINGCLASS_H_

#include <vector>
#include <random>
#include <iostream>
#include <unistd.h>

class SchellingClass {
private:
	int num_side_, num_iterations_;
	double threshold_;
	std::vector<std::vector<std::vector<int>>> game_array_;
public:
    bool is_happy(std::vector<std::vector<int>> game_array, size_t row, size_t col);
    SchellingClass(int num_side_, int num_iterations_, double threshold_);
    void set_threshold(double threshold_){this->threshold_ = threshold_;}
    double threshold(){return this->threshold_;}
    void print();
    void shuffle();
    void play();
    void display();
	virtual ~SchellingClass();
};

#endif /* SCHELLINGCLASS_H_ */
