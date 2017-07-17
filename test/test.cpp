#include <DA/irc.hpp>
#include <iostream>

int main()
try
{
	DA::irc bot;
	std::cout << bot.version.makeinfo << std::endl;
}
catch (std::exception &e)
{
	std::cout << boost::diagnostic_information(e) << std::endl;
}
