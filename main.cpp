#include<iostream> 
#include <fstream>
#include<time.h>
#include <string>
#include <vector>

std::string getWord(const std::string& filename,int index);
std::string getWord_super(std::string filename,int index);
void replaceWord(const std::string& source,std::string& target, char letter);
void displayUi(const std::string& string);
int TRIES = 50;

int main(){ 
    srand(time(NULL));
    int randomNumber = (rand() % 100)+1;
    std::string word = getWord_super("./db/sample.txt",randomNumber);//get the word from the file
    int lengthOFword = word.length();
    std::string guessedWord;

    //Not sure if using the reference would be faster here cause char datatype is too small to be effective
    for(char& c : word){
        guessedWord.append("_");
    }
    
    //ui (sort of)
    bool completed = true;
    bool shouldDisplayError = false;
    while(completed){
        if (shouldDisplayError) {
            std::cout << "Multiple chars not allowed\n";
        }
        displayUi(guessedWord);
        // There is better ways than to make gussedChar a string but this is easier for beginners
        std::string guessedChar;
        std::cout << "(" << lengthOFword << " letters)" <<"\n";
        std::getline(std::cin, guessedChar);
        if (guessedChar.length() > 1) {
            shouldDisplayError = true;
            system("cls");
            continue;
        }
        system("cls");
        int char_pos =  word.find(guessedChar);
        if(char_pos != std::string::npos){
            replaceWord(word,guessedWord,guessedChar[0]);
        }else{
            std::cout << "Try AGAIN" << "\n";
            TRIES--;
        }
        shouldDisplayError = false;
        if (guessedWord.find("_") == std::string::npos) {
            std::cout << guessedWord << "\n";
            std::cout << "You Win!!! Yay\n";
            break;
        }
        if(TRIES == 0){
            break;
        }
    }
    return 0;
}

void replaceWord(const std::string& source,std::string& target, char letter){
    if(source.length() != target.length()){
        std::cout << "source and target must have same length" << std::endl;
        return;
    }
    
    // fixed version. word.find(char) will only give the first word it sees so.
    for(int i = 0; i < source.length(); i++) {
        if (source[i] == letter) {
            target[i] = letter;
        }
    }
}
std::string getWord_super(std::string filename, int index) {
    std::vector<std::string> words;
    words.reserve(5000);
    std::ifstream inputfile(filename);
    std::string temp;
    temp.reserve(20);
    while (inputfile >> temp) {
        words.push_back(temp);
    }
    return words[index-1];
}


void displayUi(const std::string& string){
    std::cout << "Guess The Word! You Have " << TRIES << " Tries" << std::endl;
        for(char c : string){
            std::cout << c << " ";
        }
}
