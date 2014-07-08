#include "NEBinaryLoaderTemplates.hpp"

namespace NE
{
	template <>
	NEBinaryFileLoader NE_DLL &operator>>(NEBinaryFileLoader& loader, NEType::Type& data)
	{
		loader.execute(reinterpret_cast<char*>(&data), sizeof(data));

		return loader;
	}
	template <>
	NEBinaryFileLoader NE_DLL &operator>>(NEBinaryFileLoader& loader, bool& data)
	{
		loader.execute(reinterpret_cast<char*>(&data), sizeof(data));

		return loader;
	}
	template <>
	NEBinaryFileLoader NE_DLL &operator>>(NEBinaryFileLoader& loader, char& data)
	{
		loader.execute(reinterpret_cast<char*>(&data), sizeof(data));

		return loader;
	}
	template <>
	NEBinaryFileLoader NE_DLL &operator>>(NEBinaryFileLoader& loader, wchar_t& data)
	{
		loader.execute(reinterpret_cast<char*>(&data), sizeof(data));

		return loader;
	}	
	template <>
	NEBinaryFileLoader NE_DLL &operator>>(NEBinaryFileLoader& loader, short int& data)
	{
		loader.execute(reinterpret_cast<char*>(&data), sizeof(data));

		return loader;
	}
	template <>
	NEBinaryFileLoader NE_DLL &operator>>(NEBinaryFileLoader& loader, int& data)
	{
		loader.execute(reinterpret_cast<char*>(&data), sizeof(data));

		return loader;
	}
	template <>
	NEBinaryFileLoader NE_DLL &operator>>(NEBinaryFileLoader& loader, long int& data)
	{
		loader.execute(reinterpret_cast<char*>(&data), sizeof(data));

		return loader;
	}	
	template <>
	NEBinaryFileLoader NE_DLL &operator>>(NEBinaryFileLoader& loader, __int64& data)
	{
		loader.execute(reinterpret_cast<char*>(&data), sizeof(data));

		return loader;
	}
	template <>
	NEBinaryFileLoader NE_DLL &operator>>(NEBinaryFileLoader& loader, float& data)
	{
		loader.execute(reinterpret_cast<char*>(&data), sizeof(data));

		return loader;
	}
	template <>
	NEBinaryFileLoader NE_DLL &operator>>(NEBinaryFileLoader& loader, double& data)
	{
		loader.execute(reinterpret_cast<char*>(&data), sizeof(data));

		return loader;
	}
	template <>
	NEBinaryFileLoader NE_DLL &operator>>(NEBinaryFileLoader& loader, long double& data)
	{
		loader.execute(reinterpret_cast<char*>(&data), sizeof(data));

		return loader;
	}
	template <>
	NEBinaryFileLoader NE_DLL &operator>>(NEBinaryFileLoader& loader, unsigned char& data)
	{
		loader.execute(reinterpret_cast<char*>(&data), sizeof(data));

		return loader;
	}
	template <>
	NEBinaryFileLoader NE_DLL &operator>>(NEBinaryFileLoader& loader, unsigned short int& data)
	{
		loader.execute(reinterpret_cast<char*>(&data), sizeof(data));

		return loader;
	}
	template <>
	NEBinaryFileLoader NE_DLL &operator>>(NEBinaryFileLoader& loader, unsigned int& data)
	{
		loader.execute(reinterpret_cast<char*>(&data), sizeof(data));

		return loader;
	}
	template <>
	NEBinaryFileLoader NE_DLL &operator>>(NEBinaryFileLoader& loader, unsigned long int& data)
	{
		loader.execute(reinterpret_cast<char*>(&data), sizeof(data));

		return loader;
	}
	template <>
	NEBinaryFileLoader NE_DLL &operator>>(NEBinaryFileLoader& loader, unsigned __int64& data)
	{
		loader.execute(reinterpret_cast<char*>(&data), sizeof(data));

		return loader;
	}	
}
