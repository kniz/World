#pragma once

//	include:
#include "../NEKey/NEKey.hpp"
#include "../NECodeSet/NECodeSet.hpp"
#include "../../Commons/Units/NECodeType/NECodeType.hpp"
#include "../../Commons/Interfaces/NEInitializable/NEInitializable.hpp"

namespace NE
{
	class NENode;	

	class NE_DLL NENodeSelectorBase : public NEKey, public NEInitializable
	{
		typedef NENodeSelectorBase ThisClass;
		typedef NEKey SuperClass;

	public:
		ThisClass(const NETString& keyname = "");
		ThisClass(const ThisClass& source);

		//	소멸자:
	public:
		virtual ~NENodeSelectorBase();

		//	연산자 오버로딩:
	public:
		const ThisClass& operator=(const ThisClass& source);
		bool operator==(const ThisClass& source) const;
		bool operator!=(const ThisClass& source) const;

		//	인터페이스:		
		//		상속:
	public:
		const NECodeType& getCodesType() const;
		type_result setCodesType(const NECodeType& new_one);
		type_result setCodes(const NECodeSet& new_codeset);
		const NECodeSet& getCodes() const;
		type_count getCountLimit() const;
		void setCountLimit(type_count limit);
		bool isUsingAndOperation() const;
		void setUsingAndOperation(bool enable);
		virtual type_result bind() = 0;

	public:
		virtual type_result initializeReferingPoint() = 0;

	public:
		virtual void releaseValue();

	public:
		virtual void release();
		virtual type_result isValid() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

		//	내부 함수:
	private:
		const ThisClass& _assign(const ThisClass& source);
		void _release();

	protected:
		bool _use_and_operation;
		NECodeSet _codes;
		type_count _count;
		type_count _countlimit;
		bool _is_peeking_locked;
	};
}
