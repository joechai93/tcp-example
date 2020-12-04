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

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

#include "bare_bones_tcp_client.h"

BareBonesTCPClient::BareBonesTCPClient(std::string ip_address, uint16_t port)
    : m_sock{}
    , m_ip_address{ip_address}
    , m_port{port}
    , m_run_client{true}
{
    // create a socket
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
}

BareBonesTCPClient::~BareBonesTCPClient()
{
    // close socket
    close(m_sock);

    std::cout << "closed client socket " << std::endl;
}

int BareBonesTCPClient::RunClient(void)
{
    if (m_sock == -1)
    {
        return 1;
    }
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(m_port);
    inet_pton(AF_INET, m_ip_address.c_str(), &hint.sin_addr);

    // connect to the server on the socket
    int connectRes = connect(m_sock, (sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1)
    {
        return 1;
    }

    // while loop
    char buf[4096];
    std::string userInput;

    do {
        // enter lines of text
        std::cout << "> ";
        getline(std::cin, userInput);
        // send to server
        int sendRes = send(m_sock, userInput.c_str(), userInput.size() + 1, 0);
        // TODO: check if that failed
        // wait for response 
        memset(buf, 0, 4096);
        int bytesReceived = recv(m_sock, buf, 4096, 0);

        // display response 
        std::cout << "SERVER> " << std::string(buf, bytesReceived) << "\r\n";

    } while(m_run_client);
}

void BareBonesTCPClient::Shutdown()
{
    m_run_client = false;
}