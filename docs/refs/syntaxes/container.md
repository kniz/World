# container

## array, map, tuple 3종류를 기본 제공한다. 

## 자바처럼 arraylist의 버금가는 활용도를 제공한다.

* 자바는 기본 배열은 어느순간 잘 안쓰게 되고 확장성 있는 arraylist를 사용을 자주한다.
* 효율성을 버리고, 타입을 일원화하는데 초점을 맞춘다.

## container는 생성자 문법이 통용되지 않는다.

* "[", "]" 를 통해서 별도로 생성자처럼 사용한다.

## container는 unique object가 존재하지 않는다.

* unique object에 접근하는 것처럼 문법을 작성하면 실제로는 텅빈 container를 만드는 것이다. 
* container는 생성자가 없기 때문이다.

## array

### 문법

    [((value) (, value)*)*]

* type deduction으로 값의 타입을 보고 어떠한 배열인지를 유추한다.
* 텅빈 배열을 만들 수 있다.

```go
arr := str[]
arr.len // 0


arr := ["wow", "hello", 1] // obj[]
foo(strs str[]) void
    for e in strs
        sys.out(e)
foo(arr) // err
foo(arr as str[]) // casting err

arr2 := str[]
for e in arr
    arr2.add(e as str)
foo(arr2)
```

### 배열의 index는 0을 제외한 양수여야 한다. 

### add, del로 배열은 size가 고정되어 있지 않다.

### 접근시 []로 접근한다.

* arr[5]
* 접근시 O(1)에 해당한다.

### 비어있는 원소가 없다.

* arr[2], arr[4]은 되지만 arr[3] 을 하면 exception 이 발생하거나 하진 않는다.
* 물론 원소로써 null이 들어가 있을 수는 있다.

### 원소들은 모두 같은 타입이다.

### 배열을 범위를 벗어나면 runtime 에러가 발생하고 프로그램이 종료한다.



## typelist

* typelist은 여러개의 서로 다른 타입들이 container로 존재하는 것이다.

### 문법

    ((value) (, (value))*)*

### 사실 사용자는 typelist을 마음껏 다룰 수 없다.

* typelist을 정의하는 부분은 정해져 있다.
    * 다중 할당 문법
    * 메소드의 인자리스트
    * 어떠한 문법의 일부
* 사실 , 로 여러개의 값 혹은 타입을 넘기거나 다루는 모든 것을 편의상 타입리스트이라고 하는 것 뿐이다.


### 멀티 반환값을 가진 메소드 정의하기

```go
def app
    foo() int, float, char on err =>

    main() void
        a, b, c on res := foo()
```




## sequence

### 문법

    (include number) .. (include number)

* 예제
```go
arr := [1, 2, 3]
for num in 1..arr.len
    sys.out("$num,")
// 1,2,3,
```


## pair

### 문법

    (value) : (value)

* 키와 값을 갖는 1개의 쌍이다.

### key, val 로 각 member에 접근한다.

arr := "name": 3
arr.key
arr.member



## map

* hash다.

### 문법

    [((pair) (, pair)*)*]

### element가 떨어진 배열 처럼 사용할 수 있다.

### for 문에 넣으면 pair가 나온다.

```go
map := ["banana": 1, "apple":3]

for pair in map
    sys.out("$pair.key:$pair.val")

for v in map.vals
    sys.out("value=$v")

map.keys
```


## container 간 캐스팅은 container가 가진 타입 T에 대해서만 지원해야 한다.

* 원소에 대해서 casting을 해서 변환을 하면 안된다.
* 그것은 캐스팅이 아니라 변환(conversion)에 해당한다.


## 복잡한 컨테이너 문법

```go
def app
    res, res2 => foo(arr int[], cache base[str], key str) int[][str], base[str] on err
        return int[][str], base[str] on myErr

    main() void
        if (a, b on res := foo(null, null, null)) as myErr
            return

        age := a["wow"][3]
        baseWas := b["wow"]
```



## chain

* native에서만 사용하는 container다.
* 다른 알고리즘이나 container를 대신 사용해도 무방하다.
* 배열1과 배열2가 있을때 이 둘을 chain해서 배열1의 원소와  배열2의 원소를 모두 가진것처럼 보이는 배열을 만들수 있어야 한다.
* List건, vector건 모든 컨테이너에 적용되야 한다.
