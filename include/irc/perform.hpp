/*!
 * \file irc/perform.hpp
 * \brief 这个文件是操作/执行相关的内容的实现。
 * \author 吞噬黑洞的数据（745275633）
 */

#ifndef DA_IRC_PERFORM_HPP
#define DA_IRC_PERFORM_HPP

#include <irc/main.hpp>

namespace DA
{
std::string irc::send(std::string message)
{
	if (is_connect)
	{
		boost::system::error_code ec;
		sock->write_some(boost::asio::buffer(message + "\r\n"), ec);
		DA_IRC_THROW_ERROR(ec);
		return (message + "\n");
	}
	else
	{
		return "";
	}
}

std::string irc::send(std::string message, boost::system::error_code &ec)
{
	if (is_connect)
	{
		sock->write_some(boost::asio::buffer(message + "\r\n"), ec);
		return (message + "\n");
	}
	else
	{
		return "";
	}
}

std::string irc::receive()
{
	boost::system::error_code ec;
	char tmp[520] = {0};
	sock->read_some(boost::asio::buffer(tmp, 512), ec);
	std::string msg = tmp;
	CRLF2LF(msg);

	if (ec)
		DA_IRC_THROW_ERROR(ec);

	return msg;
}
std::string irc::receive(boost::system::error_code &ec)
{
	char tmp[520] = {0};
	sock->read_some(boost::asio::buffer(tmp, 512), ec);
	std::string msg = tmp;
	CRLF2LF(msg);
	return msg;
}
std::string irc::receive(std::string &message)
{
	boost::system::error_code ec;
	char tmp[520] = {0};
	sock->read_some(boost::asio::buffer(tmp, 512), ec);
	std::string msg = tmp;
	CRLF2LF(message);

	if (ec)
		DA_IRC_THROW_ERROR(ec);

	return message;
}
std::string irc::receive(std::string &message, boost::system::error_code &ec)
{
	char tmp[520] = {0};
	sock->read_some(boost::asio::buffer(tmp, 512), ec);
	std::string msg = tmp;
	CRLF2LF(message);
	return message;
}
}

#endif
