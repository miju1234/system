
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

## 📂 파일 관련 시스템 호출

### `open()`
```c
## 📂 파일 관련 시스템 호출 상세 정리

---

### 🔹 `creat()`

지정한 경로에 새 파일을 생성하고 쓰기 전용으로 엽니다.  
기존 파일이 존재할 경우, 내용을 모두 지웁니다.  
사실상 다음과 동일한 기능을 합니다:

```c
int creat(const char *path, mode_t mode);

int open(const char *path, int oflag, [mode_t mode]);


