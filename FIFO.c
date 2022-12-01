//first in first out page replacement algorithm in c

#include <stdio.h>

int main()
{
	int n = 5;
	// printf("Enter the size of reference string\n");
	// scanf("%d", &n);

	int p[n] = {4, 1, 2, 4, 5};
	// printf("Enter the processes\n");
	// for (int i = 0; i < n; i++) {
	// scanf("%d", p + i);
	// }

	int frames = 3;
	// printf("Enter Number of Frames\n");
	// scanf("%d", &frames);

	int slot[frames] = { -1};

	int pagehit = 0;
	int pagefaults = 0;

	int ptr = 0;		//Points at the process that should be removed first.

	//Iterating for each process in our reference string

	for (int i = 0; i < n; i++) {
		int current = p[i];
		bool ok = false;

		//Finding an empty slot for current process
		for (int j = 0; j < frames; j++) {
			if (slot[j] == current) {	//IF SLOT is empty
				pagehit++;			//increaes page hits
				ok = true;
				break;
			}
		}
		if (!ok) {				//else if slot is not empty then
			pagefaults++;		//increase page faults
			slot[ptr] = current; //insert the current process
			ptr = (ptr + 1) % frames;	//increment the pointer
		}
	}
	printf("Page Faults are: %d\n", pagefaults);
	printf("Page Hits are: %d\n", pagehit);

}
