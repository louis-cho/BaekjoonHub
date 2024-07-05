#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

int map[8][8], originMap[8][8];
vector<pair<int, int>> cctv;
int N, M;
int answer = 2e9;

int calcAnswer();

void scanForward(int i, int j, int dir)
{
    if (dir == 0)
    {
        for (int n = i; n >= 0; n--)
        {
            if (map[n][j] == 6)
                break;
            if (map[n][j] > 0)
                continue;
            map[n][j] = -1;
        }
    }
    else if (dir == 1)
    {
        for (int n = i; n < N; n++)
        {
            if (map[n][j] == 6)
                break;
            if (map[n][j] > 0)
                continue;
            map[n][j] = -1;
        }
    }
    else if (dir == 2)
    {
        for (int m = j; m >= 0; m--)
        {
            if (map[i][m] == 6)
                break;
            if (map[i][m] > 0)
                continue;
            map[i][m] = -1;
        }
    }
    else if (dir == 3)
    {
        for (int m = j; m < M; m++)
        {
            if (map[i][m] == 6)
                break;
            if (map[i][m] > 0)
                continue;
            map[i][m] = -1;
        }
    }
}
void scan(int i, int j, int type, int dir)
{
    switch (type)
    {
    case 1:
    {
        scanForward(i, j, dir);
    }
    break;

    case 2:
    {
        if (dir < 2)
        {
            scanForward(i, j, 0);
            scanForward(i, j, 1);
        }
        else
        {
            scanForward(i, j, 2);
            scanForward(i, j, 3);
        }
    }
    break;

    case 3:
    {
        if (dir == 0)
        {
            scanForward(i, j, UP);
            scanForward(i, j, RIGHT);
        }
        else if (dir == 1)
        {
            scanForward(i, j, RIGHT);
            scanForward(i, j, DOWN);
        }
        else if (dir == 2)
        {
            scanForward(i, j, DOWN);
            scanForward(i, j, LEFT);
        }
        else if (dir == 3)
        {
            scanForward(i, j, LEFT);
            scanForward(i, j, UP);
        }
    }
    break;

    case 4:
    {
        if (dir == 0)
        {
            scanForward(i, j, DOWN);
            scanForward(i, j, LEFT);
            scanForward(i, j, RIGHT);
        }
        else if (dir == 1)
        {
            scanForward(i, j, UP);
            scanForward(i, j, LEFT);
            scanForward(i, j, RIGHT);
        }
        else if (dir == 2)
        {
            scanForward(i, j, UP);
            scanForward(i, j, DOWN);
            scanForward(i, j, RIGHT);
        }
        else if (dir == 3)
        {
            scanForward(i, j, UP);
            scanForward(i, j, DOWN);
            scanForward(i, j, LEFT);
        }
    }
    break;

    case 5:
    {
        scanForward(i, j, UP);
        scanForward(i, j, DOWN);
        scanForward(i, j, LEFT);
        scanForward(i, j, RIGHT);
    }
    break;
    }
}

void selectCCTVDirection(int idx)
{
    if (idx == cctv.size())
    {
        int tmpAnswer = calcAnswer();
        if (tmpAnswer < answer)
        {
            answer = tmpAnswer;
        }
    }
    else
    {
        auto currentCCTV = cctv.at(idx);
        int tmp[8][8];
        memcpy(&(tmp[0][0]), &(map[0][0]), sizeof(map)); // 현재 맵 상황 복사
        for (int d = 0; d < 4; d++)
        {
            scan(currentCCTV.first, currentCCTV.second, map[currentCCTV.first][currentCCTV.second], d);
            selectCCTVDirection(idx + 1);
            memcpy(&(map[0][0]), &(tmp[0][0]), sizeof(tmp)); // 원복
        }
    }
}

int calcAnswer()
{
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (map[i][j] == 0)
                cnt++;
        }
    }

    return cnt;
}

int main(void)
{

    cin >> N >> M;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> originMap[i][j];
            if (originMap[i][j] > 0 && originMap[i][j] != 6)
            {
                cctv.push_back({i, j});
            }
        }
    }

    memcpy(&(map[0][0]), &(originMap[0][0]), sizeof(originMap));
    selectCCTVDirection(0);

    cout << answer << "\n";
    return 0;
}