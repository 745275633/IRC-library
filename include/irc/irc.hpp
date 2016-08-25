/*!
 * \file irc.hpp
 * \brief irc_class。
 * \author 吞噬黑洞的数据（745275633）
 */

#ifndef DA_IRC_IRC_HPP
#define DA_IRC_IRC_HPP

#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <boost/thread.hpp>
#include <string>

namespace DA
{

class irc
{
private:

	irc(const irc &c);
	irc &operator=(const irc &c);

protected:

	boost::mutex mu;
	boost::asio::io_service ioser;
	boost::shared_ptr<boost::asio::ip::tcp::socket> sock;

	/**
	 * \brief （这是 protected 的）此函数用于把网址转换给 boost::asio::ip::tcp::socket::connect 函数使用。
	 *
	 * 此函数用于把网址转换为 boost::asio::ip::tcp::resolver 迭代器，给 boost::asio::ip::tcp::socket::connect 函数使用。
	 * 这是一个 protected 函数。被 resolv_connec_v2 函数使用。
	 *
	 * \param name 网址， string 类型。
	 *
	 * \param port 端口号 string 类型，可以是确定的数字（如：“6667”），也可以是 boost::asio::ip::tcp::resolver::query 中可以使用的文本。
	 *
	 * \par Example
	 * \code
	 * connect(sock, get_iterator(ioser, "irc.freenode.net", "6667"));
	 * \endcode
	 */
	boost::asio::ip::tcp::resolver::iterator get_iterator(std::string name, std::string port);

public:
	/**
	 * \brief 这个缺省构造函数只进行初始化。
	 */
	irc();

	/**
	 * \brief 析构函数发送 "QUIT" 消息。
	 */
	~irc();

	/**
	 * \brief 初始化的同时还进行连接
	 *
	 * \param ioser boost::asio::io_service
	 *
	 * \par Example
	 * \code
	 * boost::asio::io_service ioser;
	 * DA::irc(ios);
	 * \endcode
	 */
	irc(std::string names, std::string port);

	/**
	 * \brief irc 库的版本信息。
	 */
	class version;

	/**
	 * \brief 已弃用，请使用 resolv_connec_v2
	 *
	 * 此函数用于通过网址连接。
	 *
	 * \param name 网址， string 类型。
	 *
	 * \param port 端口号 string 类型，可以是确定的数字（如：“6667”），也可以是 boost::asio::ip::tcp::resolver::query 中可以使用的文本。
	 *
	 * \throws boost::system::system_error 抛出错误.
	 *
	 * \par Example
	 * \code
	 * resolv_connect("irc.freenode.net", "6667");
	 * \endcode
	 */
	void resolv_connect(std::string name, std::string port);

	/**
	 * \brief 已弃用，请使用 resolv_connec_v2
	 *
	 * 此函数用于通过网址连接。
	 *
	 * \param name 网址， string 类型。
	 *
	 * \param port 端口号 string 类型，可以是确定的数字（如：“6667”），也可以是 boost::asio::ip::tcp::resolver::query 中可以使用的文本。
	 *
	 * \param ec 表明发生了什么错误，如果有。
	 *
	 * \return 同 param ec
	 *
	 * \par Example
	 * \code
	 * boost::system::error_code ec;
	 * resolv_connect("irc.freenode.net", "6667"， ec);
	 * if (ec)
	 * {
	 *   // 一个错误发生。
	 * }
	 * \endcode
	 */
	boost::system::error_code resolv_connect(std::string name, std::string port,
	        boost::system::error_code &ec);

	/**
	 * \brief 此函数用于通过网址连接。
	 *
	 * \param name 网址， string 类型。
	 *
	 * \param port 端口号 string 类型，可以是确定的数字（如：“6667”），也可以是 boost::asio::ip::tcp::resolver::query 中可以使用的文本。
	 *
	 * \throws boost::system::system_error 抛出错误.
	 *
	 * \par Example
	 * \code
	 * resolv_connect("irc.freenode.net", "6667");
	 * \endcode
	 */
	void resolv_connec_v2(std::string name, std::string port);

	/**
	 * \brief 此函数用于通过网址连接。
	 *
	 * \param name 网址， string 类型。
	 *
	 * \param port 端口号 string 类型，可以是确定的数字（如：“6667”），也可以是 boost::asio::ip::tcp::resolver::query 中可以使用的文本。
	 *
	 * \param ec 表明发生了什么错误，如果有。
	 *
	 * \return 同 param ec
	 *
	 * \par Example
	 * \code
	 * boost::system::error_code ec;
	 * resolv_connect("irc.freenode.net", "6667"， ec);
	 * if (ec)
	 * {
	 *   // 一个错误发生。
	 * }
	 * \endcode
	 */
	boost::system::error_code resolv_connec_v2(std::string name, std::string port,
	        boost::system::error_code &ec);
	
	/**
	 * \brief 此函数用于向服务器发送命令。
	 *
	 * \param message 命令内容， string 类型。
	 *
	 * \throws boost::system::system_error 抛出错误.
	 * 
	 * \par Example
	 * \code
	 * DA::irc::send("QUIT");
	 * \endcode
	 */
	void send(std::string message);
	
	/**
	 * \brief 此函数用于向服务器发送命令。
	 *
	 * \param message 命令内容， string 类型。
	 *
	 * \param ec 表明发生了什么错误，如果有。
	 *
	 * \return 同 param ec
	 *
	 * \par Example
	 * \code
	 * boost::system::error_code ec;
	 * DA::irc::send("QUIT");
	 * if (ec)
	 * {
	 *   // 一个错误发生。
	 * }
	 * \endcode
	 */
	boost::system::error_code send(std::string message, boost::system::error_code &ec);
	
	
};
}

#endif

