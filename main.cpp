#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale.h>
#include <algorithm>

using namespace std;

// estutura que armazena a transição: exemplo 1 -(a)-> 2; 1 -(b)-> e;
struct Transition {
    char srcState;
    char readSymbol;
    char destState;
};

// classe que define o automato;
class DFA {
private:
    vector<string> testWords; //armazena as palavras a serem testadas
    vector<Transition> transitions; // armazena as transições;
    string states; //string que armazena os estados;
    string alphabet; //string que armazena o alfabeto
    string finalStates; // string que armazena os estados finais
    string initialState; // string que armazena o estado inicial
    string testWordsNumber; // string que armazena o número de palavras a serem testadas
    int symbolsSize; // quantidade de simbolos da palavra
    int statesNumber; //número de estados

    //método privado que remove os espações contidos em string (ex): "a b c" -> "abc";
    void removeSpaces(string &text){
        text.erase(remove_if(text.begin(), text.end(), ::isspace), text.end());
    }
public:
    //construtor que inicia as variáveis inteiras;
    DFA() {
        this->statesNumber = 0;
        this->symbolsSize = 0;
    }

    //método para ler o arquivo!
    void readFile(string fileName){
        fstream file;

        file.open(fileName); 
        //tenta abrir o arquivo, caso não consiga, entra no loop até estar correto.
        while(!file.is_open()){
            cout << "Erro, arquivo inválido!"<< endl;
            cout << "Insira o nome do arquivo, ex: (afd.txt): "<< endl;
            cin  >> fileName;
            cout << endl;
            file.open(fileName);
        }

        getline(file, states); // lê a linha dos estados e armazena no atributo states;
        getline(file, alphabet);// lê a linha do alfabeto e armazena no atributo string alphabet;

        removeSpaces(states); // remove os espaços dos estados;;
        removeSpaces(alphabet); // remove os espaços do alfabeto;;

        //conta a quantidade de estados
        for(int i = 0; i < (int)(states.size()); i++) {
            statesNumber++;
        }

        //conta a quantidade de estados de simbolos
        for(int i = 0; i < (int)(alphabet.size()); i++) {
            symbolsSize++;
        }

        /*
            for externo que itera até o número de estados lendo do arquivo 
            cada transição e removendo o espaço;
            for interno que itera até o número do alfabeto e insere em cada posição
            do vetor a transição;
            Exemplo: transitions[1 -(a)-> 2 | 1 -(b)-> e | ...];            

        */
        for(int i = 0; i < statesNumber; i++){
            string actualTransition;
            getline(file, actualTransition);
            removeSpaces(actualTransition);
            for(int j = 0; j < symbolsSize; j++){
                transitions.push_back({ states[i], alphabet[j], actualTransition[j] });
            }
        }

        getline(file, initialState); //lê a linha do estado inicial e armazena no atributo initialState;
        getline(file, finalStates); //lê a linha dos estados finais e armazena no atributo finalStates;

        /* remove os espaços  */
        removeSpaces(initialState);
        removeSpaces(finalStates);

        getline(file, testWordsNumber); //lê a linha do número de palavras a serem testadas testWordsNumber;
        removeSpaces(testWordsNumber);
        /* 
            Itera até o número de palabras (convertida pra int, já que é um string)
            peguei a primeira posição da string e subrirati o valor da tabela ascii 
        */

        for(int i = 0; i < int(testWordsNumber[0] - '0') ; i++){
            string word;
            getline(file, word);
            removeSpaces(word);
            testWords.push_back(word);
        }
        //fecha o arquivo pois a leitura terminou;
        file.close();
    }

    // Método para testar a palavra
    void verifyAutomatoWords(){
        int wordsTested = 0;
        int wordsNumber = testWordsNumber[0] - '0';
        /*
            basicamente esses for vão verificar para cada palavra e cada letra da palavra
            se existe uma transição válida.
            o primeiro pega as palavras, o segundo pega cada symbolo da palabra e o terceiro testa 
            se acha uma transição para algum estado e se ele esse não é o estado de erro.
            Caso ele ache, o estado que estou verificado muda e sigo testando as transições e validando 
            na flag foundTransition. Caso eu saia da transição e a flag continue false, então não houve transição válida 
            logo a palavra não é reconhecida.
            Caso eu termine tudo e tenha transições válidas, verifico se o estado que terminou é de aceitação e a palavra é reconhecida; 
        */
        for(string testWord : testWords){
            char currentState = (char)(initialState[0]);
            for(char symbol : testWord){
                bool foundTransition = false;
                for (const Transition& transition : transitions) {
                    if (transition.srcState == currentState && transition.readSymbol == symbol && currentState != 'e') {
                        currentState = transition.destState;
                        foundTransition = true;
                        break;
                    }
                }

                if (!foundTransition || currentState == 'e') {
                    break;
                }
            }

            if(finalStates.find(currentState) != string::npos) {
                cout << "A palavra: " << testWord << " é reconhecida pelo autômato." << endl;
                wordsTested++;
            } else {
                cout << "A palavra: " << testWord << " não é reconhecida pelo autômato."<< endl;
                wordsTested++;
            }

            if(wordsTested >= wordsNumber){
                break;
            }
        }
    }
};

int main() {
    setlocale(LC_ALL,"Portuguese");
    int option;
    /*   
        menu para escolha do usuário
        ele pode inserir arquivos para teste até 
        que não queira mais e pode sair quando quiser;
    */
    do{
        cout << "Selecione uma opção:" << endl;
        cout << "1 - Verificar palavras no AFD." << endl;
        cout << "2 - Sair." << endl;
        cin >> option;

        switch(option){
            case 1:{
                DFA dfa;
                string fileName;
                cout << "Insira o nome do arquivo, ex: (afd.txt): "<< endl;
                cin  >> fileName;
                cout << endl;
                dfa.readFile(fileName);
                dfa.verifyAutomatoWords();
                system("pause");
                system("CLS");
                break;
            }
            case 2:{
                break;
            }
            default:{
                cout << endl << "Erro, opção inválida!" << endl << endl;
                system("pause");
                system("CLS");
            }
        }
    }while (option!=2);

    return 0;

}
