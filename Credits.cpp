#include <iostream>
#include <string>
#include "Credits.h"

/**
 * @brief Construct a new Credits::Credits object
 * 
 * @param name {std::string} Student Name
 * @param id   {std::string} Student ID
 */
Credits::Credits(std::string name, std::string id): name(name), id(id) {}

Credits::~Credits() {}

void Credits::print() {
  std::cout << "Name: " << this->name << std::endl
            << "Student ID: " << this->id << std::endl
            << "Email: " << this->id << "@student.rmit.edu.au" << std::endl << std::endl;
}
