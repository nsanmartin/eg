//
// blocking_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Based on
// Copyright (c) 2003-2016 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread/thread.hpp>

using boost::asio::ip::tcp;

const int max_length = 512;

typedef boost::shared_ptr<tcp::socket> socket_ptr;

int session_counter = 0;

void session(socket_ptr sock) {
    std::cout << "server: in session " << ++session_counter << '\n';
  try   {
    while (true)     {

        char data[max_length];

        boost::system::error_code error;

        size_t length = sock->read_some(
            boost::asio::buffer(data, max_length), error);


        if (error == boost::asio::error::eof) {
            std::cout << "Connection closed cleanly by peer.\n";
            break;
        } else if (error) { // Some other error.
            throw boost::system::system_error(error);
        }

        std::cout << "server: read: '"
                  << std::string{data, data + length} << "'\n";

        boost::asio::write(*sock, boost::asio::buffer(data, length));
    }
  } catch (std::exception& e) {
      std::cerr << "server: Exception in thread: " << e.what() << "\n";
  }
}

void server(boost::asio::io_service& io_service, unsigned short port) {
    tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
    while (true) {
        socket_ptr sock(new tcp::socket(io_service));
        a.accept(*sock);
        boost::thread t(std::bind(session, sock));
    }
}

int main(int argc, char* argv[]) {
  try   {

    boost::asio::io_service io_service;
    server(io_service, 2121);
    
  } catch (std::exception& e) {
      std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
