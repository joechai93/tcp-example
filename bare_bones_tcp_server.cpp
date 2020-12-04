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
// #include <sys/ioctl.h>

#include "bare_bones_tcp_server.h"

BareBonesTCPServer::BareBonesTCPServer(uint16_t port, std::function<std::string(std::string)> action_function)
    : m_client_socket{}
    , m_port{port}
    , m_run_server{true}
{
    // create a socket
    m_listening = socket(AF_INET, SOCK_STREAM, 0);

    m_action_function = std::bind(action_function, std::placeholders::_1);
}

BareBonesTCPServer::~BareBonesTCPServer()
{
    // close socket
    close(m_client_socket);

    std::cout << "closed client socket " << std::endl;
}

int BareBonesTCPServer::RunServer(void)
{
    if (m_listening == -1)
    {
        std::cerr << "Can't create a socket\n";
        return -1;
    }

    // Bind the socket to a IP / Port
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(m_port);
    hint.sin_addr.s_addr = INADDR_ANY;
    if (bind( m_listening, (sockaddr*)&hint, sizeof(hint)) == -1)
    {
        std::cerr << "Can't bind to IP/Port\n";
        return -2;
    }

    // Mark the socket for listening in
    if (listen(m_listening, SOMAXCONN) == -1)
    {
        std::cerr << "Can't listen\n";
        return -3;
    }

    // accept a call
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];

    int clientSocket = accept(m_listening, (sockaddr*)&client, &clientSize);

    if (clientSocket == -1)
    {
        std::cerr << "Problem with client connecting!\n";
        return -4;
    }
    
    // close the listening socket

    close(m_listening);

    memset(host, 0, NI_MAXHOST);
    memset(svc, 0, NI_MAXSERV);

    int result = getnameinfo((sockaddr*)&client,
                            sizeof(client),
                            host,
                            NI_MAXHOST,
                            svc,
                            NI_MAXSERV,
                            0);

    if (result)
    {
        std::cout << host << " connected on " << svc << std::endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << "connected on " << ntohs(client.sin_port) <<std::endl;
    }
    
    // while receiving display message, echo message
    char buf[4096];
    while (m_run_server)
    {
        // clear buffer
        memset(buf, 0, 4096);
        // wait for message
        int bytesRecv = recv(clientSocket, buf, 4096, 0);
        if (bytesRecv == -1)
        {
            std::cerr << "There was a connection issue\n";
            break;
        } else if (bytesRecv == 0) {
            std::cout << "The client disconnected\n";
            break;
        } else {
            std::cout << "Received: " << std::string(buf, 0, bytesRecv) << std::endl;
            std::string response = m_action_function(std::string(buf, 0, bytesRecv)); // perform required action
            // Resend message
            send(clientSocket, response.c_str(), response.size() + 1, 0);
        }
    }

}

void BareBonesTCPServer::Shutdown()
{
    m_run_server = false;
}
