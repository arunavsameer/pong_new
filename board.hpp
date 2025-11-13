using namespace std;


// Assuming (0,0) is at bottom left

class board {
    public:
    int height, width, border_width;
    vector <vector<bool>> is_brick;
    vector <vector<char>> brick_color;

    void gen_board (int seed = 0){
        mt19937 rng(seed);
        int max_layer_thickness = 3;
        
        // Width to fill
        int half_height = (height+1)/2;
        int three_fourth_height = (3*height + 3)/4;
        int one_tenth_height = (height+9)/10;
        int x_start = half_height - rng()%one_tenth_height;
        int x_end = three_fourth_height + rng()%one_tenth_height;

        // Height to fill
        int one_fourth_width = (width+3)/4;
        int three_fourth_width = (3*width + 3)/4;
        int one_tenth_width = (width + 9)/10;
        int y_start = one_fourth_width - rng()%one_tenth_width;
        int y_end = three_fourth_height + rng()%one_tenth_width;

        vector <int> layers;
        int available = x_end - x_start + 1;
        while (available > 0){
            int max_thickness = min(max_layer_thickness,available);
            int thickness = (max_thickness == 1) ? 1 : ((rng()%(max_thickness - 1)) + 1);
            layers.push_back(thickness);
            available -= thickness;
        }
        int x_curr = x_start;
        int prev_color = 0;
        for (auto &siz: layers){
            int n_color = (prev_color + rng()%2 + 1)%3;
            for (int i = x_curr ; i < x_curr + siz; i++){
                 for (int j = y_start ; j <= y_end ; j++){
                     is_brick[i][j] = true;
                     brick_color[i][j] = n_color;
                 }
            }
            prev_color = n_color;
            x_curr += siz;
        }
    }

    board (int h , int w, int b = 2, int seed = 3){
        height = h;
        width = w;
        border_width = b;
        is_brick.resize(height);
        brick_color.resize(height);
        for (int i = 0 ; i < h ; i++){
            is_brick[i].assign(width,0);
            brick_color[i].assign(width,0);
        }
        gen_board(seed);
    }

    void remove_brick (int x , int y){
        if (x < 0 || x >= width || y < 0 || y >= height){
            cout << "Out of bounds brick removal" << endl;
            cout << x << " " << y << endl;
            return;
        }
        is_brick[y][x] = false;
    }

    bool is_brick_here (int x , int y){
        return is_brick[y][x];
    }
};
