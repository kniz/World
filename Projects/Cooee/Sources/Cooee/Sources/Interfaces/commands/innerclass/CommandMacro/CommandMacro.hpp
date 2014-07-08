#define CommandMacro(command_name)	\
	class command_name : public Interface \
	{ \
	public: \
		command_name(const NETString& nickname)	\
			: _nickname(nickname)	{}	\
		virtual type_result run(NETStringSet& parameter); \
		virtual const NETString& getName() const; \
		virtual NEObject& clone() const; \
	public:	\
		const NETString& getNickName() const {return _nickname; }	\
	private:	\
		NETString _nickname;	\
	};
	
#define CommandCommonMethod(command_name) \
	const NETString& command_name::getName() const \
	{ \
		static NETString _name = #command_name; \
		return _name; \
	} \
	NEObject& command_name::clone() const \
	{ \
		return *(new command_name(*this)); \
	}
