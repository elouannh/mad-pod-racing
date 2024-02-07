#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

double pow(float x) {
    return x * x;
}

class Checkpoint {
public:
    int x, y;
    double distWithNext;
    Checkpoint* next;

    Checkpoint() : x(0), y(0), next(nullptr), distWithNext(0) {}

    Checkpoint(int x, int y, double distWithNext) : x(x), y(y), next(nullptr), distWithNext(distWithNext) {}

    inline static double dist(Checkpoint* cp1, Checkpoint* cp2) {
        return std::sqrt(static_cast<double>(pow(cp1->x - cp2->x) + pow(cp1->y - cp2->y)));
    };

    inline void printCheckpoint() {
        std::cerr << this->x << " " << this->y << " : " << this->distWithNext << endl;
    }

    Checkpoint* lastCheckpoint() {
        if (this->next != nullptr) return this->next->lastCheckpoint();
        return this;
    };
};

void printLinkedList(Checkpoint* head) {
    head->printCheckpoint();

    if (head->next != nullptr) {
        printLinkedList(head->next);
        std::cerr << std::endl;
    }

    std::cerr << std::endl;
}

void calculateLongestDist(Checkpoint* head, double maxDist) {
    Checkpoint* elt = head->next;
    if (head->distWithNext > maxDist) {
        maxDist = head->distWithNext;
        elt = head->next;
    }

    if (head->next != nullptr) {
        return calculateLongestDist(elt, maxDist);
    }
    else {
        return;
    }
}

int main()
{
    Checkpoint* mainCheckpoint;
    bool registered = false;

    while (1) {
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
        if (mainCheckpoint == nullptr) mainCheckpoint = new Checkpoint(next_checkpoint_x, next_checkpoint_y, next_checkpoint_dist);
        if (
            next_checkpoint_x != mainCheckpoint->lastCheckpoint()->x ||
            next_checkpoint_y != mainCheckpoint->lastCheckpoint()->y
        ) mainCheckpoint->lastCheckpoint()->next = new Checkpoint(next_checkpoint_x, next_checkpoint_y, next_checkpoint_dist);

        // You have to output the target position
        // followed by the power (0 <= thrust <= 100) or "BOOST"
        // i.e.: "x y thrust"
        std::cout << next_checkpoint_x << " " << next_checkpoint_y << " 80" << std::endl;
    }
}