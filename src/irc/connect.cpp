/*!
 * \file src/connect.hpp
 * \brief 这个文件是连接相关的内容的实现。
 * \author 吞噬黑洞的数据（745275633）
 */

#include <boost/asio.hpp>

void resolv_connect(const char *name, string port)
{
	boost::asio::ip::tcp::resolver rlv(sock.get_io_service());
	boost::asio::ip::tcp::resolver::query qry(name, port);
	boost::asio::ip::tcp::resolver::iterator iter = rlv.resolve(qry);
	boost::asio::ip::tcp::resolver::iterator end;
	boost::system::error_code ec = error::host_not_found;

	for (; ec && iter != end; ++iter)
	{
		sock.close();
		sock.connect(*iter, ec);
	}

	if (ec)
	{
		boost::asio::detail::throw_error(ec, "DA::irc::resolv_connect");
	}
}

boost::system::error_code resolv_connect(const char *name, string port, boost::system::error_code &ec)
{
	boost::asio::ip::tcp::resolver rlv(sock.get_io_service());
	boost::asio::ip::tcp::resolver::query qry(name, port);
	boost::asio::ip::tcp::resolver::iterator iter = rlv.resolve(qry);
	boost::asio::ip::tcp::resolver::iterator end;
	boost::system::error_code er = error::host_not_found;

	for (; er && iter != end; ++iter)
	{
		sock.close();
		sock.connect(*iter, er);
	}

	if (er)
	{
		ec = er;
	}
	return ec;
}

boost::asio::ip::tcp::resolver::iterator get_iterator(const char *name, string port)
{
	boost::asio::ip::tcp::resolver rlv(ioser);
	return rlv.resolve(boost::asio::ip::tcp::resolver::query(name, port));
}

void resolv_connec_v2(const char *name, string port)
{
	boost::system::error_code ec;
	connect(sock, get_iterator(ioser, name, port), ec);
	boost::asio::detail::throw_error(ec, "DA::irc::resolv_connect_v2");
}

void resolv_connec_v2(tcp::socket &sock, const char *name, string port, boost::system::error_code &ec)
{
	return connect(sock, get_iterator(ioser, name, port), ec);
}
