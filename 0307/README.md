# Ubuntu 리눅스 설치하기

---

## ✅ 사전 조건
- Windows 10 (버전 2004 이상) 또는 Windows 11
- 관리자 권한 필요

---

## 1️⃣ WSL 및 가상 머신 기능 활성화

```powershell
wsl --install
```

> 만약 `wsl` 명령이 인식되지 않으면:
```powershell
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
```

---

## 2️⃣ WSL2 기본 버전 설정

```powershell
wsl --set-default-version 2
```

---

## 3️⃣ Microsoft Store에서 Ubuntu 설치

- **Microsoft Store** 실행
- "Ubuntu 22.04 LTS" 검색
- 설치 → 실행

---

## 4️⃣ 초기 설정

- 새 Ubuntu 터미널 실행 시:
  - 사용자 이름 입력
  - 비밀번호 설정

---

## 5️⃣ 설치 확인

```bash
wsl --list --verbose
```

- `VERSION`이 2이면 WSL2 설치 완료

---

