
/***********************Comparison Sorting****************************/
	
	/***************************Bubble Sort***************************/

	void BubbleSort(int *arr, int n)
	{
		for(int i = 0; i < n; i ++ )
		{
			for(int j = n-1; j > i; j -- )
			{
				if(arr[j] < arr[j-1])
					Swap(arr[j], arr[j-1]);
			}
		}
	}


	/**************************Selection Sort**************************/	
	void SelectionSort(int *arr, int n)
	{
		for(int i = 0; i < n; i ++)
		{
			int k = i;
			for(int j = i + 1 ; j < n ; j ++ )
			{
				if(arr[j] < arr[k]) k = j;
			}
			if( k != i ) 
				Swap(arr[i], arr[k]);
		}
	}


	/**************************Insertion Sort**************************/
	void InsertionSort(int *arr, int n)
	{
		for(int i = 1 ; i < n ; i ++ )
		{
			for(int j = i ; j > 0; j -- )
			{
				if ( arr[j] < arr[j-1] )
					Swap(arr[j], arr[j-1]);
			}
		}
	}


	/****************************Shell Sort****************************/
	int m = 5, d[5] = {1, 2, 3, 5, 7};
	void ShellPass(int *arr, int d)
	{
		for(int i = d; i < n ; j ++ )
		{
			int k = d, temp = arr[k];
			while(temp < arr[k-d])
			{
				arr[k] = arr[k-d];
				k -= d;
			}
			arr[k] = temp;
		}
	}
	void ShellSort(int *arr, int n)
	{
		for(int i=m-1;i>=0;i--)
			ShellPass(arr, d[i]);
	}


	/****************************Merge Sort****************************/
	void mergeSort(int *arr, int *temp, int low, int high)//[low, high)
	{
		if(high - low <= 1) return ;
		int mid = (low + high) >> 1;
		MergeSort(arr, low, m);
		mergeSort(arr, m, high);
		int x = low, y = mid, p = x;
		while(x < mid || y < high)
		{
			if ( y == high || (x < mid && arr[x] <= arr[y]) )
				temp[p++] = arr[x++];
			else 
				temp[p++] = arr[y++];
		}
		for(int i = low; i < high; i ++ )
		{
			arr[i] = temp[i];
		}
	}


	/****************************Quick Sort****************************/
	void QuickSort(int *arr, int low, int high)// [low, high]
	{
		if(low >= high) return ;
		int x = low, y = high, mid = (x+y)>>1;
		int key = arr[mid];
		Swap(arr[x], arr[mid]);
		while(x != y)
		{
			while(x <= y &&　arr[y] >= key) y --;
			arr[x] = arr[y];
			while(x <= y &&　arr[x] <= key) x ++;
			arr[y] = arr[x];
		}
		arr[x] = key;
		QuickSort(arr, low, x - 1);
		QuickSort(arr, x + 1, high);
	}


/***************************Bucket Sort********************************/

