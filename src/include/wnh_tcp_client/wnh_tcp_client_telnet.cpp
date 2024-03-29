#include "wnh_tcp_client.h"

string wnh_tcp_client::is_port_open(const string & domain, const string & port)
{
    addrinfo *result;
    addrinfo hints{};
    hints.ai_family = AF_UNSPEC;   // either IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;
    char addressString[INET6_ADDRSTRLEN];
    const char *retval = nullptr;
    if (0 != getaddrinfo(domain.c_str(), port.c_str(), &hints, &result))
    {
        return "";
    }
    for (addrinfo *addr = result; addr != nullptr; addr = addr->ai_next)
    {
        int handle = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (handle == -1)
        {
            continue;
        }
        if (connect(handle, addr->ai_addr, addr->ai_addrlen) != -1)
        {
            switch(addr->ai_family) {
                case AF_INET:
                {
                    retval = inet_ntop(addr->ai_family, &(reinterpret_cast<sockaddr_in *>(addr->ai_addr)->sin_addr), addressString, INET6_ADDRSTRLEN);
                    break;
                }
                case AF_INET6:
                {
                    retval = inet_ntop(addr->ai_family, &(reinterpret_cast<sockaddr_in6 *>(addr->ai_addr)->sin6_addr), addressString, INET6_ADDRSTRLEN);
                    break;
                }
                default:
                {
                    retval = nullptr;
                }
            }
            close(handle);
            break;
        }
    }
    freeaddrinfo(result);
    return retval==nullptr ? "" : domain + ":" + retval + "\n";
}

//如果返回true，则说明，某个服务处于监听状态，同时说明这个端口号已经被这个服务所占用，
//不能再被其他服务所用
bool wnh_tcp_client::is_listening(const string & ip, const string & port)
{
    string addr = is_port_open(ip, port);
    if(addr.empty())
    {
        return false;
    }
    return true;
}
