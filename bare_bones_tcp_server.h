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

#ifndef __BARE_BONES_TCP_SERVER_H__
#define __BARE_BONES_TCP_SERVER_H__

#include <string>
#include <functional>

class BareBonesTCPServer
{
    public:
        BareBonesTCPServer(std::string ip_address, uint16_t port, std::function<std::string(std::string)> action_function);
        ~BareBonesTCPServer();
        void Shutdown();
        int RunServer(void);
    private:
        int m_listening;
        int m_client_socket;
        std::string m_ip_address;
        uint16_t m_port;
        bool m_run_server;
        std::function<std::string(std::string)> m_action_function;
};

#endif /* __BARE_BONES_TCP_SERVER_H__ */