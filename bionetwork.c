#include <stdio.h>
#include <string.h>
#include "Yeast.h"
#include "Mammal.h"
#include "Name.h"
//別途三つのファイルがあるのですが、著作権がわからないので載せられないです。

int main(void) {
  int matrix_common[52][164] = {0};
  int x = 0;
  printf("stressを結果に含みたい場合は0を、含みたくない場合は1を入力してください");
  scanf("%d", &x);
  for(int i = 0; i < 52; i++){
    for(int j = 0; j < 164; j++){
      if(x && strstr(molecule[i],"stress") != NULL) matrix_common[i][j] = 0;
      else if(matrix_m[i][j] == matrix_y[i][j]) matrix_common[i][j] = matrix_m[i][j];
      else matrix_common[i][j] = 0;
    }
  }
  for(int i = 0; i < 164; i++){
    int first = 1;
    int only_product = 1;

    // 反応物を列挙
    for(int j = 0; j < 52; j++){
      if(matrix_common[j][i] == -1){
        if(first) printf("R%d: ",i);
        if(!first) printf(" + ");
        printf("%s", molecule[j]);
        first = 0;
        only_product = 0;
      }
    }

    // 生成物を列挙
    first = 1;
    for(int j = 0; j < 52; j++){
      if(matrix_common[j][i] == 1){
        if(only_product && first) printf("R%d:",i);
        if(first) printf(" -> ");
        if(!first) printf(" + ");
        printf("%s", molecule[j]);
        first = 0;
      }
    }
    if(!first) printf("\n");
  }

  return 0;
}