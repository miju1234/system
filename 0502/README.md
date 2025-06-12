# 📘 Chapter 6: 프로세스

---

## 🔹 6.1 프로세스 개요

- **프로세스(process)**: 실행 중인 프로그램
- **PID (Process ID)**: 각 프로세스는 고유한 번호를 가짐
- **PPID (Parent Process ID)**: 부모 프로세스의 번호
- **종류**:
  - 시스템 프로세스 (ex. 데몬)
  - 사용자 프로세스 (사용자 실행)

### 🧾 프로세스 상태 확인

- `ps`, `ps -f`, `ps -ef`
- 항목 설명: UID, PID, PPID, STIME, TTY, TIME, CMD

### 🔍 특정 프로세스 검색

- `pgrep sshd`
- `pgrep -l sshd` (PID + 이름)
- `pgrep -ln sshd` (가장 최근)

---

## 🔹 6.2 작업 제어

### 🎬 후면 처리 (백그라운드 실행)

- `$ 명령어 &`: 백그라운드에서 실행
- 예: `$ sleep 10 &`

### 💤 쉘 재우기

- `$ sleep 초`, `(명령어; sleep; 명령어)`

### ❌ 강제 종료 / 일시 정지

- Ctrl+C (`SIGINT`): 강제 종료
- Ctrl+Z (`SIGTSTP`): 일시 정지

### 🔁 작업 전환

- `fg %작업번호`: 전면 전환
- `bg %작업번호`: 후면 전환

### 📤 입출력 리디렉션

- 출력: `$ 명령어 > file &`
- 입력: `$ 명령어 < file &`

---

## 🔹 6.3 프로세스 제어

### ⛔ 종료: `kill`

- `$ kill PID` 또는 `$ kill %작업번호`
- `$ kill -9 PID` 또는 `$ kill -KILL PID`: 강제 종료

### ⏳ 대기: `wait`

- `$ wait PID`: 자식 종료까지 대기
- `$ wait`: 모든 자식 대기

### 📊 우선순위

- `nice [-n 수치] 명령어`: 우선순위 지정 (기본: 0)
- `renice`: 실행 중 프로세스 우선순위 변경

---

## 🔹 6.4 사용자 ID

### 👤 사용자 정보

- `$ id`: uid, gid 등 정보 출력
- `$ echo $UID $EUID`: 실제/유효 사용자 ID 출력

### 🔐 set-user-ID / set-group-ID

- 실행파일에 특별 권한 부여
- 유효 ID가 파일 소유자나 그룹으로 변경됨
- 설정:
  - `$ chmod 4755 file` 또는 `$ chmod u+s file`
  - `$ chmod 2755 file` 또는 `$ chmod g+s file`

---

## 🔹 6.5 시그널과 프로세스

### 📶 시그널

- 소프트웨어 인터럽트 (예기치 않은 사건 알림)
- 주요 시그널:
  - `SIGINT`: Ctrl+C
  - `SIGTSTP`: Ctrl+Z
  - `SIGKILL`: 강제 종료
  - `SIGCHLD`: 자식 종료

### 📮 시그널 보내기

- `$ kill -SIG 시그널 PID`
- `$ kill -STOP PID`: 일시 정지
- `$ kill -CONT PID`: 계속 실행
- `$ kill -l`: 시그널 리스트 확인

---

## ✅ 핵심 요약

- **프로세스**는 실행 중인 프로그램이며, PID와 부모 PID를 가짐
- **작업 제어**는 fg/bg/kill/wait로 조절 가능
- **ID 시스템**은 접근 권한과 밀접한 관련
- **시그널**은 프로세스를 제어하는 강력한 도구

