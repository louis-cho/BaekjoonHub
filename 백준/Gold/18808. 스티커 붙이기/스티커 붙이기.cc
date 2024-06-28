#include<iostream>
using namespace std;


int N,M,K;
int R,C;
int board[40][40];
int answer = 0;

typedef struct sticker {
    int r,c;
    int area[10][10];
} sticker;

sticker list[100];

bool attach(int stickerNo, int y, int x);
void rotate(int stickerNo);

int main(void){

    cin >> N >> M >> K;
    for(int i=0; i<K; i++)
    {
        cin >> list[i].r >> list[i].c;
        for(int y=0; y<list[i].r; y++) {
            for(int x=0; x<list[i].c; x++) {
                cin >> list[i].area[y][x];
            }
        }
    }


    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            board[i][j] = 0;
        }
    }



    for(int i=0; i<K; i++) {
        bool bAttached = false;
        for(int d=0; d<4; d++) {
            for(int a=0; a<N; a++) {
                for(int b=0; b<M; b++) {
                    if(attach(i, a, b)) {
                        bAttached = true;
                        break;
                    }
                }
                if(bAttached)
                    break;
            }
            if(bAttached)
                break;
            else {
                rotate(i);
            }
        }
    }


    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++){
             if(board[i][j]) {
                answer++;
             }
        }
    }

    cout << answer;


    return 0;
}

bool attach(int stickerNo, int y, int x) {
    int height = list[stickerNo].r;
    int width = list[stickerNo].c;
    if((y + height) > N)
        return false;
    if((x + width) > M)
        return false;

    for(int i=y; i<y+height; i++) {
        for(int j=x; j<x+width; j++) {
            if(board[i][j] && list[stickerNo].area[i-y][j-x]) {
                return false;
            }
        }
    }

    for(int i=y; i<y+height; i++) {
        for(int j=x; j<x+width; j++) {
            if(list[stickerNo].area[i-y][j-x])
                board[i][j] = list[stickerNo].area[i-y][j-x];
        }
    }

    // for(int i=0; i<N; i++) {
    //     for(int j=0; j<M; j++) {
    //         cout << board[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    // cout << "\n\n\n";

    return true;
}

void rotate(int stickerNo) {

    int blank[10][10];

    for(int i=0; i<list[stickerNo].r; i++) {
        for(int j=0; j<list[stickerNo].c; j++) {
            blank[i][j] = list[stickerNo].area[i][j];
        }
    }

    for(int i=0; i<10; i++) {
        for(int j=0; j<10; j++) {
            list[stickerNo].area[i][j] = 0;
        }
    }

    for(int i=0; i<list[stickerNo].r; i++) {
        for(int j=0; j<list[stickerNo].c; j++) {
            list[stickerNo].area[j][list[stickerNo].r-i-1] = blank[i][j];
        }
    }

    int tmp = list[stickerNo].c;
    list[stickerNo].c = list[stickerNo].r;
    list[stickerNo].r = tmp;

}