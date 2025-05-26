#include<iostream> 
#include <fstream>
#include<time.h>
#include <string>


std::string getWord(const std::string& filename,int index);
void replaceWord(const std::string& source,std::string& target, char letter);
void displayUi(const std::string& string);
int TRIES = 5;

int main(){ 
    srand(time(NULL));
    int randomNumber = (rand() % 100)+1;
    std::string word = getWord("./db/sample.txt",randomNumber);//get the word from the file
    int lengthOFword = word.length();
    std::string guessedWord;
    for(char c : word){
        guessedWord.append("_");
    }
    
    //ui (sort of)
    int completed = 0;
    while(!completed){
        displayUi(guessedWord);
        char guessedChar;
        std::cout << "(" << lengthOFword << " letters)" <<"\n";
        std::cin >> guessedChar;
        system("cls");
        int char_pos =  word.find(guessedChar);
        if(char_pos != std::string::npos){
            replaceWord(word,guessedWord,guessedChar);
        }else{
            std::cout << "Try AGAIN" << "\n";
            TRIES--;
        }


        if(TRIES == 0){
            completed = 1;
        }
    }
    return 0;
}

std::string getWord(const std::string& filename,int index){
    std::ifstream inputFile(filename);
    if(!inputFile.is_open()){
         std::cerr << "Error: Unable to open file '" << filename << "'" << std::endl;
        return "";
    }
    std::string line;
    int currentLine=0;
    while(currentLine < index-1 && std::getline(inputFile,line)){
        currentLine++;
    }
    if(currentLine < index-1){
        std::cout << "File Doesn't have this word in line number " << index << std::endl;
        inputFile.close();
        return "";
    }
    std::getline(inputFile,line);
    return line;
}

void replaceWord(const std::string& source,std::string& target, char letter){
    if(source.length() != target.length()){
        std::cout << "source and target must have same length" << std::endl;
        return;
    }
    for(char c:source){
        if(c == letter){
            target[source.find(c)] = letter;
        }
    }
}

void displayUi(const std::string& string){
    std::cout << "Guess The Word! You Have " << TRIES << " Tries" << std::endl;
        for(char c : string){
            std::cout << c << " ";
        }
}
