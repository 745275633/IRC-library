/*!
 * \file src/perform.hpp
 * \brief 这个文件是操作/执行相关的内容的实现。
 * \author 吞噬黑洞的数据（745275633）
 */

#ifndef DA_IRC_PERFORM_HPP
#define DA_IRC_PERFORM_HPP

#include <irc/irc.hpp>

namespace DA
{
	void irc::send(std::string message)
	{
		boost::system::error_code ec;
		boost::mutex::scoped_lock lock(mu);
		sock->write_some(boost::asio::buffer(message + "\r\n"), ec);
		boost::asio::detail::throw_error(ec, "DA::irc::send");
	}
	
	boost::system::error_code irc::send(std::string message, boost::system::error_code &ec)
	{
		boost::mutex::scoped_lock lock(mu);
		sock->write_some(boost::asio::buffer(message + "\r\n"), ec);
		return ec;
	}
}

#endif
