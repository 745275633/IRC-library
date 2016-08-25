/*!
 * \file irc/irc.hpp
 * \brief 这个文件定义了irc_class的一些基本信息。
 * \author 吞噬黑洞的数据（745275633）
 */

#include <boost/smart_ptr.hpp>

namespace DA
{

class irc
{
protected:
	/// 主要的连接
	boost::shared_ptr<tcp::socket> sock;
}
}
