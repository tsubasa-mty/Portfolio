#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// 塩基ペア判定
bool Canpair(char a, char b){
    return ( (a=='A' && b=='U') || (a=='U' && b=='A') ||
             (a=='G' && b=='C') || (a=='C' && b=='G') );
}

// Tracebackで括弧表記を作成
void Traceback(vector<vector<int>>& dp,int i,int j,vector<int>& memo,const string &RNA){
    if(i >= j) return;

    if(j-i > 1 && Canpair(RNA[i], RNA[j]) && dp[i][j] == dp[i+1][j-1]+1){
        memo[i] = 1; memo[j] = 2;
        Traceback(dp, i+1, j-1, memo, RNA);
        return;
    }

    for(int k = i; k < j; ++k){
        if(dp[i][j] == dp[i][k] + dp[k+1][j]){
            Traceback(dp, i, k, memo, RNA);
            Traceback(dp, k+1, j, memo, RNA);
            return;
        }
    }

    if(dp[i][j] == dp[i+1][j]){
        Traceback(dp, i+1, j, memo, RNA);
        return;
    }

    if(dp[i][j] == dp[i][j-1]){
        Traceback(dp, i, j-1, memo, RNA);
        return;
    }
}

int main(){
    string RNA;
    cout << "RNA配列を入力してください（A,U,G,Cのみ）: ";
    cin >> RNA;
    int N = RNA.size();

    vector<vector<int>> dp(N, vector<int>(N,0));
    vector<int> memo(N,0);

    // DP計算
    for(int len = 2; len <= N; ++len){
        for(int i = 0; i <= N - len; ++i){
            int j = i + len - 1;
            dp[i][j] = max({ dp[i+1][j], dp[i][j-1],
                              dp[i+1][j-1] + ((j-i>1 && Canpair(RNA[i],RNA[j])) ? 1 : 0) });
            for(int k = i; k < j; ++k)
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k+1][j]);
        }
    }

    // Tracebackで括弧表記復元
    Traceback(dp, 0, N-1, memo, RNA);

    // 出力
    cout << "RNA:      " << RNA << endl;
    cout << "構造:     ";
    for(int i=0;i<N;i++){
        if(memo[i]==0) cout<<"・";
        else if(memo[i]==1) cout<<"(";
        else if(memo[i]==2) cout<<")";
    }
    cout << endl;
    cout << "最大ペア数: " << dp[0][N-1] << endl;

    return 0;
}