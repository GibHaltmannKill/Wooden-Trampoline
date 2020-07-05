#include <cstdint>
#include <iostream>

bool isBigEndian()
{
	static const char bigEndianOne[sizeof(std::int32_t)] = { 0, 0, 0, 1 };
	
	return bigEndianOne[sizeof(std::int32_t) - 1];
}

class BigEndianStream
{
private:
	std::iostream * pStream;
public:
	template<typename T> T read()
	{
		T input;
		
		char * pInput = reinterpret_cast<char *>(&input);
		
		if (isBigEndian())
		{
			pStream->read(pInput, sizeof(T));
		}
		else
		{
			for (int i = sizeof(T) - 1; i >= 0; i--)
			{
				pStream->read(pInput + i, 1);
			}
		}
		
		return input;
	}
	
	template<typename T> void write(T output)
	{
		char * pOutput = reinterpret_cast<char *>(&pOutput);
		
		if (isBigEndian())
		{
			pStream->write(pOutput, sizeof(T));
		}
		else
		{
			for (int i = sizeof(T) - 1; i >= 0; i--)
			{
				pStream->write(pOutput + i, 1);
			}
		}
	}
	
	~BigEndianStream()
	{
		delete pStream;
	}
}

//TODO:
namespace WPM
{
	class Command
	{
		
	}
	
	namespace MAPDATA 
	{
		
	}
	
	namespace BR3LC
	{
		
	}
}