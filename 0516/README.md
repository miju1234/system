# 📂 Chapter 6: 유닉스 파일 시스템 요약

---

## 🔧 파일 시스템 구조

* **부트 블록 (Boot Block)**
  시스템 부팅 시 실행되는 코드 저장 (디스크 첫 섹터).

* **슈퍼 블록 (Super Block)**
  전체 파일 시스템 메타데이터 보관 (블록 수, i-node 수 등).

* **i-리스트 (i-list)**
  파일의 메타 정보를 가진 i-node들의 목록.
  각 파일은 하나의 i-node를 가지며, 포인터를 통해 데이터 블록을 참조.

* **데이터 블록 (Data Block)**
  실제 파일의 내용을 저장하는 블록.

---

## 📁 i-노드와 블록 포인터

* i-node는 다음 정보를 포함:

  * 파일 타입 (일반 파일, 디렉터리, 장치 등)
  * 크기, 소유자, 권한, 접근/수정 시간
  * 데이터 블록을 가리키는 포인터 (직접, 간접, 이중 간접, 삼중 간접)

---

## 📂 파일 입출력 구현

* **주요 커널 자료구조**

  * **파일 디스크립터 배열 (Fd Array)**: 각 프로세스가 보유
  * **열린 파일 테이블 (Open File Table)**: 열려 있는 모든 파일의 상태 기록
  * **동적 i-노드 테이블**: 열려 있는 파일들의 i-node 정보를 유지

* **시스템 호출 예시**

  * `open()`, `dup()`, `read()`, `write()`, `close()`

---

## 📄 파일 상태 정보

* **stat 구조체**

  * `st_mode`: 파일 타입 및 권한
  * `st_size`: 파일 크기
  * `st_uid`, `st_gid`: 사용자 및 그룹 ID
  * `st_atime`, `st_mtime`, `st_ctime`: 시간 정보

* **사용 함수**

  * `stat()`, `fstat()`, `lstat()`
  * 접근 권한 변경: `chmod()`, `fchmod()`
  * 시간 변경: `utime()`
  * 소유자 변경: `chown()`, `fchown()`, `lchown()`

---

## 📂 디렉터리 구현

* 디렉터리도 하나의 파일이며, **i-node**를 가진다.
* 디렉터리 내부는 **파일 이름 + i-노드 번호** 목록 (디렉터리 엔트리).
* 사용 함수:

  * 열기: `opendir()`
  * 읽기: `readdir()`
  * 닫기: `closedir()`
  * 생성: `mkdir()`
  * 삭제: `rmdir()`

---

## 🔗 링크 (Links)

* **하드 링크 (Hard Link)**

  * 동일한 i-node를 참조. 같은 파일 시스템 내에서만 가능.

* **심볼릭 링크 (Symbolic Link)**

  * 파일 경로명을 저장하는 별도의 파일. 다른 파일 시스템도 가능.

* **사용 함수**

  * 생성: `link()`, `symlink()`
  * 제거: `unlink()`
  * 링크 확인: `readlink()`

---

## ✅ 핵심 요약

* 유닉스 파일 시스템은 부트/슈퍼 블록, i-node, 데이터 블록으로 구성
* 입출력은 커널 내부 자료구조와 시스템 호출로 관리됨
* 디렉터리도 파일이며, 링크는 파일에 대한 다른 이름을 제공

---

# 🔒 Chapter 7: 파일 및 레코드 잠금 요약

---

## 📁 7.1 파일 잠금 (`flock`)

* **flock() 함수**를 사용하여 **파일 전체**에 잠금 적용
* 잠금 종류:

  * `LOCK_SH`: 공유 잠금 (여러 프로세스 읽기 가능)
  * `LOCK_EX`: 배타 잠금 (한 프로세스만 쓰기 가능)
  * `LOCK_UN`: 잠금 해제
  * `LOCK_NB`: 논블로킹 모드 (잠금 실패 시 즉시 반환)

> 예: 두 프로세스가 같은 파일에 `LOCK_EX`를 걸면 순차적으로 실행됨

---

## 📄 7.2 레코드 잠금 (`fcntl`)

* 파일의 \*\*일부 구간(레코드)\*\*에 대해 잠금을 설정
* `fcntl()` 시스템 호출 사용

  * `F_GETLK`: 잠금 상태 확인
  * `F_SETLK`: 잠금 설정 (비블로킹)
  * `F_SETLKW`: 잠금 설정 (블로킹)
* `flock` 구조체를 통해 시작 위치, 길이, 유형(F\_RDLCK/F\_WRLCK/F\_UNLCK) 지정
* 예제:

  * `rdlock.c`: 학생 정보를 읽기 전 `F_RDLCK`으로 읽기 잠금
  * `wrlock.c`: 정보 수정 시 `F_WRLCK`으로 쓰기 잠금

---

## 🔧 7.3 간단한 잠금 함수 (`lockf`)

* `fcntl`보다 단순하게 파일의 구간 잠금을 제어할 수 있음

```c
int lockf(int fd, int cmd, off_t len);
```

### 🛠️ 주요 명령어 (`lockf`)

* `F_LOCK`: 쓰기 잠금 (잠금 해제 시까지 대기)
* `F_TLOCK`: 쓰기 잠금 (잠겨 있으면 즉시 실패)
* `F_ULOCK`: 잠금 해제
* `F_TEST`: 잠금 여부 확인

> 💡 예: `wrlockf.c`는 `lockf()`를 이용해 학생 정보 수정 시 해당 레코드를 잠금 처리합니다.

---

## 🛡️ 7.4 권고 잠금 vs 강제 잠금

### 🔹 권고 잠금 (Advisory Locking)

* 프로세스가 **자발적으로** 잠금 규칙을 따름
* 다른 프로세스가 잠금을 무시하고 접근할 수 있음
* 기본적으로 **Linux, BSD, macOS**에서 사용

### 🔸 강제 잠금 (Mandatory Locking)

* **커널이 잠금을 강제**함 → 무단 접근 차단
* 성능 저하 우려 존재
* 설정 방법:

```bash
$ chmod 2644 file  # SGID 비트 설정 + 그룹 실행 권한 제거
```

---

# 📘 Chapter 8: 프로세스

> 유닉스에서 프로세스 생성, 실행, 종료, 사용자 ID 및 메모리 구조를 다루는 핵심 개념을 설명합니다.

---

## 8.1 쉘과 프로세스

### 🐚 쉘(Shell)이란?

* 사용자와 운영체제 사이의 인터페이스
* 명령어 처리기 역할 수행

### 📘 복합 명령어 & 그룹

```bash
$ 명령어1; 명령어2; ...
$ (명령어1; 명령어2; ...) > 파일
```

### 🔁 전면/후면 처리

* 전면 처리: 명령 실행 완료까지 쉘 대기
* 후면 처리: `명령어 &`로 백그라운드 실행

```bash
$ (sleep 100; echo done) &
$ find . -name test.c -print &
$ jobs
$ fg %1
```

### 🧠 프로세스 정의

* 실행 중인 프로그램
* PID(Process ID) 부여됨

```bash
$ ps
$ ps u
$ ps -aux  # BSD
$ ps -ef   # System V
```

---

## 8.2 프로그램 실행

### 🚀 exec 시스템 호출

* `exec()`로 새로운 프로그램 실행
* 인수 및 환경 변수 전달

### 📌 main 함수 정의

```c
int main(int argc, char *argv[]);
```

### 🧪 명령줄 인수 출력 예

```c
for (int i = 0; i < argc; i++)
    printf("argv[%d]: %s\n", i, argv[i]);
```

### 🌍 환경 변수 접근

```c
extern char **environ;
for (char **ptr = environ; *ptr != NULL; ptr++)
    printf("%s\n", *ptr);

char *getenv("HOME");
```

### ⚙️ 환경 변수 설정

```c
putenv("NAME=value");
setenv("NAME", "value", 1);
unsetenv("NAME");
```

---

## 8.3 프로그램 종료

### ✅ 정상 종료

* `main()` → `exit()`
* 또는 직접 `exit()` / `_exit()` 호출

### ❌ 비정상 종료

* `abort()` 호출
* 시그널에 의한 종료

### 🧹 정리 차이

* `exit()` → 스트림 닫고 버퍼 플러시
* `_exit()` → 정리 없이 종료

### 🧼 atexit 처리기 등록

```c
atexit(func);  // 최대 32개 등록 가능
```

---

## 8.4 프로세스 ID와 사용자 ID

### 🆔 프로세스 ID

```c
getpid();   // 내 PID
getppid();  // 부모 PID
```

### 👤 사용자 및 그룹 ID

```c
getuid();    geteuid();   // 실제 / 유효 사용자 ID
getgid();    getegid();   // 실제 / 유효 그룹 ID
```

### 🧑‍💼 setuid / setgid 설정

```c
setuid(uid);     seteuid(uid);
setgid(gid);     setegid(gid);
```

### 🔐 set-user-ID 실행권한

* `chmod 4755 파일`
* 실행자 → 파일 소유자 권한 획득

```bash
$ ls -l /usr/bin/passwd
-rwsr-xr-x 1 root root ...
```

---

## 8.5 프로세스 이미지

### 🧱 프로세스 메모리 구조

* **Text**: 실행 코드
* **Data**: 전역 및 static 변수
* **Heap**: 동적 메모리 (malloc)
* **Stack**: 함수 호출 스택
* **U-Area**: 열린 파일, 디렉터리 등

---

## 🧩 핵심 요약

* 프로세스는 실행 중인 프로그램
* 쉘은 명령어를 받아 실행하는 인터페이스
* `exec`로 실행, `exit`로 종료 시 정리
* 사용자/그룹 ID에 따라 권한 결정
* 프로세스 메모리는 text/data/heap/stack 구성
