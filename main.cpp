#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <math.h>
#include <bits/stdc++.h>
#include <fstream>
// phien ban chinh thuc
// leak memory ở hàm innit và copy_board
// nhưng 2 hàm là của thầy nên viết thêm hàm copyboard để dùng riêng
using namespace std;
struct Position
{
    int x;
    int y;
    Position() { x = y = 0; }
    Position(int a, int b)
    {
        x = a;
        y = b;
    }
};
struct Move
{
    Position pos_start, pos_end;
    Move(Position s, Position e)
    {
        pos_start = s;
        pos_end = e;
    }
};
void changeBoard(int **board, vector<Position> pos, int value)
{
    vector<Position>::iterator i;
    Position xy;
    i = pos.begin();
    for (; i != pos.end(); ++i)
    {
        xy = *i;
        board[xy.x][xy.y] = value;
    }
}
void print_board(int **board)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (board[4 - i][j] == 1)
                cout << "X ";
            else if (board[4 - i][j] == -1)
                cout << "O ";
            else
                cout << "- ";
        }
        cout << endl;
    }
}

int **init_board()
{
    int **t = new int *[5];
    for (int i = 0; i < 5; i++)
    {
        t[i] = new int[5];
        if (i == 0)
        {
            for (int j = 0; j < 5; j++)
                t[i][j] = 1;
            continue;
        }
        if (i == 4)
        {
            for (int j = 0; j < 5; j++)
                t[i][j] = -1;
            continue;
        }
        for (int j = 0; j < 5; j++)
        {
            t[i][j] = 0;
        }
    }
    // t[1][0] = 1;
    // t[1][4] = 1;
    // t[2][0] = -1;
    // t[2][4] = 1;
    // t[3][0] = -1;
    // t[3][4] = -1;
    t[1][0] = 1;
    t[1][4] = 1;
    t[2][0] = 1;
    t[2][4] = -1;
    t[3][0] = -1;
    t[3][4] = -1;
    return t;
}
// int **init_board()
// {
//     int **t = new int *[5];
//     for (int i = 0; i < 5; i++)
//     {
//         t[i] = new int[5];
//         if (i == 0)
//         {
//             for (int j = 0; j < 5; j++)
//                 t[i][j] = 1;
//             continue;
//         }
//         if (i == 4)
//         {
//             for (int j = 0; j < 5; j++)
//                 t[i][j] = -1;
//             continue;
//         }
//         for (int j = 0; j < 5; j++)
//         {
//             t[i][j] = 0;
//         }
//     }

//     // t[4][0] = 1;
//     // t[4][1] = 1;
//     // t[4][4] = 1;

//     // t[3][0] = 1;
//     // t[3][1] = 1;
//     // t[3][2] = 1;
//     // t[3][3] = -1;
//     // t[3][4] = -1;

//     // t[2][1] = 1;

//     // t[1][0] = 1;
//     // t[1][1] = 1;
//     // t[1][4] = -1;

//     // t[0][1] = 1;
//     // t[0][2] = -1;
//     // t[0][3] = -1;
//     // t[0][4] = -1;

//     t[2][4] = 1;
//     t[3][3] = 1;
//     t[4][2] = 1;
//     t[3][4] = -1;
//     t[4][4] = -1;
//     t[3][4] = -1;
//     return t;
// }

int **copy_board(int **board)
{
    int **n_b = new int *[5];
    for (int i = 0; i < 5; i++)
    {
        n_b[i] = new int[5];
        for (int j = 0; j < 5; j++)
        {
            n_b[i][j] = board[i][j];
        }
    }
    return n_b;
}
void gen_move(Position pop_start, int **board, vector<Position> &dest_list)
{
    int x = pop_start.x;
    int y = pop_start.y;
    Position dest;
    if (x + 1 < 5)
    {
        dest.x = x + 1;
        dest.y = y;
        if (board[x + 1][y] != 1 && board[x + 1][y] != -1)
        {
            //kiểm tra đích đến là trống
            dest_list.push_back(dest);
        }
    }
    if (x - 1 >= 0)
    {
        dest.x = x - 1;
        dest.y = y;
        if (board[x - 1][y] != 1 && board[x - 1][y] != -1)
        {
            dest_list.push_back(dest);
            // removeDupDest(dest_list,dest);
        }
    }
    if (y + 1 < 5)
    {
        dest.x = x;
        dest.y = y + 1;
        if (board[x][y + 1] != 1 && board[x][y + 1] != -1)
        {
            dest_list.push_back(dest);
            // removeDupDest(dest_list,dest);
        }
    }
    if (y - 1 >= 0)
    {
        dest.x = x;
        dest.y = y - 1;
        if (board[x][y - 1] != 1 && board[x][y - 1] != -1)
        {
            dest_list.push_back(dest);
            // removeDupDest(dest_list,dest);
        }
    }

    if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1))
    {
        if (x + 1 < 5 && y + 1 < 5)
        {
            dest.x = x + 1;
            dest.y = y + 1;
            if (board[x + 1][y + 1] != 1 && board[x + 1][y + 1] != -1)
            {
                dest_list.push_back(dest);
                // removeDupDest(dest_list,dest);
            }
        }
        if (x - 1 >= 0 && y - 1 >= 0)
        {
            dest.x = x - 1;
            dest.y = y - 1;
            if (board[x - 1][y - 1] != 1 && board[x - 1][y - 1] != -1)
            {
                dest_list.push_back(dest);
                // removeDupDest(dest_list,dest);
            }
        }
        if (x - 1 >= 0 && y + 1 < 5)
        {
            dest.x = x - 1;
            dest.y = y + 1;
            if (board[x - 1][y + 1] != 1 && board[x - 1][y + 1] != -1)
            {
                dest_list.push_back(dest);
                // removeDupDest(dest_list,dest);
            }
        }
        if (x + 1 < 5 && y - 1 >= 0)
        {
            dest.x = x + 1;
            dest.y = y - 1;
            if (board[x + 1][y - 1] != 1 && board[x + 1][y - 1] != -1)
            {
                dest_list.push_back(dest);
                // removeDupDest(dest_list,dest);
            }
        }
    }
    // return dest_list;
};
vector<Position> ganh(int **board, Move m, int player)
{
    vector<Position> ganhList;
    int destX = m.pos_end.x;
    int destY = m.pos_end.y;

    if (destX - 1 >= 0 && destX + 1 < 5)
    {
        if (board[destX - 1][destY] == -player && board[destX + 1][destY] == -player)
        {
            //check 2 bên
            ganhList.push_back(Position(destX - 1, destY));
            ganhList.push_back(Position(destX + 1, destY));
        }
    }
    if (destY - 1 >= 0 && destY + 1 < 5)
    {
        if (board[destX][destY - 1] == -player && board[destX][destY + 1] == -player)
        {
            //check trên dưới
            ganhList.push_back(Position(destX, destY - 1));
            ganhList.push_back(Position(destX, destY + 1));
        }
    }

    if ((destX % 2 == 0 && destY % 2 == 0) || (destX % 2 == 1 && destY % 2 == 1))
    {
        if (destX - 1 >= 0 && destY - 1 >= 0 && destX + 1 < 5 && destY + 1 < 5)
        {
            if (board[destX - 1][destY - 1] == -player && board[destX + 1][destY + 1] == -player)
            {
                //check đường chéo phải
                ganhList.push_back(Position(destX - 1, destY - 1));
                ganhList.push_back(Position(destX + 1, destY + 1));
            }
        }
        if (destX + 1 < 5 && destY - 1 >= 0 && destX - 1 >= 0 && destY + 1 < 5)
        {
            if (board[destX - 1][destY + 1] == -player && board[destX + 1][destY - 1] == -player)
            {
                //check đường chéo trái
                ganhList.push_back(Position(destX - 1, destY + 1));
                ganhList.push_back(Position(destX + 1, destY - 1));
            }
        }
    }
    return ganhList;
};
vector<Position> DSlienKe(Position pos, int **board, int neighbour)
{

    int destX = pos.x;
    int destY = pos.y;
    vector<Position> neighbourList;
    // check dưới
    if (destX - 1 >= 0)
    {
        if (board[destX - 1][destY] == neighbour)
        {
            neighbourList.push_back(Position(destX - 1, destY));
        }
    }
    //check trên
    if (destX + 1 < 5)
    {
        if (board[destX + 1][destY] == neighbour)
        {
            neighbourList.push_back(Position(destX + 1, destY));
        }
    }
    //check trái
    if (destY - 1 >= 0)
    {
        if (board[destX][destY - 1] == neighbour)
        {
            neighbourList.push_back(Position(destX, destY - 1));
        }
    }
    //check phải
    if (destY + 1 < 5)
    {
        if (board[destX][destY + 1] == neighbour)
        {
            neighbourList.push_back(Position(destX, destY + 1));
        }
    }
    if ((destX % 2 == 0 && destY % 2 == 0) || (destX % 2 == 1 && destY % 2 == 1))
    {
        //check dưới phải
        if (destX - 1 >= 0 && destY + 1 < 5)
        {
            if (board[destX - 1][destY + 1] == neighbour)
            {
                neighbourList.push_back(Position(destX - 1, destY + 1));
            }
        }
        //check trên phải
        if (destX + 1 < 5 && destY + 1 < 5)
        {
            if (board[destX + 1][destY + 1] == neighbour)
            {
                neighbourList.push_back(Position(destX + 1, destY + 1));
            }
        }
        //check dưới trái
        if (destX - 1 >= 0 && destY - 1 >= 0)
        {
            if (board[destX - 1][destY - 1] == neighbour)
            {
                neighbourList.push_back(Position(destX - 1, destY - 1));
            }
        }
        //check trên trái
        if (destX + 1 < 5 && destY - 1 >= 0)
        {
            if (board[destX + 1][destY - 1] == neighbour)
            {
                neighbourList.push_back(Position(destX + 1, destY - 1));
            }
        }
    }
    return neighbourList;
}
void checkVay(Position quanDich, int visited[][5], int **board, bool &flag, vector<Position> &DSvayCheck)
{
    int x = quanDich.x;
    int y = quanDich.y;
    // cout << "board[i][j]: " << board[x][y] << " " << x << " " << y << " ";
    visited[x][y] = 1;
    vector<Position> dongDoi;
    vector<Position> empty_Pos;
    DSvayCheck.push_back(quanDich);
    dongDoi = DSlienKe(quanDich, board, board[x][y]);
    // cout << "dongDoi: " << dongDoi.size() << endl;
    empty_Pos = DSlienKe(quanDich, board, 0);
    if (dongDoi.empty() && empty_Pos.empty())
    {
        //xung quanh không có đồng đội cũng ko có ô trống
        //suy ra chỉ toàn quân địch
    }
    else if (!empty_Pos.empty())
    { // có ô trống có nghĩa là ko thể vây được
        flag = true;
    }

    vector<Position>::iterator i;
    i = dongDoi.begin();
    for (; i != dongDoi.end(); ++i)
    {
        Position xy = *i;
        if (visited[xy.x][xy.y] == 1)
        {
            continue;
        }
        else
        {
            checkVay(xy, visited, board, flag, DSvayCheck);
        }
        // if (flag)
        // {
        //     DSvayCheck.clear();
        //     return;
        // }
    }

    return;
}
vector<Position> vay(int **board, Move m, int player)
{
    vector<Position> vayList;
    vector<Position> neighbourList;
    vector<Position> DSvayTotal;
    vector<Position> DSvayCheck;
    vector<Position> ganhList;
    bool flag;
    int **nextBoard = copy_board(board);
    ganhList = ganh(board, m, player);
    if (!ganhList.empty())
    {
        changeBoard(nextBoard, ganhList, player);
    }
    // cout<<"ganhList: "<<ganhList.size()<<endl;
    ganhList.push_back(m.pos_end);
    vector<Position> neighForEach;
    vector<Position>::iterator f;
    // print_board(nextBoard);
    f = ganhList.begin();
    for (; f != ganhList.end(); ++f)
    {
        Position xy;
        xy = *f;
        neighForEach = DSlienKe(xy, nextBoard, -player);

        if (!neighForEach.empty())
        {
            neighbourList.insert(neighbourList.end(), neighForEach.begin(), neighForEach.end());
            //appending neighbourList
        }
    }
    // ganhList la danh sách các ví trí cần kiểm tra
    // neighbourList = DSlienKe(m.pos_end, board, -player);
    // trả về danh sách các đối thủ liền kề
    // cout << "neighForEach Size: " << neighbourList.size() << endl;
    int visited[5][5] = {0};
    vector<Position>::iterator i;
    i = neighbourList.begin();
    // cout<<"DS: "<<neighbourList.size()<<endl;
    for (; i != neighbourList.end(); ++i)
    {
        Position xy = *i;
        if (visited[xy.x][xy.y] == 1)
        {
            continue;
        }
        // cout<<"hel;lo"<<" "<<endl;
        flag = false;
        checkVay(*i, visited, nextBoard, flag, DSvayCheck);
        if (!flag)
        {
            if (!DSvayCheck.empty())
            {
                // cout << "hello";
                DSvayTotal.insert(DSvayTotal.end(), DSvayCheck.begin(), DSvayCheck.end());
            }
        }
        DSvayCheck.clear();
    }
    for (int i = 0; i < 5; i++)
    {
        delete[] nextBoard[i];
    }
    // nextBoard = nullptr;
    // delete nextBoard;

    return DSvayTotal;
};

vector<Move> bay_or_mo(int **current_board, int **previous_board, int player)
{
    // vector<Move> moveList = get_valid_moves(current_board,player);
    // int destX = m.pos_end.x;
    // int destY = m.pos_end.y;
    bool flagTrap = false;
    int num1Prev = 0;
    int num1Curr = 0;

    vector<Position> mayBeTrap;
    vector<Move> moveList;
    if (previous_board == nullptr || current_board == nullptr)
        return moveList;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {

            if (current_board[i][j] == 1)
            {

                num1Curr++;
            }
            if (previous_board[i][j] == 1)
            {
                num1Prev++;
            }
            // cout << 213;
            if (previous_board[i][j] == -player && current_board[i][j] != -player)
            {
                mayBeTrap.push_back(Position(i, j));
            }
            if (current_board[i][j] == player)
            {
                vector<Position> destList;
                Position pos_start = Position(i, j);
                gen_move(pos_start, current_board, destList);
                if (destList.size() != 0)
                {
                    vector<Position>::iterator i = destList.begin();
                    for (; i != destList.end(); ++i)
                    {
                        Move movePoint = Move(pos_start, *i);
                        moveList.push_back(movePoint);
                    }
                }
            }
        }
    }
    // đếm số quân của mỗi bên ở pre và current , nếu có thay đổi thì nước đi trước đó có ăn quân
    // ==> không sinh ra bẫy
    // cout<<"may be trap: "<<mayBeTrap.size()<<endl;
    vector<Position> trapList;
    if (num1Curr == num1Prev)
    {
        vector<Position>::iterator i;
        i = mayBeTrap.begin();
        Position pos;
        // num1Curr == num1Prev nước đi không ăn quân
        // previous_board[destX][destY] == -player / ví trí bẫy phải là ví trí trước của quân định
        // check gánh:
        int destX, destY;
        for (; i != mayBeTrap.end(); ++i)
        {
            pos = *i;
            destX = pos.x;
            destY = pos.y;
            if (destX - 1 >= 0 && destX + 1 < 5)
            { // check trên dưới
                if (current_board[destX - 1][destY] == -player && current_board[destX + 1][destY] == -player)
                {
                    trapList.push_back(Position(destX, destY));
                    continue;
                }
            }
            if (destY - 1 >= 0 && destY + 1 < 5)
            {
                //check trái phải
                if (current_board[destX][destY - 1] == -player && current_board[destX][destY + 1] == -player)
                {
                    trapList.push_back(Position(destX, destY));
                    continue;
                }
            }

            if ((destX % 2 == 0 && destY % 2 == 0) || (destX % 2 == 1 && destY % 2 == 1))
            {
                //check chéo phải
                if (destX - 1 >= 0 && destY - 1 >= 0 && destX + 1 < 5 && destY + 1 < 5)
                {
                    if (current_board[destX - 1][destY - 1] == -player && current_board[destX + 1][destY + 1] == -player)
                    {
                        trapList.push_back(Position(destX, destY));
                        continue;
                    }
                }
                if (destX - 1 >= 0 && destY + 1 < 5 && destX + 1 < 5 && destY - 1 >= 0)
                {
                    //check chéo trái
                    if (current_board[destX - 1][destY + 1] == -player && current_board[destX + 1][destY - 1] == -player)
                    {
                        trapList.push_back(Position(destX, destY));
                        continue;
                    }
                }
            }
        }
    }

    // vector<Move> checkTrap;
    // Move trapMove;
    vector<Move>::iterator i;
    vector<Position>::iterator j;
    vector<Move> forceMove;
    // cout<<"trap list: "<<trapList.size()<<endl;
    for (j = trapList.begin(); j != trapList.end(); ++j)
    {
        for (i = moveList.begin(); i != moveList.end(); ++i)
        {
            Position des = *j;
            Move checkMove = *i;
            if (des.x == checkMove.pos_end.x && des.y == checkMove.pos_end.y)
            {
                forceMove.push_back(checkMove);
            }
        }
    }
    return forceMove;
};

vector<Move> get_valid_moves(int **current_board, int **previous_board, int player)
{
    vector<Move> moveList;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (current_board[i][j] == player)
            {
                vector<Position> destList;
                Position pos_start = Position(i, j);
                gen_move(pos_start, current_board, destList);
                if (destList.size() != 0)
                {
                    vector<Position>::iterator i = destList.begin();
                    for (; i != destList.end(); ++i)
                    {
                        Move movePoint = Move(pos_start, *i);
                        moveList.push_back(movePoint);
                    }
                }
            }
        }
    }

    vector<Move> forceMove = bay_or_mo(current_board, previous_board, player);
    // cout<<"force Move Size: "<<forceMove.size()<<endl;
    if (forceMove.empty())
    {
        return moveList;
    }
    return forceMove;
};

void act_move(int **current_board, Move m, int player)
{
    int destX = m.pos_end.x;
    int destY = m.pos_end.y;
    int srcX = m.pos_start.x;
    int srcY = m.pos_start.y;
    ///////////// make move
    current_board[srcX][srcY] = 0;
    current_board[destX][destY] = player;
    /////////////////////
    vector<Position> ganhList = ganh(current_board, m, player);
    // cout << "ganh list: " << ganhList.size() << endl;
    vector<Position> vayList = vay(current_board, m, player);
    // cout << "vay: " << vayList.size() << endl;
    ganhList.insert(ganhList.end(), vayList.begin(), vayList.end());
    // gom lại tất cả các quân ăn được vào 1 danh sách
    int ganhListSize = ganhList.size();
    ////////////////// make change
    // cout << "ganhListSize: " << ganhListSize << endl;
    changeBoard(current_board, ganhList, player);
    return;
};
int countDie(int **board, int player)
{
    int count = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (board[i][j] == player)
            {
                count++;
            }
        }
    }
    return count;
}
class AI
{
private:
    clock_t start = clock();

public:
    bool timeOut()
    {
        clock_t end = clock();
        double totalTime = double(end - start) / double(CLOCKS_PER_SEC);
        if (totalTime > 1)
            // chuan totalTime >0.7 or nho hon 1 xiu
            return true;
        return false;
    }
    vector<Move> alphaBeteAI(int **current_board, int **pre_board, int player)
    {
        int bestValue;
        if (player == 1)
        {
            bestValue = -99999;
        }
        else
        {
            bestValue = 99999;
        }
        int beta = 99999;
        vector<Move> bestMoves;
        vector<Move> movesList = get_valid_moves(current_board, pre_board, player);
        //
        int doiThu = demQuan(current_board, -player);
        if (doiThu == 1)
        {
            Position DTpos = viTriDoiThu(current_board,-player);
            vector<Move>::iterator i = movesList.begin();
            vector<Move> newMovesList;
            for (; i != movesList.end(); ++i)
            {
                Move checkMove = *i;
                if ((checkMove.pos_start.x <= (DTpos.x+2) && checkMove.pos_start.x >= (DTpos.x-2)) && (checkMove.pos_start.y <= (DTpos.y+2) && checkMove.pos_start.y >= (DTpos.y-2))){
                    newMovesList.push_back(checkMove);
                }
            }
            if(!newMovesList.empty()){
                movesList = newMovesList;
            }
        }

        //
        if (movesList.empty())
        {
            return bestMoves;
        }
        int numOfMove = movesList.size();
        if (numOfMove == 1)
        {
            return movesList;
        }
        int depth = 1;
        vector<Move>::iterator i = movesList.begin();
        int **newBoard;
        int value;
        // double totalTime = 0;
        vector<int> bestValueList;

        while (!timeOut())
        {
            // cout << numOfMove << endl;

            i = movesList.begin();

            for (; i != movesList.end(); ++i)
            {
                newBoard = copy_board(current_board);
                act_move(newBoard, *i, player);
                if (player == 1)
                {
                    value = get_min(newBoard, current_board, bestValue, beta, depth - 1, -player);
                    // newBoard = nullptr;
                    // delete newBoard;
                    for (int i = 0; i < 5; i++)
                    {
                        delete[] newBoard[i];
                    }

                    if (value >= bestValue)
                    {
                        bestValue = value;
                        bestMoves.push_back(*i);
                        bestValueList.push_back(value);
                    }
                    if (value > 9999)
                    {
                        bestMoves.clear();
                        bestMoves.push_back(*i);
                        return bestMoves;
                    }
                }
                else
                {

                    value = get_max(newBoard, current_board, bestValue, beta, depth - 1, -player);
                    // newBoard = nullptr;
                    // delete newBoard;
                    for (int i = 0; i < 5; i++)
                    {
                        delete[] newBoard[i];
                    }
                    if (value <= bestValue)
                    {
                        bestValue = value;
                        bestMoves.push_back(*i);
                        bestValueList.push_back(value);
                    }
                    if (value < -9999)
                    {
                        bestMoves.clear();
                        bestMoves.push_back(*i);
                        return bestMoves;
                    }
                }
            }
            depth += 1;
        }

        i = bestMoves.begin();
        vector<int>::iterator j = bestValueList.begin();
        vector<Move> chooseBestMove;
        for (; i != bestMoves.end(); ++i)
        {
            if (*j == bestValue)
            {
                chooseBestMove.push_back(*i);
            }
            ++j;
        }
        // cout << "bestValue: " << bestValue << endl;
        return chooseBestMove;
    }
    int get_min(int **current_board, int **pre_board, int alpha, int beta, int depth, int player)
    {
        if (depth == 0)
        {
            return getValue(current_board, pre_board, -player);
        }
        int value = 99999;
        int **newBoard;
        int getMax;
        int soQuanAn;
        vector<Move> movesList = get_valid_moves(current_board, pre_board, player);
        vector<Move>::iterator i = movesList.begin();
        for (; i != movesList.end(); ++i)
        {
            newBoard = copy_board(current_board);
            act_move(newBoard, *i, player);
            soQuanAn = anQuan(player, newBoard, current_board) * player;
            getMax = get_max(newBoard, current_board, alpha, beta, depth - 1, -player);
            getMax = soQuanAn + getMax;
            // newBoard = nullptr;
            // delete newBoard;
            for (int i = 0; i < 5; i++)
            {
                delete[] newBoard[i];
            }
            if (value > getMax)
            {
                value = getMax;
            }
            if (value <= alpha)
            {
                return value;
            }
            if (beta > value)
            {
                beta = value;
            }
            if (timeOut())
            {
                break;
            }
        }
        return value;
    }
    int get_max(int **current_board, int **pre_board, int alpha, int beta, int depth, int player)
    {

        if (depth == 0)
        {
            return getValue(current_board, pre_board, -player);
        }
        int value = -99999;
        int **newBoard;
        int getMin;
        int soQuanAn;
        vector<Move> movesList = get_valid_moves(current_board, pre_board, player);
        vector<Move>::iterator i = movesList.begin();
        for (; i != movesList.end(); ++i)
        {
            newBoard = copy_board(current_board);
            act_move(newBoard, *i, player);
            soQuanAn = anQuan(player, newBoard, current_board) * player;
            getMin = get_min(newBoard, current_board, alpha, beta, depth - 1, -player);
            getMin = soQuanAn + getMin;

            // newBoard = nullptr;
            // delete newBoard;
            for (int i = 0; i < 5; i++)
            {
                delete[] newBoard[i];
            }
            if (value < getMin)
            {
                value = getMin;
            }
            if (value >= beta)
            {
                return value;
            }
            if (beta < value)
            {
                beta = value;
            }
            if (timeOut())
            {
                break;
            }
        }
        return value;
    }
    int getValue(int **current_board, int **pre_board, int player)
    {
        int quanX = demQuan(current_board, 1);
        int quan0 = demQuan(current_board, -1);
        if (player == 1)
        {
            if (quanX == 0)
            {
                return -99999;
            }
            else if (quan0 == 0)
            {
                return 99999;
            }
            return quanX - quan0;
            // return anQuan(1,current_board,pre_board);
        }
        if (player == -1)
        {
            if (quanX == 0)
            {
                return -99999;
            }
            else if (quan0 == 0)
            {
                return 99999;
            }
            return -(quan0 - quanX);
            // return (quan0 - quanX);
        }
        return 0;
    }
    int demQuan(int **board, int player)
    {
        int count = 0;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (board[i][j] == player)
                {
                    count++;
                }
            }
        }
        return count;
    }
    int anQuan(int player, int **current_board, int **pre_board)
    {
        return demQuan(current_board, player) - demQuan(pre_board, player);
    }
    Position viTriDoiThu(int **board, int player)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (board[i][j] == player)
                {
                    return Position(i,j);
                }
            }
        }
        return Position(1,2);
        //chac chan ko bao gio xay ra truong hop nay , nhung vay them vao de tranh warning
    }
};
Move select_move(int **current_board, int **previous_board, int player)
{
    AI AIchoose;
    vector<Move> finalBestMoves = AIchoose.alphaBeteAI(current_board, previous_board, player);
    srand(time(NULL));
    // vector<Move>::iterator i = finalBestMoves.begin();
    // for(;i!=finalBestMoves.end();++i){
    //      Move start = *i;
    //     cout <<"BEST MOVE: "<<"[" << start.pos_start.x << "," << start.pos_start.y << "] -> [" << start.pos_end.x << "," << start.pos_end.y << "]"<< endl;
    // }
    int index = rand() % finalBestMoves.size();
    return finalBestMoves[index];
};
string play(int first)
{
    int count = 0, limit = 70;
    int player;
    if (first == 1)
        player = 1;
    else
        player = -1;

    int **board = init_board();
    int **pre_board = nullptr;
    cout << "current board" << endl;
    print_board(board);
    while (count < limit)
    {

        count++;
        vector<Move> valid_moves = get_valid_moves(board, pre_board, player);
        /////////////////////////

        /////////////////////////
        if (valid_moves.size() != 0)
        {
            // srand(time(NULL));
            // int index = rand() % valid_moves.size();
            // Move new_move = valid_moves[index];

            //// helper ///////////////////////////////////
            if (player == -1)
            {
                vector<Move>::iterator i = valid_moves.begin();
                cout << "Number Of Moves: " << valid_moves.size() << " // player: " << player << "// count: " << count << endl;
                for (; i != valid_moves.end(); ++i)
                {
                    Move start = *i;
                    cout << "[" << start.pos_start.x << "," << start.pos_start.y << "] -> [" << start.pos_end.x << "," << start.pos_end.y << "]" << endl;
                }
                // int xSrc, ySrc, xDest, yDest;
                // cout << "Nhap x src: ";
                // cin >> xSrc;
                // cout << "Nhap y src: ";
                // cin >> ySrc;
                // cout << "Nhap x dest: ";
                // cin >> xDest;
                // cout << "Nhap y dest: ";
                // cin >> yDest;

                // Move new_move(Position(xSrc, ySrc), Position(xDest, yDest));
                // /////////////////////////////////////////////////
                // pre_board = copy_board(board);
                // // break;
                // act_move(board, new_move, player);
                // cout << "player: " << player << endl;
                // print_board(board);

                srand(time(NULL));
                int index = rand() % valid_moves.size();
                Move new_move = valid_moves[index];
                pre_board = copy_board(board);
                act_move(board, new_move, player);
                cout << "player: " << player << " count: " << count << endl;
                print_board(board);

                // Move m = select_move(board, pre_board, player);
                // cout << "best move: [" << m.pos_start.x << "," << m.pos_start.y << "] -> "
                //      << "[" << m.pos_end.x << "," << m.pos_end.y << "]" << endl;
                // pre_board = copy_board(board);
                // act_move(board, m, player);
                // cout << "player: " << player << " count: " << count << endl;
                // print_board(board);
            }
            else
            {
                Move m = select_move(board, pre_board, player);
                cout << "best move: [" << m.pos_start.x << "," << m.pos_start.y << "] -> "
                     << "[" << m.pos_end.x << "," << m.pos_end.y << "]" << endl;
                pre_board = copy_board(board);
                act_move(board, m, player);
                cout << "player: " << player << " count: " << count << endl;
                print_board(board);

                // srand(time(NULL));
                // int index = rand() % valid_moves.size();
                // Move new_move = valid_moves[index];
                // pre_board = copy_board(board);
                // act_move(board, new_move, player);
                // cout << "player: " << player << " count: " << count << endl;
                // print_board(board);
                // return 1;
            }
        }
        else
            break;
        player *= -1;
    }
    if (count == 70)
    {
        int x = countDie(board, 1);
        int o = countDie(board, -1);
        // cout << "Hoa // x: " << x << ", y: " << o << endl;
        // board = nullptr;
        // pre_board = nullptr;
        // delete board;
        // delete pre_board;
        for (int i = 0; i < 5; i++)
        {
            delete[] board[i];
            delete[] pre_board[i];
        }

        if (x > o)
            return "hoa";
        return "hoa";
    }
    // board = nullptr;
    // pre_board = nullptr;
    // delete board;
    // delete pre_board;
    for (int i = 0; i < 5; i++)
    {
        delete[] board[i];
        delete[] pre_board[i];
    }

    if (player == -1)
    {
        return "thang";
    }
    return "thua";
}

int writeFile(int i, string s)
{
    ofstream myfile;
    myfile.open("example.txt", ofstream::app);
    myfile << i << "/" << s << endl;
    myfile.close();
    return 0;
}
int main()
{
    int thang = 0;
    // for (int i = 0; i < 100; i++)
    // {
    //     thang += play(-1);
    // }
    for (int i = 0; i < 10; i++)
    {
        cout << i << endl;
        string s = play(1);
        // break;
        writeFile(i, s);
        // if (s.length() == 4)
        // {
        //     break;
        // }
        // if (s.length() == 5)
        // {
        //     thang++;
        // }
    }
    // for(int i )
    // cout << "ti le: " << play(1);;
    // play(1);
    // init_board();
    return 0;
}
