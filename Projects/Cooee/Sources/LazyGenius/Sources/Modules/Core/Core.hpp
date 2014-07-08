#pragma once

#include "../WindowList/WindowList.hpp"

namespace LG
{
	class NE_DLL Core
	{
	public:
		static void sendKeyPipe()
		{
			if( _kbhit()) {
				char inputed = _getch();
				if(&windows[0])
					windows[0].onKeyPressed(inputed);
			}		

			windows.collectGarbages();
		}
		static void open(Window& window)
		{
			windows.pushFront(window);
		}
		static void setColor(int tcolor, int bcolor)
		{
			SetConsoleTextAttribute(output_handle, bcolor << 4 | tcolor);
		}
		static void setColor(WORD color)
		{
			SetConsoleTextAttribute(output_handle, color);
		}
		static WORD getColor()
		{
			CONSOLE_SCREEN_BUFFER_INFO cs = {0, };
			GetConsoleScreenBufferInfo(output_handle, &cs);		
			return cs.wAttributes;
		}
		static COORD getCursorPosition()
		{
			CONSOLE_SCREEN_BUFFER_INFO cs = {0, };
			GetConsoleScreenBufferInfo(output_handle, &cs);		
			COORD temp = {cs.dwCursorPosition.X, cs.dwCursorPosition.Y};

			return temp;
		}

		static COORD getMaxCursorPosition()
		{
			CONSOLE_SCREEN_BUFFER_INFO cs = {0, };
			GetConsoleScreenBufferInfo(output_handle, &cs);		
			COORD temp = {cs.dwMaximumWindowSize.X, cs.dwMaximumWindowSize.Y};
			return temp;
		}

		static void setCursorTo(type_ushort x, type_ushort y)
		{
			x = (x > max_width) ? max_width : x;
			y = (y > max_height) ? max_height : y;
			COORD pos = {x, y};
			SetConsoleCursorPosition(output_handle, pos);
		}
		static void setCursorTo(COORD coord)
		{
			SetConsoleCursorPosition(output_handle, coord);
		}
		static HANDLE output_handle;
		static type_ushort max_width;
		static type_ushort max_height;	
		static WindowList windows;
	};
}