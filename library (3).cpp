#include "library.h"
#include <iomanip>
using namespace std;

void collect_all(ifstream &teamData, ifstream &rosterData, championship_team arr[], int &size, int capacity) {
    size = 0;
    while (size < capacity && teamData >> arr[size].team_name >> arr[size].opponent_team
           >> arr[size].ppg >> arr[size].apg >> arr[size].rpg
           >> arr[size].bpg >> arr[size].spg
           >> arr[size].highest_score >> arr[size].lowest_score
           >> arr[size].season_win_percentage) {
        size++;
    }
    collect_rosters(rosterData, arr, size);
    cout << size << " records loaded successfully.\n";
}

void collect_rosters(ifstream &rosterData, championship_team arr[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < MAX_ROSTER; j++) {
            if (!(rosterData >> arr[i].roster[j])) {
                arr[i].roster[j] = ""; 
            }
        }
    }
}

void display_one_team(const championship_team &team) {
    // Wider columns + consistent numeric formatting so rows line up cleanly.
    // (No changes to program logic; this is display-only.)
    cout << left << setw(10) << team.team_name
         << setw(10) << team.opponent_team
         << right << fixed << setprecision(1)
         << setw(7) << team.ppg
         << setw(7) << team.apg
         << setw(7) << team.rpg
         << setw(7) << team.bpg
         << setw(7) << team.spg
         << right << setprecision(0)
         << setw(7) << team.highest_score
         << setw(7) << team.lowest_score
         << right << fixed << setprecision(3)
         << setw(8) << team.season_win_percentage
         << left << endl;
}

void display_all(const championship_team arr[], int size) {
    cout << left << setw(10) << "Team" << setw(10) << "Opp"
         << right
         << setw(7) << "PPG" << setw(7) << "APG"
         << setw(7) << "RPG" << setw(7) << "BPG"
         << setw(7) << "SPG" << setw(7) << "High"
         << setw(7) << "Low" << setw(8) << "Win%" << endl;
    for (int i = 0; i < size; i++) {
        display_one_team(arr[i]);
    }
}

int find_team(const championship_team arr[], int size, const string &name) {
    for (int i = 0; i < size; i++) {
        if (arr[i].team_name == name) return i;
    }
    return -1;
}

void sort_teams(championship_team arr[], int size, int sort_choice) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            bool swap_needed = false;
            if (sort_choice == 1 && arr[j].team_name > arr[j + 1].team_name)
                swap_needed = true;
            else if (sort_choice == 2 && arr[j].ppg > arr[j + 1].ppg)
                swap_needed = true;
            else if (sort_choice == 3 && arr[j].season_win_percentage > arr[j + 1].season_win_percentage)
                swap_needed = true;

            if (swap_needed) {
                championship_team temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int menu(const championship_team arr[], int size) {
    int choice;
    cout << "\nOptions:\n";
    cout << "1. Display all teams\n";
    cout << "2. Search for a team\n";
    cout << "3. Sort data\n";
    cout << "4. Stats for a team\n";
    cout << "5. Stats across all teams\n";
    cout << "6. Remove a team\n";
    cout << "7. Quit\n";
    do {
        cout << "Enter your choice: ";
        cin >> choice;
    } while (choice < 1 || choice > 7);
    cin.ignore(); 
    return choice;
}

void team_stats(const championship_team &team) {
    double avg_score = (team.ppg + team.apg + team.rpg + team.bpg + team.spg) / 5;
    double diff = team.highest_score - team.lowest_score;

    cout << "\nStats for " << team.team_name << ":\n";
    cout << "Average of numeric stats: " << avg_score << endl;
    cout << "Difference between highest and lowest score: " << diff << endl;
}

void stats_across_teams(const championship_team arr[], int size) {
    if (size == 0) return;

    double max_ppg = arr[0].ppg;
    string max_ppg_team = arr[0].team_name;
    double min_ppg = arr[0].ppg;
    string min_ppg_team = arr[0].team_name;

    double max_win = arr[0].season_win_percentage;
    string max_win_team = arr[0].team_name;
    double min_win = arr[0].season_win_percentage;
    string min_win_team = arr[0].team_name;

    for (int i = 1; i < size; i++) {
        if (arr[i].ppg > max_ppg) { max_ppg = arr[i].ppg; max_ppg_team = arr[i].team_name; }
        if (arr[i].ppg < min_ppg) { min_ppg = arr[i].ppg; min_ppg_team = arr[i].team_name; }
        if (arr[i].season_win_percentage > max_win) { max_win = arr[i].season_win_percentage; max_win_team = arr[i].team_name; }
        if (arr[i].season_win_percentage < min_win) { min_win = arr[i].season_win_percentage; min_win_team = arr[i].team_name; }
    }

    cout << "\nStats Across All Teams:\n";
    cout << "Team with Highest PPG: " << max_ppg_team << " (" << max_ppg << ")\n";
    cout << "Team with Lowest PPG: " << min_ppg_team << " (" << min_ppg << ")\n";
    cout << "Team with Highest Win%: " << max_win_team << " (" << max_win << ")\n";
    cout << "Team with Lowest Win%: " << min_win_team << " (" << min_win << ")\n";
}

void remove_team(championship_team arr[], int &size, const string &team_name) {
    int pos = find_team(arr, size, team_name);
    if (pos == -1) {
        cout << "Team not found.\n";
        return;
    }

    for (int i = pos; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    size--;
    cout << team_name << " has been removed.\n";
}

