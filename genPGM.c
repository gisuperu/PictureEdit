#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define STR "P2"
#define W 100
#define H 500
#define D 255

#define BACKGROUND 0

int ripple(int radius, int x, int y){
    int val = (x*x + y*y) % (radius*radius);
    return val*255/(radius*radius);
}

int ichimatsu(int square, int x, int y){
    if(((x+y)/square)%2 == 1){
        return 255;
    }else{
        return 0;
    }
}

int main(int argc, char **argv){
    char str[1000]; /*画像ヘッダ*/
    int outimg[1024][768]; /*出力画像サイズ*/
    int ow,oh; /*出力画像のおおきさ*/
    int d; /*画像の階調(0-255)*/
    int x,y; /*画素を配列imgに読み込むためのループカウンタ*/
    FILE *fp1;

    /*ファイル読み込み*/
    if((fp1 = fopen(argv[1], "w"))==NULL){
        perror(argv[1]);
        exit(1);
    }

    /*画像処理*/
    /*変数定義*/
    strcpy(str, STR);
    ow = W;
    oh = H;
    d = D;

    /*画像加工*/
    srandomdev();
    int rnd = random()%2;
    int radius = 40;
    int square = 5;

    for(y = 0; y < oh; y++){
        for(x = 0; x < ow; x++){
            switch(rnd){
                case 0: outimg[x][y] = ripple(radius, x, y); break;
                case 1: outimg[x][y] = ichimatsu(square, x, y); break;
                default: outimg[x][y] = BACKGROUND;
            }
        }
    }
    

    /*画像出力*/
    fprintf(fp1, "%s\n%d %d\n%d\n", str,ow,oh,d);
    for(y = 0; y < oh; y++){
        for(x = 0; x < ow; x++){
            fprintf(fp1, "%d ", outimg[x][y]);
        }
        fprintf(fp1, "\n");
    }

    fclose(fp1);
    return(0);
}