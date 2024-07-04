#include<iostream>
#include<map>
#include<queue>
#include<algorithm>
using namespace std;


int N, K, number, answer = 0;
map<int,int> counter;
queue<int> scan_sequence;

int main(void){
    cin >> N >> K;

    for(int i=0; i<N; i++)
    {
        cin >> number;
        scan_sequence.push(number);

        if(counter.find(number) == counter.end()) {
            counter[number] = 1;
        } else {
            counter[number]++;
        }

        while (counter[number] > K) {
            counter[scan_sequence.front()]--;
            scan_sequence.pop();
        }

        answer = max(answer, (int)scan_sequence.size());
    }

    cout << answer;
    return 0;
}