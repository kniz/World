#pragma once

#include "../NEBinderBase/NEBinderBase.hpp"

namespace NE
{
	class NEKeyArray;
	class NEKey;

	class NE_DLL NEKeyBinder : public NEBinderBase
	{
		NE_DECLARE_CLASS(NEKeyBinder, NEBinderBase)
	
	public:
		template <typename ModuleSelector>
		friend class NETKeySelector;

	public:
		virtual type_bool isBinded() const;

	public:
		NEKey& getBinded();
		const NEKey& getBinded() const;
		type_result bind(const NEKey& key/*, NEType::Type manager_type*/);
		type_bool isBindedLocalKey() const;

	protected:
		type_result _markToBindLocalKey();

	private:
		NEKeyArray& _getKeySet();
		const NEKeyArray& _getKeySet() const;
		type_result _onEnlisted();
	};
}