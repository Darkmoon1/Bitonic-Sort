#include <iostream>  
using namespace std;

void segmentedBitonicSort(float* segdata, int* seg_id, int* seg_start, int n, int m)
{
	////判断输入是否有误
	if (n <= 0 || m <= 0 || m>n)
	{
		cout << "Input error!n>m>0" << endl;
		return;
	}
	if (!(seg_start[m] == n && seg_id[n - 1] == (m - 1)))
	{
		cout << "Input error! seg_start[m]==n,seg_id[n-1]==(m-1)" << endl;
		return;
	}
	//先段内排序
	for (int d = 0; d<m; d++)
	{
		int len = 1;

		//seg_start[d+1]-seg_start[d]为此段长度
		int _real_length = (seg_start[d + 1] - seg_start[d]);

		while (len <= _real_length)//循环退出的条件 
			len = len << 1;//寻找小于等于n的最大的2的幂次方len
		len = len >> 1;

		//超出2的n次方部分长度
		int _lack_length = _real_length - len;

		//判断是否是2的次方长度 是
		if (_lack_length == 0)
		{
			for (int step = 2; step <= len; step <<= 1)
			{
				//////内部循环可任意交换
				for (int i = 0; i < len; i += step << 1)//1
				{
					///前半部分升序排
					for (int step0 = step >> 1; step0 >0; step0 >>= 1)// 2
					{
						for (int j = 0; j < step; j += step0 << 1)//3
						{
							for (int k = 0; k < step0; ++k)//4
							{

								if (segdata[i + j + k + seg_start[d]] > segdata[i + j + k + step0 + seg_start[d]] || segdata[i + j + k + seg_start[d]] != segdata[i + j + k + seg_start[d]])  //交换数据使升序排列,同时判断二者之中是否有NaN
								{
									//交换data 
									float T = segdata[i + j + k + seg_start[d]];
									segdata[i + j + k + seg_start[d]] = segdata[i + j + k + step0 + seg_start[d]];
									segdata[i + j + k + step0 + seg_start[d]] = T;
								}
							}
						}
					}
					//后半部分降序排
					if (i + step < len)
					{  //////内部循环可任意交换
						for (int step0 = step >> 1; step0 >0; step0 >>= 1) //1
						{
							for (int j = 0; j < step; j += step0 << 1) //2
							{
								for (int k = 0; k < step0; ++k) //3
								{

									if (segdata[i + step + j + k + seg_start[d]] < segdata[i + step + j + step0 + k + seg_start[d]]
										|| segdata[i + step + j + step0 + k + seg_start[d]] != segdata[i + step + j + step0 + k + seg_start[d]]) //交换数据使降序排列,同时判断二者之中是否有NaN
									{
										//交换data 
										float T = segdata[i + step + j + k + seg_start[d]];
										segdata[i + step + j + k + seg_start[d]] = segdata[i + step + j + k + step0 + seg_start[d]];
										segdata[i + step + j + k + step0 + seg_start[d]] = T;
									}
								}
							}
						}
					}
				}

			}
		}
		//不是2的次方长度
		else
		{
			//step 1 
			for (int step = 2; step <= len; step <<= 1)
			{
				//////内部循环可任意交换
				for (int i = 0; i < len; i += step << 1)//1
				{
					///前半部分升序排
					for (int step0 = step >> 1; step0 >0; step0 >>= 1)// 2
					{
						for (int j = 0; j < step; j += step0 << 1)//3
						{
							for (int k = 0; k < step0; ++k)//4
							{

								if (segdata[i + j + k + seg_start[d]] > segdata[i + j + k + step0 + seg_start[d]] || segdata[i + j + k + seg_start[d]] != segdata[i + j + k + seg_start[d]])  //交换数据使升序排列,同时判断二者之中是否有NaN
								{
									//交换data 
									float T = segdata[i + j + k + seg_start[d]];
									segdata[i + j + k + seg_start[d]] = segdata[i + j + k + step0 + seg_start[d]];
									segdata[i + j + k + step0 + seg_start[d]] = T;
								}
							}
						}
					}
					//后半部分降序排
					if (i + step < len)
					{  //////内部循环可任意交换
						for (int step0 = step >> 1; step0 >0; step0 >>= 1) //1
						{
							for (int j = 0; j < step; j += step0 << 1) //2
							{
								for (int k = 0; k < step0; ++k) //3
								{

									if (segdata[i + step + j + k + seg_start[d]] < segdata[i + step + j + step0 + k + seg_start[d]]
										|| segdata[i + step + j + step0 + k + seg_start[d]] != segdata[i + step + j + step0 + k + seg_start[d]]) //交换数据使降序排列,同时判断二者之中是否有NaN
									{
										//交换data 
										float T = segdata[i + step + j + k + seg_start[d]];
										segdata[i + step + j + k + seg_start[d]] = segdata[i + step + j + k + step0 + seg_start[d]];
										segdata[i + step + j + k + step0 + seg_start[d]] = T;
									}
								}
							}
						}
					}
				}

			}

			//step 2
			for (int step = 2; step <= len; step <<= 1)
			{
				//////内部循环可任意交换
				for (int i = _lack_length; i < len + _lack_length; i += step << 1)//1
				{
					///前半部分升序排
					for (int step0 = step >> 1; step0 >0; step0 >>= 1)// 2
					{
						for (int j = 0; j < step; j += step0 << 1)//3
						{
							for (int k = 0; k < step0; ++k)//4
							{

								if (segdata[i + j + k + seg_start[d]] > segdata[i + j + k + step0 + seg_start[d]] || segdata[i + j + k + seg_start[d]] != segdata[i + j + k + seg_start[d]])  //交换数据使升序排列,同时判断二者之中是否有NaN
								{
									//交换data 
									float T = segdata[i + j + k + seg_start[d]];
									segdata[i + j + k + seg_start[d]] = segdata[i + j + k + step0 + seg_start[d]];
									segdata[i + j + k + step0 + seg_start[d]] = T;
								}
							}
						}
					}
					//后半部分降序排
					if (i + step < len)
					{  //////内部循环可任意交换
						for (int step0 = step >> 1; step0 >0; step0 >>= 1) //1
						{
							for (int j = 0; j < step; j += step0 << 1) //2
							{
								for (int k = 0; k < step0; ++k) //3
								{

									if (segdata[i + step + j + k + seg_start[d]] < segdata[i + step + j + step0 + k + seg_start[d]]
										|| segdata[i + step + j + step0 + k + seg_start[d]] != segdata[i + step + j + step0 + k + seg_start[d]]) //交换数据使降序排列,同时判断二者之中是否有NaN
									{
										//交换data 
										float T = segdata[i + step + j + k + seg_start[d]];
										segdata[i + step + j + k + seg_start[d]] = segdata[i + step + j + k + step0 + seg_start[d]];
										segdata[i + step + j + k + step0 + seg_start[d]] = T;
									}
								}
							}
						}
					}
				}

			}

			//step 3
			for (int step = 2; step <= len; step <<= 1)
			{
				//////内部循环可任意交换
				for (int i = 0; i < len; i += step << 1)//1
				{
					///前半部分升序排
					for (int step0 = step >> 1; step0 >0; step0 >>= 1)// 2
					{
						for (int j = 0; j < step; j += step0 << 1)//3
						{
							for (int k = 0; k < step0; ++k)//4
							{

								if (segdata[i + j + k + seg_start[d]] > segdata[i + j + k + step0 + seg_start[d]] || segdata[i + j + k + seg_start[d]] != segdata[i + j + k + seg_start[d]])  //交换数据使升序排列,同时判断二者之中是否有NaN
								{
									//交换data 
									float T = segdata[i + j + k + seg_start[d]];
									segdata[i + j + k + seg_start[d]] = segdata[i + j + k + step0 + seg_start[d]];
									segdata[i + j + k + step0 + seg_start[d]] = T;
								}
							}
						}
					}
					//后半部分降序排
					if (i + step < len)
					{  //////内部循环可任意交换
						for (int step0 = step >> 1; step0 >0; step0 >>= 1) //1
						{
							for (int j = 0; j < step; j += step0 << 1) //2
							{
								for (int k = 0; k < step0; ++k) //3
								{

									if (segdata[i + step + j + k + seg_start[d]] < segdata[i + step + j + step0 + k + seg_start[d]]
										|| segdata[i + step + j + step0 + k + seg_start[d]] != segdata[i + step + j + step0 + k + seg_start[d]]) //交换数据使降序排列,同时判断二者之中是否有NaN
									{
										//交换data 
										float T = segdata[i + step + j + k + seg_start[d]];
										segdata[i + step + j + k + seg_start[d]] = segdata[i + step + j + k + step0 + seg_start[d]];
										segdata[i + step + j + k + step0 + seg_start[d]] = T;
									}
								}
							}
						}
					}
				}

			}

		}
		///////对整个数组进行排序
		



	}
}
void main()
{
	float data[10] = { 0,sqrt(-1.f) - 100 , 2, 100, 4, 0.5, sqrt(-1.f), 3, 0.1, 2 };
	int seg_id[10] = { 0, 0, 0, 1, 1, 1, 2, 2, 2, 2 };
	int seg_start[4] = { 0,3,6,10 };
	int n = 10;
	int m = 3;

	
	for (int i = 0; i < n; ++i)
	{
		cout << data[i] << "\t";
	}
	cout << endl;

	for (int i = 0; i < n; ++i)
	{
		cout << seg_id[i] << "\t";
	}
	cout << endl;

	//调用分段双调函数	
	segmentedBitonicSort(data, seg_id, seg_start, n, m);
	//输出

	for (int i = 0; i < n; ++i)
	{
		cout << data[i] << "\t";
	}
	cout << endl;
	system("pause");

}

