#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))
#define ran(a, b) rng() % ((b) - (a) + 1) + (a)

class contestant {
public:
  int id, rating;
  string name;
  contestant(): id(0), rating(0), name("") {}
  contestant(int id, int rating, string name): id(id), rating(rating), name(name) {}
};

class TeamFormation {
public:
  const int RANDOMNESS = 200;
  const int MIN_RATING = 800;
  const int MAX_RATING = 2600;

  vector <contestant> v;

  TeamFormation(vector <contestant> &cont) {
    for (auto c: cont) {
      v.push_back(c);
    }

    for (int iter = 1; iter <= 100000; iter++) {
      random_shuffle(v.begin(), v.end());
    }

    assert(runValidator() && "validator failed!");
  }

  bool runValidator() {
    set <int> ids;
    for (auto c: v) {
      if (!(c.id > 0 && c.rating >= MIN_RATING && c.rating <= MAX_RATING && (int)c.name.size() > 0)) {
        return false;
      }

      ids.insert(c.id);
    }

    return (int)ids.size() == (int)v.size();
  }

  bool isValid(int threshold) {
    for (int i = 0; i < (int)v.size(); i += 2) {
      if (v[i].rating + v[i + 1].rating > threshold) {
        return false;
      }
    }

    return true;
  }

  vector <contestant> possible(int threshold) {
    for (int iter = 1; iter <= 100000; iter++) {
      random_shuffle(v.begin(), v.end());
      if (isValid(threshold)) {
        return v;
      }
    }

    return {};
  }

  void FormTeam() {
    int lo = 2 * MIN_RATING, hi = 2 * MAX_RATING, optimal = -1;
    while (lo <= hi) {
      int mid = (lo + hi) >> 1;
      vector <contestant> result = possible(mid);
      if ((int)result.size() > 0) {
        optimal = mid;
        hi = mid - 1;
      } else {
        lo = mid + 1;
      }
    }

    assert(optimal != -1 && "no valid solution!");
    cout << "optimal threshold: " << optimal + RANDOMNESS << "\n\n";

    vector <contestant> output = possible(optimal + RANDOMNESS);

    int id = 0;
    for (int i = 0; i < (int)output.size(); i+=2) {
      if (i > 0) cout << "\n";
      cout << "Team #" << ++id << ":" << "\n";
      cout << output[i].id << " " << output[i].rating << " " << output[i].name << "\n";
      cout << output[i + 1].id << " " << output[i + 1].rating << " " << output[i + 1].name << "\n";
    }
  }
};

int main() {
  srand(time(0));
  ios_base::sync_with_stdio(false); cin.tie(0);

  vector <contestant> v = {{
    contestant(1, 1659, "shakib59"),
    contestant(2, 1737, "sakib_alamin"),
    contestant(3, 2112, "Shaad7"),
    contestant(4, 1913, "Tasdid"),
    contestant(5, 1545, "nur_riyad"),
    contestant(6, 1853, "HeWhoMustNotBeNamed"),
    contestant(7, 1702, "masudur_rahman"),
    contestant(8, 1685, "bhowmik"),
    contestant(9, 1754, "LazyMediocre"),
    contestant(10, 1563, "segmented"),
  }};


  TeamFormation *formation = new TeamFormation(v);
  formation -> FormTeam();
  return 0;
}
