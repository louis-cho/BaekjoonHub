#include<iostream>
#include<stack>
using namespace std;

int n, answer=0;
int current = 0;
int x, y;
stack<int> skyline;

int main(void)
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> x >> y;
		
		// 일단 숫자 하나 증가
		if (y == 0) {
			while (!skyline.empty()) {
				skyline.pop();
			}
			continue;
		}
		answer++;

		// 나보다 크면 다 빼
		while (!skyline.empty() && y < skyline.top()) {
			skyline.pop();
		}

		// 나랑 같은 놈이 나오면 하나 감소 나는 넣지마
		if (!skyline.empty() && y == skyline.top()) {
			answer--;
		}
		else {
			skyline.push(y);
		}
		
	}

	cout << answer;
}