/*!
 * \file irc/version.hpp
 * \brief 这个文件定义了版本信息。
 * \author 吞噬黑洞的数据（745275633）
 */

#ifndef DA_IRC_VERSION_HPP
#define DA_IRC_VERSION_HPP

namespace DA
{
class irc::version_b
{
public:
	const int VERSION_MAJOR = 0;
	const int MAJOR_VERSION = 0;
	const int VERSION_MINOR = 1;
	const int MINOR_VERSION = 1;
	const int VERSION_REVISION = 0;
	const int REVISION_VERSION = 0;
	const int VERSION_BUILD = 33;
	const int BUILD_VERSION = 33;
	const char VERSION[50] = "0.1.0 Build 33";
	const char makeinfo[100] = "Made from DA's IRC library 0.1.0 Build 33";
};
}

#endif
