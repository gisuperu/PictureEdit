#include <stdio.h>
#include <stdlib.h>

#define THRESHOLD 127


int main(int argc, char **argv){
    char str[1000]; /*画像ヘッダ*/
    int img[1024][768]; /*入力画像サイズ*/
    int outimg[1024][768]; /*出力画像サイズ*/
    int w,h; /*入力画像のおおきさ*/
    int ow,oh; /*出力画像のおおきさ*/
    int d; /*画像の階調(0-255)*/
    int x,y; /*画素を配列imgに読み込むためのループカウンタ*/
    FILE *fp1,*fp2;

    /*ファイル読み込み*/
    if((fp1 = fopen(argv[1], "r"))==NULL){
        perror(argv[1]);
        exit(1);
    }
    if((fp2 = fopen(argv[2], "w"))==NULL){
        perror(argv[2]);
        exit(1);
    }
    /*ファイルヘッダ読み込み*/
    fscanf(fp1,"%s",str);
    fscanf(fp1,"%d %d", &w, &h);
    fscanf(fp1,"%d",&d );

    /*画像処理*/
    /*画像読み込み*/
    for(y = 0; y < h; y++){
        for(x = 0; x < w; x++){
            fscanf(fp1, "%d", &img[x][y]);
        }
    }

    /*画像加工*/
    ow = w;
    oh = h;
    for(y = 0; y < oh; y++){
        for(x = 0; x < ow; x++){
            if(img[x][y] > THRESHOLD){
                outimg[x][y] = 255;
            }else{
                outimg[x][y] = 0;
            }
        }
    }
    

    /*画像出力*/
    fprintf(fp2, "%s\n%d %d\n%d\n", str,ow,oh,d);
    for(y = 0; y < oh; y++){
        for(x = 0; x < ow; x++){
            fprintf(fp2, "%d ", outimg[x][y]);
        }
        fprintf(fp2, "\n");
    }

    fclose(fp1);
    fclose(fp2);
    return(0);
}