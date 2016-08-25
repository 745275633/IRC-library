/*!
 * \file irc/irc.hpp
 * \brief 定义了irc_class的一些基本信息
 * \author 吞噬黑洞的数据（745275633）
 */

#include <boost/smart_ptr.hpp>

/// \brief DA技术工作室命名空间
namespace DA
{

/// \brief 主类
class irc
{
protected:
    boost::shared_ptr<tcp::socket> socket;
}
}
