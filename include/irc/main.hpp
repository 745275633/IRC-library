/*!
 * \file irc/main.hpp
 * \brief irc类的定义。
 * \author 吞噬黑洞的数据（745275633）
 */

#ifndef DA_IRC_MAIN_HPP
#define DA_IRC_MAIN_HPP

#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>
#include <boost/throw_exception.hpp>
#include <string>

#define DA_IRC_THROW_ERROR(err) \
	if (err)\
	{\
		boost::system::system_error e(err, BOOST_THROW_EXCEPTION_CURRENT_FUNCTION);\
		::boost::exception_detail::throw_exception_(e,BOOST_THROW_EXCEPTION_CURRENT_FUNCTION,__FILE__,__LINE__);\
	}

namespace DA
{

class irc : boost::noncopyable
{
protected:

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
	 * \return 返回对应的 boost::asio::ip::tcp::resolver::iterator 。
	 *
	 * \par Example
	 * \code
	 * connect(sock, get_iterator(ioser, "irc.freenode.net", "6667"));
	 * \endcode
	 */
	boost::asio::ip::tcp::resolver::iterator get_iterator(std::string name, std::string port);

	inline static void CRLF2LF(std::string &str)
	{
		std::string::size_type pos;

		while ((pos = str.find("\r\n")) != std::string::npos)
		{
			str.replace(pos, 2, "\n");
		}
	}

public:
	/**
	 * \brief 是否已连接。
	 */
	bool is_connect = false;

	/**
	 * \brief 这个缺省构造函数只进行初始化。
	 */
	irc();

	/**
	 * \brief 析构函数发送 "QUIT" 消息。
	 */
	~irc();

	/**
	 * \brief 初始化的同时还进行连接。
	 *
	 * \param name 服务器地址。
	 *
	 * \param port 端口号。
	 *
	 * \throws boost::system::system_error 抛出错误。
	 *
	 * \par Example
	 * \code
	 * DA::irc("irc.freenode.net", "6667");
	 * \endcode
	 */
	irc(std::string name, std::string port);

	/**
	 * \brief 初始化的同时还进行连接。
	 *
	 * \param name 服务器地址。
	 *
	 * \param port 端口号。
	 *
	 * \param ec 表明发生了什么错误，如果有。
	 *
	 * \par Example
	 * \code
	 * boost::system::error_code ec;
	 * DA::irc("irc.freenode.net", "6667", ec);
	 * if (ec)
	 * {
	 *   // 一个错误发生
	 * }
	 * \endcode
	 */
	irc(std::string name, std::string port, boost::system::error_code &ec);

	/**
	 * \brief 初始化的同时还进行连接、发送 USER 指令、NICK 指令。
	 *
	 * USER指令是在连接开始建立后来详细说明用户的username，hostname，servername，realname的。USER指令也被server之间用来通信用来通告一个新的用户连接上了服务器，只有当client的USER和NICK指令抵达服务器后才完成了注册连接的步骤。
	 * 一般情况下 hostname 和 servername 在服务器明确知道这是一个client发过来的USER指令的时候，他们都会被忽略。
	 * 
	 * NICK 命令是用来给予用户一个昵称或者修改之前的昵称。如果一个 NICK 信息到达了一台已经存在一个这个昵称的服务器上，就会发生 nickname 冲突。
	 *
	 * \param name 服务器地址。
	 *
	 * \param port 端口号。
	 *
	 * \param username 用户名(NICKname)。
	 *
	 * \param hostname 主机名。
	 *
	 * \param servername 服务器地址。
	 *
	 * \param realname 真名。
	 *
	 * \throws boost::system::system_error 抛出错误。
	 */
	irc(std::string name, std::string port, std::string username, std::string hostname,
	    std::string servername, std::string realname);

	/**
	 * \brief 初始化的同时还进行连接、发送 USER 指令、NICK 指令。
	 *
	 * USER指令是在连接开始建立后来详细说明用户的username，hostname，servername，realname的。USER指令也被server之间用来通信用来通告一个新的用户连接上了服务器，只有当client的USER和NICK指令抵达服务器后才完成了注册连接的步骤。
	 * 一般情况下 hostname 和 servername 在服务器明确知道这是一个client发过来的USER指令的时候，他们都会被忽略。
	 * 
	 * NICK 命令是用来给予用户一个昵称或者修改之前的昵称。如果一个 NICK 信息到达了一台已经存在一个这个昵称的服务器上，就会发生 nickname 冲突。
	 *
	 * \param name 服务器地址。
	 *
	 * \param port 端口号。
	 *
	 * \param username 用户名(NICKname)。
	 *
	 * \param hostname 主机名。
	 *
	 * \param servername 服务器地址。
	 *
	 * \param realname 真名。
	 *
	 * \param ec 表明发生了什么错误，如果有。
	 */
	irc(std::string name, std::string port, std::string username, std::string hostname,
	    std::string servername, std::string realname, boost::system::error_code &ec);

	/**
	 * \brief 初始化的同时还进行连接、发送 USER 指令、NICK 指令、JOIN指令。
	 *
	 * USER指令是在连接开始建立后来详细说明用户的username，hostname，servername，realname的。USER指令也被server之间用来通信用来通告一个新的用户连接上了服务器，只有当client的USER和NICK指令抵达服务器后才完成了注册连接的步骤。
	 * 一般情况下 hostname 和 servername 在服务器明确知道这是一个client发过来的USER指令的时候，他们都会被忽略。
	 * 
	 * NICK 命令是用来给予用户一个昵称或者修改之前的昵称。如果一个 NICK 信息到达了一台已经存在一个这个昵称的服务器上，就会发生 nickname 冲突。
	 * 
	 * JOIN指令是用来收听一个指定的频道时使用的。
	 *
	 * \param name 服务器地址。
	 *
	 * \param port 端口号。
	 *
	 * \param username 用户名(NICKname)。
	 *
	 * \param hostname 主机名。
	 *
	 * \param servername 服务器地址。
	 *
	 * \param realname 真名。
	 *
	 * \param channel 频道名。
	 *
	 * \throws boost::system::system_error 抛出错误。
	 */
	irc(std::string name, std::string port, std::string username, std::string hostname,
	    std::string servername, std::string realname, std::string channel);

	/**
	 * \brief 初始化的同时还进行连接、发送 USER 指令、NICK 指令、JOIN指令。
	 *
	 * USER指令是在连接开始建立后来详细说明用户的username，hostname，servername，realname的。USER指令也被server之间用来通信用来通告一个新的用户连接上了服务器，只有当client的USER和NICK指令抵达服务器后才完成了注册连接的步骤。
	 * 一般情况下 hostname 和 servername 在服务器明确知道这是一个client发过来的USER指令的时候，他们都会被忽略。
	 * 
	 * NICK 命令是用来给予用户一个昵称或者修改之前的昵称。如果一个 NICK 信息到达了一台已经存在一个这个昵称的服务器上，就会发生 nickname 冲突。
	 * 
	 * JOIN指令是用来收听一个指定的频道时使用的。
	 *
	 * \param name 服务器地址。
	 *
	 * \param port 端口号。
	 *
	 * \param username 用户名(NICKname)。
	 *
	 * \param hostname 主机名。
	 *
	 * \param servername 服务器地址。
	 *
	 * \param realname 真名。
	 *
	 * \param channel 频道名。
	 *
	 * \param ec 表明发生了什么错误，如果有。
	 */
	irc(std::string name, std::string port, std::string username, std::string hostname,
	    std::string servername, std::string realname, std::string channel, boost::system::error_code &ec);

	/**
	 * \brief 初始化的同时还进行连接、发送 USER 指令、NICK 指令、JOIN指令。
	 *
	 * USER指令是在连接开始建立后来详细说明用户的username，hostname，servername，realname的。USER指令也被server之间用来通信用来通告一个新的用户连接上了服务器，只有当client的USER和NICK指令抵达服务器后才完成了注册连接的步骤。
	 * 一般情况下 hostname 和 servername 在服务器明确知道这是一个client发过来的USER指令的时候，他们都会被忽略。
	 * 
	 * NICK 命令是用来给予用户一个昵称或者修改之前的昵称。如果一个 NICK 信息到达了一台已经存在一个这个昵称的服务器上，就会发生 nickname 冲突。
	 * 
	 * JOIN指令是用来收听一个指定的频道时使用的。
	 *
	 * \param name 服务器地址。
	 *
	 * \param port 端口号。
	 *
	 * \param username 用户名(NICKname)。
	 *
	 * \param hostname 主机名。
	 *
	 * \param servername 服务器地址。
	 *
	 * \param realname 真名。
	 *
	 * \param channel 频道名。
	 *
	 * \param key 频道密码。
	 *
	 * \throws boost::system::system_error 抛出错误。
	 */
	irc(std::string name, std::string port, std::string username, std::string hostname,
	    std::string servername, std::string realname, std::string channel, std::string key);

	/**
	 * \brief 初始化的同时还进行连接、发送 USER 指令、NICK 指令、JOIN指令。
	 *
	 * USER指令是在连接开始建立后来详细说明用户的username，hostname，servername，realname的。USER指令也被server之间用来通信用来通告一个新的用户连接上了服务器，只有当client的USER和NICK指令抵达服务器后才完成了注册连接的步骤。
	 * 一般情况下 hostname 和 servername 在服务器明确知道这是一个client发过来的USER指令的时候，他们都会被忽略。
	 * 
	 * NICK 命令是用来给予用户一个昵称或者修改之前的昵称。如果一个 NICK 信息到达了一台已经存在一个这个昵称的服务器上，就会发生 nickname 冲突。
	 * 
	 * JOIN指令是用来收听一个指定的频道时使用的。
	 *
	 * \param name 服务器地址。
	 *
	 * \param port 端口号。
	 *
	 * \param username 用户名(NICKname)。
	 *
	 * \param hostname 主机名。
	 *
	 * \param servername 服务器地址。
	 *
	 * \param realname 真名。
	 *
	 * \param channel 频道名。
	 *
	 * \param key 频道密码。
	 *
	 * \param ec 表明发生了什么错误，如果有。
	 */
	irc(std::string name, std::string port, std::string username, std::string hostname,
	    std::string servername, std::string realname, std::string channel, std::string key,
	    boost::system::error_code &ec);

	/**
	 * \brief irc 库的版本信息。
	 */
	class version;

	/**
	 * \brief 已弃用，请使用 resolv_connec_v2
	 *
	 * 此函数用于通过网址连接。
	 *
	 * \deprecated
	 *
	 * \param name 网址， string 类型。
	 *
	 * \param port 端口号 string 类型，可以是确定的数字（如：“6667”），也可以是 boost::asio::ip::tcp::resolver::query 中可以使用的文本。
	 *
	 * \throws boost::system::system_error 抛出错误。
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
	 * \deprecated
	 *
	 * \param name 网址， string 类型。
	 *
	 * \param port 端口号 string 类型，可以是确定的数字（如：“6667”），也可以是 boost::asio::ip::tcp::resolver::query 中可以使用的文本。
	 *
	 * \param ec 表明发生了什么错误，如果有。
	 *
	 * \return 同 参数 ec
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
	 * \throws boost::system::system_error 抛出错误。
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
	 * \return 同 参数 ec
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
	 * \throws boost::system::system_error 抛出错误。
	 *
	 * \return 返回发送的命令。
	 *
	 * \par Example
	 * \code
	 * DA::irc::send("QUIT");
	 * \endcode
	 */
	std::string send(std::string message);

	/**
	 * \brief 此函数用于向服务器发送命令。
	 *
	 * \param message 命令内容， string 类型。
	 *
	 * \param ec 表明发生了什么错误，如果有。
	 *
	 * \return 返回发送的命令。
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
	std::string send(std::string message, boost::system::error_code &ec);

	/**
	 * \brief 此函数用于接收服务器发送的信息。
	 *
	 * \throws boost::system::system_error 抛出错误。
	 *
	 * \return 返回接收的信息内容。
	 *
	 * \par Example
	 * \code
	 * string  msg = DA::irc::receive();
	 * \endcode
	 */
	std::string receive();

	/**
	 * \brief 此函数用于接收服务器发送的信息。
	 *
	 * \param ec 表明发生了什么错误，如果有。
	 *
	 * \return 返回接收的信息内容。
	 *
	 * \par Example
	 * \code
	 * boost::system::error_code ec;
	 * string  msg = DA::irc::receive();
	 * if (ec)
	 * {
	 *   // 一个错误发生。
	 * }
	 * \endcode
	 */
	std::string receive(boost::system::error_code &ec);

	/**
	 * \brief 此函数用于接收服务器发送的信息。
	 *
	 * \param message 接收的信息内容， string & 类型。
	 *
	 * \throws boost::system::system_error 抛出错误。
	 *
	 * \return 返回接收的信息内容。
	 *
	 * \par Example
	 * \code
	 * string msg;
	 * DA::irc::receive(msg);
	 * \endcode
	 */
	std::string receive(std::string &message);

	/**
	 * \brief 此函数用于接收服务器发送的信息。
	 *
	 * \param message 接收的信息内容， string & 类型。
	 *
	 * \param ec 表明发生了什么错误，如果有。
	 *
	 * \return 返回接收的信息内容。
	 *
	 * \par Example
	 * \code
	 * boost::system::error_code ec;
	 * string msg;
	 * DA::irc::receive(msg);
	 * if (ec)
	 * {
	 *   // 一个错误发生。
	 * }
	 * \endcode
	 */
	std::string receive(std::string &message, boost::system::error_code &ec);

	/**
	 * \brief 发送 QUIT 指令。
	 *
	 * 一个客户端的会话可以通过一个 QUIT 指令来终结。服务器必须在收到 client 的 QUIT 指令后关闭这个 client 的连接。
	 *
	 * \param ec 表明发生了什么错误，如果有。
	 *
	 * \return 返回发送的命令。
	 */
	std::string quit();

	/**
	 * \brief 发送 QUIT 指令。
	 *
	 * 一个客户端的会话可以通过一个 QUIT 指令来终结。服务器必须在收到 client 的 QUIT 指令后关闭这个 client 的连接。
	 *
	 * \throws boost::system::system_error 抛出错误。
	 *
	 * \return 返回发送的命令。
	 */
	std::string quit(boost::system::error_code &ec);

	/**
	 * \brief 发送 USER 指令。
	 *
	 * USER指令是在连接开始建立后来详细说明用户的username，hostname，servername，realname的。USER指令也被server之间用来通信用来通告一个新的用户连接上了服务器，只有当client的USER和NICK指令抵达服务器后才* 完成了注册连接的步骤。
	 * 一般情况下hostname和servername在服务器明确知道这是一个client发过来的USER指令的时候，他们都会被忽略。
	 *
	 * \param username 用户名(NICKname)。
	 *
	 * \param hostname 主机名。
	 *
	 * \param servername 服务器地址。
	 *
	 * \param realname 真名。
	 *
	 * \throws boost::system::system_error 抛出错误。
	 *
	 * \return 返回发送的命令。
	 */
	std::string user(std::string username, std::string hostname, std::string servername,
	                 std::string realname);

	/**
	 * \brief 发送 USER 指令。
	 *
	 * USER指令是在连接开始建立后来详细说明用户的username，hostname，servername，realname的。USER指令也被server之间用来通信用来通告一个新的用户连接上了服务器，只有当client的USER和NICK指令抵达服务器后才* 完成了注册连接的步骤。
	 * 一般情况下hostname和servername在服务器明确知道这是一个client发过来的USER指令的时候，他们都会被忽略。
	 *
	 * \param username 用户名(NICKname)。
	 *
	 * \param hostname 主机名。
	 *
	 * \param servername 服务器地址。
	 *
	 * \param realname 真名。
	 *
	 * \param ec 表明发生了什么错误，如果有。
	 *
	 * \return 返回发送的命令。
	 */
	std::string user(std::string username, std::string hostname, std::string servername,
	                 std::string realname, boost::system::error_code &ec);

	/**
	 * \brief 发送 NICK 指令。
	 *
	 * NICK 命令是用来给予用户一个昵称或者修改之前的昵称。如果一个 NICK 信息到达了一台已经存在一个这个昵称的服务器上，就会发生 nickname 冲突。
	 *
	 * \param nickname nickname。
	 *
	 * \throws boost::system::system_error 抛出错误。
	 *
	 * \return 返回发送的命令。
	 */
	std::string nick(std::string nickname);

	/**
	 * \brief 发送 NICK 指令。
	 *
	 * NICK 命令是用来给予用户一个昵称或者修改之前的昵称。如果一个 NICK 信息到达了一台已经存在一个这个昵称的服务器上，就会发生 nickname 冲突。
	 *
	 * \param nickname nickname。
	 *
	 * \param ec 表明发生了什么错误，如果有。
	 *
	 * \return 返回发送的命令。
	 */
	std::string nick(std::string nickname, boost::system::error_code &ec);

	/**
	 * \brief 发送 JOIN 指令。
	 *
	 * JOIN指令是用来收听一个指定的频道时使用的。
	 *
	 * \param channel 频道名。
	 *
	 * \throws boost::system::system_error 抛出错误。
	 *
	 * \return 返回发送的命令。
	 */
	std::string join(std::string channel);

	/**
	 * \brief 发送 JOIN 指令。
	 *
	 * JOIN指令是用来收听一个指定的频道时使用的。
	 *
	 * \param channel 频道名。
	 * 
	 * \param ec 表明发生了什么错误，如果有。
	 *
	 * \return 返回发送的命令。
	 */
	std::string join(std::string channel, boost::system::error_code &ec);

	/**
	 * \brief 发送 JOIN 指令。
	 *
	 * JOIN指令是用来收听一个指定的频道时使用的。
	 *
	 * \param channel 频道名（包括‘#’）。
	 *
	 * \param key 频道密码。
	 *
	 * \throws boost::system::system_error 抛出错误。
	 *
	 * \return 返回发送的命令。
	 */
	std::string join(std::string channel, std::string key);

	/**
	 * \brief 发送 JOIN 指令。
	 *
	 * JOIN指令是用来收听一个指定的频道时使用的。
	 *
	 * \param channel 频道名（包括‘#’）。
	 *
	 * \param key 频道密码。
	 *
	 * \param ec 表明发生了什么错误，如果有。
	 *
	 * \return 返回发送的命令。
	 */
	std::string join(std::string channel, std::string key, boost::system::error_code &ec);

};
}

#endif

