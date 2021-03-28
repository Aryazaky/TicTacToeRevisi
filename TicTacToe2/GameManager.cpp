#include "GameManager.h"

// Returns true if s1 is substring of s2
int isSubstring(std::string s1, std::string s2)
{
    if (s1.size() > s2.size()) {
        return -1;
    }
    /* A loop to slide pat[] one by one */
    for (int i = 0; i < (std::ptrdiff_t)s2.size() - (std::ptrdiff_t)s1.size(); i++) {
        int j;

        /* For current index i, check for
        pattern match */
        for (j = 0; j < s1.size() && j < s2.size() - 1; j++)
            if (s2[i + j] != s1[j])
                break;

        if (j == s1.length())
            return i;
    }

    return -1;
}

GameManager::GameManager()
{
    srand(time(NULL));
    G.game_state = GameState::idle;
    G.winner = CellType::empty;
    G.turn = -1;
    G.turn_count = 0;
    cursor = 0;

    filepath = "tictactoe_savedata.txt";
}


bool GameManager::SaveGameAsTxt()
{
    // Object to write in file
    std::ofstream file_obj;

    // Opening file in append mode
    file_obj.open(filepath, std::ios::app);

    // Object of class to input data in file
    GameData obj;

    // Assigning data into object
    obj = this->G;

    // Writing the object's data in file
    file_obj.write((char*)&obj, sizeof(obj));
    file_obj.close();
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
        G.player_list.push_back(Player(name, AssignCellType()));
    }
}

// Mengacak isi vector. Index vector = turn
void GameManager::RandomizeTurn()
{
    std::shuffle(std::begin(G.player_list), std::end(G.player_list), std::default_random_engine(0));
    if (G.game_state != GameState::idle) {
        std::cout << "Urutan giliran tidak dapat diubah jika permainan sedang berlangsung\n";
    }
    G.turn = rand() % G.player_list.size();
}


// Kalau siap main, bisa jalan
void GameManager::StartGame()
{
    IsReadyToPlay();
    if (G.game_state==GameState::ready) {
        G.game_state = GameState::playing;
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
    while (G.game_state==GameState::playing)
    {
        PlayTurn();
        NextTurn();
        SaveGameAsTxt();
    }
    AddMatchHistoryToAll();
}

void GameManager::AddMatchHistoryToAll()
{
    for (auto& player : G.player_list) {
        player.AddMatchHistory(GetMatchStateOf(player));
        std::cout << player.GetName() << "\n" << player.DisplayMatchHistory() << "\n\n";
    }
}

void GameManager::PlayTurn()
{
    cursor = 0;
    bool done = false;
    int clicks = 0;
    int isAI = isSubstring("_AI_", G.player_list[G.turn].GetName());
    bool disableAI = false;
    while (!done) {
        DisplayGame();
        // Jika ada AI di nama player, maka kelakuannya auto
        if (isAI >= 0 && !disableAI) {
            AIControl(done);
        }
        else
        {
            KeyboardControl(clicks, done);
        }
        if (G.winner != CellType::empty) {
            done = true;
            G.game_state = GameState::finished;
        }
    }
}

void GameManager::AIControl(bool& done)
{
    if (!G.board.SetCellAt(rand() % G.board.Size(), G.player_list[G.turn].GetType()))
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
                cursor = G.board.Size() - 1;
            }
            clicks = 0;
            break;
        case'd':
            cursor++;
            cursor %= G.board.Size();
            clicks = 0;
            break;
        case'x':
            std::cout << "G,turn=" << G.turn;
            if (G.board.SetCellAt(cursor, G.player_list[G.turn].GetType())) {
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
    if (G.board.CheckDiagonal() != CellType::empty)
    {
        G.winner = G.board.CheckDiagonal();
    }
    else if (G.board.CheckHorizontal() != CellType::empty)
    {
        G.winner = G.board.CheckHorizontal();
    }
    else if(G.board.CheckVertical() != CellType::empty)
    {
        G.winner = G.board.CheckVertical();
    }
    else if (G.board.IsFull())
    {
        G.winner = CellType::draw;
    }
    return G.winner;
}


// Menampilkan game ke console
void GameManager::DisplayGame()
{
    system("cls");
    std::cout << "AI Controls! Turn " << G.turn;
    std::cout << "Giliran " << G.player_list[G.turn].GetName() << "\n";
    G.board.DisplayBoard(cursor);
}


// Menghapus list player dan cell di board
void GameManager::ResetGame()
{
    G.board.ClearCells();
    G.turn_count = 0;
}


void GameManager::SetBoardSize(int width, int height)
{
    if (G.game_state == GameState::playing || G.game_state == GameState::finished) {
        std::cout << "Tidak bisa merubah setting ketika permainan sedang berlangsung!\n";
    }
    else if (width < 1 || height < 1)
    {
        std::cout << "Tidak bisa memasukkan nilai negatif!\n";
    }
    else
    {
        G.board.ClearCells();
        G.board.GenerateEmptyCells(width, height);
    }
}


// Mengecek apakah board size > 0, player > 0, dan turncount == 0
bool GameManager::IsReadyToPlay()
{
    if (G.board.Size() > 0 && G.player_list.size() > 0 && G.turn_count == 0) {
        G.game_state = GameState::ready;
        return true;
    }
    return false;
}


void GameManager::NextTurn()
{
    G.turn += 1;
    G.turn %= G.player_list.size();
    G.turn_count++;
}


CellType GameManager::AssignCellType()
{
    const int EMPTY_VAL = 0;
    static int assigned = EMPTY_VAL + 1;
    if (G.game_state == GameState::finished) {
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
    if (G.winner != CellType::empty) {
        if (player.GetType() != G.winner) {
            if (G.winner == CellType::draw) {
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
    std::cout << "Filepath baru: ";
    std::cin >> filepath;
}


void GameManager::LoadSaveFile()
{
    if (std::filesystem::exists(filepath)) {
        // Open txt file 
        std::ifstream file;
        std::string line;
        file.open(filepath, std::ios::in);
        GameData obj;

        // After this attempt to open a file, we can safely use perror() only  
        // in case f.is_open() returns False.
        if (!file.is_open()) {
            perror(("error while opening file " + filepath).c_str());
        }
        // Read the file via std::getline(). Rules obeyed:
        //   - first the I/O operation, then error check, then data processing
        //   - failbit and badbit prevent data processing, eofbit does not
        file.read((char*)&obj, sizeof(obj));
        this->G = obj;
        // Only in case of set badbit we are sure that errno has been set in
        // the current context. Use perror() to print error details.
        if (file.bad()) {
            perror(("error while reading file " + filepath).c_str());
        }
        file.close();
    }
    else {
        SaveGameAsTxt();
    }
}
