# reference 

## Ref 클래스가 담당한다.

## Strong 바인딩을 표현한다.

## Node의 일종이며 proxy로 동작한다.

## 컴파일러는 mutable 변수를 발견하면 이 Ref를 member로 등록한다.

## 컴파일러는 immutable 변수를 발견하면 그 변수를 직접 member로 등록할 수 있다. (안해도 동작에는 차이가 없다)

## Ref는 Node 타입이면 무엇이든 바인드 할 수 있어야 한다.

## Ref는 getType()이라는 verify용 함수가 있다.
* TVarRef<T>는 getType()을 고정된 TClass<T>로 반환한다.
* GVarRef는 getType()을 변수로 제공한다. 컴파일러가 생성할 수 있도록. 

## verify는 RTTI를 사용하는 것이다.
* 바인딩된 객체가 getType()과 자식 혹은 동일한 타입인지를 체크한다. 

## 메소드에 대한 참조자는 FuncRef 라는 별도의 클래스를 상속받아 사용한다.
* 메소드의 경우에는 상속으로 체크할 수 없고, 인자의 종류와 갯수가 정확히
  일치하는 지를 기준으로 verify 해야 하기 때문이다.'
* 인자의 종류가 정확히 일치해야 한다. 묵시적 변환 같은 것 허용하지 않는다.
