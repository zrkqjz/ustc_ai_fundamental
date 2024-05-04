#include <vector>
#include <map>
#include <limits>
#include <iostream>
#include <string>

namespace ChineseChess
{
    //注意是先y再x，y的范围是0-sizeX，x的范围是0-sizeY，太怪了
    //棋力评估，这里的棋盘方向和输入棋盘方向不同，在使用时需要仔细
    //生成合法动作代码部分已经使用，经过测试是正确的，大家可以参考
    std::vector<std::vector<int>> JiangPosition = {
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {1, -8, -9, 0, 0, 0, 0, 0, 0, 0},
                                                {5, -8, -9, 0, 0, 0, 0, 0, 0, 0},
                                                {1, -8, -9, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            };

    std::vector<std::vector<int>> ShiPosition = {
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 3, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            };
        
    std::vector<std::vector<int>> XiangPosition = {
                                                {0, 0, -2, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 3, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, -2, 0, 0, 0, 0, 0, 0, 0},
                                            };

    std::vector<std::vector<int>> MaPosition = {
                                                {0, -3, 5, 4, 2, 2, 5, 4, 2, 2},
                                                {-3, 2, 4, 6, 10, 12, 20, 10, 8, 2},
                                                {2, 4, 6, 10, 13, 11, 12, 11, 15, 2},
                                                {0, 5, 7, 7, 14, 15, 19, 15, 9, 8},
                                                {2, -10, 4, 10, 15, 16, 12, 11, 6, 2},
                                                {0, 5, 7, 7, 14, 15, 19, 15, 9, 8},
                                                {2, 4, 6, 10, 13, 11, 12, 11, 15, 2},
                                                {-3, 2, 4, 6, 10, 12, 20, 10, 8, 2},
                                                {0, -3, 5, 4, 2, 2, 5, 4, 2, 2},
                                            };

    std::vector<std::vector<int>> PaoPosition = {
                                                {0, 0, 1, 0, -1, 0, 0, 1, 2, 4},
                                                {0, 1, 0, 0, 0, 0, 3, 1, 2, 4},
                                                {1, 2, 4, 0, 3, 0, 3, 0, 0, 0},
                                                {3, 2, 3, 0, 0, 0, 2, -5, -4, -5},
                                                {3, 2, 5, 0, 4, 4, 4, -4, -7, -6},
                                                {3, 2, 3, 0, 0, 0, 2, -5, -4, -5},
                                                {1, 2, 4, 0, 3, 0, 3, 0, 0, 0},
                                                {0, 1, 0, 0, 0, 0, 3, 1, 2, 4},
                                                {0, 0, 1, 0, -1, 0, 0, 1, 2, 4},
                                            };

    std::vector<std::vector<int>> JuPosition = {
                                                {-6, 5, -2, 4, 8, 8, 6, 6, 6, 6},
                                                {6, 8, 8, 9, 12, 11, 13, 8, 12, 8},
                                                {4, 6, 4, 4, 12, 11, 13, 7, 9, 7},
                                                {12, 12, 12, 12, 14, 14, 16, 14, 16, 13},
                                                {0, 0, 12, 14, 15, 15, 16, 16, 33, 14},
                                                {12, 12, 12, 12, 14, 14, 16, 14, 16, 13},
                                                {4, 6, 4, 4, 12, 11, 13, 7, 9, 7},
                                                {6, 8, 8, 9, 12, 11, 13, 8, 12, 8},
                                                {-6, 5, -2, 4, 8, 8, 6, 6, 6, 6},
                                            };

    std::vector<std::vector<int>> BingPosition = {
                                                {0, 0, 0, -2, 3, 10, 20, 20, 20, 0},
                                                {0, 0, 0, 0, 0, 18, 27, 30, 30, 0},
                                                {0, 0, 0, -2, 4, 22, 30, 45, 50, 0},
                                                {0, 0, 0, 0, 0, 35, 40, 55, 65, 2},
                                                {0, 0, 0, 6, 7, 40, 42, 55, 70, 4},
                                                {0, 0, 0, 0, 0, 35, 40, 55, 65, 2},
                                                {0, 0, 0, -2, 4, 22, 30, 45, 50, 0},
                                                {0, 0, 0, 0, 0, 18, 27, 30, 30, 0},
                                                {0, 0, 0, -2, 3, 10, 20, 20, 20, 0},
                                            };

    //棋子价值评估
    std::map<std::string, int> piece_values = {
                                            {"Jiang", 10000},
                                            {"Shi", 10},
                                            {"Xiang", 30},
                                            {"Ma", 300},
                                            {"Ju", 500},
                                            {"Pao", 300},
                                            {"Bing", 90}
                                        };

    //行期可能性评估，这里更多是对下一步动作的评估
    std::map<std::string, int> next_move_values = {
                                            {"Jiang", 9999},
                                            {"Ma", 100},
                                            {"Ju", 500},
                                            {"Pao", 100},
                                            {"Bing", -20}
                                        };
    
    //动作结构体，每个动作设置score，可以方便剪枝
    struct Move {
        int init_x;
        int init_y;
        int next_x;
        int next_y;
        int score;
    };

    // 定义棋盘上的棋子结构体
    struct ChessPiece {
        char name; // 棋子名称
        int init_x, init_y; // 棋子的坐标
        bool color;   //棋子阵营 true为红色、false为黑色
    };

    // 定义棋盘类
    class ChessBoard {
    private:
        int sizeX, sizeY;   //棋盘大小，固定
        std::vector<ChessPiece> pieces;   //棋盘上所有棋子
        std::vector<std::vector<char>> board;    //当前棋盘、二维数组表示
        std::vector<Move> red_moves;    //红方棋子的合法动作
        std::vector<Move> black_moves;   //黑方棋子的合法动作
    public:
        // 初始化棋盘，提取棋盘上棋子，并生成所有合法动作
        void initializeBoard(const std::vector<std::vector<char>>& init_board) {
            board = init_board;
            sizeX = board.size();
            sizeY = board[0].size();

            for (int i = 0; i < sizeX; ++i) {
                for (int j = 0; j < sizeY; ++j) {
                    char pieceChar = board[i][j];
                    if (pieceChar == '.') continue;

                    ChessPiece piece;
                    piece.init_x = j;
                    piece.init_y = i;
                    piece.color = (pieceChar >= 'A' && pieceChar <= 'Z');
                    piece.name = pieceChar;
                    pieces.push_back(piece);

                    switch (pieceChar) {
                        case 'R':
                            generateJuMoves(j, i, piece.color);
                            break;
                        case 'C':
                            generatePaoMoves(j, i, piece.color);
                            break;
                        case 'N':
                            generateMaMoves(j, i, piece.color);
                            break;
                        case 'B':
                            generateXiangMoves(j, i, piece.color);
                            break;
                        case 'A':
                            generateShiMoves(j, i, piece.color);
                            break;
                        case 'K':
                            generateJiangMoves(j, i, piece.color);
                            break;
                        case 'P':
                            generateBingMoves(j, i, piece.color);
                            break;
                        case 'r':
                            generateJuMoves(j, i, piece.color);
                            break;
                        case 'c':
                            generatePaoMoves(j, i, piece.color);
                            break;
                        case 'n':
                            generateMaMoves(j, i, piece.color);
                            break;
                        case 'b':
                            generateXiangMoves(j, i, piece.color);
                            break;
                        case 'a':
                            generateShiMoves(j, i, piece.color);
                            break;
                        case 'k':
                            generateJiangMoves(j, i, piece.color);
                            break;
                        case 'p':
                            generateBingMoves(j, i, piece.color);
                            break;
                        default:
                            break;
                    }
                } 
            }
        }
        
        //生成车的合法动作
        void generateJuMoves(int x, int y, bool color) {
            //前后左右分别进行搜索，遇到棋子停止，不同阵营可以吃掉
            std::vector<Move> JuMoves;
            for(int i = x + 1; i < sizeY; i++) {
                Move cur_move;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = i;
                cur_move.next_y = y;
                cur_move.score = 0;
                if (board[y][i] != '.') {
                    bool cur_color = (board[y][i] >= 'A' && board[y][i] <= 'Z');
                    if (cur_color != color) {
                        JuMoves.push_back(cur_move);
                    }
                    break;
                }
                JuMoves.push_back(cur_move);
            }

            for(int i = x - 1; i >= 0; i--) {
                Move cur_move;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = i;
                cur_move.next_y = y;
                cur_move.score = 0;
                if (board[y][i] != '.') {
                    bool cur_color = (board[y][i] >= 'A' && board[y][i] <= 'Z');
                    if (cur_color != color) {
                        JuMoves.push_back(cur_move);
                    }
                    break;
                }
                JuMoves.push_back(cur_move);
            }

            for(int j = y + 1; j < sizeX; j++) {
                Move cur_move;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = x;
                cur_move.next_y = j;
                cur_move.score = 0;
                if (board[j][x] != '.') {
                    bool cur_color = (board[j][x] >= 'A' && board[j][x] <= 'Z');
                    if (cur_color != color) {
                        JuMoves.push_back(cur_move);
                    }
                    break;
                }
                JuMoves.push_back(cur_move);
            }

            for(int j = y - 1; j >= 0; j--) {
                Move cur_move;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = x;
                cur_move.next_y = j;
                cur_move.score = 0;
                if (board[j][x] != '.') {
                    bool cur_color = (board[j][x] >= 'A' && board[j][x] <= 'Z');
                    if (cur_color != color) {
                        JuMoves.push_back(cur_move);
                    }
                    break;
                }
                JuMoves.push_back(cur_move); 
            }
            for (int i = 0; i < JuMoves.size(); i++) {
                if(color) {
                    JuMoves[i].score = JuPosition[JuMoves[i].next_x][9 - JuMoves[i].next_y] - JuPosition[x][9 -y];
                    red_moves.push_back(JuMoves[i]);
                }
                else {
                    JuMoves[i].score = JuPosition[JuMoves[i].next_x][JuMoves[i].next_y] - JuPosition[x][y];
                    black_moves.push_back(JuMoves[i]);
                }
            }
        }

        //生成马的合法动作
        void generateMaMoves(int x, int y, bool color) {
            //便利所有可能动作，筛选
            std::vector<Move> MaMoves;
            int dx[] = {2, 1, -1, -2, -2, -1, 1, 2};
            int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
            //简化，不考虑拌马脚
            //TODO 可以实现拌马脚过程
            for(int i = 0; i < 8; i++) {
                Move cur_move;
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx < 0 || nx >= 9 || ny < 0 || ny >= 10) continue;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = nx;
                cur_move.next_y = ny;
                cur_move.score = 0;
                if (board[ny][nx] != '.') {
                    //注意棋盘坐标系，这里nx、ny相反是正确的
                    bool cur_color = (board[ny][nx] >= 'A' && board[ny][nx] <= 'Z');
                    if (cur_color != color) {
                        MaMoves.push_back(cur_move);
                    }
                    continue;
                }
                MaMoves.push_back(cur_move);
            }
            for (int i = 0; i < MaMoves.size(); i++) {
                if(color) {
                    MaMoves[i].score = MaPosition[MaMoves[i].next_x][9 - MaMoves[i].next_y] - MaPosition[x][9 - y];
                    red_moves.push_back(MaMoves[i]);
                }
                else {
                    MaMoves[i].score = MaPosition[MaMoves[i].next_x][MaMoves[i].next_y] - MaPosition[x][y];
                    black_moves.push_back(MaMoves[i]);
                }
            }
        }

        //生成炮的合法动作
        void generatePaoMoves(int x, int y, bool color) {
            //和车生成动作相似，需要考虑炮翻山吃子的情况
            std::vector<Move> PaoMoves;
            //TODO
            //炮架结构体
            struct CannonMount {
                int x = -1;
                int y = -1;
                bool color = color;
            };
            CannonMount mount[4];
            CannonMount target[4];
            //这段丑陋的代码用于找到炮架和炮架后第一个棋子，注意先y后x，太怪了真的
            for(int i = y - 1; i >= 0; i--) {
                if (board[i][x] != '.' && mount[0].y == -1) {
                    mount[0].y = i;
                    mount[0].x = x;
                    continue;
                }
                if (board[i][x] != '.' &&  mount[0].y != -1) {
                    target[0].y = i;
                    target[0].x = x;
                    break;
                }
            }
            for(int i = y + 1; i < sizeX; i++) {
                if (board[i][x] != '.' && mount[1].y == -1) {
                    mount[1].y = i;
                    mount[1].x = x;
                    continue;
                }
                if (board[i][x] != '.' &&  mount[1].y != -1) {
                    target[1].y = i;
                    target[1].x = x;
                    break;
                }
            }
            for(int i = x - 1; i >= 0; i--) {
                if (board[y][i] != '.' && mount[2].x == -1) {
                    mount[2].y = y;
                    mount[2].x = i;
                    continue;
                }
                if (board[y][i] != '.' &&  mount[2].x != -1) {
                    target[2].y = y;
                    target[2].x = i;
                    break;
                }
            }
            for(int i = x + 1; i < sizeY; i++) {
                if (board[y][i] != '.' && mount[3].x == -1) {
                    mount[3].y = y;
                    mount[3].x = i;
                    continue;
                }
                if (board[y][i] != '.' &&  mount[3].x != -1) {
                    target[3].y = y;
                    target[3].x = i;
                    break;
                }
            }
            //丑陋的代码结束

            std::vector<std::pair<int, int>> positions;
            for(int i = 0; i < sizeY; i++) {
                positions.push_back(std::make_pair(y, i));
            }
            for(int j = 0; j < sizeX; j++) {
                positions.push_back(std::make_pair(j, x));
            }
            for (int j = 0; j < positions.size(); j++) {
                Move cur_move;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = positions[j].second;
                cur_move.next_y = positions[j].first;
                cur_move.score = 0;
                bool crossMount = false;//是否翻过炮架
                for(int i = 0; i < 4; i++){
                    //隔着炮架
                    if (   (cur_move.next_x == mount[i].x  
                           && ((mount[i].y - cur_move.next_y) * (mount[i].y - y) < 0))
                        || (cur_move.next_y == mount[i].y 
                           && ((mount[i].x - cur_move.next_x) * (mount[i].x - x) < 0))
                       ) 
                    {   
                        crossMount = true;
                        //吃子
                        if (board[positions[j].first][positions[j].second] != '.') {
                            bool cur_color = (board[positions[j].first][positions[j].second] >= 'A' && board[positions[j].first][positions[j].second] <= 'Z');
                            if (cur_move.next_x == target[i].x && cur_move.next_y == target[i].y) {
                                if (cur_color != color) {
                                    PaoMoves.push_back(cur_move);
                                    break;
                                }
                            }
                        }
                    }
                }
                //不隔炮架，走空地
                if (!crossMount) {
                    if (board[positions[j].first][positions[j].second] == '.') {
                        PaoMoves.push_back(cur_move);
                    }
                }
            }

            for (int i = 0; i < PaoMoves.size(); i++) {
                if(color) {
                    PaoMoves[i].score = PaoPosition[PaoMoves[i].next_x][9 - PaoMoves[i].next_y] - PaoPosition[x][9 -y];
                    red_moves.push_back(PaoMoves[i]);
                }
                else {
                    PaoMoves[i].score = PaoPosition[PaoMoves[i].next_x][PaoMoves[i].next_y] - PaoPosition[x][y];
                    black_moves.push_back(PaoMoves[i]);
                }
            }
        }

        //生成相的合法动作
        void generateXiangMoves(int x, int y, bool color) {
            std::vector<Move> XiangMoves;
            //TODO
            int dx[] = {2, 2, -2, -2};
            int dy[] = {2, -2, 2, -2};
            for(int i = 0; i < 4; i++) {
                Move cur_move;
                int nx = x + dx[i];
                int ny = y + dy[i];
                // 越界，过河
                if (nx < 0 || nx >= 9 || ny < 0 || ny >= 10
                   || (y < 5 && ny >= 5) || (y >= 5 && ny < 5))
                    continue;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = nx;
                cur_move.next_y = ny;
                cur_move.score = 0;
                //塞象眼
                if (board[y + dy[i] / 2][x + dx[i] / 2] != '.') 
                    continue;
                //吃子
                if (board[ny][nx] != '.') {
                    //注意棋盘坐标系，这里nx、ny相反是正确的
                    bool cur_color = (board[ny][nx] >= 'A' && board[ny][nx] <= 'Z');
                    if (cur_color != color) {
                        XiangMoves.push_back(cur_move);
                    }
                    continue;
                }
                XiangMoves.push_back(cur_move);
            }

            for (int i = 0; i < XiangMoves.size(); i++) {
                if(color) {
                    XiangMoves[i].score = XiangPosition[XiangMoves[i].next_x][9 - XiangMoves[i].next_y] - XiangPosition[x][9 -y];
                    red_moves.push_back(XiangMoves[i]);
                }
                else {
                    XiangMoves[i].score = XiangPosition[XiangMoves[i].next_x][XiangMoves[i].next_y] - XiangPosition[x][y];
                    black_moves.push_back(XiangMoves[i]);
                }
            }
        }

        //生成士的合法动作
        void generateShiMoves(int x, int y, bool color) {
            std::vector<Move> ShiMoves;
            //TODO
            int dx[] = {1, 1, -1, -1};
            int dy[] = {1, -1, -1, 1};
            for(int i = 0; i < 4; i++){
                Move cur_move;
                int nx = x + dx[i];
                int ny = y + dy[i];
                //走出九宫格
                if (nx < 3 || nx >= 6
                    ||(y >= 5 && (ny < 7 || ny > 9))
                    ||(y < 5 && (ny < 0 || ny > 2))) 
                    continue;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = nx;
                cur_move.next_y = ny;
                cur_move.score = 0;
                if (board[ny][nx] != '.') {
                    bool cur_color = (board[ny][nx] >= 'A' && board[ny][nx] <= 'Z');
                    if (cur_color != color) {
                        ShiMoves.push_back(cur_move);
                    }
                    continue;
                }
                ShiMoves.push_back(cur_move);
            }


            for (int i = 0; i < ShiMoves.size(); i++) {
                if(color) {
                    ShiMoves[i].score = ShiPosition[ShiMoves[i].next_x][9 - ShiMoves[i].next_y] - ShiPosition[x][9 -y];
                    red_moves.push_back(ShiMoves[i]);
                }
                else {
                    ShiMoves[i].score = ShiPosition[ShiMoves[i].next_x][ShiMoves[i].next_y] - ShiPosition[x][y];
                    black_moves.push_back(ShiMoves[i]);
                }
            }
        }

        //生成将的合法动作
        void generateJiangMoves(int x, int y, bool color) {
            std::vector<Move> JiangMoves;
            //TODO
            int dx[] = {0, 0, 1, -1};
            int dy[] = {1, -1, 0, 0};
            for(int i = 0; i < 4; i++){
                Move cur_move;
                int nx = x + dx[i];
                int ny = y + dy[i];
                //走出九宫格
                if (nx < 3 || nx >= 6
                    ||(y >= 5 && (ny < 7 || ny > 9))
                    ||(y < 5 && (ny < 0 || ny > 2))) 
                    continue;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = nx;
                cur_move.next_y = ny;
                cur_move.score = 0;
                if (board[ny][nx] != '.') {
                    bool cur_color = (board[ny][nx] >= 'A' && board[ny][nx] <= 'Z');
                    if (cur_color != color) {
                        JiangMoves.push_back(cur_move);
                    }
                    continue;
                }
                JiangMoves.push_back(cur_move);
            }

            for (int i = 0; i < JiangMoves.size(); i++) {
                if(color) {
                    JiangMoves[i].score = JiangPosition[JiangMoves[i].next_x][9 - JiangMoves[i].next_y] - JiangPosition[x][9 -y];
                    red_moves.push_back(JiangMoves[i]);
                }
                else {
                    JiangMoves[i].score = JiangPosition[JiangMoves[i].next_x][JiangMoves[i].next_y] - JiangPosition[x][y];
                    black_moves.push_back(JiangMoves[i]);
                }
            }
        }

        //生成兵的合法动作
        void generateBingMoves(int x, int y, bool color) {
            //需要分条件考虑，小兵在过楚河汉界之前只能前进，之后可以左右前
            std::vector<Move> BingMoves;
            //TODO
            int dx[] = {0, 0, 1, -1};
            int dy[] = {1, -1, 0, 0};
            bool CrossRiver = (color == false && y >= 5) || (color == true && y < 5);
            for(int i = 0; i < 4; i++){
                Move cur_move;
                int nx = x + dx[i];
                int ny = y + dy[i];
                //越界
                if (nx < 0 || nx >= 9 || ny < 0 || ny >= 10) continue;
                //没过河
                if (!CrossRiver && color == true && dy[i] == 0
                || !CrossRiver && color == false && dy[i] == 0)
                    continue;
                //不能后退
                if (color == true && dy[i] == 1
                 || color == false && dy[i] == -1) 
                    continue;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = nx;
                cur_move.next_y = ny;
                cur_move.score = 0;
                if (board[ny][nx] != '.') {
                    bool cur_color = (board[ny][nx] >= 'A' && board[ny][nx] <= 'Z');
                    if (cur_color != color) {
                        BingMoves.push_back(cur_move);
                    }
                    continue;
                }
                BingMoves.push_back(cur_move);
            }

            for (int i = 0; i < BingMoves.size(); i++) {
                if(color) {
                    BingMoves[i].score = BingPosition[BingMoves[i].next_x][9 - BingMoves[i].next_y] - BingPosition[x][9 -y];
                    red_moves.push_back(BingMoves[i]);
                }
                else {
                    BingMoves[i].score = BingPosition[BingMoves[i].next_x][BingMoves[i].next_y] - BingPosition[x][y];
                    black_moves.push_back(BingMoves[i]);
                }
            }
        }
    
        //终止判断
        bool judgeTermination() {
            //TODO
            int king_num = 0;
            for(int i = 0; i < sizeX; i++){
                for(int j = 0; j < sizeY; j++){
                    if (board[i][j] == 'K' || board[i][j] == 'k') king_num += 1;
                }
            }
            if (king_num != 2) return true;
            else return false;
        }

        //棋盘分数评估，根据当前棋盘进行棋子价值和棋力评估，max玩家减去min玩家分数
        int evaluateNode() {
            //TODO
            int red_score = 0;
            int black_score = 0;
            for(int i = 0; i < sizeY; i++){
                for(int j = 0; j < sizeX; j++){
                    char pieceChar = board[j][i];
                    if (pieceChar == '.') continue;
                    switch(pieceChar){
                        case 'K':
                            red_score += JiangPosition[i][9 - j];
                            red_score += piece_values["Jiang"];
                            break;
                        case 'k':
                            black_score += JiangPosition[i][j];
                            black_score += piece_values["Jiang"];
                            break;
                        case 'R':
                            red_score += JuPosition[i][9 - j];
                            red_score += piece_values["Ju"];
                            break;
                        case 'r':
                            black_score += JuPosition[i][j];
                            black_score += piece_values["Ju"];
                            break;
                        case 'C':
                            red_score += PaoPosition[i][9 - j];
                            red_score += piece_values["Pao"];
                            break;
                        case 'c':
                            black_score += PaoPosition[i][j];
                            black_score += piece_values["Pao"];
                            break;
                        case 'N':
                            red_score += MaPosition[i][9 - j];
                            red_score += piece_values["Ma"];
                            break;
                        case 'n':
                            black_score += MaPosition[i][j];
                            black_score += piece_values["Ma"];
                            break;
                        case 'B':
                            red_score += XiangPosition[i][9 - j];
                            red_score += piece_values["Xiang"];
                            break;
                        case 'b':
                            black_score += XiangPosition[i][j];
                            black_score += piece_values["Xiang"];
                            break;
                        case 'A':
                            red_score += ShiPosition[i][9 - j];
                            red_score += piece_values["Shi"];
                            break;
                        case 'a':
                            black_score += ShiPosition[i][j];
                            black_score += piece_values["Shi"];
                            break;
                        case 'P':
                            red_score += BingPosition[i][9 - j];
                            red_score += piece_values["Bing"];
                            break;
                        case 'p':
                            black_score += BingPosition[i][j];
                            black_score += piece_values["Bing"];
                            break;
                        default:
                            break;
                    }
                }
            }
            return red_score - black_score;
        }

        //测试接口
        std::vector<Move> getMoves(bool color) {
            if(color) return red_moves;
            return black_moves;
        }
    
        std::vector<ChessPiece> getChessPiece() {
            return pieces;
        }
    
        std::vector<std::vector<char>> getBoard() {
            return board;
        }
    };

    // 定义博弈树节点类
    class GameTreeNode {
    private:
        bool color; // 当前玩家类型，true为红色方、false为黑色方
        ChessBoard board; // 当前棋盘状态
        std::vector<GameTreeNode*> children; // 子节点列表
        int evaluationScore; // 棋盘评估分数

    public:
        // 构造函数
        Move best_move;
        GameTreeNode(bool color, std::vector<std::vector<char>> initBoard, int evaluationScore)
            : color(color), evaluationScore(evaluationScore) {
            board.initializeBoard(initBoard);
            std::vector<Move> moves = board.getMoves(color);
            children.clear();
            std::vector<std::vector<char>> cur_board = board.getBoard();

            // 为合法动作创建子节点
            // for (int i = 0; i < moves.size(); i++) {
            //     GameTreeNode* child = updateBoard(cur_board, moves[i], color);
            //     children.push_back(child);
            // }
        }

        //根据当前棋盘和动作构建新棋盘（子节点）
        GameTreeNode updateBoard(std::vector<std::vector<char>> cur_board, Move move, bool color) {
            //TODO
            //更新棋盘
            std::vector<std::vector<char>> new_board = cur_board;
            new_board[move.next_y][move.next_x] = cur_board[move.init_y][move.init_x];
            new_board[move.init_y][move.init_x] = '.';
            if (color) {
                GameTreeNode test(false, new_board, std::numeric_limits<int>::max()); 
                return test;
            }
            else{
                GameTreeNode test(true, new_board, std::numeric_limits<int>::min());
                return test;
            }
        }

        //返回节点评估分数
        int getEvaluationScore() {
            evaluationScore = board.evaluateNode();
            return evaluationScore;
        }

        //返回棋盘类
        ChessBoard getBoardClass() {
            return board;
        }

        bool isTerminate(){
            return board.judgeTermination();
        }

        
        ~GameTreeNode() {
            for (GameTreeNode* child : children) {
                delete child;
            }
        }

    };
    
}