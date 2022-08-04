#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(a, b) ((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))
#define ran(a, b) rng() % ((b) - (a) + 1) + (a)

class contestant {
public:
  int id, rating;
  string name, username;
  contestant(): id(0), rating(0), name(""), username("") {}
  contestant(int id, int rating, string name, string username): id(id), rating(rating), name(name), username(username) {}
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
      if (!(c.id > 0 && c.rating >= MIN_RATING && c.rating <= MAX_RATING && (int)c.name.size() > 0 && (int)c.username.size() > 0)) {
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

  vector <contestant> possibleTeams(int threshold) {
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
      vector <contestant> result = possibleTeams(mid);
      if ((int)result.size() > 0) {
        optimal = mid;
        hi = mid - 1;
      } else {
        lo = mid + 1;
      }
    }

    assert(optimal != -1 && "no valid solution!");
    cout << "threshold: " << optimal + RANDOMNESS << "\n\n";

    vector <contestant> output = possibleTeams(optimal + RANDOMNESS);

    int id = 0;
    for (int i = 0; i < (int)output.size(); i+=2) {
      if (i > 0) cout << "\n";
      cout << "Team #" << ++id << ":" << "\n";
      cout << output[i].name << " and " << output[i+1].name << "\n";
      cout << "Team Details\n";
      cout <<  "1. Rating: " << output[i].rating << ", Username: " << output[i].username << "\n";
      cout <<  "2. Rating: " << output[i + 1].rating << ", Username: " << output[i + 1].username << "\n";
    }
  }
};

int main() {
  srand(time(0));
  ios_base::sync_with_stdio(false); cin.tie(0);

  vector <contestant> v = {{
    contestant(1, 1659,"Junayed", "shakib59"),
    contestant(2, 1737,"Sakib Alamin", "sakib_alamin"),
    contestant(3, 2112,"Shaad", "Shaad7"),
    contestant(4, 1913, "Tasdid", "Tasdid"),
    contestant(5, 1545, "Riyad", "nur_riyad"),
    contestant(6, 1853, "Alif", "_HeWhoMustNotBeNamed_"),
    contestant(7, 1702, "Masud", "masudur_rahman"),
    contestant(8, 1685, "Pulak", "bhowmik"),
    contestant(9, 1754, "Kamol", "LazyMediocre"),
    contestant(10, 1563, "Raka", "segmented"),
    contestant(11, 1494, "Sayem", "factoradic"),
    contestant(12, 2012, "Rakibul Hossain", "Wolve_rine"),
    contestant(13, 1702, "MASUDUR RAHMAN", "MASUDUR_RAHMAN"),
  }};


  TeamFormation *formation = new TeamFormation(v);
  formation -> FormTeam();
  return 0;
}
