//Least Recently Used Page Replacement Algorithm in C
#include <stdio.h>

int main()
{
	/*User Input & Output
	// int n = 5;
	// printf("Enter the size of reference string\n");
	// scanf("%d", &n);

	// int p[n] = {4, 1, 2, 4, 5};
	// printf("Enter the processes\n");
	// for (int i = 0; i < n; i++) {
	// scanf("%d", p + i);
	// }

	//	int frames = 0;
	// printf("Enter Number of Frames\n");
	// scanf("%d", &frames);
	*/

	//HardCoded Input & Output

	// int p[] = {5, 7, 5, 6, 7, 3};		//frame=3  //F=4 H=2
	int p[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};	//frames=4 F=6 H=7
	// int p[] = {1, 2, 1, 0, 3, 0, 4, 2, 4};		//frames=3 F=6 H=3
	int n = sizeof(p) / sizeof(int);
	int frames = 4;

	int slot[frames] = { -1};
	int recent[frames];

	for (int i = 0; i < frames; i++) {
		recent[i] = -i;		//originally 0-i;
		// recent[i] = i - frames;		//not working on second array.
	}

	for (int i = 0; i < frames; i++) {
		printf("%d ", recent[i]);
	}

	int pagehit = 0;
	int pagefaults = 0;

	//Iterating for each process in our reference string
	for (int i = 0; i < n; i++) {

		int currentp = p[i];
		bool ok = false;
		for (int j = 0; j < frames; j++) {
			if (slot[j] == currentp) {
				pagehit++;
				printf("Hit: CurrentP %d Slot %d\n", currentp, j);
				for (int x = 0; x < frames; x++) {
					if (x == j)continue;
					recent[x]--;
				}
				recent[j]=0;
				ok = true;
				break;
			}
		}

		if (!ok) {
			int mn = 1000, index = -1;
			for (int j = 0; j < frames; j++) {
				if (recent[j] < mn) {
					mn = recent[j];
					index = j;
				}
			}
			pagefaults++;
			slot[index] = currentp;
			recent[index]=0;
			printf("Fault: CurrentP %d Slot %d\n", currentp, index);

			for (int j = 0; j < frames; j++) {
				if (j == index)continue;
				recent[j]--;
			}
		}
		for (int i = 0; i < frames; i++) {
			printf("%d ", recent[i]);
		}
		printf("\n");
	}

	// for (int i = 0; i < frames; i++) {
	// 	printf("%d ", recent[i]);
	// }


	printf("Page Faults are: %d\n", pagefaults);
	printf("Page Hits are: %d\n", pagehit);

}
