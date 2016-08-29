#include <irc.hpp>
#include <iostream>

int main()

try
{
	DA::irc bot;
}
catch (std::exception &e)
{
	std::cout << boost::diagnostic_information(e) << std::endl;
}
