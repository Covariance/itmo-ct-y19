#include <bits/stdc++.h>
using namespace std;

int main() {
    queue<int> st;
    int n;
    cin >>n;
    int cnt = 0;
    int choice = 0;
    while (choice == 0 || choice == 1) {
        cout <<"0 to malloc();   1 to free(x);  anything else to break\n";
        cin >>choice;
        if (choice == 0) {
            if (cnt < n) {
                cout <<"You get block number " <<cnt <<"\n";
                cnt++;
            } else {
                if (st.size() > 0) {
                    cout <<"You get block number " <<st.front() <<"\n";
                    st.pop();
                } else {
                    cout <<"Not enough memory.\n";
                }
            }
        }
        if (choice == 1) {
            int x;
            cin >>x;
            st.push(x);
        }
    }
    return 0;
}
