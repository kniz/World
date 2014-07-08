template <typename T>
class NETemplateChecker
{
public:
	static enum 
	{
		isPrimitive = 0
	};
};

template <>
class NETemplateChecker<bool>
{
public:
	static enum
	{
		isPrimitive = 1
	};
};
template <>
class NETemplateChecker<char>
{
public:
	static enum
	{
		isPrimitive = 1
	};
};
template <>
class NETemplateChecker<wchar_t>
{
public:
	static enum
	{
		isPrimitive = 1
	};
};
template <>
class NETemplateChecker<short int>
{
public:
	static enum
	{
		isPrimitive = 1
	};
};
template <>
class NETemplateChecker<int>
{
public:
	static enum
	{
		isPrimitive = 1
	};
};
template <>
class NETemplateChecker<float>
{
public:
	static enum
	{
		isPrimitive = 1
	};
};
template <>
class NETemplateChecker<double>
{
public:
	static enum
	{
		isPrimitive = 1
	};
};
template <>
class NETemplateChecker<__int64>
{
public:
	static enum
	{
		isPrimitive = 1
	};
};
template <>
class NETemplateChecker<unsigned char>
{
public:
	static enum
	{
		isPrimitive = 1
	};
};
template <>
class NETemplateChecker<unsigned int>
{
public:
	static enum
	{
		isPrimitive = 1
	};
};
template <>
class NETemplateChecker<unsigned long int>
{
public:
	static enum
	{
		isPrimitive = 1
	};
};
template <>
class NETemplateChecker<unsigned __int64>
{
public:
	static enum
	{
		isPrimitive = 1
	};
};
