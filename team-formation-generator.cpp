#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rnd(a, b)((((rand() << 15) ^ rand()) % ((b) - (a) + 1)) + (a))
#define ran(a, b) rng() % ((b) - (a) + 1) + (a)

class Contestant {
public:
  int id, rating;
  string name, username;
  Contestant(): id(0), rating(0), name(""), username("") {}
  Contestant(int id, int rating, string name, string username): id(id), rating(rating), name(name), username(username) {}
};

class Team {
public:
  Contestant member1;
  Contestant member2;
  int teamRating;
  Team(Contestant mem1, Contestant mem2): member1(mem1), member2(mem2), teamRating(mem1.rating + mem2.rating) {}

  bool operator < (const Team & other) const {
    return teamRating < other.teamRating;
  }
};

class TeamFormation {
public:
  const int RANDOMNESS = 200;
  const int MIN_RATING = 800;
  const int MAX_RATING = 2600;

  vector <Contestant> v;

  TeamFormation(vector <Contestant> &cont) {
    for (auto c: cont) {
      v.push_back(c);
    }

    for (int iter = 1; iter <= 100; iter++) {
      random_shuffle(v.begin(), v.end());
    }

    assert(runValidator() && "validator failed!");
  }

  bool runValidator() {
    set <int> ids;
    for (auto c: v) {
      if (!(c.id > 0 && c.rating >= MIN_RATING && c.rating <= MAX_RATING && (int) c.name.size() > 0 && (int) c.username.size() > 0)) {
        return false;
      }

      ids.insert(c.id);
    }

    return (int)ids.size() == (int)v.size();
  }

  bool isValid(int threshold) {
    for (int i = 0; i < (int) v.size(); i += 2) {
      if (v[i].rating + v[i + 1].rating > threshold) {
        return false;
      }
    }

    return true;
  }

  vector <Contestant> possibleTeams(int threshold) {
    for (int iter = 1; iter <= 10000; iter++) {
      random_shuffle(v.begin(), v.end());
      if (isValid(threshold)) {
        return v;
      }
    }

    return {};
  }

  vector <Team> FormTeam() {
    int lo = 2 * MIN_RATING, hi = 2 * MAX_RATING, optimal = -1;
    while (lo <= hi) {
      int mid = (lo + hi) >> 1;
      vector <Contestant> result = possibleTeams(mid);
      if ((int) result.size() > 0) {
        optimal = mid;
        hi = mid - 1;
      } else {
        lo = mid + 1;
      }
    }

    assert(optimal != -1 && "no valid solution!");

    vector <Contestant> output = possibleTeams(optimal + RANDOMNESS);
    vector <Team> teams;

    for (int i = 0; i < (int) output.size(); i += 2) {
      Team *tmp = new Team(output[i], output[i + 1]);
      teams.push_back(*tmp);
    }

    sort(teams.begin(), teams.end());

    return teams;
  }

  void FormTeam(int iteration) {
    vector <Team> teams;
    int diff = INT_MAX;
    for (int iter = 1; iter <= iteration; iter++) {
      vector <Team> t = FormTeam();
      int sz = t.size();
      if (t[sz - 1].teamRating - t[0].teamRating < diff) {
        diff = t[sz - 1].teamRating - t[0].teamRating;
        teams = t;
      }
    }

    for (int i = 0; i < (int) teams.size(); i++) {
      if (i > 0) cout << "\n";
      cout << "Team #" << i + 1 << ":" << "\n";
      cout << teams[i].member1.name << " and " << teams[i].member2.name << ": Team Rating (" << teams[i].teamRating << ") " << "\n";
      cout << "Team Details\n";
      cout << "1. Rating: " << teams[i].member1.rating << ", Username: " << teams[i].member1.username << "\n";
      cout << "2. Rating: " << teams[i].member2.rating << ", Username: " << teams[i].member2.username << "\n";
    }
  }
};

int main() {
  srand(time(0));
  ios_base::sync_with_stdio(false); cin.tie(0);

  vector <Contestant> v = {{
      Contestant(1, 1659, "Junayed", "shakib59"),
      Contestant(2, 1737, "Sakib Alamin", "sakib_alamin"),
      Contestant(3, 2112, "Shaad", "Shaad7"),
      Contestant(4, 1913, "Tasdid", "Tasdid"),
      Contestant(5, 1545, "Riyad", "nur_riyad"),
      Contestant(6, 1853, "Alif", "_HeWhoMustNotBeNamed_"),
      Contestant(7, 1702, "Masud", "masudur_rahman"),
      Contestant(8, 1685, "Pulak", "bhowmik"),
      Contestant(9, 1754, "Kamol", "LazyMediocre"),
      Contestant(10, 1563, "Raka", "segmented"),
      Contestant(11, 1494, "Sayem", "factoradic"),
      Contestant(12, 2012, "Rakibul", "Wolve_rine"),
      Contestant(13, 1949, "Rasel", "Superm4n"),
      Contestant(14, 1602, "Sakib", "s4k1b"),
      Contestant(15, 1610, "Piyush", "piyush1146115"),
      Contestant(16, 1536, "Mehedi", "heheh"),
      Contestant(17, 1705, "Emruz", "Emruz_Hossain"),
      Contestant(18, 1378, "Dipto", "Drac_007"),
    }
  };

  TeamFormation * formation = new TeamFormation(v);
  formation -> FormTeam(100);
  return 0;
}
