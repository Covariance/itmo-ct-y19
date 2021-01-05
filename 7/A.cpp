//
// Created by covariance on 21.12.2020.
//

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>

#define cost first
#define day second

using namespace std;

typedef __gnu_pbds::tree<
    uint32_t,
    __gnu_pbds::null_type,
    less<>,
    __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update>
    ordered_set;

uint32_t cnt_taken(ordered_set &days, uint32_t day) {
  return days.order_of_key(day) + (days.find(day) == days.end() ? 0 : 1);
}

bool check(ordered_set &days, uint32_t m, uint32_t taken, uint32_t last) {
  if(last - m + cnt_taken(days, m) == taken) {
    return days.find(m) == days.end();
  }
  return true;
}

void insert_event(ordered_set &days, uint32_t day) {
  if (days.find(day) == days.end()) {
    days.insert(day);
    return;
  }
  uint32_t taken = cnt_taken(days, day);
  uint32_t l = 0, r = day, m;
  while (l + 1 < r) {
    m = l + ((r - l) >> 1u);
    if (check(days, m, taken, day)) {
      l = m;
    } else {
      r = m;
    }
  }

  days.insert(l);
}

int main() {
#ifndef DEBUG
  freopen("schedule.in", "r", stdin);
  freopen("schedule.out", "w", stdout);
#endif
  uint32_t n;
  uint64_t fine = 0;
  cin >> n;
  vector<pair<uint32_t, uint32_t>> events(n);
  for (auto &i : events) {
    cin >> i.day >> i.cost;
    fine += i.cost;
  }

  ordered_set days;
  sort(events.begin(), events.end(), [](const pair<uint32_t, uint32_t> &lhs, const pair<uint32_t, uint32_t> &rhs)
  -> bool {return lhs.cost > rhs.cost || (lhs.cost == rhs.cost && lhs.day < rhs.day);});


  for (auto event : events) {
    if (cnt_taken(days, event.day) < event.day) {
      insert_event(days, event.day);
      fine -= event.cost;
    }
  }

  cout << fine;

  return 0;
}