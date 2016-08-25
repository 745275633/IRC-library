/*************************************************************************
    > 文件名: include/web.hpp
    > 作者: 吞噬黑洞的数据（745275633）
    > 邮箱: 7452756333@163.com
    > 创建时间: 2016年08月22日 星期一 15时29分55秒
    >
 ************************************************************************/

#ifndef DABOT_WEB_HPP
#define DABOT_WEB_HPP

#include <iostream>
#include <cstdlib>
using namespace std;

#include <boost/asio.hpp>
using namespace boost;
using namespace boost::asio;
using namespace boost::asio::ip;

extern "C"
{
#include <signal.h>
}

#include "debug.hpp"
#include "DAbot_config.hpp"
#include "config.hpp"

void resolv_connect(tcp::socket &sock, const char *name, string port);
tcp::resolver::iterator get_iterator(io_service &ioser, const char *name, string port);
void DAbot_run(config cfg);

#endif

