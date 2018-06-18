#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

//�ҵ������㷨
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
	float Max = 9999999;//��Ϊ�����
	//�ȶ�������
	for (int d = 0; d<m; d++)
	{
		int len = 1;
		
		//seg_start[d+1]-seg_start[d]Ϊ�˶γ���
		int _real_length = (seg_start[d + 1] - seg_start[d]);

		while (len <= _real_length)//ѭ���˳������� 
			len = len << 1;//Ѱ��С�ڵ���n������2���ݴη�len
		len = len >> 1;

		//�ж��Ƿ���2�Ĵη����� ��
		if (_real_length == len)
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
			//����n����С2���ݴη�
			len = len << 1;
			int _overLength = len - _real_length;
			for (int i = 0; i < _overLength; i++)
			{
				memcpy(seg_id + (i + seg_start[d])*sizeof(int), &Max, sizeof(float));
			}

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
								int first = i + j + k + seg_start[d];
								int last = i + j + k + step0 + seg_start[d];

								if (first < (seg_start[d] + _real_length) && last < (seg_start[d] + _real_length))
								{
									if (segdata[first] > segdata[last] || segdata[first] != segdata[first])  //��������ʹ��������,ͬʱ�ж϶���֮���Ƿ���NaN
									{
										//����data 
										float T = segdata[first];
										segdata[first] = segdata[last];
										segdata[last] = T;
									}
								}
								else if (first < (seg_start[d] + _real_length) && last >= (seg_start[d] + _real_length))
								{
									//�ڴ濽��
									float _lastOne = 0.f;
									memcpy(&_lastOne, seg_id + (last - _real_length) * sizeof(int), sizeof(float));

									if (segdata[first] > _lastOne || segdata[first] != segdata[first])  //��������ʹ��������,ͬʱ�ж϶���֮���Ƿ���NaN
									{
										//����data 
										float T = segdata[first];
										segdata[first] = _lastOne;
										memcpy(seg_id + (last - _real_length) * sizeof(int), &T, sizeof(float));
										//seg_id[last - _real_length] = T;
									}
								}
								else
								{
									float _firstOne = 0.f;
									float _lastOne = 0.f;
									memcpy(&_firstOne, seg_id + (first - _real_length) * sizeof(int), sizeof(float));
									memcpy(&_lastOne, seg_id + (last - _real_length) * sizeof(int), sizeof(float));

									if (_firstOne > _lastOne || _firstOne != _firstOne)  //��������ʹ��������,ͬʱ�ж϶���֮���Ƿ���NaN
									{
										//����data 
										memcpy(seg_id + (first - _real_length) * sizeof(int), &_lastOne, sizeof(float));
										memcpy(seg_id + (last - _real_length) * sizeof(int), &_firstOne, sizeof(float));
										//float T = _firstOne;
						/*				seg_id[first - _real_length] = seg_id[last - _real_length];
										seg_id[last - _real_length] = T;*/
									}
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
									int first = i + step + j + k + seg_start[d];
									int last = i + step + j + step0 + k + seg_start[d];

									if (first < (seg_start[d] + _real_length) && last < (seg_start[d] + _real_length))
									{
										if (segdata[first] < segdata[last] || segdata[first] != segdata[first])  //��������ʹ��������,ͬʱ�ж϶���֮���Ƿ���NaN
										{
											//����data 
											float T = segdata[first];
											segdata[first] = segdata[last];
											segdata[last] = T;
										}
									}
									else if (first < (seg_start[d] + _real_length) && last >= (seg_start[d] + _real_length))
									{
										//�ڴ濽��
										float _lastOne = 0;
										memcpy(&_lastOne, seg_id + (last - _real_length) * sizeof(int), sizeof(float));

										if (segdata[first] < _lastOne || segdata[first] != segdata[first])  //��������ʹ��������,ͬʱ�ж϶���֮���Ƿ���NaN
										{
											//����data 
											float T = segdata[first];
											segdata[first] = _lastOne;
											memcpy(seg_id + (last - _real_length) * sizeof(int), &T, sizeof(float));
											//seg_id[last - _real_length] = T;
										}
									}
									else
									{
										float _firstOne = 0;
										float _lastOne = 0;
										memcpy(&_firstOne, seg_id + (first - _real_length) * sizeof(int), sizeof(float));
										memcpy(&_lastOne, seg_id + (last - _real_length) * sizeof(int), sizeof(float));

										if (_firstOne < _lastOne || _firstOne != _firstOne)  //��������ʹ��������,ͬʱ�ж϶���֮���Ƿ���NaN
										{
											//����data 
											memcpy(seg_id + (first - _real_length) * sizeof(int), &_lastOne, sizeof(float));
											memcpy(seg_id + (last - _real_length) * sizeof(int), &_firstOne, sizeof(float));
											//float T = _firstOne;
											/*				seg_id[first - _real_length] = seg_id[last - _real_length];
											seg_id[last - _real_length] = T;*/
										}
									}
								}
							}
						}
					}

				}

			}
		}		

	}
	for (int i = 0; i < n; i++)
	{
		if (segdata[i] == Max)
			segdata[i] = NAN;
	}
}

//CSDNʵ�� https://blog.csdn.net/hanshuning/article/details/49132089
void segmentedBitonicSort1(float* data, int* seg_id, int* seg_start, int n, int m)
{
	////�ж������Ƿ�����
	if (n <= 0 || m <= 0 || m>n)
	{
		for (int i = 0; i < n; ++i)
		{
			cout << data[i] << "\t";
		}
		cout << endl << "m:" << m << endl << "n:" << n << endl;
		cout << "Input error!n>m>0" << endl;
		return;
	}
	if (!(seg_start[m] == n && seg_id[n - 1] == (m - 1)))
	{
		for (int i = 0; i < n; ++i)
		{
			cout << data[i] << "\t";
		}
		cout << endl;
		for (int i = 0; i < n; ++i)
		{
			cout << seg_id[i] << "\t";
		}
		cout << endl << "m:" << m << endl << "n:" << n << endl;
		cout << "Input error! seg_start[m]==n,seg_id[n-1]==(m-1)" << endl;
		return;
	}
	//�ȶ�������
	for (int d = 0; d<m; d++)
	{
		int len = 1;
		//seg_start[d+1]-seg_start[d]Ϊ�˶γ���
		while (len < seg_start[d + 1] - seg_start[d])//ѭ���˳������� 
			len = len << 1;//Ѱ�Ҵ���n����С��2���ݴη�len

		float Max = 9999999;//��Ϊ�����
						   //vector<float> segdata(len);

		vector<float> segdata(len);

		for (int i = 0; i < seg_start[d + 1] - seg_start[d]; i++)
		{
			segdata[i] = data[seg_start[d] + i];
		}
		//���len > n,��˵������ĸ���������Ҫ��������䵽len�� 
		for (int i = seg_start[d + 1] - seg_start[d]; i < len; i++)
			segdata[i] = Max;


		///////�����������������
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

							if (segdata[i + j + k] > segdata[i + j + k + step0] || segdata[i + j + k] != segdata[i + j + k])  //��������ʹ��������,ͬʱ�ж϶���֮���Ƿ���NaN
							{

								//����data 
								float T = segdata[i + j + k];
								segdata[i + j + k] = segdata[i + j + k + step0];
								segdata[i + j + k + step0] = T;
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

								if (segdata[i + step + j + k] < segdata[i + step + j + step0 + k]
									|| segdata[i + step + j + step0 + k] != segdata[i + step + j + step0 + k]) //��������ʹ��������,ͬʱ�ж϶���֮���Ƿ���NaN
								{
									//����data 
									float T = segdata[i + step + j + k];
									segdata[i + step + j + k] = segdata[i + step + j + k + step0];
									segdata[i + step + j + k + step0] = T;
								}
							}
						}
					}
				}
			}
		}
		//��ֵ
		for (int i = seg_start[d]; i < seg_start[d + 1]; i++)
		{
			data[i] = segdata[i - seg_start[d]];
			if (data[i] == Max)
				data[i] = sqrt(-1.f);
		}
	}
}


void main()
{
	

	int n, m;
	float *data0;
	float *data1;
	int *seg_id;
	int *seg_start;
	int lastn = 5000, lastm = 5000;

	data0 = new float[lastn];
	data1 = new float[lastn];
	seg_id = new int[lastn];
	seg_start = new int[lastm + 1];
	int cal = 0;
	int correct_cal = 0;
	ifstream _testDatas;

	//�ر��ļ����� ��key��ֵfalse;
	//bool key = false;
	bool key = true;
	
	if (key)
	{
		_testDatas.open("test.txt");
		if (!_testDatas)
		{
			cout << "error_read" << endl;
			return;
		}
	}

	while (!_testDatas.eof()&&(_testDatas >> n >> m)&&key)
	{
		cal++;
		if (n > lastn)
		{
			data0 = new float[n];
			data1 = new float[n];
			seg_id = new int[n];
			//seg_id1 = new int[n];
			lastn = n;
		}

		if (m > lastm)
		{
			seg_start = new int[m + 1];
			lastm = m;
		}


		//seg_start1 = new int[m + 1];
		for (int i = 0; i < n; i++)
		{
			_testDatas >> data0[i];
		}

		memcpy(data1, data0, n * sizeof(float));
		for (int i = 0; i < n; i++)
		{
			_testDatas >> seg_id[i];
		}
		
		//memcpy(seg_id1, seg_id, n * sizeof(int));

		for (int i = 0; i < m+1; i++)
		{
			_testDatas >> seg_start[i];
		}
		//memcpy(seg_start1, seg_start, (m + 1) * sizeof(int));

		segmentedBitonicSort1(data1, seg_id, seg_start, n, m);
		segmentedBitonicSort(data0, seg_id, seg_start, n, m);

		if (equal(data0, data0 + n -1 , data1, data1 + n -1))
		{
			correct_cal++;
		}
		else
		{
			cout << "not_____equal" << endl << "data: ";
			for (int i = 0; i < n; ++i)
			{
				cout << data0[i] << "\t";
			}
			cout << endl;
			cout << "data1: ";
			for (int i = 0; i < n; ++i)
			{
				cout << data1[i] << "\t";
			}
			cout << endl;
		}

		

	}
	
	if (key)
	{
		_testDatas.close();
		if (data0 != NULL)
		{
			delete[]data0;
		}
		if (data1 != NULL)
		{
			delete[]data1;
		}
		if (seg_id != NULL)
		{
			delete[]seg_id;
		}
		if (seg_start != NULL)
		{
			delete[]seg_start;
		}
	}




	float data3[5] = { NAN, 0.8, 0.4, NAN, 0.5 };
	float data4[5] = { NAN, 0.8, 0.4, NAN, 0.5 };

	int seg_id3[5] = { 0,   0,   1,  1,   1 };

	int seg_start3[3] = { 0,2,5 };

	int n3 = 5;

	int m3 = 2;
	cout << correct_cal << endl;
	cout << cal << endl;
	////���÷ֶ�˫������
	//segmentedBitonicSort1 CSDNʵ�ִ���
	segmentedBitonicSort1(data4, seg_id3, seg_start3, n3, m3);

	//segmentedBitonicSort �ҵ�ʵ�ִ���
	segmentedBitonicSort(data3, seg_id3, seg_start3, n3, m3);
	////���

	for (int i = 0; i < n3; ++i)
	{
		cout << data3[i] << "\t";
	}
	cout << endl;
	for (int i = 0; i < n3; ++i)
	{
		cout << data4[i] << "\t";
	}

	cout << endl;
	//NaN������ô�ȽϽ������0
	cout << (equal(data3, data3 + n3 - 1, data4, data4 + n3 - 1));
	getchar();
	return;

}


