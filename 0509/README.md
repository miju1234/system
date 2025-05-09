
---

## 📌 시스템 호출 개요

- 시스템 호출: 커널에 서비스를 요청하는 프로그래밍 인터페이스  
- 주요 호출 분류:

| 분류        | 시스템 호출 |
|-------------|--------------|
| 파일        | `open()`, `close()`, `read()`, `write()`, `lseek()`, `dup()` |
| 프로세스    | `fork()`, `exec()`, `wait()`, `exit()` |
| 메모리      | `malloc()`, `calloc()`, `free()` |
| 시그널      | `signal()`, `kill()`, `alarm()`, `sleep()` |
| 통신        | `pipe()`, `socket()` |


---

### 🔹 `open()`

파일을 열고, 파일 디스크립터를 반환합니다.

```c
int open(const char *path, int oflag, mode_t mode);
```

- `O_RDONLY`: 읽기 전용  
- `O_WRONLY`: 쓰기 전용  
- `O_RDWR`: 읽기/쓰기 모두  
- `O_CREAT`: 파일이 없으면 생성  
- `O_TRUNC`: 기존 내용을 모두 삭제  
- `O_APPEND`: 항상 파일 끝에 추가

---

### 🔹 `creat()`

파일을 생성하고 쓰기 전용으로 엽니다.

```c
int creat(const char *path, mode_t mode);
```

- `open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);` 와 동일

---

### 🔹 `close()`

열린 파일 디스크립터를 닫습니다.

```c
int close(int fd);
```

- 성공 시 0, 실패 시 -1

---

### 🔹 `read()`

파일로부터 데이터를 읽어 버퍼에 저장합니다.

```c
ssize_t read(int fd, void *buf, size_t nbytes);
```

- 반환값: 읽은 바이트 수, 0 (EOF), -1 (오류)

---

### 🔹 `write()`

버퍼의 데이터를 파일로 씁니다.

```c
ssize_t write(int fd, const void *buf, size_t nbytes);
```

- 반환값: 실제로 기록된 바이트 수

---

### 🔹 `dup()` / `dup2()`

파일 디스크립터를 복제하여 하나의 파일을 공유하도록 합니다.

```c
int dup(int oldfd);
int dup2(int oldfd, int newfd);
```

- `dup()`: 사용 가능한 가장 작은 번호 반환  
- `dup2()`: `newfd`를 닫고 복제

---

### 🔹 `lseek()`

파일 위치 포인터를 이동시킵니다.

```c
off_t lseek(int fd, off_t offset, int whence);
```

- `SEEK_SET`: 파일의 시작 기준  
- `SEEK_CUR`: 현재 위치 기준  
- `SEEK_END`: 파일 끝 기준

---

### 📂 예제 프로그램 설명

#### ✅ `fopen.c`
- 파일을 열고 성공 여부 출력

#### ✅ `fsize.c`
- 파일을 반복적으로 읽고 총 크기 계산

#### ✅ `copy.c`
- 두 파일을 지정해 파일 내용을 복사

#### ✅ `dup.c`
- `dup()`을 사용하여 동일 파일에 쓰기

#### ✅ `dbcreate.c`
- `student.h` 구조체 기반으로 학생 정보를 DB에 기록  
- `lseek()`을 통해 학번 위치 계산 후 저장

#### ✅ `dbquery.c`
- 입력받은 학번에 해당하는 레코드를 조회 및 출력

#### ✅ `dbupdate.c`
- 기존 레코드를 읽고 점수를 수정 후 다시 저장

---

### 🧾 구조체 정의 (`student.h`)

```c
#define MAX 24
#define START_ID 1401001

struct student {
    char name[MAX];
    int id;
    int score;
};
```

---

### 🧠 핵심 개념 요약

- 시스템 호출은 커널 기능을 요청하는 인터페이스입니다.  
- 파일 디스크립터는 열린 파일을 식별하는 정수입니다.  
- `open()`과 `read()`/`write()`를 통해 저수준 파일 입출력이 가능하며,  
  `dup()`/`lseek()` 등은 고급 제어를 제공합니다.


