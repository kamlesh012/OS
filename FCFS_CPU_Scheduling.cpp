//FCFS CPU Scheduling Algorithm
//Works for Both Type of (Different & Same) Arrival Times

#include <iostream>
#include <algorithm>
using namespace std;
struct Process {
	int at;
	int bt;
};

bool comp(struct Process &a, struct Process &b) {
	return a.at < b.at;
}

int main() {
	int n; cin >> n;
	Process arr[n];

	for (int i = 0; i < n; i++) {
		cin >> arr[i].at;
	}

	for (int i = 0; i < n; i++) {
		cin >> arr[i].bt;
	}

	sort(arr, arr + n, comp);
	int total = 0;
	int completion = 0;
	int ct[n];
	completion = arr[0].bt;
	ct[0] = arr[0].bt;

	for (int i = 1; i < n; i++) {
		completion += arr[i].bt;
		ct[i] = completion;
	}

	int tat[n], wt[n];
	float avgtat = 0.0f, avgwt = 0.0f;

	for (int i = 0; i < n; i++) {
		tat[i] = ct[i] - arr[i].at;
		wt[i] = tat[i] - arr[i].bt;
		avgtat += tat[i];
		avgwt += wt[i];
	}

	avgtat /= n;
	avgwt /= n;

	cout << "Process\tAT\tBT\tTAT\tWt\n";
	for (int i = 0; i < n; i++) {
		cout << i + 1 << " " << arr[i].at << " " << arr[i].bt << " " << tat[i] << " " << wt[i] << endl;
	}
	cout << "Average TAT is\t" << avgtat << endl << "Average WT is\t" << avgwt << endl;




	return 0;
}
