#include<stdio.h>
int main(){
  int cardnum;
  char name[20];  //小伙伴注意了，这个就是定义了一个字符串数组，可以容纳 20 字符
  printf("**********************************************************\n");
  printf("******** Welcome to the books management system ************\n");
  printf("**********************************************************\n");
  printf("~~~~~~~~~\t\t\t\t~~~~~~~~~~~~~~\n");
  printf("Please input your card number:\n");
  scanf("%d", &cardnum);
  printf("Please input your name:\n");
  scanf("%s", name);
  printf("\nWelcome，%s！Your card number is：%d\n", name, cardnum);
  return 0;
}