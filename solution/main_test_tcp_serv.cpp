/*
MIT License

Copyright (c) 2019 Joe Chai

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <signal.h>
#include <iostream>
#include <iomanip>
#include <eigen3/Eigen/Dense>


#include "bare_bones_tcp_server.h"

void signal_callback_handler(int signum);
std::string example_action_function(std::string input);
std::string action_function(std::string input);


int main()
{
    signal(SIGINT, signal_callback_handler);
    std::function<std::string(std::string)> input_function;

    input_function = std::bind(action_function, std::placeholders::_1);

    BareBonesTCPServer tcp_server( 54000, input_function);
    tcp_server.RunServer();

    return 0;
}

void signal_callback_handler(int signum) {
    std::cout << "CTRL-C Shutdown Requested " << std::endl;
    // Terminate program
    //exit(signum);
}

std::string action_function(std::string input)
{
    return input;
}

std::string example_action_function(std::string input)
{
    std::cout <<  "action performed\n";
    return input;
}
