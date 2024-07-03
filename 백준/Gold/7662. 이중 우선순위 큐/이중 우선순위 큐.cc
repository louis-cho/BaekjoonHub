#include<iostream>
#include<set>
using namespace std;

int T, k, num, remain, remain_small, remain_bigger;
char ch;

int main(void)
{
	cin >> T;
	for (int t = 0; t < T; t++) {

		remain = 0;
		multiset<int> m_set;

		cin >> k;
		for (int i = 0; i < k; i++) {
			cin >> ch >> num;

			
			if (ch == 'D') {
				if (m_set.empty())
					continue;

				if (num == -1) {
					m_set.erase(m_set.begin());
				}
				else if (num == 1) {
					auto last_elem = m_set.end();
					last_elem--;
					m_set.erase(last_elem);
				}
			}

			else if (ch == 'I') {
				m_set.insert(num);
			}
		}

		if (m_set.empty()) {
			cout << "EMPTY\n";
		}
		else {
			cout << *(--m_set.end()) << " " << *m_set.begin() << "\n";
		}
	}
}