#include <iostream>
using namespace std;

int main (void)
{
	int repeat = 0;
	cin >> repeat;
	bool ans[repeat];
	for (int i = 0; i < repeat; i++)
	{
		int p = 0, q = 0, m = 0, n = 0, sum = 0;
	       	cin >> p >> q >> n;
		ans[i] = 1;
		for (int j = 0; j < n; j++)
		{
			int t1,t2, time;
			cin >> t1 >> t2;
			time = t2 - t1;
			sum += time;
			if (sum > p || time > q)
			{
				ans[i] = 0;
				break;
			}
		}
	}

	for (int i = 0; i < repeat; i++)
		cout << ans[i];

	return 0;
}
	
