////#include<iostream>
////#include<vector>
////#include<cstring>
////using namespace std;
////#include<assert.h>
////
////void Combination(char *string, int number, vector<char> &result);
////
////void Combination(char *string)
////{
////	assert(string != NULL);
////	vector<char> result;
////	int i, length = strlen(string);
////	for (i = 1; i <= length; ++i){
////		cout << "i:" << i << endl;
////		Combination(string, i, result);
////	}
////}
////
////void Combination(char *string, int number, vector<char> &result)
////{
////	vector<char>::iterator iter;
////	assert(string != NULL);
////	if (number == 0)
////	{
////		cout << "1" << endl;
////		static int num = 1;
////		printf("第%d个组合\t", num++);
////
////		iter = result.begin();
////		for (; iter != result.end(); ++iter)
////			printf("%c", *iter);
////		printf("\n");
////		return;
////	}
////	if (*string == '\0')
////		return;
////	cout << "2" << endl;
////	result.push_back(*string);
////	cout << "压入vector的元素有哪些：\n" << endl;
////	iter = result.begin();
////	for (; iter != result.end(); ++iter)
////		printf("%c", *iter);
////	printf("\n");
////
////
////
////	cout << "3" << endl;
////	Combination(string + 1, number - 1, result);
////	cout << "4" << endl;
////	result.pop_back();
////	cout << "弹出之后vector的元素有哪些：\n" << endl;
////	iter = result.begin();
////	for (; iter != result.end(); ++iter)
////		printf("%c", *iter);
////	printf("\n");
////
////	Combination(string + 1, number, result);
////	cout << "5" << endl;
////}
////
////int main(void)
////{
////	char str[] = "abc";
////	Combination(str);
////	system("pause");
////	return 0;
////}
//
////同时输出LCS和LCS的长度
//
//#include <iostream>  
//#include <string>  
//using namespace std;
//
//int length_LCS(string s1, string s2, int **c, int **b, int m, int n)  //输出LCS的长度  
//{
//	/*处理特殊的0行和0列*/
//	for (int i = 0; i <= m; i++)
//		c[i][0] = 0;
//	for (int j = 0; j <= n; j++)
//		c[0][j] = 0;
//
//	/*处理其他行和列*/
//	for (int i = 1; i <= m; i++)
//	{
//		for (int j = 1; j <= n; j++)
//		{
//			if (s1[i - 1] == s2[j - 1])
//			{
//				c[i][j] = c[i - 1][j - 1] + 1;
//				b[i - 1][j - 1] = 0;
//			}
//			else
//			{
//				if (c[i - 1][j] >= c[i][j - 1])
//				{
//					c[i][j] = c[i - 1][j];
//					b[i - 1][j - 1] = 1;
//				}
//				else
//				{
//					c[i][j] = c[i][j - 1];
//					b[i - 1][j - 1] = -1;
//				}
//			}
//		}
//	}
//	return c[m][n];
//}
//
///*二维数组b[1..m,1..n]，b[i,j]标记c[i,j]是由哪一个子问题的解求得的，以决定搜索的方向。取值范围为LeftTop、Top、Left三种情况。*/
//void Print_LCS(int **b, string x, int i, int j) //输出LCS序列  
//{
//	if (i == 0 || j == 0)
//		return;
//	if (b[i - 1][j - 1] == 0)
//	{
//		Print_LCS(b, x, i - 1, j - 1);
//		cout << x[i - 1];
//	}
//	else if (b[i - 1][j - 1] == 1)
//	{
//		Print_LCS(b, x, i - 1, j);
//	}
//	else
//		Print_LCS(b, x, i, j - 1);
//}
//
//int main()
//{
//	string s1, s2;
//	cout << "请输入两个序列:" << endl;
//	cin >> s1 >> s2;
//	int m = s1.length(), n = s2.length();
//	int **c = new int*[m + 1]; //动态分配二维数组  
//	for (int i = 0; i <= m; i++)
//		c[i] = new int[n + 1];
//	int **b = new int*[m]; //动态分配二维数组  
//	for (int j = 0; j<m; j++)
//		b[j] = new int[n];
//	cout << "LCS的长度:" << length_LCS(s1, s2, c, b, m, n) << endl;
//	cout << "打印其中的一个LCS:";
//	Print_LCS(b, s1, m, n);
//	//此处最好的处理是释放空间  
//	cout << endl;
//	return 0;
//}
