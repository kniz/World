#include "CError.hpp"
#include "CWindow.hpp"

//	생성자
CError::CError(CString error_name, CString error_explain, CString function_name, bool never_alert)
: _error_name(error_name), _error_explain(error_explain), _function_name(function_name)
, _never_alert(never_alert)
{}
//	소멸자
CError::~CError()
{}
//	메세지 박스를 띄운다. 심각한 오류는, CWindow에 에러가 throw됬을때 catch해서 showMessage를 호출한다.
void	CError::showMessage()
{	
	//	예외상황 처리:
	if (_never_alert == true)
		return ;


	//	메인코드:
	//		변수채우기:
	CString top		= DEFAULT_CERROR_MESSAGEBOX_COMMENT_TOP,
			bottom	= DEFAULT_CERROR_MESSAGEBOX_COMMENT_BOTTOM;	
	CString msg = ( top +
		_T("에러 이름:\t\t") + _error_name + 
		_T("\n해결 방법:\t\t") + _error_explain +
		_T("\n에러가 발생한 함수:\t") + _function_name +
		 bottom);
	//		메세지 박스 띄우기:
	MessageBox(CWindow::_hWnd, msg, _T("error!"), MB_OK);
}
//	Error.ini에 ANSI 텍스트 형태로 오류정보를 넣는다. error.log에 정보를 기록한다. 그냥 넘어갈만한 오류는 log 만 호출한다.
void	CError::log()
{
	//	오류 횟수 구하기:
	CString error_count;
	LPTSTR	buffer = new TCHAR[128];
	GetPrivateProfileString(_T("헤더"),_T("에러횟수"),NULL, buffer, 128, _T(".\\error.log"));
	error_count.Format(_T("%d"), _ttoi(buffer) + 1);	

	//	날짜와 시간 구하기:	 WritePrivateProfileString( []섹션, 키이름. 키값, 파일명 )
	CString	categori = error_count + _T("번째 에러");	

	//	오류기록: 한국어만.
	WritePrivateProfileString(categori, _T("날짜"), getCurrentDate(), _T(".\\error.log"));
	WritePrivateProfileString(categori, _T("시간"), getCurrentTime(), _T(".\\error.log"));
	WritePrivateProfileString(categori, _T("에러종류"), _error_name, _T(".\\error.log"));
	WritePrivateProfileString(categori, _T("에러가 발생한 함수명"), _function_name, _T(".\\error.log"));			
	WritePrivateProfileString(categori, _T("========================================"), _T(" "), _T(".\\error.log")); // 다음 에러정보와 빈칸을 만들기 위해			
	
	//	오류횟수 갱신:
	WritePrivateProfileString(_T("헤더"), _T("에러횟수"), error_count, _T(".\\error.log"));
}	
//	현재 날짜 구하기
CString	CError::getCurrentDate()
{
	TCHAR	date[9];
	_tstrdate_s(date);	
	return CString(date);
}
//	현재 시간 구하기
CString	CError::getCurrentTime()
{
	TCHAR	time[9];
	_tstrtime_s(time);	

	return CString(time);
}