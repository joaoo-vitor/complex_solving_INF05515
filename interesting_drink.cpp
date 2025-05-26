#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> prices_shops(n);
    
    for (int i = 0; i < n; i++) {
        cin >> prices_shops[i];
    }
    int days;
    cin >> days;
    vector<int> coins_at_day(days);
    for (int i = 0; i < days; i++) {
        cin >> coins_at_day[i];
    }

    sort(prices_shops.begin(), prices_shops.end());
    for (int day=0; day<days; day++) {
        //logn algorithm
        int a = 0; int b=prices_shops.size()-1;
        int result;
        while(a<b){
            if((b-a)==1){
                if (coins_at_day[day]<prices_shops[a]){
                   result=0; 
                }else if (coins_at_day[day]<prices_shops[b]){
                    result=a;
                }else result=b;
                break;
            }
            int mid = a+(a+b)/2;
            if(prices_shops[mid]>coins_at_day[day]){
                b = mid;
            }else{
                a=mid;
            }
        }
        cout << result;
    }
}
