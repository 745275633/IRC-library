/*************************************************************************
    > 文件名: src/web/runtime.cpp
    > 作者: 吞噬黑洞的数据（745275633）
    > 邮箱: 7452756333@163.com
    > 创建时间: 2016年08月22日 星期一 16时13分42秒
    >
 ************************************************************************/

#include "runtime.hpp"

extern string DAbothome;

boost::shared_ptr<tcp::socket> gsock;

string getnick(string buf)
{
	return buf.substr(1, buf.find("!~") - 1);
}

void command(string str)
{
	if (str.substr(0, 14) == "command local ")
	{
		//string tmp = str.substr(14) + " > /tmp/DAbot_out";
		std::system(str.substr(14).c_str());
		DEBUGOUT(str.substr(14).c_str());
	}
	else if (str.substr(0, 12) == "command irc ")
	{
		system::error_code ec;
		gsock->write_some(buffer(str.substr(12)), ec);

		if (ec)
			throw boost::system::system_error(ec);

		DEBUGOUT(str.substr(12).c_str());
	}
	else
	{
		if (str.substr(0, 4) == "say ")
		{
			string tmp;
			tmp = "espeak -vzh " + str.substr(4);
			std::system(tmp.c_str());
			DEBUGOUT(tmp);
		}
	}
}

void end(int sigum)
{
	string str = "QUIT\r\n";
	gsock->write_some(buffer(str));
	cout << endl << "Bye." << endl;
	exit(0);
}

void DAbot_run(config cfg)
{
	struct sigaction act;
	act.sa_flags = 0;
	act.sa_handler = end;
	sigaction(SIGINT, &act, NULL);

	try
	{
		system::error_code ec;
		io_service ioser;
		gsock = boost::make_shared<tcp::socket>(ioser);
		//ip::tcp::socket sock(ioser);
		//resolv_connect(sock, cfg.server_address.c_str(), "6667");
		connect(*gsock, get_iterator(ioser, cfg.server_address.c_str(), "6667"));
		//gsock = &sock;
		string write_buf;
		write_buf = "USER " + cfg.nickname + " " + cfg.hostname + " " + cfg.server_address + " :" +
		            cfg.realname + "\r\n";
		gsock->write_some(buffer(write_buf));
		write_buf = "NICK " + cfg.nickname + "\r\n";
		gsock->write_some(buffer(write_buf));
		write_buf = "JOIN " + cfg.channel + "\r\n";
		gsock->write_some(buffer(write_buf));

		while (true)
		{
			std::vector<char> read_buf(512, 0);
			gsock->read_some(buffer(read_buf), ec);

			if (ec == boost::asio::error::eof)
				break;
			else if (ec)
				throw boost::system::system_error(ec);

			string buf;
			buf.assign(read_buf.begin(), read_buf.end());
			buf.erase(buf.find_last_not_of('\0') + 1);
			cout << buf << flush;

			if (buf.find("!~") == string::npos)
			{
				if (buf.find("PING") != string::npos)
				{
					string tmp;
					tmp.assign(read_buf.begin(), read_buf.end());
					tmp[1] = 'O';
					gsock->write_some(buffer(tmp));
					cout << tmp;
				}
			}
			else if (buf.find("PRIVMSG") != string::npos)
			{
				ptime p = second_clock::local_time();
				date d = p.date();
				time_duration td = p.time_of_day();
				string filename;
				filename = DAbothome + "log/" + to_iso_extended_string(d);
				ofstream log(filename.c_str(), ios_base::out | ios_base::app);

				if (!log.is_open())
				{
					cerr << "日志写入失败" << endl;
				}
				else
				{
					log << "[" << td << "] <" << getnick(buf) << "> " << buf.substr(buf.find(":", 1) + 1);
					log.close();
				}

				if (buf.find(" :.") != string::npos)
				{
					command(buf.substr(buf.find(":", 1) + 2));
				}
			}
			else
			{
			}
		}
	}
	catch (std::exception &e)
	{
		cout << e.what() << endl;
		end(0);
	}

	end(0);
}
