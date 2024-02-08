#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

double pow(float x) {
    return x * x;
}

class Checkpoint 
{
    public:
        int x, y;
        double distWithNext;

        Checkpoint() : x(0), y(0), distWithNext(0) { }

        Checkpoint(int x, int y, double distWithNext) : x(x), y(y), distWithNext(distWithNext) { }
};

class Track
{
    public:
        Checkpoint checkpoints[4];
        int cpIndex = 0;
    
    inline void createCheckpoint(int x, int y, double distWithNext) 
    {
        this->checkpoints[cpIndex] = Checkpoint(x, y, distWithNext);
        this->cpIndex++;
    }

    inline bool getCp(int x, int y) 
    {
        for (int i = 0; i < this->cpIndex; i++)
            if (this->checkpoints[i].x == x && this->checkpoints[i].y == y) return true;
        return false;
    }

    inline std::pair<Checkpoint, Checkpoint> longest()
    {
        Checkpoint cp1, cp2;
        double max = 0;

        for (int i = 0; i < this->cpIndex - 1; i++)
        {
            if (this->checkpoints[i].distWithNext > max)
            {
                cp1 = this->checkpoints[i];
                cp2 = this->checkpoints[i + 1];
                max = cp1.distWithNext;
            }
        }

        if (this->checkpoints[this->cpIndex - 1].distWithNext > max)
        {
            cp1 = this->checkpoints[this->cpIndex - 1];
            cp2 = this->checkpoints[0];
            max = cp1.distWithNext;
        }

        return std::make_pair(cp1, cp2);
    }

    inline Checkpoint last() {
        return this->checkpoints[this->cpIndex - 1];
    }

    inline Checkpoint head() {
        return this->checkpoints[0];
    }

    inline bool alreadyAdded(int x, int y) {
        return this->last().x == x && this->last().y == y;
    }

    inline bool isEmpty() {
        return this->cpIndex == 0;
    }

    inline bool finishedTrack(int x, int y) {
        return this->head().x == x && this->head().y == y;
    }
};

int main()
{
    Track track = Track();
    std::pair<Checkpoint, Checkpoint> longestPath;

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
        if (track.isEmpty()) track.createCheckpoint(next_checkpoint_x, next_checkpoint_y, next_checkpoint_dist);

        if (!track.finishedTrack(next_checkpoint_x, next_checkpoint_y)) {
            track.createCheckpoint(next_checkpoint_x, next_checkpoint_y, next_checkpoint_dist);

            if (track.finishedTrack(next_checkpoint_x, next_checkpoint_y)) {
                longestPath = track.longest();
            }
        }

        if (next_checkpoint_x == longestPath.first.x && next_checkpoint_y == longestPath.first.y) {
            std::cout << next_checkpoint_x << " " << next_checkpoint_y << " 100 boost" << std::endl;
        }
        else {
            std::cout << next_checkpoint_x << " " << next_checkpoint_y << " 80" << std::endl;
        }


        // You have to output the target position
        // followed by the power (0 <= thrust <= 100) or "BOOST"
        // i.e.: "x y thrust"
    }
}