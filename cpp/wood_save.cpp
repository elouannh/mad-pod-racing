#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    while (1)
    {
        int x;
        int y;
        int next_checkpoint_x; // x position of the next check point
        int next_checkpoint_y; // y position of the next check point
        int next_checkpoint_dist; // distance to the next checkpoint
        int next_checkpoint_angle; // angle between your pod orientation and the direction of the next checkpoint
        std::cin >> x >> y >> next_checkpoint_x >> next_checkpoint_y >> next_checkpoint_dist >> next_checkpoint_angle; std::cin.ignore();
        int opponent_x;
        int opponent_y;
        std::cin >> opponent_x >> opponent_y; std::cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        // You have to output the target position
        // followed by the power (0 <= thrust <= 100) or "BOOST"
        // i.e.: "x y thrust"
        if (next_checkpoint_dist > 5000) {
            if (next_checkpoint_angle > -10 && next_checkpoint_angle < 10) {
                cout << next_checkpoint_x << " " << next_checkpoint_y << " " << "BOOST" << endl;
            }
            else {
                cout << next_checkpoint_x << " " << next_checkpoint_y << " " << "100" << endl;
            }
        }
        else if (next_checkpoint_dist > 1000) {
            cout << next_checkpoint_x << " " << next_checkpoint_y << " " << "100" << endl;
        }
        else if (next_checkpoint_dist > 500) {
            int speed = next_checkpoint_dist / 200 + 30;
            if (speed > 100) speed = 100;
            cout << next_checkpoint_x << " " << next_checkpoint_y << " " << speed << endl;
        }
        else {
            int speed = next_checkpoint_dist / 20 + 10;
            if (speed > 100) speed = 100;
            cout << next_checkpoint_x << " " << next_checkpoint_y << " " << speed << endl;
        }
    }
}