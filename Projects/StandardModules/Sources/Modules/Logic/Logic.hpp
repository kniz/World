#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL Logic : public NEModule
	{
	public:
		typedef Logic ThisClass;
		typedef NEModule SuperClass;

	public:
		enum OperatorType
		{
			OPERATOR_IS_EQUAL_TO = 0,
			OPERATOR_IS_NOT_EQUAL_TO,
			OPERATOR_IS_LESS_THAN,
			OPERATOR_IS_LESS_THAN_OR_EQUAL_TO,
			OPERATOR_IS_MORE_THAN,
			OPERATOR_IS_MORE_THAN_OR_EQUAL_TO,
			OPERATOR_END
		};

	public:
		virtual type_result initialize()
		{
			getKeySet().create(3);
			getKeySet().push( NEKeySelector() );				//	0:	Target
			getKeySet().push( NEFloatKey() );					//	1:	rhs
			getKeySet().push( NEIntKey(OPERATOR_IS_EQUAL_TO) );	//	2:	OperationType

			return RESULT_SUCCESS;
		}

	public:
		const NEKeySelector& getTargets() const
		{
			const NEKey& key = getKeySet()[0];
			if( ! &key || ! key.isSubClassOf(NEType::NEKEY_SELECTOR))
			{
				ALERT_ERROR("0번 키는 NEKEY_SELECTOR여야 합니다.");
				NEKeySelector* nullpoint = 0;
				return *nullpoint;
			}

			return static_cast<const NEKeySelector&>(key);
		}
		NEKeySelector& getTargets()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<NEKeySelector&>(casted->getTargets());
		}
		const type_float& getSource() const
		{
			const NEKey& key = getKeySet()[1];
			if( ! &key || ! key.isSubClassOf(NEType::NEFLOAT_KEY))
			{
				ALERT_ERROR("1번키는 NEFLOAT_KEY여야 합니다.");
				type_float* nullpoint = 0;
				return *nullpoint;
			}

			return static_cast<const NEFloatKey&>(key).getValue();
		}
		type_float& getSource()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_float&>(casted->getSource());
		}
		const type_int& getOperationType() const
		{
			const NEKey& key = getKeySet()[2];
			if( ! &key || ! key.isSubClassOf(NEType::NEINT_KEY))
			{
				ALERT_ERROR("2번키는 NEINT_KEY여야 합니다.");
				type_int* nullpoint = 0;
				return *nullpoint;
			}

			return static_cast<const NEIntKey&>(key).getValue();
		}
		type_int& getOperationType()
		{
			const ThisClass* casted = (const ThisClass*) this;

			return const_cast<type_int&>(casted->getOperationType());
		}



	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;

			if(_header.isValid() != RESULT_NOTHING)
			{
				_header.getName() = _T("Logic");
				_header.getDeveloper() = _T("kniz");
				_header.setRevision(1);
				_header.getComment() = _T("0번: 대상\n1번: 비교할 값(단, 대상이 Primitive 단일형일때만 가능하다)\n2번: 비교연산종류(0:==, 1:!= 2:<, 3:<=, 4:>, 5:>=)");
				_header.getVersion()  = _T("0.0.1a");
				_header.getReleaseDate() = _T("2013-10-15");
				_header.getModuleDependencies().create(0);
				_header.setMaxErrorCodeCount(0);
			}

			return _header;
		}

	public:
		virtual type_result execute();	

	public:
		virtual NEObject& clone() const { return *(new Logic(*this)); }
	};
}
