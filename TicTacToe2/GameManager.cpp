#include "GameManager.h"

// Returns true if s1 is substring of s2
int isSubstring(std::string s1, std::string s2)
{
    int M = s1.length();
    int N = s2.length();

    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++) {
        int j;

        /* For current index i, check for
        pattern match */
        for (j = 0; j < M; j++)
            if (s2[i + j] != s1[j])
                break;

        if (j == M)
            return i;
    }

    return -1;
}

GameManager::GameManager()
{
    srand(time(NULL));
    game_state = GameState::idle;
    winner = CellType::empty;
    turn = -1;
    turn_count = 0;
    cursor = 0;

    filepath = "D:\\tictactoe_savedata.txt";
}

bool GameManager::LoadGameFromTxt(std::string raw_text)
{
    // TODO: Add your implementation code here.
    return false;
}


bool GameManager::SaveGameAsTxt()
{
    // TODO: Add your implementation code here.
    return false;
}


// Ngisi data player di dalam fungsi
void GameManager::AddPlayers(int count)
{
    std::string name;
    int init = count;
    while (count--) {
        std::cout << "Isi nama player baru (" << init - count << " dari " << init << "): ";
        std::cin >> name;
        player_list.push_back(Player(name, AssignCellType()));
    }
}

// Mengacak isi vector. Index vector = turn
void GameManager::RandomizeTurn()
{
    std::shuffle(std::begin(player_list), std::end(player_list), std::default_random_engine(0));
    if (game_state != GameState::idle) {
        std::cout << "Urutan giliran tidak dapat diubah jika permainan sedang berlangsung\n";
    }
    turn = rand() % player_list.size();
}


// Kalau siap main, bisa jalan
void GameManager::StartGame()
{
    IsReadyToPlay();
    if (game_state==GameState::ready) {
        game_state = GameState::playing;
        RandomizeTurn();
        GameLoop();
    }
    else
    {
        std::cout << "Game belum siap atau sedang berlangsung!\n";
    }
}


void GameManager::GameLoop()
{
    while (game_state==GameState::playing)
    {
        PlayTurn();
        NextTurn();
        SaveGameAsTxt();
    }
    AddMatchHistoryToAll();
}

void GameManager::AddMatchHistoryToAll()
{
    for (auto& player : player_list) {
        player.AddMatchHistory(GetMatchStateOf(player));
        std::cout << player.GetName() << "\n" << player.DisplayMatchHistory() << "\n\n";
    }
}

void GameManager::PlayTurn()
{
    cursor = 0;
    bool done = false;
    int clicks = 0;
    bool isAI = isSubstring("AI", player_list[turn].GetName());
    while (!done) {
        DisplayGame();
        // Jika ada AI di nama player, maka kelakuannya auto
        if (isAI) {
            AIControl(done);
        }
        else
        {
            KeyboardControl(clicks, done);
        }
        if (winner != CellType::empty) {
            done = true;
            game_state = GameState::finished;
        }
    }
}

void GameManager::AIControl(bool& done)
{
    if (!board.SetCellAt(rand() % board.Size(), player_list[turn].GetType()))
    {
        CheckWin();
        done = true;
    }
}

void GameManager::KeyboardControl(int& clicks, bool& done)
{
    if (_kbhit()) {
        clicks++;
        char ch = _getch();
        switch (ch)
        {
        case'a':
            cursor--;
            if (cursor < 0) {
                cursor = board.Size() - 1;
            }
            clicks = 0;
            break;
        case'd':
            cursor++;
            cursor %= board.Size();
            clicks = 0;
            break;
        case'x':
            if (board.SetCellAt(cursor, player_list[turn].GetType())) {
                CheckWin();
                clicks = 0;
                done = true;
            }
            break;
        default:
            if (clicks > 3) {
                std::cout << "Kontrol menggunakan a dan d untuk gerak. x untuk pilih.\n";
                clicks = 0;
            }
            break;
        }
    }
}


CellType GameManager::CheckWin()
{
    if (board.CheckDiagonal() != CellType::empty) 
    {
        winner = board.CheckDiagonal();
    }
    else if (board.CheckHorizontal() != CellType::empty)
    {
        winner = board.CheckHorizontal();
    }
    else if(board.CheckVertical() != CellType::empty)
    {
        winner = board.CheckVertical();
    }
    else if (board.IsFull())
    {
        winner = CellType::draw;
    }
    return winner;
}


// Menampilkan game ke console
void GameManager::DisplayGame()
{
    system("cls");
    std::cout << "Giliran " << player_list[turn].GetName() << "\n";
    board.DisplayBoard(cursor);
}


// Menghapus list player dan cell di board
void GameManager::ResetGame()
{
    board.ClearCells();
    turn_count = 0;
}


void GameManager::SetBoardSize(int width, int height)
{
    if (game_state == GameState::playing || game_state == GameState::finished) {
        std::cout << "Tidak bisa merubah setting ketika permainan sedang berlangsung!\n";
    }
    else if (width < 1 || height < 1)
    {
        std::cout << "Tidak bisa memasukkan nilai negatif!\n";
    }
    else
    {
        board.ClearCells();
        board.GenerateEmptyCells(width, height);
    }
}


// Mengecek apakah board size > 0, player > 0, dan turncount == 0
bool GameManager::IsReadyToPlay()
{
    if (board.Size() > 0 && player_list.size() > 0 && turn_count == 0) {
        return true;
    }
    return false;
}


void GameManager::NextTurn()
{
    turn += 1;
    turn %= player_list.size();
    turn_count++;
}


CellType GameManager::AssignCellType()
{
    const int EMPTY_VAL = 0;
    static int assigned = EMPTY_VAL + 1;
    if (game_state == GameState::finished) {
        assigned = EMPTY_VAL + 1;
    }
    if (assigned >= static_cast<int>(CellType::draw)) {
        std::cout << "Warning! jumlah player melebihi tipe cell. Player selanjutnya akan diberi tipe yang sama dengan player pertama.\n";
        assigned = EMPTY_VAL + 1;
    }
    return static_cast<CellType>(assigned++);
}


MatchState GameManager::GetMatchStateOf(Player player)
{
    if (winner != CellType::empty) {
        if (player.GetType() != winner) {
            if (winner == CellType::draw) {
                return MatchState::draw;
            }
            return MatchState::lose;
        }
        else
        {
            return MatchState::win;
        }
    }
    return MatchState::empty;
}


// Mengubah filepath save/load file. Jika tidak dispesifikasikan nama file, defaultnya saves.txt
void GameManager::SetFilepath()
{
    // TODO: Add your implementation code here.
}


void GameManager::LoadSaveFile()
{
    // Open txt file 
    std::ifstream file(filepath);
    std::string line;

    // After this attempt to open a file, we can safely use perror() only  
    // in case f.is_open() returns False.
    if (!file.is_open())
        perror(("error while opening file " + filepath).c_str());
    // Read the file via std::getline(). Rules obeyed:
    //   - first the I/O operation, then error check, then data processing
    //   - failbit and badbit prevent data processing, eofbit does not
    while (getline(file, line)) {
        ProcessLine(line);
    }
    // Only in case of set badbit we are sure that errno has been set in
    // the current context. Use perror() to print error details.
    if (file.bad())
        perror(("error while reading file " + filepath).c_str());
    file.close();
}


void GameManager::ProcessLine(std::string& line)
{

}