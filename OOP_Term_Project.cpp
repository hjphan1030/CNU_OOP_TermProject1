// CNU Object Oriented Programming - Term Project
// 202102727_한현준

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

class TextEditor{
private:
    int row, col;
    int lineIndex = 0;
    string fileName;
    string printBuffer;
    vector<char> text;
    vector<string> lines;

public:
    TextEditor(int row, int col, string fileName, string input){
        this->row = row;
        this->col = col;
        this->fileName = fileName;
        copy(input.begin(), input.end(), back_inserter(this->text));
    }

    void textToLines(int k){ // Convert vector<char> text to vector<string> lines.
        string line;
        string word;
        int index = k;
        lines.clear();
        while(index < text.size()){
            if(text[index] == '\n'){
                line += '\n';
                lines.push_back(line);
                line = "";
            }
            else if(text[index] == ' '){
                word += ' ';
                if(line.size() + word.size() <= this->col){
                    line += word;
                }
                else{
                    line += '\n';
                    lines.push_back(line);
                    line = word;
                }
                word = "";
            }
            else{
                word += text[index];
            }

            index++;
        }
        line += word;
        lines.push_back(line);
    }

    void linesToText(){// Convert vector<string> lines to vector<char> text.
        this->text.clear();
        for(string s : lines){
            for(char c : s){
                text.push_back(c);
            }
        }
    }

    void printLines(int k){
        printBuffer = "";
        for(int i = 0; i < this->row && k + i < lines.size(); i++){
            if(i < 9){
                cout << " " << i + 1  << "| " << lines[k + i];
                printBuffer += " " + to_string(i + 1) + "| " + lines[k + i];
            }
            else{
                cout << i + 1 << "| " << lines[k + i];
                printBuffer += to_string(i + 1) + "| " + lines[k + i];

            }
        }
    }

    string getPrintBuffer(){
        return printBuffer;
    }

    void saveFile(){
        linesToText();
        ofstream outputFile(this->fileName);
        for(char c : text){
            outputFile << c;
        }
        outputFile.close();
    }

    void printNextPage(){
        lineIndex += row;
        if(lineIndex > lines.size()){
            lineIndex -= row;
            throw "This is the last page!";
        }
        else{
            printLines(lineIndex);
        }
    }

    void printPreviousPage(){
        lineIndex -= row;
        if(lineIndex < 0){
            lineIndex += row;
            throw "This is the first page!";
        }
        else{
            printLines(lineIndex);
        }
    }

// 구현하지 못한 기능
    // void replaceWordAndPrint(string s1, string s2){
    //     linesToText();
    //     int indexOfS1;
    //     string text_tmp;
    //     for(char c : text){
    //         text_tmp += c;
    //     }
    //     while(indexOfS1 = text_tmp.find(s1) != string::npos){
    //         text_tmp.replace(indexOfS1, s2.length(), s2);
    //     }
    //     this->text.clear();
    //     for(char c : text_tmp){
    //         text.push_back(c);
    //     }

    //     lineIndex = 0;
    //     textToLines(lineIndex);
    //     printLines(lineIndex);
    // }
};



int main(){
    const int ROW = 20; // 20 lines
    const int COL = 75; // 75 bytes
    const string FILENAME = "test.txt";

    ifstream inputFile(FILENAME);
    string inputText;
    if(inputFile.is_open()){
        while(!inputFile.eof()){
            char c_tmp;
            inputFile.get(c_tmp);
            inputText += c_tmp;
        }
        inputText = inputText.substr(0, inputText.size() - 1);
    }
    else{
        cout << "Unable to open file." << endl;
    }
    inputFile.close();

    TextEditor editor(ROW, COL, FILENAME, inputText); // Text editor class.
    editor.textToLines(0);
    editor.printLines(0);
    
    string command;
    bool inputError = false;
    string consoleMessage = "";
    while(true){
        cout << endl;
        for(int i = 0; i<COL + 4;i++){
            cout << "-";
        }
        cout << "\nn:다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장후종료\n";
        for(int i = 0; i<COL + 4;i++){
            cout << "-";
        }
        cout << endl;
        if(inputError == false)
            consoleMessage = "(콘솔메시지)";
        cout << consoleMessage << endl;
        for(int i = 0; i<COL + 4;i++){
            cout << "-";
        }
        cout << "\n입력: ";
        cin >> command;

        int i1, i2, i3;
        string s1, s2;
        inputError = false;
        switch(command[0]){
        case 'i':
        case 'd':
        case 's':
        case 'c':
            inputError = true;
            consoleMessage = "구현하지 못하였습니다. ㅠ";
            cout << editor.getPrintBuffer();
            break;
        case 't':
            editor.saveFile();
            return 0;
        case 'n':
            if(command.size() > 1){
                inputError = true;
                consoleMessage = "Invalid input. Please try again.";
                cout << editor.getPrintBuffer();
                break;
            }
            try{
                editor.printNextPage();
            }catch(const char* msg){
                inputError = true;
                consoleMessage = msg;
                cout << editor.getPrintBuffer();
            }
            break;
        case 'p':
            if(command.size() > 1){
                inputError = true;
                consoleMessage = "Invalid input. Please try again.";
                cout << editor.getPrintBuffer();
                break;
            }
            try{
                editor.printPreviousPage();
            }catch(const char* msg){
                inputError = true;
                consoleMessage = msg;
                cout << editor.getPrintBuffer();
            }
            break;
        default:
            inputError = true;
            consoleMessage = "Invalid input. Please try again.";
            cout << editor.getPrintBuffer();
            break;
        }
    }

    return 0;
}