/*!
 * \file irc/constructor.hpp
 * \brief 这个文件实现了构造函数和析构函数。
 * \author 吞噬黑洞的数据（745275633）
 */

#ifndef DA_IRC_CONSTRUCTOR_HPP
#define DA_IRC_CONSTRUCTOR_HPP

#include <iostream>
#include <memory>

namespace DA
{

irc::irc()
{
	sock = std::make_shared<boost::asio::ip::tcp::socket>(ioser);
	version = std::make_shared<version_b>();
	std::cout << version->makeinfo << std::endl;
}

irc::~irc()
{
	std::cout << version->makeinfo << std::endl;
	quit();
}

irc::irc(std::string name, std::string port): irc()
{
	boost::system::error_code ec;
	resolv_connec_v2(name, port, ec);
	DA_IRC_THROW_ERROR(ec);
}

irc::irc(std::string name, std::string port, boost::system::error_code &ec): irc()
{
	resolv_connec_v2(name, port, ec);
}

irc::irc(std::string name, std::string port, std::string username, std::string hostname,
         std::string servername, std::string realname): irc(name, port)
{
	boost::system::error_code ec;
	user(username, hostname, servername, realname, ec);
	DA_IRC_THROW_ERROR(ec);
	nick(username, ec);
	DA_IRC_THROW_ERROR(ec);
}

irc::irc(std::string name, std::string port, std::string username, std::string hostname,
         std::string servername, std::string realname, boost::system::error_code &ec): irc(name, port, ec)
{
	if (ec) return;

	user(username, hostname, servername, realname, ec);

	if (ec) return;

	nick(username, ec);
}

irc::irc(std::string name, std::string port, std::string username, std::string hostname,
         std::string servername, std::string realname, std::string channel): irc(name, port, username,
	                 hostname, servername, realname)
{
	boost::system::error_code ec;
	join(channel, ec);
	DA_IRC_THROW_ERROR(ec);
}

irc::irc(std::string name, std::string port, std::string username, std::string hostname,
         std::string servername, std::string realname, std::string channel,
         boost::system::error_code &ec): irc(name, port, username, hostname, servername, realname, ec)
{
	if (ec) return;

	join(channel, ec);
}

irc::irc(std::string name, std::string port, std::string username, std::string hostname,
         std::string servername, std::string realname, std::string channel, std::string key): irc(name, port,
	                 username, hostname, servername, realname)
{
	boost::system::error_code ec;
	join(channel, key);
	DA_IRC_THROW_ERROR(ec);
}

irc::irc(std::string name, std::string port, std::string username, std::string hostname,
         std::string servername, std::string realname, std::string channel, std::string key,
         boost::system::error_code &ec): irc(name, port, username, hostname, servername, realname, ec)
{
	if (ec) return;

	join(channel, key, ec);
}

}

#endif
