# 📚 0404 미션 - 생성형 AI + C 프로그래밍

## ✅ 미션 주제

> **0~255 사이의 수를 입력 받아:**
>
> 1. 8비트 **2진수**로 출력  
> 2. **1의 개수**를 출력  
> 3. **상위 4비트**를 출력

---

## 💬 사용한 프롬프트

> "C 언어로 0~255 사이의 정수를 입력 받아 8비트 2진수로 출력하고, 해당 이진수에서 1의 개수를 출력한 뒤, 상위 4비트를 출력하는 프로그램을 작성해줘."

---

## 💻 C 코드

```c
#include <stdio.h>

void print_binary(unsigned char num) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
}

int count_ones(unsigned char num) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if ((num >> i) & 1)
            count++;
    }
    return count;
}

void print_upper_4bits(unsigned char num) {
    printf("상위 4비트: ");
    for (int i = 7; i >= 4; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

int main() {
    int input;
    printf("0~255 사이의 정수를 입력하세요: ");
    if (scanf("%d", &input) != 1 || input < 0 || input > 255) {
        printf("입력 오류: 0부터 255 사이의 정수를 입력하세요.\n");
        return 1;
    }

    unsigned char num = (unsigned char)input;

    printf("2진수: ");
    print_binary(num);
    printf("\n");

    int ones = count_ones(num);
    printf("1의 개수: %d\n", ones);

    print_upper_4bits(num);

    return 0;
}
