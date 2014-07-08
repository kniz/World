// #pragma once
// 
// #include "../../Includes/Includes.hpp"
// 
// namespace NE
// {
// 	class WNDManager
// 	{
// 	private:
// 		WNDManager();
// 		WNDManager(const WNDManager& source);
// 
// 	private:
// 		virtual ~WNDManager();
// 
// 	public:
// 		NEList<Window*, true>& getWindowList();
// 		const NEList<Window*, true>& getWindowList() const;
// 
// 	protected:
// 		NEList<HWND> _hwndlist;
// 
// 	public:
// 		static WNDManager& getInstance();
// 	};
// }