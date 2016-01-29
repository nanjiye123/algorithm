//UVa1152
//和为0的4个值
//使用sort，时间为2.815；使用qsort，时间为3.416
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 4000 + 10;
int A[maxn], B[maxn], C[maxn], D[maxn], sum[maxn*maxn];

int cmp(const void *a, const void *b)
{
    return ( *(int*)a - *(int*)b );//升序
}

int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        int n;
        cin>>n;//每个集合元素个数
        for(int i=0; i<n; i++)
        {   
            cin>>A[i]>>B[i]>>C[i]>>D[i]; 
        }
        
        int c=0;
        for(int i=0; i<n; i++)
        {   
            for(int j=0; j<n; j++)
            {   
                sum[c++] = A[i] + B[j];
            }
        }
        //qsort(sum, c, sizeof(sum[0]), cmp);
        sort(sum, sum+c);
        long long int result=0;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                result += upper_bound(sum, sum+c, -C[i]-D[j])
                          - lower_bound(sum,sum+c, -C[i]-D[j]);//重要
            }
        }
 
        cout << result << endl;
        if(T) cout<<endl;
    }
    return 0;
}

