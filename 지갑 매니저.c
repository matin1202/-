
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#pragma warning(disable:4996)

int t = 7, b = 0;

int equal(char str[9]) {
 char colors[17][9] = { "검정", "파랑", "초록", "청록", "빨강", "자주", "노랑", "흰색", "회색", "하늘", "연두", "밝은 청록", "주황", "밝은 자주",  "연 노랑" };
 for (int n = 0;n < 17;n++) {
  if (strcmp(str, colors[n]) == 0) {
   return n;
  }
 }
 return -1;
}

void setColor(int text, int background) {
 int color = (background << 4) | text;
 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void menus(char text[100]) {
 setColor(10, b);
 printf("%s", text);
 setColor(t, b);
}

void bigNumbers(int n) {
 setColor(12, b);
 printf("%d", n);
 setColor(t, b);
 }

void smallNumbers(int n) {
 setColor(9, b);
 printf("%d", n);
 setColor(t, b);
}

void perpareScan() {
 setColor(13, b);
}

void afterScan() {
 setColor(t, b);
}


int main() {
 int i, number, j, k, l;
 char *buffer[20];
 char *ptr;
 char country[50][10];
 char choose_country[10];
 char object[50][20];
 char choose_object[20];
 int price[50];
 int choose_price, result_price;
 char purchase[8], conti[8];
 unsigned long long total = 0;
 FILE *fp = fopen("data.txt", "r");

 for (i = 0; i < 50; i++) {
  memset(buffer, 0, sizeof(buffer));

  fscanf(fp, "%s", buffer);

  ptr = strtok(buffer, ",");
  strcpy(country[i], ptr);

  ptr = strtok(NULL, ",");
  strcpy(object[i], ptr);

  ptr = strtok(NULL, ",");
  price[i] = atof(ptr);
 }
 while(1) {
  char menu[40];
  printf("      원하는 기능을 입력해주세요.\n");
  menus(" | 지갑매니저 |   | 배경색상변경 |\n");
  printf("> ");
  perpareScan();
  scanf("%s", menu);
  afterScan();
  if (strcmp(menu, "지갑매니저") == 0) {
   while (1) {
    while (1) {
     printf("나라 이름을 입력하여 주세요: ");
     perpareScan();
     scanf("%s", choose_country);
     afterScan();
     for (j = 0; j < 50; j++) {
      if (strcmp(choose_country, country[j]) == 0) {
       number = 1;
      }
     }
     if (number == 1) {
      break;
     }
     if (strcmp(choose_country, "몰라") == 0) {
      printf("  나라 목록 \n");
      menus("중국     태국     이집트     미국     영국\n");
     }
     else {
      printf("나라 이름을 다시 확인하여 주세요 \n");
     }
    }
    while (1) {
     printf("물건을 입력하여 주세요: ");
     perpareScan();
     scanf("%s", choose_object);
     afterScan();
     for (k = 0; k < 50; k++) {
      if (strcmp(choose_object, object[k]) == 0) {
       number = 2;
      }
     }
     if (number == 2) {
      break;
     }
     if (strcmp(choose_object, "몰라") == 0) {
      if (strcmp(choose_country, "중국") == 0) {
       printf("     물건 목록 \n");
       menus("물     치약     우산     도장     동전지갑     빵     비빔밥     향궈     햄버거     과일\n");
      }
      else if (strcmp(choose_country, "태국") == 0) {
       printf("     물건 목록 \n");
        menus("물     치약     우산     조각상     파스     빵     비빔밥     타이수끼     햄버거     과일\n");
      }
      else if (strcmp(choose_country, "이집트") == 0) {
       printf("     물건 목록 \n");
       menus("물     치약     우산     조각상     은팔찌     빵     비빔밥     따미야     햄버거     과일\n");
      }
      else if (strcmp(choose_country, "미국") == 0) {
       printf("     물건 목록 \n");
       menus("물     치약     우산     조각상     스노우볼     빵     비빔밥     케이크     햄버거     과일\n");
      }
      else {
       printf("     물건 목록 \n");
       menus("물     치약     우산     버스모형     빅벤시계     빵     비빔밥     케이크     햄버거     과일\n");
      }
     }
     else {
      printf("물건을 다시 확인하여 주세요 \n");
     }
    }
    printf("물건 가격을 입력해 주세요(달러 / 파운드 / 위안 / 바트): ");
    perpareScan();
    scanf("%d", &choose_price);
    afterScan();
    for (l = 0; l < 50; l++) {
     if (strcmp(choose_country, country[l]) == 0 && strcmp(choose_object, object[l]) == 0) {
      if (strcmp(choose_country, "중국") == 0) {
       choose_price = choose_price * 163;
      }
      else if (strcmp(choose_country, "태국") == 0) {
       choose_price *= 33;
      }
      else if (strcmp(choose_country, "이집트") == 0) {
       choose_price *= 62;
      }
      else if (strcmp(choose_country, "미국") == 0) {
       choose_price *= 1118;
      }
      else {
       choose_price *= 1464;
      }
      result_price = choose_price - price[l];
      if (result_price > 0) {
       printf("%s은(는) ", object[l]);
       bigNumbers(result_price);
       printf("원 더 비쌉니다. (사용자가 입력한 가격 : ");
       bigNumbers(choose_price);
       printf("원)\n");
      }
      else if (result_price < 0) {
       printf("%s은(는) ", object[l]);
       smallNumbers(~result_price+1);
       printf("원 더 쌉니다. (사용자가 입력한 가격 : ");
       bigNumbers(choose_price);
       printf("원)\n");
      }
      else {
       printf("%s은(는) 원가입니다. (사용자가 입력한 가격: %d원)\n", object[l], choose_price);
      }
     }
    }
    while (1) {
     printf("그 물건을 사셨나요?(네 / 아니요): ");
     perpareScan();
     scanf("%s", purchase);
     afterScan();
     if (strcmp(purchase, "네") == 0) {
      total = total + choose_price;
      printf("현재까지 사용하신 요금은 ");
      smallNumbers(total);
      printf("원 입니다. \n");
      break;
     }
     else if (strcmp(purchase, "아니요") == 0) {
      printf("현재까지 사용하신 요금은 ");
      smallNumbers(total);
      printf("원 입니다. \n");
      break;
     }
     else {
      printf("다시 작성하여 주세요 \n");
     }
    }

    while (1) {
     printf("계속하시겠습니까?(네 / 아니요): ");
     perpareScan();
     scanf("%s", conti);
     afterScan();
     if (strcmp(conti, "네") == 0) {
      system("cls");
      break;
     }
     else if (strcmp(conti, "아니요") == 0) {
      return 0;
     }
     else {
      printf("다시 작성하여 주세요 \n");
     }
    }
   }
  }
  if (strcmp(menu, "배경색상변경") == 0) {
   for (;;) {
    char colors[17][14] = { "검정 ■", "파랑 ■", "초록 ■", "청록 ■", "빨강 ■", "자주 ■", "노랑 ■", "흰색 ■", "회색 ■", "하늘 ■", "연두 ■", "밝은 청록 ■", "주황 ■", "밝은 자주 ■",  "연 노랑 ■" };
    for (int n = 0;n < 14;n++) {
     setColor(t, n);
     printf("%s\n", colors[n]);
    }
    setColor(t, b);
    printf("색상을 선택하세요.\n");
    char choose[9];
    perpareScan();
    scanf("%s", choose);
    afterScan();
    if (equal(choose) == -1) {
     printf("색상을 확인해주세요.\n");
     continue;
    }
    setColor(t, equal(choose));
    b = equal(choose);
    system("cls");
    break;
   }
  }
 }
 return 0;
}
