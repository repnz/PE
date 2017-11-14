#pragma once
#include <istream>
#include <strstream>
#include <vector>

class Parser
{
private:
	std::istream& _stream;
public:
	explicit Parser(std::istream& stream);

	template <typename T>
	void Read(T& ptr, const std::size_t size);

	template <typename T>
	void Read(T& ptr, const std::strstream::pos_type pos, const std::size_t size);

	template <typename T>
	void Read(T& ptr, const std::strstream::pos_type pos);

	template <typename T>
	void Read(T& ptr);

	template <typename T>
	T Read(const std::strstream::pos_type pos);

	template <typename T>
	T Read();

	template <typename T>
	std::vector<T> ReadVector(const std::size_t count);

	template <typename T>
	std::vector<T> ReadVector(const std::size_t count, const std::strstream::pos_type pos);
};

inline Parser::Parser(std::istream& stream) : _stream(stream)
{
	_stream.exceptions(std::istream::failbit | std::istream::badbit);
}


template <typename T>
void Parser::Read(T& ptr, const std::strstream::pos_type pos, const std::size_t size)
{
	_stream.seekg(pos);
	Read(ptr, size);
}


template <typename T>
void Parser::Read(T& ptr, const std::strstream::pos_type pos)
{
	return Read(ptr, pos, sizeof(T));
}

template <typename T>
void Parser::Read(T& ptr, const std::size_t size)
{	
	_stream.read(reinterpret_cast<char*>(&ptr), size);
}

template <typename T>
void Parser::Read(T& ptr)
{
	Read(ptr, sizeof(T));
}

template <typename T>
T Parser::Read(const std::strstream::pos_type pos)
{
	T data;
	Read(data, pos);
	return data;
}

template <typename T>
T Parser::Read()
{
	T data;
	Read(data);
	return data;
}

template <typename T>
std::vector<T> Parser::ReadVector(const std::size_t count)
{
	std::vector<T> v(count);

	Read<T>(v[0], count*sizeof(T));

	return v;
}

template <typename T>
std::vector<T> Parser::ReadVector(const std::size_t count, const std::strstream::pos_type pos)
{
	_stream.seekg(pos);

	return ReadVector<T>(count);
}

