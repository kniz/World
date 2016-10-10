//	---------------------------------------------------------------------------------
//	클래스명:	NEShortCutSet
//	설명	:	복수의 NEShortCut를 관리하고, 셀렉터들에게 friend선언을 하도록 만들어진
//				클래스.
//	관계	:	기반클래스.	NETVector<NEShortCut>
//	특성	:	
//	알고리즘:	
//	사용방법:	NETVector를 참고하라.
//	메모	:	
//	히스토리:	2011-07-12	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once

#include "../../Commons/Interfaces/NEEnlistable/NEEnlistable.hpp"
#include "../NEShortCut/NEShortCut.hpp"

namespace NE
{
	template 
	class NE_DLL NETVector<NEShortCut>;

	class NE_DLL NEShortCutSet : public NETVector<NEShortCut>, public NEEnlistable
	{
		NE_DECLARE_CLASS(NEShortCutSet, NETVector<NEShortCut>)

	public:
		friend class NEEnlistableManager;

	public:
		NEShortCutSet();
		NEShortCutSet(const NECodeType& type);
		NEShortCutSet(const This& source);

	public:
		virtual ~NEShortCutSet();

	public:
		This& operator=(const This& source);
		type_bool operator==(const This& source) const;
		type_bool operator!=(const This& source) const;

	public:
		const NECodeType& getCodeType() const;

	public:
		virtual void release();
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	public:
		virtual type_result _enlist(NENode& node, type_index real_index);
		virtual type_result _unlist(NENode& node, type_index real_index);

	private:
		type_result _enlist(NENode& node, const NECode& code, type_index real_index);
		type_result _unlist(NENode& node, const NECode& code, type_index real_index);

	private:
		NECodeType _type;
	};
}