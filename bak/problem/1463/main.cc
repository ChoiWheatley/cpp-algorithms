/*
문제
정수 X에 사용할 수 있는 연산은 다음과 같이 세 가지 이다.

X가 3으로 나누어 떨어지면, 3으로 나눈다.
X가 2로 나누어 떨어지면, 2로 나눈다.
1을 뺀다.
정수 N이 주어졌을 때, 위와 같은 연산 세 개를 적절히 사용해서 1을 만들려고 한다. 연산을 사용하는 횟수의 최솟값을 출력하시오.

입력
첫째 줄에 1보다 크거나 같고, 106보다 작거나 같은 정수 N이 주어진다.

출력
첫째 줄에 연산을 하는 횟수의 최솟값을 출력한다.

예제 입력 1 
2
예제 출력 1 
1
예제 입력 2 
10
예제 출력 2 
3
*/
#include<iostream>
#include<climits>
#include<cmath>
using namespace std;
int memo[1000001] = {INT_MAX};

int f(int n);

int main(void)
{
	memo[1] = 0;
	memo[0] = 0;
	int n = 0;
	cin >> n;
	cout << f(n) << '\n';
}
int f(int n)
{
	if ( n == 1 ) return 0;
	for (int i = 2; i <= n; i++){
		memo[i] = 1 + memo[i-1];
		if ( i%3 == 0 ) memo[i] = min(memo[i], 1 + memo[i/3]);
		if ( i%2 == 0 ) memo[i] = min(memo[i], 1 + memo[i/2]);
	}
	return memo[n];
}
