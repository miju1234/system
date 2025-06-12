# 📘 Chapter 4: C 표준 파일 입출력 요약

---

## 🔹 시스템 호출 vs C 라이브러리 함수
- **시스템 호출**: 커널에 직접 서비스 요청 (`read`, `write` 등)
- **C 라이브러리 함수**: 시스템 호출을 감싸 사용자에게 편의 제공 (`fopen`, `fclose` 등)

---

## 🔹 파일과 파일 포인터
- **fopen()**: 파일 열기  
  ```c
  FILE *fp = fopen("file.txt", "r");
  ```
- **FILE 구조체**: 파일 스트림 정보 저장 (버퍼, 포인터, 상태 등)
- **fclose(fp)**: 파일 닫기

---

## 🔹 텍스트 파일 입출력 함수

| 목적      | 표준 입출력    | 파일 입출력        |
|-----------|----------------|--------------------|
| 문자입력  | `getchar()`    | `fgetc()`, `getc()` |
| 문자출력  | `putchar()`    | `fputc()`, `putc()` |
| 문자열입력| `gets()`       | `fgets()`          |
| 문자열출력| `puts()`       | `fputs()`          |
| 포맷입력  | `scanf()`      | `fscanf()`         |
| 포맷출력  | `printf()`     | `fprintf()`        |

---

## 🔹 이진 파일 입출력
- **fopen("file", "rb/wb/ab")**: 바이너리 모드로 파일 열기
- **fread()/fwrite()**: 블록 단위 입출력  
  ```c
  fread(&data, sizeof(data), 1, fp);
  fwrite(&data, sizeof(data), 1, fp);
  ```

---

## 🔹 임의 접근 (랜덤 액세스)
- **fseek(fp, offset, mode)**: 파일 위치 설정
  - `SEEK_SET`, `SEEK_CUR`, `SEEK_END`
- **ftell(fp)**: 현재 파일 위치 반환
- **rewind(fp)**: 파일 처음으로 이동

---

## 🔹 버퍼 입출력
- **C 라이브러리 버퍼 방식**
  - 완전 버퍼: 파일 (ex. `fopen`)
  - 줄 버퍼: 표준 입출력 (ex. `stdout`)
  - 버퍼 없음: 오류 출력 (ex. `stderr`)
- **setbuf(fp, buf)**: 버퍼 설정
- **setvbuf(fp, buf, mode, size)**:
  - `_IOFBF`: 완전 버퍼
  - `_IOLBF`: 줄 버퍼
  - `_IONBF`: 버퍼 없음
- **fflush(fp)**: 버퍼 비우기 (flush)

---

## 🔹 문자열 처리 함수 (string.h)

| 함수            | 설명                                       |
|----------------|--------------------------------------------|
| `strcpy`, `strncpy` | 문자열 복사                            |
| `strcat`, `strncat` | 문자열 연결                            |
| `strcmp`, `strncmp` | 문자열 비교                            |
| `strchr`, `strrchr` | 문자 위치 찾기                         |
| `strstr`           | 부분 문자열 검색                        |
| `strlen`           | 문자열 길이                             |
| `strtok`           | 문자열 토큰화                           |

---

## ✅ 핵심 요약
- `fopen`으로 파일 열기 → `FILE*` 반환
- `fgetc`, `fputc`: 문자 단위
- `fgets`, `fputs`: 줄 단위
- `fread`, `fwrite`: 블록 단위
- `fseek`, `ftell`: 임의 접근
- `setvbuf`, `fflush`: 버퍼 조절
