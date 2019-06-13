#pragma once

//This is used to write output into the file ./out.txt

class Log {
protected:
	Log() = default;
public:
	static void writeLog(std::string msg);	//writes string into "out.txt" file into new line
	static void emptyLog();		//empties "out.txt" file
};