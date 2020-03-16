#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

// House
struct House {
    int x, y;
    bool democrat;
    double distance;

    House(int X, int Y, bool Democrat){
        x = X;
        y = Y;
        democrat = Democrat;
    }
};

bool compare(House &one, House &two) {
    if (one.distance < two.distance) return true;
    else return false;
}

void distanceCalc(int ox, int oy, House &p) {
    double distance = sqrt( (ox - p.x)*(ox - p.x) + (oy - p.y)*(oy - p.y) );
    p.distance = distance;
}

int main(){
    // Ten cases
    for (short casenum = 0; casenum < 10; casenum++){
        
        // Stores whether a house is occupied or not
        bool map[401][401] = { false };

        //Location of the origin of the circle
        int ox, oy;
        scanf("%d %d", &ox, &oy);

        // List of houses and their affiliations
        std::vector<House> houses;

        // Radius size
        const double R = 50.;

        // Getting houses information
        for (int house = 0; house < 100; house++) {
            // Variables
            int hx, hy;
            char affiliation;

            // Reading input
            scanf("%d %d %c", &hx, &hy, &affiliation);

            // Assigning houses
            bool democrat = (affiliation == 'D');
            houses.push_back(House(hx, hy, democrat));
            map[hx+200][hy+200] = true;
        }

        // Integers to calculate the percentage.
        int democratPossibilities = 0; 
        int totalPossibilities = 0;

        // Checking all the different house locations
        for (int dx = -50; dx < 51; dx++){
            for (int dy = -50; dy < 51; dy++) {
                // Prospective house location
                int px = ox + dx;
                int py = oy + dy;                    

                // Checking prospective location (inside radius and not occupied by a house)
                if (((px-ox)*(px-ox) + (py-oy)*(py-oy) <= R*R) && !map[px+200][py+200]) {

                    // This house is inside the circle, so increase total possibilities
                    totalPossibilities++;

                    // Calculating distances
                    for (std::vector<House>::iterator iter = houses.begin(); iter != houses.end(); iter++){
                        distanceCalc(px, py, *iter);
                    }

                    // Begin calculation of affiliation
                    std::sort(houses.begin(), houses.end(), compare);

                    //int affiliation = 0; // +1 for vote for democrat, -1 for vote for republican. Final value >= 0 is democrat.
                    int affiliation = 0;

                    int i = 0; // Temporary index counter
                    // Collecting votes from all eligible homes (1st, 2nd, and 3rd closest neighbours, along with all those tied for third place.)
                    while (houses[i].distance <= houses[2].distance) {
                        if (houses[i].democrat) affiliation++; else affiliation--;
                        i++;
                    }

                    // Democrat win
                    if (affiliation >= 0){
                        democratPossibilities++;
                    }
                }
            }
        }

        // Calculating chance that democrats win and rounding to one decimal place
        double democratChance = (double)democratPossibilities * 100.0 / (double)totalPossibilities ;
        printf("%.1f\n", democratChance);
        
    }
    
    return 0;
}
