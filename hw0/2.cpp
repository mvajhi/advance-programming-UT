#include <iostream>
using namespace std;

int main (void)
{
	int repeat = 0;
	cin >> repeat;
	int ans[repeat][2];
	for (int i = 0; i < repeat; i++)
	{
		int p = 0, q = 0, m = 0, n = 0, sum = 0, longest = 0;
	       	cin >> p >> q >> n;
		for (int j = 0; j < n; j++)
		{
			int t1,t2, time;
			cin >> t1 >> t2;
			time = t2 - t1;
			sum += time;
			if (time > longest)
				longest = time;
		}
		ans[i][0] = sum - p;
		if (ans[i][0] < 0)
			ans[i][0] = 0;
		ans[i][1] = longest - q;
		if (ans[i][1] < 0)
			ans[i][1] = 0;
	}

	for (int i = 0; i < repeat; i++)
		cout << ans[i][0] << " " << ans[i][1] << "\n";

	return 0;
}
	
