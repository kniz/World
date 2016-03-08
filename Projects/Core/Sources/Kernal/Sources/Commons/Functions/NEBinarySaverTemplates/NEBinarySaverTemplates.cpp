#include "NEBinarySaverTemplates.hpp"

namespace NE
{
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const char& data)
	{
		saver.execute(reinterpret_cast<const char* const>(&data), sizeof(data));

		return saver;
	}
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const wchar_t& data)
	{
		saver.execute(reinterpret_cast<const char* const>(&data), sizeof(data));

		return saver;
	}
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const bool& data)
	{
		saver.execute(reinterpret_cast<const char* const>(&data), sizeof(data));

		return saver;
	}
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const short int& data)
	{
		saver.execute(reinterpret_cast<const char* const>(&data), sizeof(data));

		return saver;
	}	
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const int& data)
	{
		saver.execute(reinterpret_cast<const char* const>(&data), sizeof(data));

		return saver;
	}
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const long int& data)
	{
		saver.execute(reinterpret_cast<const char* const>(&data), sizeof(data));

		return saver;
	}
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const __int64& data)
	{
		saver.execute(reinterpret_cast<const char* const>(&data), sizeof(data));

		return saver;
	}
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const float& data)
	{
		saver.execute(reinterpret_cast<const char* const>(&data), sizeof(data));

		return saver;
	}
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const double& data)
	{
		saver.execute(reinterpret_cast<const char* const>(&data), sizeof(data));

		return saver;
	}
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const long double& data)
	{
		saver.execute(reinterpret_cast<const char* const>(&data), sizeof(data));

		return saver;
	}
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const unsigned char& data)
	{
		saver.execute(reinterpret_cast<const char* const>(&data), sizeof(data));

		return saver;
	}
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const unsigned short int& data)
	{
		saver.execute(reinterpret_cast<const char* const>(&data), sizeof(data));

		return saver;
	}	
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const unsigned int& data)
	{
		saver.execute(reinterpret_cast<const char* const>(&data), sizeof(data));

		return saver;
	}
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const unsigned long int& data)
	{
		saver.execute(reinterpret_cast<const char* const>(&data), sizeof(data));

		return saver;
	}
	template <>
	NEBinaryFileSaver NE_DLL &operator<<(NEBinaryFileSaver& saver, const unsigned __int64& data)
	{
		saver.execute(reinterpret_cast<const char* const>(&data), sizeof(data));

		return saver;
	}	
}
