/*!
 * \file irc/connect.hpp
 * \brief 这个文件包含了连接相关的内容。
 * \author 吞噬黑洞的数据（745275633）
 */

#include <boost/asio.hpp>
#include <boost/stsyem/error_code.hpp>

namespace DA
{

class irc
{
protected:

	boost::asio::io_service ioser;

	/**
	 * \brief （这是 protected 的）此函数用于把网址转换给 boost::asio::ip::tcp::socket::connect 函数使用。
	 *
	 * 此函数用于把网址转换为 boost::asio::ip::tcp::resolver 迭代器，给 boost::asio::ip::tcp::socket::connect 函数使用。
	 * 这是一个 protected 函数。被 resolv_connec_v2 函数使用。
	 *
	 * \param name 网址， const char * 类型。
	 *
	 * \param port 端口号 string 类型，可以是确定的数字（如：“6667”），也可以是 boost::asio::ip::tcp::resolver::query 中可以使用的文本。
	 *
	 * \par Example
	 * \code
	 * connect(sock, get_iterator(ioser, "irc.freenode.net", "6667"));
	 * \endcode
	 */
	boost::asio::ip::tcp::resolver::iterator get_iterator(const char *name,
	        string port)

public:

	/**
	 * \brief 已弃用，请使用 resolv_connec_v2
	 *
	 * 此函数用于通过网址连接。
	 *
	 * \param name 网址， const char * 类型。
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
	void resolv_connect(const char *name, string port)

	/**
	 * \brief 已弃用，请使用 resolv_connec_v2
	 *
	 * 此函数用于通过网址连接。
	 *
	 * \param name 网址， const char * 类型。
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
	boost::system::error_code resolv_connect(const char *name, string port, boost::system::error_code &ec)

	/**
	 * \brief 此函数用于通过网址连接。
	 *
	 * \param name 网址， const char * 类型。
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
	void resolv_connec_v2(const char *name, string port)

	/**
	 * \brief 此函数用于通过网址连接。
	 *
	 * \param name 网址， const char * 类型。
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
	boost::system::error_code resolv_connec_v2(const char *name, string port， boost::system::error_code &ec)
}
}
