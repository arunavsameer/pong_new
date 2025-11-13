using namespace std;
#include <vector>

class slider{
    int start, end, v_x;
public:
    slider(int s, int e, int v) : start(s), end(e), v_x(v) {}
    slider(int s, int e) : start(s), end(e), v_x(1) {}
    slider() : start(0), end(0), v_x(0) {}

    void move_slider_left(){
        start -= v_x;
        end -= v_x;
    }

    void move_slider_right(){
        start += v_x;
        end += v_x;
    }

    pair<int, int> get_location() const {
        return {start, end};
    }
};