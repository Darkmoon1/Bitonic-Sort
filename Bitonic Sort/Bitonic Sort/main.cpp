#include <iostream>  
using namespace std;

void segmentedBitonicSort(float* segdata, int* seg_id, int* seg_start, int n, int m)
{
	////�ж������Ƿ�����
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
	//�ȶ�������
	for (int d = 0; d<m; d++)
	{
		int len = 1;

		//seg_start[d+1]-seg_start[d]Ϊ�˶γ���
		int _real_length = (seg_start[d + 1] - seg_start[d]);

		while (len <= _real_length)//ѭ���˳������� 
			len = len << 1;//Ѱ��С�ڵ���n������2���ݴη�len
		len = len >> 1;

		//����2��n�η����ֳ���
		int _lack_length = _real_length - len;

		//�ж��Ƿ���2�Ĵη����� ��
		if (_lack_length == 0)
		{
			for (int step = 2; step <= len; step <<= 1)
			{
				//////�ڲ�ѭ�������⽻��
				for (int i = 0; i < len; i += step << 1)//1
				{
					///ǰ�벿��������
					for (int step0 = step >> 1; step0 >0; step0 >>= 1)// 2
					{
						for (int j = 0; j < step; j += step0 << 1)//3
						{
							for (int k = 0; k < step0; ++k)//4
							{

								if (segdata[i + j + k + seg_start[d]] > segdata[i + j + k + step0 + seg_start[d]] || segdata[i + j + k + seg_start[d]] != segdata[i + j + k + seg_start[d]])  //��������ʹ��������,ͬʱ�ж϶���֮���Ƿ���NaN
								{
									//����data 
									float T = segdata[i + j + k + seg_start[d]];
									segdata[i + j + k + seg_start[d]] = segdata[i + j + k + step0 + seg_start[d]];
									segdata[i + j + k + step0 + seg_start[d]] = T;
								}
							}
						}
					}
					//��벿�ֽ�����
					if (i + step < len)
					{  //////�ڲ�ѭ�������⽻��
						for (int step0 = step >> 1; step0 >0; step0 >>= 1) //1
						{
							for (int j = 0; j < step; j += step0 << 1) //2
							{
								for (int k = 0; k < step0; ++k) //3
								{

									if (segdata[i + step + j + k + seg_start[d]] < segdata[i + step + j + step0 + k + seg_start[d]]
										|| segdata[i + step + j + step0 + k + seg_start[d]] != segdata[i + step + j + step0 + k + seg_start[d]]) //��������ʹ��������,ͬʱ�ж϶���֮���Ƿ���NaN
									{
										//����data 
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
		//����2�Ĵη�����
		else
		{
			//step 1 
			for (int step = 2; step <= len; step <<= 1)
			{
				//////�ڲ�ѭ�������⽻��
				for (int i = 0; i < len; i += step << 1)//1
				{
					///ǰ�벿��������
					for (int step0 = step >> 1; step0 >0; step0 >>= 1)// 2
					{
						for (int j = 0; j < step; j += step0 << 1)//3
						{
							for (int k = 0; k < step0; ++k)//4
							{

								if (segdata[i + j + k + seg_start[d]] > segdata[i + j + k + step0 + seg_start[d]] || segdata[i + j + k + seg_start[d]] != segdata[i + j + k + seg_start[d]])  //��������ʹ��������,ͬʱ�ж϶���֮���Ƿ���NaN
								{
									//����data 
									float T = segdata[i + j + k + seg_start[d]];
									segdata[i + j + k + seg_start[d]] = segdata[i + j + k + step0 + seg_start[d]];
									segdata[i + j + k + step0 + seg_start[d]] = T;
								}
							}
						}
					}
					//��벿�ֽ�����
					if (i + step < len)
					{  //////�ڲ�ѭ�������⽻��
						for (int step0 = step >> 1; step0 >0; step0 >>= 1) //1
						{
							for (int j = 0; j < step; j += step0 << 1) //2
							{
								for (int k = 0; k < step0; ++k) //3
								{

									if (segdata[i + step + j + k + seg_start[d]] < segdata[i + step + j + step0 + k + seg_start[d]]
										|| segdata[i + step + j + step0 + k + seg_start[d]] != segdata[i + step + j + step0 + k + seg_start[d]]) //��������ʹ��������,ͬʱ�ж϶���֮���Ƿ���NaN
									{
										//����data 
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
				//////�ڲ�ѭ�������⽻��
				for (int i = _lack_length; i < len + _lack_length; i += step << 1)//1
				{
					///ǰ�벿��������
					for (int step0 = step >> 1; step0 >0; step0 >>= 1)// 2
					{
						for (int j = 0; j < step; j += step0 << 1)//3
						{
							for (int k = 0; k < step0; ++k)//4
							{

								if (segdata[i + j + k + seg_start[d]] > segdata[i + j + k + step0 + seg_start[d]] || segdata[i + j + k + seg_start[d]] != segdata[i + j + k + seg_start[d]])  //��������ʹ��������,ͬʱ�ж϶���֮���Ƿ���NaN
								{
									//����data 
									float T = segdata[i + j + k + seg_start[d]];
									segdata[i + j + k + seg_start[d]] = segdata[i + j + k + step0 + seg_start[d]];
									segdata[i + j + k + step0 + seg_start[d]] = T;
								}
							}
						}
					}
					//��벿�ֽ�����
					if (i + step < len)
					{  //////�ڲ�ѭ�������⽻��
						for (int step0 = step >> 1; step0 >0; step0 >>= 1) //1
						{
							for (int j = 0; j < step; j += step0 << 1) //2
							{
								for (int k = 0; k < step0; ++k) //3
								{

									if (segdata[i + step + j + k + seg_start[d]] < segdata[i + step + j + step0 + k + seg_start[d]]
										|| segdata[i + step + j + step0 + k + seg_start[d]] != segdata[i + step + j + step0 + k + seg_start[d]]) //��������ʹ��������,ͬʱ�ж϶���֮���Ƿ���NaN
									{
										//����data 
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
				//////�ڲ�ѭ�������⽻��
				for (int i = 0; i < len; i += step << 1)//1
				{
					///ǰ�벿��������
					for (int step0 = step >> 1; step0 >0; step0 >>= 1)// 2
					{
						for (int j = 0; j < step; j += step0 << 1)//3
						{
							for (int k = 0; k < step0; ++k)//4
							{

								if (segdata[i + j + k + seg_start[d]] > segdata[i + j + k + step0 + seg_start[d]] || segdata[i + j + k + seg_start[d]] != segdata[i + j + k + seg_start[d]])  //��������ʹ��������,ͬʱ�ж϶���֮���Ƿ���NaN
								{
									//����data 
									float T = segdata[i + j + k + seg_start[d]];
									segdata[i + j + k + seg_start[d]] = segdata[i + j + k + step0 + seg_start[d]];
									segdata[i + j + k + step0 + seg_start[d]] = T;
								}
							}
						}
					}
					//��벿�ֽ�����
					if (i + step < len)
					{  //////�ڲ�ѭ�������⽻��
						for (int step0 = step >> 1; step0 >0; step0 >>= 1) //1
						{
							for (int j = 0; j < step; j += step0 << 1) //2
							{
								for (int k = 0; k < step0; ++k) //3
								{

									if (segdata[i + step + j + k + seg_start[d]] < segdata[i + step + j + step0 + k + seg_start[d]]
										|| segdata[i + step + j + step0 + k + seg_start[d]] != segdata[i + step + j + step0 + k + seg_start[d]]) //��������ʹ��������,ͬʱ�ж϶���֮���Ƿ���NaN
									{
										//����data 
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
		///////�����������������
		



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

	//���÷ֶ�˫������	
	segmentedBitonicSort(data, seg_id, seg_start, n, m);
	//���

	for (int i = 0; i < n; ++i)
	{
		cout << data[i] << "\t";
	}
	cout << endl;
	system("pause");

}

