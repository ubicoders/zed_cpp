// #ifndef UDP_CLIENT_HPP
// #define UDP_CLIENT_HPP

// #include <boost/asio.hpp>
// #include <iostream>
// #include <thread>
// #include <chrono>

// using boost::asio::ip::udp;

// class UdpClient
// {
// public:
//     UdpClient(boost::asio::io_service &io_service, const std::string &host, const std::string &port)
//         : socket_(io_service), resolver_(io_service), query_(udp::v4(), host, port), server_alive_(false)
//     {
//         server_endpoint_ = *resolver_.resolve(query_);
//     }

//     void connect()
//     {
//         try
//         {
//             socket_.open(udp::v4());
//             server_alive_ = true;
//             std::cout << "Connected to server " << server_endpoint_ << std::endl;
//         }
//         catch (std::exception &e)
//         {
//             std::cerr << "Error connecting to server: " << e.what() << std::endl;
//             server_alive_ = false;
//             return;
//         }
//     }

//     void close()
//     {
//         socket_.close();
//     }

//     void send(const std::string &message)
//     {
//         try
//         {
//             socket_.send_to(boost::asio::buffer(message), server_endpoint_);
//             // std::cout << "Sent message: " << message << std::endl;
//         }
//         catch (std::exception &e)
//         {
//             std::cerr << "Error sending message: " << e.what() << std::endl;
//             server_alive_ = false; // Mark server as not alive if sending fails
//         }
//     }

//     void on_message()
//     {
//         std::cout << "Listening for messages..." << std::endl;
//         socket_.async_receive_from(
//             boost::asio::buffer(reply_, 1024), sender_endpoint_,
//             [this](const boost::system::error_code &ec, std::size_t bytes_recvd)
//             {
//                 if (!ec && bytes_recvd > 0)
//                 {
//                     std::cout << "Received message: " << std::string(reply_, bytes_recvd) << std::endl;
//                     // Continue listening for more messages
//                     on_message();
//                 }
//                 else
//                 {
//                     std::cerr << "Receive error: " << ec.message() << std::endl;
//                     if (ec != boost::asio::error::operation_aborted)
//                     {
//                         // Only restart the receive if the error was not due to an operation being aborted
//                         on_message();
//                     }
//                 }
//             });
//     }

// private:
//     udp::socket socket_;
//     udp::resolver resolver_;
//     udp::resolver::query query_;
//     udp::endpoint server_endpoint_;
//     udp::endpoint sender_endpoint_;
//     char reply_[1024];
//     bool server_alive_;
// };

// #endif // UDP_CLIENT_HPP
