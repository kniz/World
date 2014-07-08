#include "Assign.hpp"

namespace NE
{
	type_result NE_DLL Assign::execute()
	{
		//	pre:
		//		타겟팅:
		//			키셀렉터:
		NEKeySelector& operand_source = static_cast<NEKeySelector&>( getKeySet()[0] );
		NEFloatKey& operand_target = static_cast<NEFloatKey&>( getKeySet()[1] );		


		//	main:
		while(NEKey* src = &operand_source.getKey())			
			*src = operand_target;

		return RESULT_SUCCESS;
	}
}