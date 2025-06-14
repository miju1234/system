# 📘 리눅스 기본 명령어 요약

## 📂 1. 시스템 정보 확인

| 명령어 | 설명 |
|--------|------|
| `date` | 현재 날짜와 시간 출력 |
| `hostname` | 컴퓨터 이름 확인 |
| `uname` | OS 정보 확인 (`-a` 옵션으로 전체 출력) |
| `whoami` | 현재 사용자 계정 |
| `who` | 로그인한 사용자 전체 목록 |
| `clear` | 터미널 화면 정리 |

---

## 📁 2. 디렉토리 명령어

| 명령어 | 설명 |
|--------|------|
| `pwd` | 현재 작업 디렉토리 경로 확인 |
| `cd` | 디렉토리 이동 (없으면 홈으로) |
| `cd ~` | 홈 디렉토리로 이동 |
| `cd ..` | 부모 디렉토리로 이동 |
| `mkdir` | 새 디렉토리 생성 |
| `mkdir -p` | 중간 디렉토리 포함 생성 |
| `rmdir` | 빈 디렉토리 삭제 |

> 🔸 디렉토리는 트리 형태 계층 구조를 가짐  
> 🔸 경로명은 절대경로(`/`)와 상대경로(`./`, `../`)로 구분됨

---

## 📄 3. 파일 관련 명령어

| 명령어 | 설명 |
|--------|------|
| `touch` | 빈 파일 생성 |
| `cat` | 파일 내용 출력, 입력 저장 가능 (`cat > 파일`) |
| `more`, `less` | 페이지 단위 출력 |
| `head`, `tail` | 앞/뒤 10줄 출력 (`-n` 옵션 사용 가능) |
| `wc` | 줄/단어/문자 수 출력 (`-l`, `-w`, `-c` 옵션) |
| `cp` | 파일 복사 (`-i`로 덮어쓰기 확인) |
| `mv` | 파일 이동/이름 변경 |
| `rm` | 파일 삭제 |
| `rm -r` | 디렉토리 포함 전부 삭제 |

---

## 🔗 4. 링크

| 종류 | 설명 |
|------|------|
| 하드 링크 | i-node 공유 (같은 파일 내용 공유) |
| 심볼릭 링크 | 경로를 참조하는 파일 (별도의 포인터) |

```bash
ln 원본 새이름          # 하드 링크
ln -s 원본 새이름       # 심볼릭 링크

## 🔐 5. 접근권한 및 소유자

### 📄 파일 권한 구조 (`ls -l` 예시)

```bash
-rw-r--r-- 1 user group 2088 4월 16 13:37 cs1.txt
```

| 항목 | 설명 |
|------|------|
| `-` | 일반 파일 (`d`: 디렉토리, `l`: 링크 등) |
| `rw-` | 소유자 권한: 읽기(r), 쓰기(w) |
| `r--` | 그룹 권한: 읽기 |
| `r--` | 기타 사용자 권한: 읽기 |
| 숫자 1 | 하드 링크 수 |
| user/group | 소유자/그룹 |
| 2088 | 파일 크기 (bytes) |
| 날짜 | 최종 수정일 |
| cs1.txt | 파일명 |

---

### 🔑 5. 권한 설정 방법

#### ✅ 숫자(8진수) 방식

| 권한 값 | 의미 |
|---------|------|
| 777 | rwxrwxrwx |
| 755 | rwxr-xr-x |
| 644 | rw-r--r-- |
| 700 | rwx------ |

```bash
chmod 755 filename
```

#### ✅ 기호 방식

| 기호 | 의미 |
|------|------|
| u | 사용자 (user) |
| g | 그룹 (group) |
| o | 기타 사용자 (others) |
| a | 전체 사용자 (all) |
| + | 권한 추가 |
| - | 권한 제거 |
| = | 권한 설정 |

```bash
chmod g+w file.txt   # 그룹에게 쓰기 권한 추가
chmod o-r file.txt   # 기타 사용자에게 읽기 권한 제거
```

---

### 👤 소유자/그룹 변경

```bash
chown user file         # 파일 소유자 변경
chgrp group file        # 그룹 변경
chown -R user dir/      # 디렉토리 전체 변경
```

> 슈퍼유저(root)만 소유자 변경 가능

---

## 📤 6. 입출력 재지정 및 파이프

### ▶ 출력 재지정

| 기호 | 기능 |
|------|------|
| `>` | 표준출력을 파일로 저장 (덮어쓰기) |
| `>>` | 표준출력을 파일에 추가 |
| `<` | 표준입력을 파일에서 읽음 |

```bash
echo "Hello" > hello.txt
echo "World" >> hello.txt
cat < hello.txt
```

---

### ▶ 파이프 `|`

- 한 명령의 출력을 다음 명령의 입력으로 전달

```bash
ls | sort -r
ls | wc -l
cat file.txt | grep "linux"
```

---

### ▶ 복합 예시

```bash
cat file1 file2 > combined.txt
ls -al | grep ".cpp" > cpp_list.txt
```

---

## 📝 7. gedit 편집기 (GUI 기반 텍스트 에디터)

### ▶ 소개

- GNOME 환경에서 기본 제공되는 GUI 텍스트 편집기
- 텍스트 파일, 프로그래밍 코드, 마크업 문서 편집에 적합

---

### ▶ 실행 방법

```bash
gedit file.txt         # 파일 열기
gedit &                # 편집기만 실행
```

- 또는 메뉴에서 [프로그램] → [텍스트 편집기]

---

### ▶ 주요 기능 요약

| 항목 | 설명 |
|------|------|
| 파일 | 새로 만들기, 열기, 저장, 다른 이름 저장 |
| 편집 | 복사, 붙여넣기, 실행 취소 등 |
| 보기 | 도구 모음, 강조 모드 |
| 찾기 | 텍스트 찾기/바꾸기, 줄 이동 |
| 도구 | 맞춤법 검사, 문서 통계 |
| 설정 | 글꼴, 테마, 플러그인 설정 등 |

---

