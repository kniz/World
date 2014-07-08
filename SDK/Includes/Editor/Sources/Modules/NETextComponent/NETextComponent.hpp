#pragma once

#include "../NEComponent/NEComponent.hpp"

namespace NE
{
	class NE_DLL NETextComponent : public NEComponent
	{
	public:
		NETextComponent();
		NETextComponent(const NETextComponent& source);

	public:
		virtual ~NETextComponent();

	public:
		const NETextComponent& operator=(const NETextComponent& source);
		bool operator==(const NETextComponent& source) const;
		bool operator!=(const NETextComponent& source) const;

	public:
		bool isTextFixed() const;
		void setTextFixed(bool is_text_fixed);
		NETString getText() const;
		type_result setText(const NETString& source);

	public:
		virtual void release();
		virtual type_result isValid() const;
		virtual NEType::Type getType() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		
	private:
		void _release();
				
	protected:
		NETString _text;
		bool _is_text_fixed;
	};
}
