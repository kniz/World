#include "Logic.hpp"

namespace NE
{
	type_result NE_DLL Logic::execute()
	{
		//	pre:
		NEKeySelector& sel = getTargets();
		NEFloatKey rhs(getSource());
		type_int op_type = getOperationType();


		//	main:
		while(NEKey* itr = &sel.getKey())
		{		
			//	연산 동작:
			//		연산 결과를 담을 버퍼:
			bool result_of_operation = false;
			//		연산:
			switch(op_type)
			{
			case OPERATOR_IS_EQUAL_TO:
				result_of_operation = (*itr == rhs);
				break;
			case OPERATOR_IS_NOT_EQUAL_TO:
				result_of_operation = (*itr != rhs);
				break;
			case OPERATOR_IS_LESS_THAN:
				result_of_operation = (*itr < rhs);
				break;
			case OPERATOR_IS_LESS_THAN_OR_EQUAL_TO:
				result_of_operation = (*itr <= rhs);
				break;
			case OPERATOR_IS_MORE_THAN:
				result_of_operation = (*itr > rhs);
				break;
			case OPERATOR_IS_MORE_THAN_OR_EQUAL_TO:
				result_of_operation = (*itr >= rhs);
				break;
			default:
				ALERT_ERROR("잘못된 연산 타입입니다.\n주어진 연산 타입 : %d", op_type);
				return RESULT_TYPE_ERROR | RESULT_ABORT_ACTION;
			}
			//	결과 분석:
			//		하나라도 false가 된다면 검색 종료:	모든 Key1에 대해서 true가 되야만 true를 반환한다.
			if( ! result_of_operation)
			{
				sel.initializeReferingPoint();
				return RESULT_SUCCESS | RESULT_FALSE | RESULT_ABORT_ACTION;
			}
		}


		return RESULT_SUCCESS | RESULT_TRUE;
	}
}