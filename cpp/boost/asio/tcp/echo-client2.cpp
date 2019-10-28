//
// blocking_tcp_echo_client.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Based on:
// Copyright (c) 2003-2016 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

enum { max_length = 1024 };

int main(int argc, char* argv[]) {
    try {
        
        boost::asio::io_service io_service;
        const char * ip_addr = argc > 1 ? argv[1] :  "127.0.0.1";
        tcp::resolver resolver(io_service);
        tcp::resolver::query query(tcp::v4(),ip_addr , "2121");
        tcp::resolver::iterator iterator = resolver.resolve(query);

        tcp::socket socket(io_service);
        boost::asio::connect(socket, iterator);

        int nmsgs {17};
        
        for (int i = 0; i < nmsgs; ++i) {

            auto request = std::to_string(i) + '|';
            
            boost::asio::write(
                socket,
                boost::asio::buffer(request.data(), request.size()));

            char reply[max_length];

            boost::system::error_code error;
            size_t reply_length = socket.read_some(
                boost::asio::buffer(reply, max_length), error);

            if (error == boost::asio::error::eof) {
                break;
            } else if (error) { // Some other error.
                throw boost::system::system_error(error);
            }

            
            std::cout << "client: Reply is: ";
            std::cout.write(reply, reply_length);
            std::cout << "\n";
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
