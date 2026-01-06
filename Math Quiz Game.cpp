#include <iostream>   // Ein-/Ausgabe-Bibliothek
#include <cstdlib>    // Für rand(), srand()
#include <ctime>      // Für time()

using namespace std;

//==================== ENUM =============================

// Fragelevel
enum enQeustionsLevl
{
    EasyLevel = 1,  // Leicht
    MedLevel = 2,   // Mittel
    HardLevel = 3,  // Schwer
    Mix = 4,        // Mischung
};

// Operationstypen
enum enOperationType
{
    Add = 1,    // Addition
    Sub = 2,    // Subtraktion
    Mult = 3,   // Multiplikation
    Div = 4,    // Division
    MixOp = 5,  // Gemischte Operationen
};

//==================== STRUCT ===========================

// Struktur für eine Frage
struct stQuestion
{
    int Number1 = 0;             // Erste Zahl
    int Number2 = 0;             // Zweite Zahl

    enQeustionsLevl QuestionLevel;  // Schwierigkeitslevel
    enOperationType OperationType;  // Art der Rechenoperation

    int CorrectAnswer = 0;       // Korrekte Antwort
    int PlayerAnswer = 0;        // Antwort vom Spieler
    bool AnswerResult = false;   // Ergebnis ob richtig oder falsch
};

// Struktur für das Quiz
struct stQuizz
{
    stQuestion QuestionList[100]; // Array für bis zu 100 Fragen
    short NumberOfQuestions;      // Anzahl der Fragen

    enQeustionsLevl QuestionsLevel; // Gewähltes Level
    enOperationType OperationsType; // Gewählte Operation

    short NumberOfWrongAnswer = 0;  // Anzahl falscher Antworten
    short NumberOfRightAnswer = 0;  // Anzahl richtiger Antworten

    bool isPass = false;            // Ob der Spieler bestanden hat
};

//=================== GET / Random / Calculator ==================

// Zufallszahl von From bis To generieren
int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

// Berechnet die einfache Rechnung basierend auf Operationstyp
int SimpleCalculator(int Number1, int Number2, enOperationType OperationType)
{
    if (Number2 == 0) Number2 = 1; // Vermeidung Division durch 0

    switch (OperationType)
    {
    case enOperationType::Add: return Number1 + Number2;
    case enOperationType::Sub: return Number1 - Number2;
    case enOperationType::Mult: return Number1 * Number2;
    case enOperationType::Div: return Number1 / Number2;
    default: return Number1 + Number2;
    }
}

// Zufälligen Operationstyp zurückgeben
enOperationType GetRandomOperationType()
{
    int Op = RandomNumber(1, 4);
    return (enOperationType)Op;
}

// Gibt Symbol der Operation zurück
string GetOpTypeSymbol(enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add: return "+";
    case enOperationType::Sub: return "-";
    case enOperationType::Mult: return "*";
    case enOperationType::Div: return "/";
    default: return "?";
    }
}

// Text für Schwierigkeitslevel zurückgeben
string GetQuestionLevelText(enQeustionsLevl QuestionsLevel)
{
    string arrQuestionLevelText[4] = { "Easy" , "Med", "Hard" ,"Mix" };
    return arrQuestionLevelText[QuestionsLevel - 1];
}

// Text für Endergebnis zurückgeben
string GetFinalResultText(bool Pass)
{
    if (Pass) return "Pass :-)";
    else return "Fail :-(";
}

//=================== User Input ==================

// Anzahl der Fragen vom Spieler einlesen
short ReadHoeManyQuestion()
{
    short Number = 0;
    do
    {
        cout << "How Many Questions do you want to Answer ? ";
        cin >> Number;
    } while (Number < 1 || Number >50); // Validierung
    return Number;
}

// Level vom Spieler einlesen
enQeustionsLevl ReadQuestionsLevel()
{
    short Level;
    do
    {
        cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> Level;
    } while (Level < 1 || Level>4); // Validierung
    return (enQeustionsLevl)Level;
}

// Operationstyp vom Spieler einlesen
enOperationType ReadOperationsType()
{
    short Type;
    do
    {
        cout << "Enter Operations Type [1] Add + , [2] Sub - , [3] Mul * , [4] Div , [5] Mix ? ";
        cin >> Type;
    } while (Type < 1 || Type>5); // Validierung
    return (enOperationType)Type;
}

// Antwort vom Spieler einlesen
int ReadQuestionAnswer()
{
    int Answer = 0;
    cin >> Answer;
    return Answer;
}

//=================== Printing / Display ==================

// Bildschirm löschen und Farbe zurücksetzen
void ResetScreen()
{
    system("cls");
    system("color 0F");
}

// Begrüßung anzeigen
void WelcomeGame()
{
    cout << "\n========================================\n";
    cout << "     WELCOME TO MATH QUIZ GAME           \n";
    cout << "========================================\n";
}

// Bildschirmfarbe je nach Antwort ändern
void SetScreenColor(bool Answer)
{
    if (Answer) system("color 2F"); // Grün für richtig
    else
    {
        system("color 4F");          // Rot für falsch
        cout << "\a";                // Ton ausgeben
    }
}

// Frage auf dem Bildschirm ausgeben
void PrintTheQuestion(stQuizz& Quizz, short Q_Number)
{
    cout << "\n";
    cout << "Question [" << Q_Number + 1 << "/" << Quizz.NumberOfQuestions << "] \n\n";
    cout << Quizz.QuestionList[Q_Number].Number1 << endl;
    cout << Quizz.QuestionList[Q_Number].Number2 << " ";
    cout << GetOpTypeSymbol(Quizz.QuestionList[Q_Number].OperationType);
    cout << "\n______________" << endl;
}

// Ergebnisse des Quiz anzeigen
void PrintQuizzResults(stQuizz Quizz)
{
    cout << "\n";
    cout << "__________________________\n\n";
    cout << " Final Results: " << GetFinalResultText(Quizz.isPass);
    cout << "\n__________________________\n\n";
    cout << "Number of Question: " << Quizz.NumberOfQuestions << endl;
    cout << "Question Level    : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
    cout << "Operation Type     : " << GetOpTypeSymbol(Quizz.OperationsType) << endl;
    cout << "Number of Right Answer: " << Quizz.NumberOfRightAnswer << endl;
    cout << "Number of Wrong Answer: " << Quizz.NumberOfWrongAnswer << endl;
    cout << "________________________\n\n";
}

//=================== Question Generation ==================

// Neue Frage generieren
stQuestion GenerateQuestion(enQeustionsLevl QuestionLevel, enOperationType OpType)
{
    stQuestion Question;

    if (QuestionLevel == enQeustionsLevl::Mix)
        QuestionLevel = (enQeustionsLevl)RandomNumber(1, 3); // Zufälliges Level wählen

    if (OpType == enOperationType::MixOp)
        OpType = GetRandomOperationType(); // Zufällige Operation

    Question.OperationType = OpType;

    switch (QuestionLevel)
    {
    case enQeustionsLevl::EasyLevel:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        break;
    case enQeustionsLevl::MedLevel:
        Question.Number1 = RandomNumber(10, 20);
        Question.Number2 = RandomNumber(10, 20);
        break;
    case enQeustionsLevl::HardLevel:
        Question.Number1 = RandomNumber(20, 100);
        Question.Number2 = RandomNumber(20, 100);
        break;
    }

    Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
    Question.QuestionLevel = QuestionLevel;
    return Question;
}

// Alle Fragen für das Quiz generieren
void GenerateQuizzQuestions(stQuizz& Quizz)
{
    for (short i = 0; i < Quizz.NumberOfQuestions; i++)
        Quizz.QuestionList[i] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OperationsType);
}

//=================== Correction / Answer Checking ==================

// Antwort prüfen und Ergebnisse speichern
void CorrectTheQuestionAnswer(stQuizz& Quizz, short Q_Number)
{
    if (Quizz.QuestionList[Q_Number].PlayerAnswer != Quizz.QuestionList[Q_Number].CorrectAnswer)
    {
        Quizz.QuestionList[Q_Number].AnswerResult = false;
        Quizz.NumberOfWrongAnswer++;
        cout << "Wrong Answer :-( \n";
        cout << "The right answer is: " << Quizz.QuestionList[Q_Number].CorrectAnswer << "\n";
    }
    else
    {
        Quizz.QuestionList[Q_Number].AnswerResult = true;
        Quizz.NumberOfRightAnswer++;
        cout << "Right Answer :-) \n";
    }
    cout << endl;
    SetScreenColor(Quizz.QuestionList[Q_Number].AnswerResult);
}

// Alle Antworten durchgehen und korrigieren
void AskAndCorrectQuestionListAnswer(stQuizz& Quizz)
{
    for (short Q_Number = 0; Q_Number < Quizz.NumberOfQuestions; Q_Number++)
    {
        PrintTheQuestion(Quizz, Q_Number);
        Quizz.QuestionList[Q_Number].PlayerAnswer = ReadQuestionAnswer();
        CorrectTheQuestionAnswer(Quizz, Q_Number);
    }
    Quizz.isPass = (Quizz.NumberOfRightAnswer >= Quizz.NumberOfWrongAnswer); // Bestehenslogik
}

//=================== Game Logic ==================

// Hauptlogik für das Quiz
void PlayMathGame()
{
    stQuizz Quizz;
    Quizz.NumberOfQuestions = ReadHoeManyQuestion();
    Quizz.QuestionsLevel = ReadQuestionsLevel();
    Quizz.OperationsType = ReadOperationsType();

    GenerateQuizzQuestions(Quizz);
    AskAndCorrectQuestionListAnswer(Quizz);
    PrintQuizzResults(Quizz);
}

// Startet das Quiz und wiederholt bei Wunsch
void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        WelcomeGame();
        PlayMathGame();
        cout << endl << "Do you Want to Play Again ? Y/N ? ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

//=================== MAIN ==================

int main()
{
    srand((unsigned)time(NULL)); // Zufallsgenerator initialisieren
    StartGame();                  // Spiel starten
    return 0;
}
