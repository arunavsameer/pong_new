using namespace std;
#include <vector>
#include <algorithm>

class ball{
    int loc_x, loc_y, v_x, v_y;
public:
    ball(int l_x, int l_y, int v_x, int v_y) : loc_x(l_x), loc_y(l_y), v_x(v_x), v_y(v_y) {}
    ball() : loc_x(0), loc_y(0), v_x(0), v_y(0) {}

    void move_ball_x(){
        loc_x += ((v_x == 0) ? 0 : ((v_x > 0) ? 1 : -1));
        // loc_y += (v_y) / abs(v_y);
    }
    void move_ball_y(){
        // loc_x += ((v_x == 0) ? 0 : ((v_x > 0) ? 1 : -1));
        loc_y += (v_y) / abs(v_y);
    }

    pair<int, int> get_location() const {
        return {loc_x, loc_y};
    }

    void flip_v_y(){
        v_y = -v_y;
    }

    void flip_v_x(){
        v_x = -v_x;
    }

    int get_vx() const {
        return v_x;
    }

    void change_v(int delta_vx, int delta_vy){
        v_x += delta_vx;
        v_y += delta_vy;
    }

};