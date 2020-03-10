#include <getopt.h>
#include <iostream>

int main(int argc, char *argv[]) {

    // Check if the user entered a number
    std::string num;
    try{
        num = std::string(argv[1]);
    } catch(std::logic_error) {
        std::cout << "Please include a number to process." << std::endl;
        return -1;
    }

    // TODO: Add in number checking

    std::cout << "Processing " << num << " with 3 nodes\n";
    
    // TODO: Start different processing nodes
}