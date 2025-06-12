# 🐚 Bash 쉘 스크립트

---

## 1. Bash 쉘 소개

- **Bash (Bourne Again Shell)**: 리눅스 기본 쉘
- **시작 파일**
  - `/etc/profile`, `/etc/bash.bashrc`: 시스템 전체 설정
  - `~/.bash_profile`, `~/.bashrc`: 사용자별 설정

```bash
# ~/.bash_profile 예시
if [ -f ~/.bashrc ]; then
  . ~/.bashrc
fi
export PATH=$PATH:$HOME/bin
```

---

## 2. 별명(alias) 및 히스토리(history)

### 🔸 별명 설정
```bash
alias ll='ls -al --color=yes'
unalias ll
alias
```

### 🔸 히스토리
```bash
history
!!       # 직전 명령 재실행
!20      # 20번 명령 재실행
!gcc     # gcc로 시작하는 명령
!?test   # test 포함 명령
```

---

## 3. 변수

### 🔸 단순 변수
```bash
city="Seoul"
echo $city
```

### 🔸 리스트 변수
```bash
cities=(Seoul Busan Mokpo)
echo ${cities[1]}     # Busan
echo ${#cities[@]}    # 리스트 길이
```

### 🔸 표준 입력
```bash
read name
read x y  # 공백 기준 분할
```

---

## 4. 지역변수와 환경변수

- **지역 변수**: 현재 셸에만 적용
- **환경 변수**: 자식 프로세스에 상속됨 (`export` 사용)

```bash
export country=Korea
echo $HOME $USER $PATH
```

---

## 5. 쉘 스크립트 작성

### 🔸 기본 구조
```bash
#!/bin/bash
echo "Hello, World"
```

### 🔸 실행 방법
```bash
chmod +x script.sh
./script.sh
```

---

## 6. 수식과 연산

### 🔸 조건식 예
```bash
if [ $a -eq $b ]; then ...; fi
if (( a == b )); then ...; fi
```

### 🔸 연산자 종류

| 종류 | 예시 |
|------|------|
| 산술비교 | `-eq`, `-ne`, `-gt`, `-lt` |
| 문자열비교 | `=`, `!=`, `-n`, `-z` |
| 파일비교 | `-e`, `-r`, `-w`, `-x`, `-f`, `-d` |
| 논리연산 | `!`, `&&`, `||` |

### 🔸 산술 연산
```bash
let a=2*3
declare -i a
```

---

## 7. 조건문

```bash
if [ 조건 ]; then
  명령들
elif [ 조건 ]; then
  명령들
else
  명령들
fi
```

### 🔸 case 문
```bash
case $변수 in
  "1") echo "one";;
  "2") echo "two";;
  *) echo "default";;
esac
```

---

## 8. 반복문

### 🔸 for
```bash
for file in *; do
  echo $file
done
```

### 🔸 while
```bash
while (( $i <= 10 )); do
  let i++
done
```

---

## 9. 고급 기능

### 🔸 함수
```bash
greet() {
  echo "Hello, $1"
}
greet World
```

### 🔸 shift
```bash
while [ $# -gt 0 ]; do
  echo $1
  shift
done
```

### 🔸 디렉터리 전체 처리
```bash
for file in *; do
  echo $file
done
```

### 🔸 재귀 호출
```bash
# 하위 디렉토리 모두 순회
if [ -d $dir ]; then
  cd $dir
  for x in *; do
    if [ -d $x ]; then
      ./script.sh $x
    fi
  done
fi
```

---

## ✅ 핵심 요약

- 변수: 단순 변수와 리스트 변수 구분
- 쉘 변수는 지역/환경 변수로 나뉨 (`export`)
- 조건, 반복, 함수, 파일처리 등 Bash 스크립트 기능 풍부
- 명령어 이력과 재실행 가능
- shift, for, case, 함수 등을 이용한 유연한 제어 흐름 구성
