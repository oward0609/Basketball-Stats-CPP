#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_TEAMS = 15;
const int MAX_ROSTER = 19;

struct championship_team {
    string team_name;
    string opponent_team;
    double ppg, apg, rpg, bpg, spg;
    int highest_score, lowest_score;
    double season_win_percentage;
    string roster[MAX_ROSTER]; 
};

// Function declarations
void collect_all(ifstream &teamData, ifstream &rosterData, championship_team arr[], int &size, int capacity);
void collect_rosters(ifstream &rosterData, championship_team arr[], int size);
void display_one_team(const championship_team &team);
void display_all(const championship_team arr[], int size);
int menu(const championship_team arr[], int size);
int find_team(const championship_team arr[], int size, const string &name);
void sort_teams(championship_team arr[], int size, int sort_choice);
void team_stats(const championship_team &team);
void stats_across_teams(const championship_team arr[], int size);
void remove_team(championship_team arr[], int &size, const string &team_name);