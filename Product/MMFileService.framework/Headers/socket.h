#ifndef BASE_TOOL_SOCKET_SOCKET_H_
#define BASE_TOOL_SOCKET_SOCKET_H_

#include <stdint.h>
#include <sys/types.h>

namespace base_tool {
    ssize_t SocketRead(int sockfd, void*buf, size_t count, int timeout);
    ssize_t SocketWrite(int sockfd, const void *buf, size_t count, int timeout);
    ssize_t SocketReadN(int sockfd, void *buf, size_t nbyte, int timeout);
    ssize_t SocketWriteN(int sockfd, const void *buf, size_t count, int timeout);
    int SocketCreateTcpListen(const char * ip_str, uint16_t port);
    int SocketCreateTcpConnect(const char *hostname, const char *servname, int timeout);
}
#endif //BASE_TOOL_SOCKET_SOCKET_H_
