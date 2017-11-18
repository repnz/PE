#include <PE.Parser/StreamParser.h>

std::string StreamParser::ReadString(const uint32_t pos)
{
	std::string str;

	_stream.seekg(pos);

	char buff[25];


	while (true)
	{
		_stream.read(buff, sizeof(buff)-1);
		
		// get length
		buff[24] = 0;
		const size_t len = strlen(buff);

		// append buffer
		str.append(buff, len);

		// if the buffer length is not full, finished
		if (len < sizeof(buff))
		{
			break;
		}
	}

	return str;
}

void StreamParser::Move(const int value)
{
	std::strstream::pos_type pos = _stream.tellg();

	pos += value;

	_stream.seekg(pos);
}