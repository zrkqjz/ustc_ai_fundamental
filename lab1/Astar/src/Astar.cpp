#include<vector>
#include<iostream>
#include<queue>
#include<map>
#include<fstream>
#include<sstream>
#include<string>
#include<set>

#define INF 0x3f3f3f3f

using namespace std;

struct Map_Cell
{
    int type;
    // TODO: 定义地图信息
    int accumulated_cost = INF;
    int remained_energy = 0;
    bool in_open_list[4] = {false, false, false, false};
};

struct Search_Cell
{
    int h;
    int g;
    // TODO: 定义搜索状态
    Search_Cell *parent = nullptr;

    bool operator==(const Search_Cell &a) const
    {
        return h == a.h && g == a.g && parent->h == a.parent->h && parent->g == a.parent->g;
    }

/*     ~Search_Cell()
    {
        if (parent != nullptr)
        {
            delete parent;
        }
    } */
};

int M, N, T;
Map_Cell **Map;
pair<int, int> start_point; // 起点
pair<int, int> end_point;   // 终点
int Heuristic_Funtion(const Search_Cell *a, const int energy)
{
    int manhattan_distance = abs(a->h - end_point.first) + abs(a->g - end_point.second);
    return manhattan_distance;
    //return 0;
}

// 自定义比较函数对象，按照 Search_Cell 结构体的 g + h 属性进行比较
struct CompareF {
    bool operator()(const Search_Cell *a, const Search_Cell *b) const {
        return (Map[a->h][a->g].accumulated_cost + Heuristic_Funtion(a, Map[a->h][a->g].remained_energy)) 
                > (Map[b->h][b->g].accumulated_cost + Heuristic_Funtion(b, Map[b->h][b->g].remained_energy));
    }
};

// TODO: 定义启发式函数


int Astar_search(const string input_file, int &step_nums, string &way)
{
    ifstream file(input_file);
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return -1;
    }

    string line;
    getline(file, line); // 读取第一行
    stringstream ss(line);
    string word;
    vector<string> words;
    while (ss >> word) {
        words.push_back(word);
    }
    M = stoi(words[0]);
    N = stoi(words[1]);
    T = stoi(words[2]);

    Map = new Map_Cell *[M];
    // 加载地图
    for(int i = 0; i < M; i++)
    {
        Map[i] = new Map_Cell[N];
        getline(file, line);
        stringstream ss(line);
        string word;
        vector<string> words;
        while (ss >> word) {
            words.push_back(word);
        }
        for(int j = 0; j < N; j++)
        {
            Map[i][j].type = stoi(words[j]);
            if(Map[i][j].type == 3)
            {
                start_point = {i, j};
            }
            else if(Map[i][j].type == 4)
            {
                end_point = {i, j};
            }
        }
    }
    // 以上为预处理部分
    // ------------------------------------------------------------------

    Search_Cell *search_cell = new Search_Cell;
    search_cell->h = start_point.first;
    search_cell->g = start_point.second; 
    search_cell->parent = nullptr;
    Map[search_cell->h][search_cell->g].accumulated_cost = 0;
    Map[search_cell->h][search_cell->g].remained_energy = T;
    

    priority_queue<Search_Cell *, vector<Search_Cell *>, CompareF> open_list;
    set<Search_Cell *> close_list;
    open_list.push(search_cell);
    for(int i = 0; i < 4; i++){
        Map[search_cell->h][search_cell->g].in_open_list[i] = true;
    }
    

    bool find_end = false;
    int total_step = 0;
    while(!open_list.empty())
    {
        // TODO: A*搜索过程实现
        Search_Cell *n = open_list.top();
        open_list.pop();
        close_list.insert(n);
        total_step += 1;

        // judge if current_cell is the end point
        if(n->h == end_point.first && n->g == end_point.second)
        {
            find_end = true;
            // add current_cell to the left of way
            Search_Cell *temp = n;
            step_nums = 0;
            char step = 'U';
            while(temp->parent != nullptr)
            {
                step_nums += 1;
                // judge step direction by parent and temp's position
                if (temp->parent != nullptr){
                    if (temp->parent->h == temp->h){
                        if (temp->parent->g < temp->g){
                            step = 'R';
                        }
                        else{
                            step = 'L';
                        }
                    }
                    else{
                        if (temp->parent->h < temp->h){
                            step = 'D';
                        }
                        else{
                            step = 'U';
                        }
                    }
                }
                way = step + way;
                temp = temp->parent;
            }
            break;
        }

        // consider all adjacents of current_cell
        int adj[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (int i = 0; i < 4; i++){
            Search_Cell *adj_cell = new Search_Cell;
            adj_cell->h = n->h + adj[i][0];
            adj_cell->g = n->g + adj[i][1];
            // edge, in close list, wall, run out of energy
            if (adj_cell->h < 0 || adj_cell->h >= M || adj_cell->g < 0 || adj_cell->g >= N 
                || close_list.find(adj_cell) != close_list.end()
                || Map[adj_cell->h][adj_cell->g].type == 1
                || (Map[n->h][n->g].remained_energy < 2 && Map[adj_cell->h][adj_cell->g].type != 2 && Map[adj_cell->h][adj_cell->g].type != 4)){
                continue;
            }

            if ((!Map[adj_cell->h][adj_cell->g].in_open_list[i] && Map[adj_cell->h][adj_cell->g].remained_energy < Map[n->h][n->g].remained_energy - 1)
               || Map[n->h][n->g].accumulated_cost + 1 < Map[adj_cell->h][adj_cell->g].accumulated_cost){
                adj_cell->parent = n;
                Map[adj_cell->h][adj_cell->g].accumulated_cost = Map[n->h][n->g].accumulated_cost + 1;
                if (Map[adj_cell->h][adj_cell->g].type == 2){
                    Map[adj_cell->h][adj_cell->g].remained_energy = T;
                }
                else if (Map[adj_cell->h][adj_cell->g].remained_energy < Map[n->h][n->g].remained_energy - 1){
                    Map[adj_cell->h][adj_cell->g].remained_energy = Map[n->h][n->g].remained_energy - 1;
                }
                if (Map[adj_cell->h][adj_cell->g].remained_energy >= 0 && !Map[adj_cell->h][adj_cell->g].in_open_list[i]){
                    open_list.push(adj_cell);
                    Map[adj_cell->h][adj_cell->g].in_open_list[i] = true;
                }
                
            }
        }
    }

    // ------------------------------------------------------------------
    // TODO: 填充step_nums与way
    if (!find_end){
        step_nums = -1;
        way = "No way!";
    }

    // ------------------------------------------------------------------
    // 释放动态内存

    while(!open_list.empty())
    {
        auto temp = open_list.top();
        delete[] temp;
        open_list.pop();
    }
/*     for(int i = 0; i < close_list.size(); i++)
    {
        delete[] close_list[i];
    } */
    close_list.clear();
    for(int i = 0; i < M; i++)
    {
        delete[] Map[i];
    }
    delete[] Map;
    return total_step;
}

void output(const string output_file, int &step_nums, string &way)
{
    ofstream file(output_file);
    if(file.is_open())
    {
        file << step_nums << endl;
        if(step_nums >= 0)
        {
            file << way << endl;
        }

        file.close();
    }
    else
    {
        cerr << "Can not open file: " << output_file << endl;
    }
    return;
}

int main(int argc, char *argv[])
{
    string input_base = "../input/input_";
    string output_base = "../output/output_";
    int num_step = 0;
    // input_0为讲义样例，此处不做测试
    for(int i = 0; i < 11; i++)
    {
        int step_nums = -1;
        string way = "";
        num_step = Astar_search(input_base + to_string(i) + ".txt", step_nums, way);
        output(output_base + to_string(i) + ".txt", step_nums, way);
    }
    cout << "num_step for all input with manhattan distance as Heuristic: " << num_step << endl;
    // cout << "num_step for all input without Heuristic: " << num_step << endl;
    return 0;
}