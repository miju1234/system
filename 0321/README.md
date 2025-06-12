## 📘 제3장 C 프로그래밍 환경 요약

---

### 🔹 3.1 C 언어 기초

#### ✅ 프로그램 구조
- `.c` 파일에는 `#include`, `#define`, 전역변수, 함수 정의 포함
- `main()` 함수에서 다른 함수 호출

#### ✅ 함수
- 형식: `리턴타입 함수명(매개변수) { ... }`
- `return`으로 값 반환
- 값 전달 방식(pass by value) 사용

#### ✅ 배열
- 일차원 배열: `int a[5];`
- 이차원 배열: `int a[2][3];`
- `for` 문으로 반복 처리

#### ✅ 포인터
- 선언: `int *p = &a;`
- `*p`: 포인터가 가리키는 값, `&a`: 변수 주소

#### ✅ 포인터와 배열
```c
int a[4] = {10,20,30,40};
int *p = a;
```

#### ✅ 문자열과 포인터
```c
char *p = "Hello";
char m[] = "World";
```
- `char *arr[] = {"red", "blue"}`: 포인터 배열

#### ✅ 구조체
- 선언 예:
```c
struct student {
  char name[10];
  int age;
};
```
- 사용: 배열, 포인터로 접근 가능

---

### ✏️ 3.2 gedit & gcc 사용법

#### ✅ gedit
- GUI 기반 편집기
- 실행: `gedit 파일명 &` 또는 프로그램 메뉴

#### ✅ gcc 컴파일
```bash
gcc hello.c         # a.out 생성
gcc -o hello hello.c  # 실행파일 이름 지정
```

#### ✅ 다중 파일 컴파일
```bash
gcc -c main.c
gcc -c copy.c
gcc -o main main.o copy.o
```

---

### 🛠 3.3 자동 빌드 도구 (Makefile)

#### ✅ Makefile 구성
```makefile
main: main.o copy.o
	gcc -o main main.o copy.o

main.o: main.c copy.h
	gcc -c main.c

copy.o: copy.c
	gcc -c copy.c
```

#### ✅ 실행 방법
```bash
make           # 기본 실행
make -f my.mk  # 지정 파일 사용
```

> 변경된 파일만 다시 컴파일

---

### 🐞 3.4 디버거 (gdb)

#### ✅ 사용법
```bash
gcc -g -o main main.c copy.c
gdb main
```

#### ✅ 주요 명령어

| 명령어 | 설명 |
|--------|------|
| `l` | 코드 보기 |
| `b 함수명` | 중단점 설정 |
| `r` | 실행 |
| `n`, `s` | 다음 줄 실행, 함수 내부 진입 |
| `p 변수` | 변수 값 확인 |
| `c` | 계속 실행 |
| `q` | 종료 |

---

### 💻 3.5 Eclipse 통합 개발환경

- GUI 기반 IDE
- `File → New → C Project` 생성
- 소스는 `src/`, 헤더는 `includes/`에 관리
- 코드 편집, 빌드, 실행, 디버깅 통합 지원

---

✅ `chap3.pdf`는 C 프로그래밍의 **기초 문법부터 개발 도구 사용까지** 실습 환경을 전체적으로 안내하는 내용입니다.
