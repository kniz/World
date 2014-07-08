#ifdef DEVELOPER
#	ifdef _DEBUG
#		define _NAME					"[!output module_name]"
#		define _DEVELOPER				"[!output module_author]"
#		define _REVISION				[!output module_revision] // 커널에서 판별하는 버전표기
#		define _VERSION					"[!output module_version]" // 사용자에게 보여주는 용도의 버전표기
#		define _COMMENT					"[!output module_comment]"
#		define	_DATE					"[!output module_date]"
#		define _DEPENDENCIES_COUNT		0
#		define _KEY_NUMBER				[!output module_key_count]
#	else
#		define _NAME					"[!output module_name]"
#		define _DEVELOPER				"[!output module_author]"
#		define _REVISION				[!output module_revision] // 커널에서 판별하는 버전표기
#		define _VERSION					"[!output module_version]" // 사용자에게 보여주는 용도의 버전표기
#		define _COMMENT					"[!output module_comment]"
#		define	_DATE					"[!output module_date]"
#		define _DEPENDENCIES_COUNT		0
#		define _KEY_NUMBER				[!output module_key_count]
#	endif
#else
#	define _NAME						"[!output module_name]"
#	define _DEVELOPER					"[!output module_author]"
#	define _REVISION					[!output module_revision] // 커널에서 판별하는 버전표기
#	define _VERSION						"[!output module_version]" // 사용자에게 보여주는 용도의 버전표기
#	define _COMMENT						"[!output module_comment]"
#	define	_DATE						"[!output module_date]"
#	define _DEPENDENCIES_COUNT			0
#	define _KEY_NUMBER					[!output module_key_count]
#endif

