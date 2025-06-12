# 🔧 Chapter 9: 프로세스 제어와 관련 시스템 호출 요약

---

## 🔹 9.1 fork() 시스템 호출

- 부모 프로세스가 호출 시 **자식 프로세스 복사 생성**
- 호출 결과:
  - 부모에게는 자식의 PID 반환
  - 자식에게는 0 반환

### 🔸 예제

```c
pid_t pid = fork();
if (pid > 0) printf("부모");
else if (pid == 0) printf("자식");
```

---

## 🔹 9.2 wait() / waitpid()

- 부모가 자식의 종료를 기다릴 때 사용
- `wait(&status)` : 자식 종료 대기
- `waitpid(pid, &status, options)` : 특정 자식 대기

### 🔸 상태 처리 매크로
- `WIFEXITED(status)`: 정상 종료 여부
- `WEXITSTATUS(status)`: 종료 코드 추출

---

## 🔹 9.3 exec() 함수군

- 현재 프로세스를 **새 프로그램으로 덮어씀**
- 종류: `execl`, `execv`, `execle`, `execvp`, `execvpe`

### 🔸 예제

```c
execl("/bin/ls", "ls", "-l", NULL);
execvp("ls", argv);
```

---

## 🔹 9.4 system() 호출

- 명령어 문자열을 해석하여 `sh`로 실행
- 내부적으로 `fork()` + `exec()` + `wait()` 조합

---

## 🔹 9.5 입출력 재지정

- 파일 디스크립터 조작하여 stdin, stdout 변경
- `dup2(fd, 1)`: 파일 fd를 표준출력으로 연결

### 🔸 예제

```c
int fd = open("out.txt", O_WRONLY|O_CREAT, 0644);
dup2(fd, 1);   // stdout → out.txt
execlp("ls", "ls", NULL);
```

---

## 🔹 9.6 프로세스 그룹과 세션

- `getpid()`, `getppid()`: PID, 부모 PID
- `getpgid(pid)`, `setpgid(pid, pgid)`: 그룹 제어
- 세션 생성: `setsid()`

---

## 🔹 예제 파일 요약

| 파일명       | 설명 |
|--------------|------|
| `fork1.c`    | `fork()` 호출의 반환값 확인 |
| `fork2.c`    | 부모/자식이 출력하는 메시지 |
| `fork3.c`    | 두 번 `fork()` 호출로 자식 2개 생성 |
| `forkwait.c` | 자식 종료 후 `wait()` 사용 |
| `waitpid.c`  | 특정 PID를 기다리는 `waitpid()` |
| `execute1.c` | `execl()`로 외부 명령 실행 |
| `execute2.c` | 여러 자식이 다양한 명령 실행 |
| `execute3.c` | 인수로 받은 명령 실행 |
| `redirect1.c`| 표준출력을 파일로 재지정 |
| `redirect2.c`| `ls` 명령 결과를 파일로 출력 |
| `pgrp1.c`    | PID, GID 출력 |
| `pgrp2.c`    | 자식이 새로운 그룹 생성 |
| `syscall.c`  | `system()` 함수 사용 |

---

## ✅ 핵심 요약

- `fork()`는 프로세스 복제, `exec()`는 실행파일 덮어쓰기
- `wait()`는 자식 종료 대기, `waitpid()`는 특정 자식만 대기
- 입출력 재지정은 `dup2()`로 가능
- 프로세스 그룹/세션은 고급 제어 용도로 사용
- 다양한 예제는 `실제 코드 기반 실습`에 적합

