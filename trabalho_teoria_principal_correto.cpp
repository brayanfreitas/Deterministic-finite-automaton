#include<iostream>
#include<cstdio>
#include<fstream>
#include<vector>
#include<string>
#include<map>
#include<set>
using namespace std;



int main()
{

int esc=0;


cout<<"---------------------- Trabalho AFD ---------------"<<endl;
cout<<"Alunos:"<<endl<<"Hiroto Sato Tanaka - 2017018111"<<endl;


system("pause");
system("cls");
do{

ifstream arq;
    string linha,inicio,estado,alfabeto,aux,t,escolha;
    vector<string> transicoes,testes,alfabetos,estados,aceitacao,x,apoio;
    vector<string>::iterator it;
    char linhas[100];
    map<int,map<int,string>> automato;
    map<char,int> palavra;
    int num=0;
    char prox,inicia, fins[100], atu,ttt;
    int atual, aceitaveis[100],m, tam_testes[100],test[100],teste,y=0,tt=0,atualfix=0;


cout<<"Entre com o nome do arquivo desejado:(Arquivo.txt) "<<endl;
cin>> escolha;
//Carrega o arquivo
    arq.open(escolha);

    if (arq.is_open()) //Abre o arquivo .txt
    {
        int i=1; //linha
        while(getline(arq,linha))
        {

            if(i==1)
                {

                    estados.push_back(linha);
                    estado =linha;



                }
            else if(i==2){
                    alfabetos.push_back(linha);
                    alfabeto =linha;

            }else if(i<=(2+estado.length()))
            {

              transicoes.push_back( linha);

            }else if(i==3+estado.length())
            {
                inicio=linha;
            }else if(i==4+estado.length())
            {
              aceitacao.push_back(linha);
              aux = linha;
            }else if(i==5+estado.length())
            {

                apoio.push_back(linha);
                ttt = apoio[0][0];
                tt=((int)ttt - '0');

            }else
            {
                testes.push_back(linha);
                t = linha;
                test[y] = t.length();
                y++;

            }

            i++;
        }

    int num_estados = estado.length();
    int num_alfabeto = alfabeto.length();

    inicia = inicio[0];
    int tam_aceitacao = aux.length();

    for( m =0; m<tam_aceitacao;m++) //Coletar os m estados de aceita�o
    {
        fins[m] = aceitacao[0][m];

    }
    int l=0;


    while(1) //garante a posi�o do estado inicial na matriz
    {
        if(inicia==estados[0][l])
        {
           // cout<<"Entrou"<<endl;

            break;

        }

        l++;
    }
    m = aux.length();
int pos =0;
      for(int g=0; g<m;g++) //garante a posi�o dos estados de aceita�o na matriz
    {
        if(fins[g]==estados[0][l])
        {
            aceitaveis[pos] = g;
            pos++;
        }


    }

   atualfix = atual = l;

    for(int d=0; d<num_alfabeto;d++) //Remapeia o alfabeto para os cabe�alhos da matriz.
    {

        palavra[alfabetos[0][d]]= d;
    }



    for(int T =0;T<tt;T++)
    {
         for(int v=0; v<50;v++)
            cout<<" ";
        cout<< "CASO DE TESTE "<<T<<": "<<endl;
        atual = atualfix;
        cout<<endl;
        for(int z=0;z<test[T];z++)
        {

           cout<<"Estado Atual :" << atual <<endl;


            cout<<"Entrada  ->"<<testes[T][z]<<endl;
            atu = transicoes[atual][palavra[testes[T][z]]];
            if(atu!='e')
            {
               atual = ((int) (atu - '0'));
                atual--;
            }
            else // caso de estado de erro
            {
                pos=-5;
            }



        }


        atual ++;
        for(int e=0; e<m;e++)
    {
        if(pos == -5)//quando houver um estado de erro, que leva para um estado que apartir dele n�o se sai mais,ou seja, � indiferente o resto da palavra.
        {
            cout<<"Entrou em estado de erro e"<<endl;
            break;
        }

        cout<<endl;
        cout<<"Comparando "<<atual<<" e " <<(int)(fins[e]-'0')<<endl;
        if((atual) == (int)(fins[e]-'0'))
        {
            cout<<"Esta palavra faz parte da linguagem!"<<endl;
            pos =-2;
            break;
        }
    }

    if(pos!=-2)
        cout<<"Esta palavra nao pertence a linaguagem"<<endl;

        pos =0;

    }
    arq.close();


    }
    else{ cout<<"N�o foi poss�vel abrir o arquivo"<<endl;} //caso o arquivo n�o exista ou de erro
    //Termina de carregar o aruivo e seus dados




//MENU
            cout<<endl<<endl<<endl;
     for(int v=0; v<150;v++)
            cout<<"-";

      for(int v=0; v<50;v++)
            cout<<" ";
            cout<<endl<<"Gostaria de rodar outro arquivo?"<<endl;
      for(int v=0; v<50;v++)
            cout<<" ";
            cout<<"-->Se SIM, apagando o ultimo resultado digite 1"<<endl;
      for(int v=0; v<50;v++)
            cout<<" ";
            cout<<"-->Se SIM, sem apagar o ultimo resultado digite 2"<<endl;
        for(int v=0; v<50;v++)
            cout<<" ";
            cout<<"-->Se NAO, digite 0"<<endl;
     for(int v=0; v<150;v++)
            cout<<"-";
            cout<<endl;

    cin>>esc;
    if(esc==1)
    {
        system("cls");
    }else if (esc==2)
    {
        esc=1;
    }


}while(esc);


system("cls");
cout<<endl;
for(int v=0; v<50;v++)
            cout<<" ";
cout<<"Obrigado pelo seu tempo!"<<endl;
for(int v=0; v<25;v++)
            cout<<endl;
return 0;


}
