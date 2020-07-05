#include <cstdint>
#include <fstream>

bool isBigEndian()
{
	static const char bigEndianOne[sizeof(std::int32_t)] = { 0, 0, 0, 1 };
	
	return bigEndianOne[sizeof(std::int32_t) - 1];
}

class BigEndianStream
{
private:
	std::filebuf buffer;
	bool bufOpen;
public:
	bool isOpen()
	{
		return bufOpen;
	}
	
	template<typename T> T read()
	{
		if (!bufOpen) return;
		
		T input;
		
		char * pInput = reinterpret_cast<char *>(&input);
		
		if (isBigEndian())
		{
			buffer->sgetn(pInput, sizeof(T));
		}
		else for (int i = sizeof(T) - 1; i >= 0; i--)
		{
			pInput[i] = buffer->sgetc();
		}
		
		return input;
	}
	
	template<typename T> void write(T output)
	{
		if (!bufOpen) return;
		
		char * pOutput = reinterpret_cast<char *>(&output);
		
		if (isBigEndian())
		{
			buffer->sputn(pOutput, sizeof(T));
		}
		else for (int i = sizeof(T) - 1; i >= 0; i--)
		{
			buffer->sputc(pOutput[i]);
		}	
	}
	
	BigEndianStream(const char * path) : buffer()
	{
		bufOpen = buffer.open(path) != nullptr;
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