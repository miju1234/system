# ⚙️ Chapter 9: 프로세스 제어 요약

> 이 장에서는 프로세스 생성, 실행, 종료, 입출력 재지정, 프로세스 그룹과 시스템 부팅 과정을 다룹니다.

---

## 9.1 프로세스 생성

### 🔧 `fork()` 시스템 호출

* 부모 프로세스가 자식 프로세스를 복제하여 생성
* 자식 프로세스에는 `0`, 부모에게는 자식 PID 반환
* 두 프로세스는 병렬적으로 실행됨

```c
pid_t fork(void);
```

### 👨‍👦 자식/부모 구분

```c
pid = fork();
if (pid == 0) {
    // 자식 프로세스 실행 코드
} else {
    // 부모 프로세스 실행 코드
}
```

### 예제: `fork1.c`, `fork2.c`, `fork3.c`

* 각각 하나 또는 두 개의 자식 생성 예시 포함

---

## 9.1-2 자식 종료 기다리기

### 🕒 `wait()`, `waitpid()`

* 부모는 자식 종료 시까지 대기
* 자식 종료 코드 `status`로 받음

```c
pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);
```

* `waitpid()`는 특정 자식 프로세스 대기 가능
* `status >> 8`로 종료 코드 확인

---

## 9.2 프로그램 실행

### 🔄 `exec()` 시스템 호출

* 기존 프로세스를 새로운 프로그램으로 대치
* `main()`부터 새로 시작, **성공 시 리턴하지 않음**

```c
execl(path, arg0, ..., NULL);
execvp(file, argv);
```

### 예제

* `execute1.c`: `echo` 실행
* `execute2.c`: echo, date, ls 실행
* `execute3.c`: 명령줄 인수로 받은 명령 실행

```c
if ((pid = fork()) == 0) {
    execvp(argv[1], &argv[1]);
    // 실패 시 stderr 출력
}
```

---

## 🧪 `system()` 함수

* 쉘을 통해 명령어 실행
* 내부적으로 `fork`, `exec`, `waitpid` 사용

```c
int system(const char *cmdstring);
```

### 예제

```c
system("date > file");
```

* 리턴값: 종료코드 또는 오류 상태

---

## 9.3 입출력 재지정

### 📤 출력 리다이렉션 구현

* `dup2()`로 파일 디스크립터 변경

```c
int dup2(int oldfd, int newfd);
```

### 예제

* `redirect1.c`: 표준출력을 파일로
* `redirect2.c`: 자식 프로세스의 stdout을 파일로 전환 후 명령 실행

```c
fd = open(argv[1], O_WRONLY);
dup2(fd, 1);
execvp(argv[2], &argv[2]);
```

---

## 9.4 프로세스 그룹

### 👥 그룹 개념

* 여러 프로세스 묶음
* 그룹 리더: PID == GID
* `getpgrp()`: 현재 프로세스 그룹 ID 반환

### 그룹 생성/변경

```c
int setpgid(pid_t pid, pid_t pgid);
```

* `setpgid(0,0)` → 현재 프로세스를 새로운 그룹으로 설정

### 예제

* `pgrp1.c`, `pgrp2.c`: fork 후 GID 확인 및 설정

---

## 9.5 시스템 부팅

### 🖥️ 부팅 과정

* **swapper**: 커널 스케줄러
* **init**: 시스템 초기화 `/etc/inittab`
* **getty/login**: 로그인 프롬프트
* **shell**: 로그인 후 사용자 쉘 실행

### 핵심

* 부팅도 fork → exec로 이루어짐

---

## 🧩 핵심 요약

* `fork()`는 부모 프로세스를 복제하여 자식 생성
* `exec()`는 새 프로그램으로 프로세스를 대체
* `wait()`와 `waitpid()`는 자식 종료 대기
* `dup2()`로 입출력 재지정 가능
* `setpgid()`로 프로세스 그룹 제어
* 시스템 부팅은 fork/exec 기반의 프로세스 흐름
