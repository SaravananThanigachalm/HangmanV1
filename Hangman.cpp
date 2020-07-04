#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<time.h>
#include<algorithm> 

using namespace std;

void PrintMessage(string message, bool printTop = true, bool printBottom = true){
    if (printTop){
        cout<<"+======================================================================+"<<endl; //70 = are ter 
        cout<<"|";
    }
    else{
        cout<<"|";
    }
    
    bool front = true;
    for (int i = message.length(); i < 70; i++){
        if (front){
            message = " " + message;
        }
        else{
            message = message + " ";
        }
        front = !front;        
    }
    cout<<message.c_str();
    if (printBottom){   
        cout<<"|"<<endl;
        cout<<"+======================================================================+"<<endl; //70 = are ter 
    }
    else{
        cout<<"|"<<endl;
    }
}

void Hangman(int guessCount = 0){
    if (guessCount >= 1){
        PrintMessage("|", false, false);
    }
    else{
        PrintMessage("", false, false);
    }
    if (guessCount >= 2){
        PrintMessage("|", false, false);
    }
    else{
        PrintMessage("", false, false);
    }
    if (guessCount >= 3){
        PrintMessage("O", false, false);
    }
    else{
        PrintMessage("", false, false);
    }
    if (guessCount == 4){
        PrintMessage("/  ", false, false);
    }
    if (guessCount == 5){
        PrintMessage("/| ", false, false);
    }
    if (guessCount >= 6){
        PrintMessage("/|\\", false, false);
    }
    else{
        PrintMessage("", false, false);
    }
    if (guessCount >= 7){
        PrintMessage("|", false, false);
    }
    else{
        PrintMessage("", false, false);
    }
    if (guessCount == 8){
        PrintMessage("/  ", false, false);
    }
    if (guessCount >= 9){
        PrintMessage("/ \\", false, false);
    }
    else{
        PrintMessage("", false, false);
    }
}
void PrintLetter(string input, char from, char to){
    string s;
    for (char i = from; i <= to; i++){
        if (input.find(i) == string::npos){
            s += i; 
            s += " ";
        }
        else{
            s += "  ";
        }
    }
    PrintMessage(s, false, false);
}

void PrintAvailable(string picked){
    PrintMessage("The Remaing Letters are", true, false);
    PrintLetter(picked, 'A', 'M');
    PrintLetter(picked, 'N', 'Z');
}

bool PrintWord(string word, string guessed){
    bool won = true;
    string s;
    for (int i = 0; i < word.length(); i++){
        if (guessed.find(word[i]) == string::npos){
            won = false;
            s += " _ ";
        }
        else{
            s += word[i];
            s += " ";
        }
    }
    PrintMessage(s,false);
    return won;
}

string removeSpaces(string str){ 
    str.erase(remove(str.begin(), str.end(), ' '), str.end()); 
    return str; 
} 

string LoadWord(string path){
    int count = 0;
    string word;
    vector<string> v;
    ifstream reader(path);
    if(reader.is_open()){
        while (std::getline(reader, word)){
            v.push_back(word);
        }
        int randomLine = rand() % v.size();
        word = v.at(randomLine);
        word = removeSpaces(word);
        reader.close();
    }
    return word;
}

int TriesLeft(string word, string guessed){
    int error = 0;
    for (int i = 0; i < guessed.length(); i++){
        if (word.find(guessed[i]) == string::npos){
            error++;
        }
        
    }
    return error;
}

int main(){
    srand(time(0));
    string guess, guessword;
    guessword = LoadWord("MoviesList.txt");
    int tries = 0;
    bool win = false;
    do{
        system("cls");
        PrintMessage("Welcome to the Hangman V1", true, false);
        PrintMessage("By Saravanan T", false, true);
        Hangman(tries);
        PrintAvailable(guess);
        PrintMessage("Guess the Movie", true, false);
        win = PrintWord(guessword, guess);

        if(win)
            break;
        
        char x;
        cout<<"> "; cin>>x;
        if(guess.find(x) == string::npos)
            guess += x;

        tries = TriesLeft(guessword, guess);

    } while (tries < 10);

    if(win){
        PrintMessage("Congrats! You have WON");
        cout<<endl;
    }
    else{
        PrintMessage("GAME OVER");
        cout<<endl;
        cout<<"The word is "<< guessword<<endl<<endl;
    }
    system("pause");
    getchar();
    return 0;
}