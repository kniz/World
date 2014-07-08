#include "NEKeySet.hpp"
#include "../Kernal/Kernal.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEKeySet::NEKeySet()
		: NEArrayTemplate<NEKey*, true, NEType::NEKEYSET>()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEKeySet::NEKeySet(type_count size)
		: NEArrayTemplate<NEKey*, true>(size)
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEKeySet::NEKeySet(const NEKeySet& source)
		: NEArrayTemplate<NEKey*, true>(source)
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEKeySet::~NEKeySet()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NEKeySet NE_DLL &NEKeySet::operator+=(const NEKeySet& source)
	{
		NEArrayTemplate<NEKey*, true>::operator+=(source);

		return *this;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEKeySet NE_DLL NEKeySet::operator+(const NEKeySet& source) const
	{
		NEKeySet buffer(getSize() + source.getSize());

		buffer.push(*this);
		buffer.push(source);
		
		return buffer;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	//	save는 기존의 NEPointerArray로도 가능하다
	NEBinaryFileSaver NE_DLL &NEKeySet::serialize(NEBinaryFileSaver& saver) const
	{	//	pre:
		//		기반 클래스의 저장 호출
		SuperClass::serialize(saver);



		//	main:
		//		실제 데이터 저장:
		for(type_index n=0; n < _length ;n++)
		{	//		헤더 추출:
			NEType::Type type = _data[n]->getType();
			//		헤더 저장:	타입코드로, load시 어떤인스턴스를 생성해야하는가에 대한 정보를 남긴다
			saver << type; 
			//		실제 데이터 저정:	NEModule::serialize()를 호출한다.
			saver << *(_data[n]);
		}



		//	post:
		return saver;
	}



	//	---------------------------------------------------------------------------------
	//	설명:		키셋을 파일로 부터 로드한다.
	//	동작조건:	키의 구성물(타입 및 데이터)는 변동이 허락되나, 키의 갯수는 고정되어야한다.
	//				그 이유에 대해서는, 하단에 있는 "엘리먼트 초기화" 부분을 참고하라.
	//	메모:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileLoader NE_DLL &NEKeySet::serialize(NEBinaryFileLoader& loader)
	{	//	배경:
		//		왜 헤더를 먼저 로드하는가?:
		//			모듈은 여러가지 형태로 NEModule을 상속해서 사용한다.
		//			그러나, Kernal에서는 어떠한 모듈이 load 되어야 하는지 모른다.
		//			또한, 존재하지 않는 모듈의 정보가 있을 수도 있다.
		//
		//			예를들면,
		//				A PC에서 저장한 Save 파일은, A 노드엔진에 놓여진 모듈을 사용해서 만들어 졌다.
		//				같은 Save 파일을 B PC에서 Load 한다면, 존재하지 않는 모듈이 발생한다.
		//			
		//			그래서 헤더를 먼저 읽은 후, 로드하려는 모듈이 현재 PC에도 존재하는지
		//			확인한다.
		//			존재할 경우, 모듈매니져에서 해당 모듈의 복사생성자를 통해 
		//			인스턴스를 가져온다.

		//	pre:
		//		기반 클래스 호출:
		SuperClass::serialize(loader);
		NEKeyManager& keyer = Kernal::getInstance().getKeyManager();
		//	main:
		//		엘리먼트 초기화:
		//			인스턴스 생성 및 엘리먼트 초기화는 모듈의 initialize() 함수로부터
		//			생성된다.
		//			여기서는 이미 생성된 인스턴스가 존재한다는 가정하에, serialize로
		//			데이터를 로드하는 프로세스만 실행할 것이다.
		type_index length = _length;
		_length = 0;
		//		엘리먼트 로드:
		for(type_index n=0; n < length ;n++)
		{
			//		타입로드:
			NEType::Type type = NEType::UNDEFINED;
			loader >> type;
			NEKey& source_key = keyer.getKey(type);
			if( ! &source_key)
			{
				KERNAL_ERROR(" : ");
				continue;
			}

			push(source_key);

			//	데이터 로드:
			NEKey& last_key = getElement(getLengthLastIndex());
			loader >> last_key;
		}



		//	post:
		return loader;
	}

	NEObject NE_DLL &NEKeySet::clone() const
	{
		return *(new NEKeySet(*this));
	}
}
