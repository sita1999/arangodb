////////////////////////////////////////////////////////////////////////////////
/// DISCLAIMER
///
/// Copyright 2016 ArangoDB GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author Andreas Streichardt
////////////////////////////////////////////////////////////////////////////////

#include "Scheduler/SocketUnixDomain.h"

using namespace arangodb;

size_t SocketUnixDomain::write(StringBuffer* buffer, boost::system::error_code& ec) {
  if (_encrypted) {
    return socketcommon::doWrite(_sslSocket, buffer, ec);
  } else {
    return socketcommon::doWrite(_socket, buffer, ec);
  }
}
void SocketUnixDomain::asyncWrite(boost::asio::mutable_buffers_1 const& buffer, AsyncHandler const& handler) {
  if (_encrypted) {
    return socketcommon::doAsyncWrite(_sslSocket, buffer, handler);
  } else {
    return socketcommon::doAsyncWrite(_socket, buffer, handler);
  }
}
size_t SocketUnixDomain::read(boost::asio::mutable_buffers_1 const& buffer, boost::system::error_code& ec) {
  if (_encrypted) {
    return socketcommon::doRead(_sslSocket, buffer, ec);
  } else {
    return socketcommon::doRead(_socket, buffer, ec);
  }
}
void SocketUnixDomain::shutdownReceive() {
  // mop: was not implemented for SSL. not sure if it should be?
  _socket.shutdown(boost::asio::local::stream_protocol::socket::shutdown_receive);
} 
void SocketUnixDomain::shutdownReceive(boost::system::error_code& ec) {
  // mop: was not implemented for SSL. not sure if it should be?
  _socket.shutdown(boost::asio::local::stream_protocol::socket::shutdown_receive, ec);
} 
void SocketUnixDomain::shutdownSend(boost::system::error_code& ec) {
  // mop: was not implemented for SSL. not sure if it should be?
  _socket.shutdown(boost::asio::local::stream_protocol::socket::shutdown_send, ec);
} 
int SocketUnixDomain::available(boost::system::error_code& ec) {
  return _socket.available(ec);
} 
void SocketUnixDomain::asyncRead(boost::asio::mutable_buffers_1 const& buffer, AsyncHandler const& handler) {
  if (_encrypted) {
    return socketcommon::doAsyncRead(_sslSocket, buffer, handler);
  } else {
    return socketcommon::doAsyncRead(_socket, buffer, handler);
  }
}
