#include <fstream>
#include "node.h"
#include <sstream>
#include <string>
#include <algorithm>
#include <chrono>

using namespace ChineseChess;

bool increase(const Move& a, const Move& b) {
    return a.score < b.score; // 升序排序
}
bool decrease(const Move& a, const Move& b) {
    return a.score > b.score; // 降序排序
}

//博弈树搜索，depth为搜索深度
int alphaBeta(GameTreeNode& node, int alpha, int beta, int depth, bool isMaximizer) {
    if (depth == 0 || node.isTerminate()) {
        return node.getEvaluationScore();
    }
    //TODO alpha-beta剪枝过程
    std::vector<Move> moves = node.getBoardClass().getMoves(isMaximizer);
    std::vector<std::vector<char>> cur_board = node.getBoardClass().getBoard();
    if (isMaximizer) {
        std::sort(moves.begin(), moves.end(), decrease);
    } else {
        std::sort(moves.begin(), moves.end(), increase);
    }
    Move best_move = moves[0];
    Move step;
    for(int i = 0; i < moves.size(); i++) {
        step = moves[i];
        GameTreeNode child_node = node.updateBoard(cur_board, step, isMaximizer);
        int score = alphaBeta(child_node, alpha, beta, depth - 1, !isMaximizer);
        if (isMaximizer) {
            if (score > alpha) {
                alpha = score;
                best_move = step;
            }
            if (alpha >= beta) {
                break;
            }
        } else {
            if (score < beta) {
                beta = score;
                best_move = step;
            }
            if (alpha >= beta) {
                break;
            }
        }
    }
    node.best_move = best_move;
    return isMaximizer ? alpha : beta;
}

// 返回值为搜索部分的时间
int work(int file_num) {
    std::string base = "E:\\MyCode\\ustc_ai_intro\\lab1\\Alpha_Beta\\"; //"../";
    std::string input_file = base + "input/" + std::to_string(file_num) + ".txt";
    std::string output_file = base + "output/output_" + std::to_string(file_num) + ".txt";
    std::ifstream file(input_file);
    std::vector<std::vector<char>> board;

    std::string line;
    int n = 0;
    while (std::getline(file, line)) {
        std::vector<char> row;

        for (char ch : line) {
            row.push_back(ch);
        }

        board.push_back(row);
        n = n + 1;
        if (n >= 10) break;
    }

    file.close();
    GameTreeNode root(true, board, std::numeric_limits<int>::min());

    //TODO
    Move result;
    auto start = std::chrono::high_resolution_clock::now();
    alphaBeta(root, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), 3, true);
    auto end = std::chrono::high_resolution_clock::now();
    result = root.best_move;

    ChessBoard _board = root.getBoardClass();
    std::vector<std::vector<char>> cur_board = _board.getBoard();
    std::ofstream output(output_file);
    output << cur_board[result.init_y][result.init_x] << " (" << result.init_x << "," << result.init_y << ")  (" << result.next_x << "," << result.next_y << ")";
    //代码测试
    
    std::cout << "chessboard of " << file_num << ":" <<std::endl;
    for (int i = 0; i < cur_board.size(); i++) {
        for (int j = 0; j < cur_board[0].size(); j++) {
            std::cout << cur_board[i][j];
        }
        std::cout << std::endl;
    }

    std::vector<Move> red_moves = _board.getMoves(true);
    std::vector<Move> black_moves = _board.getMoves(false);

    std::ofstream red_file(base + "move/red_" + std::to_string(file_num) + ".txt");
    std::ofstream black_file(base + "move/black_" + std::to_string(file_num) + ".txt");

    for (int i = 0; i < red_moves.size(); i++) {
        red_file << "init: " << red_moves[i].init_x <<  " " << red_moves[i].init_y << std::endl;
        red_file << "next: " << red_moves[i].next_x <<  " " << red_moves[i].next_y << std::endl;
        red_file << "score " << red_moves[i].score << std::endl;
    }
    red_file.close(); // 关闭文件

    for (int i = 0; i < black_moves.size(); i++) {
        black_file << "init: " << black_moves[i].init_x <<  " " << black_moves[i].init_y << std::endl;
        black_file << "next: " << black_moves[i].next_x <<  " " << black_moves[i].next_y << std::endl;
        black_file << "score " << black_moves[i].score << std::endl;
    }
    black_file.close(); // 关闭文件

    /* for (int i = 0; i < red_moves.size(); i++) {
        std::cout << "init: " << red_moves[i].init_x <<  " " << red_moves[i].init_y << std::endl;
        std::cout << "next: " << red_moves[i].next_x <<  " " << red_moves[i].next_y << std::endl;
        std::cout << "score " << red_moves[i].score << std::endl;
    }
    for (int i = 0; i < black_moves.size(); i++) {
        std::cout << "init: " << black_moves[i].init_x <<  " " << black_moves[i].init_y << std::endl;
        std::cout << "next: " << black_moves[i].next_x <<  " " << black_moves[i].next_y << std::endl;
        std::cout << "score " << black_moves[i].score << std::endl;
    } */

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

int main() {
    int time = 0;
    for(int i = 1; i < 11; i++) {
        time += work(i);
    }
    std::cout << "total time for all file: " << time << "ms" << std::endl;
    return 0;
}