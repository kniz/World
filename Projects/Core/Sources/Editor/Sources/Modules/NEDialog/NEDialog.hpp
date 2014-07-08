#pragma once

#include "../NEPanel/NEPanel.hpp"

namespace NE
{
	class NE_DLL NEDialog : public NEPanel
	{	
	public:
		NEDialog();		
		NEDialog(const NEDialog& source);

	public:
		virtual ~NEDialog();

	public:
		const NEDialog& operator=(const NEDialog& source);
		bool operator==(const NEDialog& source) const;
		bool operator!=(const NEDialog& source) const;

	public:	
		void disconnectCaller();
		type_result setCaller(NEPanel& caller, type_index component_index_to_call);
		NEPanel& getCaller();
		const NEPanel& getCaller() const;
		type_index getComponentIndexToCall() const;
		bool willDisableTheCaller() const;

	public:
		virtual NEType::Type getType() const;
		virtual void release();

	public:
		virtual type_result onLoad(); // 다이얼로그 호출시, 호출된 패널을 
		virtual type_result onUnload(); // 다이얼로-그 소멸시, 자신을 호출한 패널에게 onReturnedDialgue 메세지를 보낸다.
		
	private:
		const NEDialog& _assign(const NEDialog& source);

	protected:
		bool _disable_the_caller;
		NEPanel* _caller;
		type_index _component_index_to_call;
	};
}
