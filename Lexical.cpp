#include <iostream>
#include "Lexical.h"
#include <string>
#include <vector>
#include <fstream>
using namespace std;
Lexical::Lexical(string s)
{
    Str=s;test=0;
    //ctor
}
void Lexical::readfichier()
{
    const string NomFichier("ProgrammeTest.txt");

    ofstream monFlux(NomFichier.c_str());
    if(monFlux)
    {
        monFlux <<Str<< endl;
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
    ifstream fichier("ProgrammeTest.txt");
    if(!fichier)
    {
            cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }
    else {
    string ligne; //Une variable pour stocker les lignes lues
    while(getline(fichier, ligne)) //Tant qu'on n'est pas à la fin, on lit
      {
         cout << ligne << endl;
      }
    }
}
char Lexical::lc()
{
    TUniteLexical ul;
    char car; //Une variable pour stocker les caractères du fichier
    if(Str[test]!='\0') //Tant qu'on n'est pas à la fin, on lit
    {
         car=Str[test];c=car;return car;
    }
    else{
        car='\0';
        return car;
       }
}
void Lexical::fin()
{
        TUniteLexical ul;tokens.push_back(FIN);
        ul.UL="FIN";ul.attribut=-1;cout<<"EOF"<<"\t";
        affiche(ul);
        cout<<"Tableau de motsCles : {";
        for(int i=0;i<motsCles.size()-1;i++)cout<<motsCles[i]<<", ";
        cout<<motsCles[motsCles.size()-1]<<"}";
        cout<<endl;
        cout<<"Tableau de motsReserves : {";
        for(int i=0;i<motsReserves.size()-1;i++)cout<<motsReserves[i]<<", ";
        cout<<motsReserves[motsReserves.size()-1]<<"}";
        cout<<endl;
        cout<<"Tableau des identifiants : {";
        for(int i=0;i<identifiants.size()-1;i++)cout<<identifiants[i]<<", ";
        cout<<identifiants[identifiants.size()-1]<<"}";
        cout<<endl;
}
bool Lexical::estBlanc(char cc)
{
        return (cc==' ' || cc=='\t' || cc=='\n' || cc=='\r');
}
int Lexical::getIndex(string stringToFind, vector<string> stringArray)
{
        int index = -1;
        for (int i=0;i<stringArray.size();i++) {
            if (stringArray[i]==stringToFind) {
            index = i;
            break;
            }
        }
        return index;
}
int Lexical::getIndexIdentif(string stringToFind, vector<string> stringArray)
{
        int index = -1;
        for (int i=0;i<stringArray.size();i++) {
            if (stringArray[i]==stringToFind) {
            index = i;
            break;
            }
        }
        return index;
}
int Lexical::estMotcle(string  lexeme)
{
        return getIndex(lexeme,motsCles);
}
int Lexical::estMotreserve(string lexeme)
{
        return getIndex(lexeme,motsReserves);
}
void Lexical::ULIdentif(string lexeme)
{
        TUniteLexical ul;
        int pos = getIndexIdentif(lexeme,identifiants);
        if(pos==-1){
            identifiants.push_back(lexeme);
        }
        ul.UL="IDENT";ul.attribut=getIndexIdentif(lexeme,identifiants);cout<<lexeme<<"\t";
        affiche(ul);
}
void Lexical::affiche(TUniteLexical ul1)
{
    char car;
    for(int i=0;i<ul1.UL.size();i++){car=toupper(ul1.UL[i]);cout<<car;}
    cout<<"\t\t"<<ul1.attribut<<endl;
}
void Lexical::uniteSuivante()
{
        string lexeme="";TUniteLexical ul;

        //if(c=='/0')
        while(estBlanc(c)) {c=lc();test++;}
        switch(c){

            case '+': {
                c=lc();test++;tokens.push_back(BIN_OP);
                ul.UL="BIN_OP";ul.attribut=getIndex("+",binOp);cout<<"+"<<"\t";
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }case '.': {
                c=lc();test++;tokens.push_back(PT);
                ul.UL="PT";ul.attribut=-1;cout<<"."<<"\t";
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '-':{
                c=lc();test++;tokens.push_back(BIN_OP);
                ul.UL="BIN_OP";ul.attribut=getIndex("-",binOp);cout<<"-"<<"\t";
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '<':{
                c=lc();test++;
                if(c=='='){
                    c=lc();test++;tokens.push_back(BIN_COMP);
                    ul.UL="BIN_COMP";ul.attribut=getIndex("<=",binComp);cout<<"<="<<"\t";
                }
                else{
                    tokens.push_back(BIN_COMP);ul.UL="BIN_COMP";ul.attribut=getIndex("<",binComp);cout<<"<"<<"\t";
                }
                    affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
                }
            case '>':{
                c=lc();test++;
                if(c=='='){
                    c=lc();test++;
                    tokens.push_back(BIN_COMP);ul.UL="BIN_COMP";ul.attribut=getIndex(">=",binComp);cout<<">="<<"\t";
                }
                else{
                    tokens.push_back(BIN_COMP);ul.UL="BIN_COMP";ul.attribut=getIndex(">",binComp);cout<<">"<<"\t";
                }
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '*': {
                c=lc();test++;tokens.push_back(BIN_OP);
                ul.UL="BIN_OP";ul.attribut=getIndex("*",binOp);cout<<"*"<<"\t";
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '&': {
                c=lc();test++;tokens.push_back(AND);
                ul.UL="AND";ul.attribut=-1;cout<<"&"<<"\t";
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '|': {
                c=lc();test++;tokens.push_back(OR);
                ul.UL="OR";ul.attribut=-1;cout<<"|"<<"\t";
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '/': {
                c=lc();test++;tokens.push_back(BIN_OP);
                ul.UL="BIN_OP";ul.attribut=getIndex("/",binOp);cout<<"/"<<"\t";
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '=':{
                c=lc();test++;
                if(c=='='){
                    c=lc();test++;tokens.push_back(BIN_COMP);
                    ul.UL="BIN_COMP";ul.attribut=getIndex("==",binComp);cout<<"=="<<"\t";
                }
                else{
                    tokens.push_back(AFF);ul.UL="AFF";ul.attribut=-1;cout<<"="<<"\t";
                }
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '!':{
                c=lc();test++;
                if(c=='='){
                    c=lc();test++;tokens.push_back(BIN_COMP);
                    ul.UL="BIN_COMP";ul.attribut=getIndex("=!",binComp);cout<<"!="<<"\t";
                }
                else{
                    tokens.push_back(NON);ul.UL="NON";ul.attribut=-1;cout<<"!"<<"\t";
                }
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '[':{
                c=lc();test++;tokens.push_back(CROCH_OUV);
                ul.UL="CROCH_OUV";ul.attribut=-1;cout<<"["<<"\t";
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case ']':{
                c=lc();test++;tokens.push_back(CROCH_FER);
                ul.UL="CROCH_FER";ul.attribut=-1;cout<<"]"<<"\t";
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '(':{
                c=lc();test++;tokens.push_back(PAR_OUV);
                ul.UL="PAR_OUV";ul.attribut=-1;cout<<"("<<"\t";
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case ')':{
                c=lc();test++;tokens.push_back(PAR_FER);
                ul.UL="PAR_FER";ul.attribut=-1;cout<<")"<<"\t";
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case ',':{
                c=lc();test++;tokens.push_back(VERG);
                ul.UL="VERG";ul.attribut=-1;cout<<","<<"\t";
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '{':{
                c=lc();test++;tokens.push_back(ACC_OUV);
                ul.UL="ACC_OUV";ul.attribut=-1;cout<<"{"<<"\t";
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '}':{
                c=lc();test++;tokens.push_back(ACC_FER);
                ul.UL="ACC_FER";ul.attribut=-1;cout<<"}"<<"\t";
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case ';':{
                c=lc();test++;tokens.push_back(PT_VER);
                ul.UL="PT_VER";ul.attribut=-1;cout<<";"<<"\t";
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '#':{
                c=lc();test++;tokens.push_back(COMMENT);
                ul.UL="COMMENT";ul.attribut=-1;cout<<'#'<<"\t";
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            default:
            {
                if(isdigit(c)){
                    while(isdigit(c)){
                        lexeme += c; //Aj
                        c=lc();test++;
                    }
                    tokens.push_back(NOMBRE);ul.UL="NOMBRE";ul.attribut=stoi(lexeme);cout<<lexeme<<"\t";
                    affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
                }
                else if(isalpha(c)){
                    while(isalpha(c)||isdigit(c)){
                        lexeme += c; //Aj
                        c=lc();test++;
                    }
                    int pos = estMotcle(lexeme);
                    int pos1 = estMotreserve(lexeme);
                    if(pos!=-1){
                        tokens.push_back(pos);ul.UL=motsCles[pos];ul.attribut=pos;cout<<lexeme<<"\t";
                        affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
                    }
                    if(pos1!=-1){
                        tokens.push_back(pos1);ul.UL=motsReserves[pos1];ul.attribut=pos1;cout<<lexeme<<"\t";
                        affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
                    }
                    ULIdentif(lexeme);if(c=='\0'){fin();exit(0);}else uniteSuivante();
                }
                else{
                    c=lc();test++;tokens.push_back(ERROR);
                    ul.UL="ERROR";ul.attribut=2;cout<<lexeme<<"\t";
                    affiche(ul);if(c=='\0')exit(0);uniteSuivante();
                }
}}
}
