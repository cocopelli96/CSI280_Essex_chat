// System Level Includes
#include <iostream>
#include <string>

// Other Includes
#include "tacopie/tacopie"


/*
 *  Purpose: Main function for execution.
 *      Pre: N/A
 *     Post: N/A
 */
int main(int argc, char* argv[])
{
    std::string inputBuffer;

    while(inputBuffer.compare("exit") != 0)
    {
        std::cout << "Input some text: ";
        std::getline(std::cin, inputBuffer);

        if(inputBuffer.compare("exit") == 0)
            break;

        std::cout << "Echo: " << inputBuffer << std::endl;;
    }

    std::cout << "Bye!" << std::endl;

    return 0;

    
}