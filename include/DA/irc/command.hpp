/*!
 * \file irc/command.hpp
 * \brief 这个文件定义了常用的命令。
 * \author 吞噬黑洞的数据（745275633）
 */

#ifndef DA_IRC_COMMAND_HPP
#define DA_IRC_COMMAND_HPP

#include <string>
#include <sstream>

namespace DA
{
std::string irc::quit()
{
	boost::system::error_code ec;
	std::string a = send("QUIT", ec);
	DA_IRC_THROW_ERROR(ec);
	return a;
}

std::string irc::quit(boost::system::error_code &ec)
{
	return send("QUIT", ec);
}

std::string irc::user(std::string username, std::string hostname,
                      std::string servername,
                      std::string realname)
{
	boost::system::error_code ec;
	std::string a = send("USER " + username + " " + hostname + " " + servername +
	                     " :" + realname, ec);
	DA_IRC_THROW_ERROR(ec);
	return a;
}

std::string irc::user(std::string username, std::string hostname,
                      std::string servername,
                      std::string realname, boost::system::error_code &ec)
{
	return send("USER " + username + " " + hostname + " " + servername + " :" +
	            realname, ec);
}

std::string irc::nick(std::string nickname)
{
	boost::system::error_code ec;
	std::string a = send("NICK " + nickname, ec);
	DA_IRC_THROW_ERROR(ec);
	return a;
}

std::string irc::nick(std::string nickname, boost::system::error_code &ec)
{
	return send("NICK " + nickname, ec);
}

std::string irc::join(std::string channel)
{
	boost::system::error_code ec;
	std::string a = send("JOIN " + channel, ec);
	DA_IRC_THROW_ERROR(ec);
	return a;
}

std::string irc::join(std::string channel, boost::system::error_code &ec)
{
	return send("JOIN " + channel, ec);
}

std::string irc::join(std::string channel, std::string key)
{
	boost::system::error_code ec;
	std::string a = send("JOIN " + channel + " " + key, ec);
	DA_IRC_THROW_ERROR(ec);
	return a;
}

std::string irc::join(std::string channel, std::string key,
                      boost::system::error_code &ec)
{
	return send("JOIN " + channel + " " + key, ec);
}

std::string irc::privmsg(const std::string &who, const std::string &message)
{
	if (message.find("\n") == std::string::npos)
	{
		boost::system::error_code ec;
		std::string a;
		a = send("PRIVMSG " + who + " :" + message, ec);
		DA_IRC_THROW_ERROR(ec);
		return a;
	}
	else
	{
		return privmsg(who, std::stringstream(message));
	}
}

std::string irc::privmsg(const std::string &who, const std::string &message,
                         boost::system::error_code &ec)
{
	if (message.find("\n") == std::string::npos)
		return send("PRIVMSG " + who + " :" + message, ec);
	else
		return privmsg(who, std::stringstream(message), ec);
}
std::string irc::privmsg(const std::string &who, std::stringstream message)
{
	std::string s;
	std::string o;

	while (std::getline(message, s))
	{
		privmsg(who, s);
		o += s;
		o += "\n";
	}

	return o;
}
std::string irc::privmsg(const std::string &who, std::stringstream message,
                         boost::system::error_code &ec)
{
	std::string s;
	std::string o;

	while (std::getline(message, s))
	{
		privmsg(who, s, ec);
		o += s;
		o += "\n";
	}

	return o;
}
}

#endif
