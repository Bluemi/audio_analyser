#ifndef __DEBUG_CLASS__
#define __DEBUG_CLASS__

#include <vector>
#include <string>
#include <fstream>

#define NOTE_COLOR FBLUE
#define ERROR_COLOR FRED
#define WARN_COLOR FYELLOW
#define TEST_COLOR FPURPLE
#define DEFAULT_COLOR "\u001B[0m"

#define FBLACK "\u001B[30m"
#define FRED "\u001B[31m"
#define FGREEN "\u001B[32m"
#define FYELLOW "\u001B[33m"
#define FBLUE "\u001B[34m"
#define FPURPLE "\u001B[35m"
#define FCYAN "\u001B[36m"

namespace Debug
{
	enum Tag { endl, error, warn, note, test };
	class DebugClass
	{
		public:
			DebugClass();
			~DebugClass();

			template <typename T>
			DebugClass& operator<<(T t)
			{
				appendString(std::to_string(t));
				return *this;
			}
			DebugClass& operator<<(const char*);
			DebugClass& operator<<(const Debug::Tag tag);

			const char* LOG_FILE_NAME = "debug.log";
		private:
			void appendColor(std::string c);
			void appendString(std::string s);

			std::vector<std::string> strings_;
			std::ofstream fileWriter;
	};
	extern DebugClass out;
}

#endif
