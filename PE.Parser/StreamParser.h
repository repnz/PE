#pragma once
#include <istream>
#include <strstream>
#include <vector>

class StreamParser
{
private:
	std::istream& _stream;
public:
	explicit StreamParser(std::istream& stream);

	template <typename T>
	void Read(T* ptr, const std::size_t size);

	template <typename T>
	void Read(T* ptr, const std::strstream::pos_type pos, const std::size_t size);

	template <typename T>
	void ReadFrom(T* ptr, const std::strstream::pos_type pos);

	template <typename T>
	void Read(T* ptr);

	template <typename T>
	T Read(const std::strstream::pos_type pos);

	template <typename T>
	T Read();

	template <typename T>
	std::vector<T> ReadVector(const std::size_t count);

	template <typename T>
	std::vector<T> ReadVector(const std::size_t count, const std::strstream::pos_type pos);

	void Move(const int value);

	template <typename T>
	void ReadVector(std::vector<T>& v, const std::strstream::pos_type pos, const std::size_t count);

	template <typename T>
	void ReadNullTerminatedVector(std::vector<T>& v);

	template <typename T>
	void ReadVector(std::vector<T>& v, const std::size_t count);

	std::string ReadString();

	std::string ReadString(uint32_t filePointer);
	
	void Seek(const uint32_t filePointer);
};

inline StreamParser::StreamParser(std::istream& stream) : _stream(stream)
{
}

template <typename T>
void StreamParser::Read(T* ptr, const std::strstream::pos_type pos, const std::size_t size)
{
	_stream.seekg(pos);
	Read(ptr, size);
}


template <typename T>
void StreamParser::ReadFrom(T* ptr, const std::strstream::pos_type pos)
{
	Read(ptr, pos, sizeof(T));
}

template <typename T>
void StreamParser::Read(T* ptr, const std::size_t size)
{	
	_stream.read(reinterpret_cast<char*>(ptr), size);
}

template <typename T>
void StreamParser::Read(T* ptr)
{
	Read(ptr, sizeof(T));
}

template <typename T>
T StreamParser::Read(const std::strstream::pos_type pos)
{
	T data;
	ReadFrom(&data, pos);
	return data;
}

template <typename T>
T StreamParser::Read()
{
	T data;
	Read(&data, sizeof(T));
	return data;
}

template <typename T>
std::vector<T> StreamParser::ReadVector(const std::size_t count)
{
	if (count == 0)
	{
		return std::vector<T>();
	}

	std::vector<T> v(count);

	ReadVector(v, count);

	return v;
}


template <typename T>
void StreamParser::ReadVector(std::vector<T>& v, const std::size_t count)
{
	if (count == 0)
	{
		return;
	}

	Read<T>(v.data(), count * sizeof(T));
}

template <typename T>
void StreamParser::ReadVector(std::vector<T>& v, const std::strstream::pos_type pos, const std::size_t count)
{
	_stream.seekg(pos);

	ReadVector<T>(v, count);
}

template <typename T>
bool IsAllZero(const T* t)
{
	const uint8_t* buff = reinterpret_cast<const uint8_t*>(t);

	for (uint32_t i = 0; i < sizeof(T); ++i)
	{
		if (buff[i] != 0)
		{
			return false;
		}
	}

	return true;
}

template <typename T>
void StreamParser::ReadNullTerminatedVector(std::vector<T>& v)
{
	uint32_t in = 0;

	do
	{
		v.resize(in + 1);
		Read(&v[in], sizeof(T));
		++in;
	}
	while (!IsAllZero(&v[in - 1]));
}


template <typename T>
std::vector<T> StreamParser::ReadVector(const std::size_t count, const std::strstream::pos_type pos)
{
	_stream.seekg(pos);

	return ReadVector<T>(count);
}
