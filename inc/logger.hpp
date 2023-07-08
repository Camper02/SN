#pragma once
#include <fstream>
#include <ctime>
#include <string>
#include <iostream>


namespace ns_log
{
	class Logger
	{
	private:
		std::ofstream log_file;
	public:
		Logger()
		{
			log_file.open("logs/log.txt");
			if (log_file.is_open())
			{
				send_message("start_logging");
			}
			else
			{
				std::cout << "gg";
			}
		}
		~Logger()
		{
			send_message("end_logging");
			log_file.close();
		}
		void send_message(std::string m)
		{
			std::time_t t = std::time(nullptr);
			std::string mes = std::asctime(std::localtime(&t));
			mes.erase(mes.size() - 6);
			mes += (";;" + m + "\n");
			log_file << mes;
		}
		void end()
		{
			send_message("end_logging");
			log_file.close();
		}
	};
}