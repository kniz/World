//	---------------------------------------------------------------------------------
//	클래스명:	NEListTemplate<T*, true>::Iterator
//	설명	:	NEListTemplate에 사용되는 Iterator을 나타내는 클래스.
//	관계	:	중첩클래스.	NEListTemplate
//	특성	:	NEListTemplate에 friend 선언
//				Iterator은 외부에도 공개된다.
//	알고리즘:	각 엘리먼트의 메모리 할당, 해제가 일어난다.
//	사용방법:	getNext(),	data
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
class Iterator
{
	//	프렌드 선언:
	friend class NEListTemplate;

	//	생성자:
public:
	Iterator(const T* source, typename Iterator* next);

	//	소멸자:
public:
	~Iterator();

	//	접근자:
public:
	T& getValue();	
	const T& getValue() const;
	void setValue(T* source);
	const Iterator* getNext() const;
	Iterator* getNext();

	//	멤버변수:
protected:
	T*	_value;

protected:	
	Iterator* _next;
};
