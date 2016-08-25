/*************************************************************************
    > 文件名: src/web/init.hpp
    > 作者: 吞噬黑洞的数据（745275633）
    > 邮箱: 7452756333@163.com
    > 创建时间: 2016年08月22日 星期一 15时34分48秒
    >
 ************************************************************************/

#include "web.hpp"

void resolv_connect(tcp::socket &sock, const char *name, string port)
{
	tcp::resolver rlv(sock.get_io_service());
	tcp::resolver::query qry(name, port);
	tcp::resolver::iterator iter = rlv.resolve(qry);
	tcp::resolver::iterator end;
	system::error_code ec = error::host_not_found;

	for (; ec && iter != end; ++iter)
	{
		sock.close();
		sock.connect(*iter, ec);
	}

	if (ec)
	{
		DEBUGOUT("无法连接");
		throw system::system_error(ec);
	}
}

tcp::resolver::iterator get_iterator(io_service &ioser, const char *name, string port)
{
	tcp::resolver rlv(ioser);
	tcp::resolver::iterator iter = rlv.resolve(tcp::resolver::query(name, port));
	return iter;
}

