#include <stdio.h>
#include <stdlib.h>


#define BACKGROUND 255

int main(int argc, char **argv){
    char str[1000]; /*画像ヘッダ*/
    int img1[1024][768]; /*入力画像サイズ(1つ目)*/
    int img2[1024][768]; /*入力画像サイズ(2つ目)*/
    // static int outimg[1024][768]; /*出力画像サイズ*/
    int w1,h1; /*入力画像のおおきさ(1つ目)*/
    int w2,h2; /*入力画像のおおきさ(2つ目)*/
    int ow,oh; /*出力画像のおおきさ*/
    int d; /*画像の階調(0-255)*/
    int x,y; /*画素を配列imgに読み込むためのループカウンタ*/
    FILE *fp1,*fp2,*fp3;

    /*ファイル読み込み*/
    if((fp1 = fopen(argv[1], "r"))==NULL){
        perror(argv[1]);
        exit(1);
    }
    if((fp2 = fopen(argv[2], "r"))==NULL){
        perror(argv[2]);
        exit(1);
    }
    if((fp3 = fopen(argv[3], "w"))==NULL){
        perror(argv[3]);
        exit(1);
    }
    /*ファイルヘッダ読み込み*/
    fscanf(fp1,"%s",str);
    fscanf(fp1,"%d %d", &w1, &h1);
    fscanf(fp1,"%d",&d );

    fscanf(fp2,"%s",str);
    fscanf(fp2,"%d %d", &w2, &h2);
    fscanf(fp2,"%d",&d );

    /*画像処理*/
    /*画像読み込み*/
    for(y = 0; y < h1; y++){
        for(x = 0; x < w1; x++){
            fscanf(fp1, "%d", &img1[x][y]);
        }
    }
    for(y = 0; y < h2; y++){
        for(x = 0; x < w2; x++){
            fscanf(fp2, "%d", &img2[x][y]);
        }
    }

    /*画像加工*/
    int smlw, smlh;/*小さい方の画像のおおきさ*/
    int lrgw, lrgh;/*大きい方の画像のおおきさ*/
    int smlorgx, smlorgy;/*小さい方の画像原点(左上)*/
    int lrgorgx, lrgorgy;/*大きい方の画像原点(左上)*/
    int smlimg;/*小さい方の画像番号(1or2)*/

    ow = (w1 > w2) ? w1 : w2;
    oh = (h1 > h2) ? h1 : h2;
    
    if(ow == w2 && oh == h2){
        smlimg = 1;
    }else if(ow == w1 || oh == h1){
        smlimg = 2;
    }else{
        smlimg = 2;
    }
    switch (smlimg){
        case 1:
            smlw = w1;
            smlh = h1;
            lrgw = w2;
            lrgh = h2;
            break;
        case 2:
            smlw = w2;
            smlh = h2;
            lrgw = w1;
            lrgh = h1;
            break;
        default:
            smlw = 0;
            smlh = 0;
            lrgw = ow;
            lrgh = oh;
            break;
    }

    smlorgx = (ow - smlw)/2;
    smlorgy = (oh - smlh)/2;
    lrgorgx = (ow - lrgw)/2;
    lrgorgy = (oh - lrgh)/2;

    // for(y = 0; y < oh; y++){
    //     for(x = 0; x < ow; x++){
    //         if(x >= smlorgx && x < smlorgx+smlw && y >= smlorgy && y < smlorgy+smlh){
    //             switch (smlimg){
    //             case 1:
    //                 outimg[x][y] = img1[x-smlorgx][y-smlorgy];
    //                 break;
    //             case 2:
    //                 outimg[x][y] = img2[x-smlorgx][y-smlorgy];
    //                 break;
    //             default:
    //                 outimg[x][y] = img2[x-smlw][y-smlh];
    //                 break;
    //             }
    //         }else if(x >= lrgorgx && x < lrgorgx+lrgw && y >= lrgorgy && y < lrgorgy+lrgh){
    //             switch (smlimg){
    //             case 1:
    //                 outimg[x][y] = img2[x-lrgorgx][y-lrgorgy];
    //                 break;
    //             case 2:
    //                 outimg[x][y] = img1[x-lrgorgx][y-lrgorgy];
    //                 break;
    //             default:
    //                 outimg[x][y] = img1[x-lrgorgx][y-lrgorgy];
    //                 break;
    //             }
    //         }else{
    //             outimg[x][y] = BACKGROUND;
    //         }
    //     }
    // }
    

    /*画像出力*/
    fprintf(fp3, "%s\n%d %d\n%d\n", str,ow,oh,d);
    int seg;
    for(y = 0; y < oh; y++){
        for(x = 0; x < ow; x++){
            // fprintf(fp3, "%d ", outimg[x][y]);
            
            if(x >= smlorgx && x < smlorgx+smlw && y >= smlorgy && y < smlorgy+smlh){
                switch (smlimg){
                case 1:
                    seg = img1[x-smlorgx][y-smlorgy];
                    break;
                case 2:
                    seg = img2[x-smlorgx][y-smlorgy];
                    break;
                default:
                    seg = img2[x-smlw][y-smlh];
                    break;
                }
            }else if(x >= lrgorgx && x < lrgorgx+lrgw && y >= lrgorgy && y < lrgorgy+lrgh){
                switch (smlimg){
                case 1:
                    seg = img2[x-lrgorgx][y-lrgorgy];
                    break;
                case 2:
                    seg = img1[x-lrgorgx][y-lrgorgy];
                    break;
                default:
                    seg = img1[x-lrgorgx][y-lrgorgy];
                    break;
                }
            }else{
                seg = BACKGROUND;
            }
            fprintf(fp3, "%d ", seg);
        }
        fprintf(fp3, "\n");
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    return(0);
}