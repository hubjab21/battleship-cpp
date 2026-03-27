#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <random>
#include <clocale>

using namespace std;

class Board
{
public:
    int board_size = 10;
    int row_label = 1;
    int ship_count = 0;
    int hit_count = 0;
    int random_row = 0;
    int random_col = 0;
    clock_t start_time = 0, end_time = 0;
    double elapsed_time = 0;

    void set_board_size()
    {
        while ((board_size <= 9 && board_size >= 2) != true)
        {
            cout << "Enter board size in range 2 to 9: ";
            cin >> board_size;
        }
    }

    void initialize_board(vector<vector<char>> &board)
    {
        board.resize(board_size);
        for (int i = 0; i < (int)board.size(); i++)
        {
            board[i].resize(board_size);
        }

        for (int i = 0; i < (int)board.size(); i++)
        {
            for (int j = 0; j < (int)board[i].size(); j++)
            {
                board[i][j] = 35;
            }
        }
    }

    void place_ships(vector<vector<char>> &board)
    {
        for (int i = 0; i < board_size * 2; i++)
        {
            static mt19937 generator(random_device{}());
            uniform_int_distribution<int> distribution(0, board_size - 1);
            random_row = distribution(generator);
            random_col = distribution(generator);
            board[random_row][random_col] = 38;
        }
    }

    void count_ships(vector<vector<char>> &board)
    {
        for (int i = 0; i < board_size; i++)
        {
            for (int j = 0; j < board_size; j++)
            {
                if (board[i][j] == 38)
                {
                    ship_count++;
                }
            }
        }
    }

    void attack_position(vector<vector<char>> &board)
    {
        int x, y;

        cout << endl;
        cout << "Ships remaining to find: " << ship_count - hit_count << ". Enter position x y: ";
        cin >> y >> x;

	#ifdef _WIN32
        	system("cls");
	#else
        	system("clear");
	#endif

        if (x == 0 || y == 0)
        {
            cout << "Enter valid position (not 0 0)." << endl << endl;
        }
        else if (x > board_size || y > board_size)
        {
            cout << "Enter position within board size." << endl << endl;
        }
        else
        {
            x--;
            y--;

            if (board[x][y] == 38)
            {
                cout << "Hit!" << endl;
                board[x][y] = 36;
            }
            else if (((x >= 0 && x < board_size) && (y < board_size && y >= 0)) && board[x][y] == 35)
            {
                cout << "Miss!" << endl;
                board[x][y] = 33;
            }
            else if (board[x][y] == 36 || board[x][y] == 33)
            {
                cout << "This position was already targeted." << endl;
            }
            else
            {
                cout << "Invalid position." << endl;
            }
            cout << endl;
        }
    }

    void print_board(vector<vector<char>> &board)
    {
        row_label = 1;
        for (int i = 0; i <= board_size; i++)
        {
            if (i == 0)
            {
                for (int k = 0; k <= board_size; k++)
                {
                    cout << k << " ";
                }
            }
            else
            {
                for (int j = 0; j <= board_size; j++)
                {
                    if (j == 0)
                    {
                        cout << row_label << " ";
                        row_label++;
                    }
                    else
                    {
                        if (board[i - 1][j - 1] != 38)
                        {
                            cout << board[i - 1][j - 1] << " ";
                        }
                        else
                        {
                            cout << "# ";
                        }
                    }
                }
            }

            cout << endl;
        }

        cout << endl;
    }

    void check_game_end(vector<vector<char>> &board)
    {
        if (elapsed_time == 0)
        {
            start_time = clock();
        }

        hit_count = 0;
        for (int i = 0; i < board_size; i++)
        {
            for (int j = 0; j < board_size; j++)
            {
                if (board[i][j] == 36)
                {
                    hit_count++;
                }
            }
        }

        if (ship_count == hit_count)
        {
            end_time = clock();
            elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            cout << endl
                 << "You won the game on a " << board_size << "x" << board_size
                 << " board in " << elapsed_time << " seconds." << endl;
            cout << "Congratulations!" << endl;
            exit(0);
        }

        elapsed_time++;
    }
};

int main()
{
    setlocale(LC_ALL, "");

    vector<vector<char>> board;
    Board game_board;

    game_board.set_board_size();
    game_board.initialize_board(board);
    cout << endl;
    game_board.print_board(board);
    game_board.place_ships(board);
    game_board.count_ships(board);

    while (true)
    {
        game_board.attack_position(board);
        game_board.print_board(board);
        game_board.check_game_end(board);
    }

    return 0;
}
