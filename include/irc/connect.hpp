/*!
 * \file irc/connect.hpp
 * \brief 这个文件是连接相关的内容的实现。
 * \author 吞噬黑洞的数据（745275633）
 */

#ifndef DA_IRC_CONNECT_HPP
#define DA_IRC_CONNECT_HPP

namespace DA
{

void irc::resolv_connect(std::string name, std::string port)
{
	using boost::asio::ip::tcp::resolver;
	resolver rlv(ioser);
	resolver::query qry(name, port);
	boost::system::error_code ec = boost::asio::error::host_not_found;

	for (resolver::iterator it = rlv.resolve(qry), resolver::iterator end; ec && iter != end; ++iter)
	{
		sock->close();
		sock->connect(*iter, ec);
	}

	DA_IRC_THROW_ERROR(ec);
	is_connect = true;
}

boost::system::error_code irc::resolv_connect(std::string name, std::string port,
        boost::system::error_code &ec)
{
	using boost::asio::ip::tcp::resolver;
	resolver rlv(ioser);
	resolver::query qry(name, port);
	boost::system::error_code ec = boost::asio::error::host_not_found;

	for (resolver::iterator it = rlv.resolve(qry), resolver::iterator end; ec && iter != end; ++iter)
	{
		sock->close();
		sock->connect(*iter, ec);
	}

	if (!ec)
	{
		is_connect = true;
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
	is_connect = true;
}

boost::system::error_code irc::resolv_connec_v2(std::string name, std::string port,
        boost::system::error_code &ec)
{
	connect(*sock, get_iterator(name, port), ec);

	if (!ec)
	{
		is_connect = true;
	}

	return ec;
}

}

#endif
