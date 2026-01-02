#include <iostream>
#include <fstream>
#include "library.h"

using namespace std;

int main() {
    championship_team all_teams[MAX_TEAMS];
    int num_teams = 0, choice;
    string team_name;
    ifstream teamData, rosterData;

    cout << "Welcome to the Championship Teams Program!\n";

    
    do {
        cout << "Enter team data filename (e.g., championships.dat): ";
        string filename;
        cin >> filename;
        teamData.open(filename);
    } while (!teamData.is_open());

    
    do {
        cout << "Enter roster data filename (e.g., activeroster.dat): ";
        string filename;
        cin >> filename;
        rosterData.open(filename);
    } while (!rosterData.is_open());

    collect_all(teamData, rosterData, all_teams, num_teams, MAX_TEAMS);

    teamData.close();
    rosterData.close();

    do {
        choice = menu(all_teams, num_teams);
        switch (choice) {
            case 1:
                display_all(all_teams, num_teams);
                break;
            case 2:
                cout << "Enter team name to search: ";
                getline(cin, team_name);
                {
                    int pos = find_team(all_teams, num_teams, team_name);
                    if (pos != -1) display_one_team(all_teams[pos]);
                    else cout << "Team not found.\n";
                }
                break;
            case 3:
                {
                    int sort_choice;
                    cout << "\nSort by:\n1. Alphabetical order\n2. PPG\n3. Win Percentage\n";
                    do {
                        cout << "Enter choice: ";
                        cin >> sort_choice;
                    } while (sort_choice < 1 || sort_choice > 3);
                    cin.ignore(); 

                    sort_teams(all_teams, num_teams, sort_choice);
                    cout << "Teams sorted.\n";
                    display_all(all_teams, num_teams);
                }
                break;
            case 4:
                cout << "Enter team name for stats: ";
                getline(cin, team_name);
                {
                    int pos = find_team(all_teams, num_teams, team_name);
                    if (pos != -1) team_stats(all_teams[pos]);
                    else cout << "Team not found.\n";
                }
                break;
            case 5:
                stats_across_teams(all_teams, num_teams);
                break;
            case 6:
                cout << "Enter team name to remove: ";
                getline(cin, team_name);
                remove_team(all_teams, num_teams, team_name);
                break;
            case 7:
                cout << "Goodbye!\n";
                break; 
        }
    } while (choice != 7);

    return 0;
}
