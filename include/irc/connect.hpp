/*!
 * \file irc/connect.hpp
 * \brief 这个文件是连接相关的内容的实现。
 * \author 吞噬黑洞的数据（745275633）
 */

#ifndef DA_IRC_CONNECT_HPP
#define DA_IRC_CONNECT_HPP

#include <irc/main.hpp>

namespace DA
{

void irc::resolv_connect(std::string name, std::string port)
{
	boost::asio::ip::tcp::resolver rlv(ioser);
	boost::asio::ip::tcp::resolver::query qry(name, port);
	boost::asio::ip::tcp::resolver::iterator iter = rlv.resolve(qry);
	boost::asio::ip::tcp::resolver::iterator end;
	boost::system::error_code ec = boost::asio::error::host_not_found;

	for (; ec && iter != end; ++iter)
	{
		sock->close();
		sock->connect(*iter, ec);
	}

	DA_IRC_THROW_ERROR(ec);
	is_connect = trun;
}

boost::system::error_code irc::resolv_connect(std::string name, std::string port,
        boost::system::error_code &ec)
{
	boost::asio::ip::tcp::resolver rlv(ioser);
	boost::asio::ip::tcp::resolver::query qry(name, port);
	boost::asio::ip::tcp::resolver::iterator iter = rlv.resolve(qry);
	boost::asio::ip::tcp::resolver::iterator end;
	boost::system::error_code er = boost::asio::error::host_not_found;

	for (; er && iter != end; ++iter)
	{
		sock->close();
		sock->connect(*iter, er);
	}

	if (er)
	{
		ec = er;
	}
	else
	{
		is_connect = trun;
	}

	return ec;
}

boost::asio::ip::tcp::resolver::iterator irc::get_iterator(std::string name, std::string port)
{
	boost::asio::ip::tcp::resolver rlv(ioser);
	return rlv.resolve(boost::asio::ip::tcp::resolver::query(name, port));
}

void irc::resolv_connec_v2(std::string name, std::string port)
{
	boost::system::error_code ec;
	connect(*sock, get_iterator(name, port), ec);
	DA_IRC_THROW_ERROR(ec);
	is_connect = trun;
}

boost::system::error_code irc::resolv_connec_v2(std::string name, std::string port,
        boost::system::error_code &ec)
{
	connect(*sock, get_iterator(name, port), ec);
	if(!ec)
	{
		is_connect = trun;
	}
	return ec;
}

}

#endif
