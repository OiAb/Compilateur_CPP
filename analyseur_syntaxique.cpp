#include "analyseur_syntaxique.h"
//#include "analyseur_lexical.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
analyseur_syntaxique::analyseur_syntaxique(string s)
{
    Str=s;int i;
    parcourir=0;nbErreur=0;
    //ctor
}
//ulb sciences informatique
void analyseur_syntaxique::finsyntax()
{
    int i;//cout<<motCourant<<endl;
    cout<<endl;
    if(motCourant==FIN&&nbErreur==0){cout<<"Programme syntaxiquement correct."<<endl;}
    else {cout<<"Programme syntaxiquement incorrect avec "<<nbErreur<<" erreurs."<<endl;}
    cout<<endl;
        cout<<"Tableau de tous les identifiants : {";
        for(int i=0;i<identifiants.size()-1;i++)cout<<identifiants[i]<<", ";
        cout<<identifiants[identifiants.size()-1]<<"}";
        cout<<endl;
        cout<<"Tableau des identifiants des fonctions : {";
        for(int i=0;i<identificateurs.size()-1;i++)cout<<identificateurs[i]<<", ";
        cout<<identificateurs[identificateurs.size()-1]<<"}";
        cout<<endl;
        cout<<"Tableau des variables type entier : {";
        for(int i=0;i<variables.size()-1;i++)cout<<variables[i]<<", ";
        cout<<variables[variables.size()-1]<<"}";
        cout<<endl;
        cout<<"Tableau des variables type tableau des entiers : {";
        for(int i=0;i<Variabletab.size()-1;i++)cout<<Variabletab[i]<<", ";
        cout<<Variabletab[Variabletab.size()-1]<<"}";
        cout<<endl;
        cout<<"Tableau des variables type struct : {";
        for(int i=0;i<Variablestruct.size()-1;i++)cout<<Variablestruct[i]<<", ";
        cout<<Variablestruct[Variablestruct.size()-1]<<"}";
        cout<<endl;
}
void analyseur_syntaxique::programme()
{
   motCourant=tokens[0];
   if(motCourant==5||motCourant==7)
    {
       listeDeclarations();
       listeFonctions();
    }
    else if(motCourant==IDENT)
    {
        listeFonctions();
    }
    else{nbErreur++;cout<<"Erreur"<<nbErreur<<": undefined start of program"<<endl;}
}
void analyseur_syntaxique::listeDeclarations()
{
    declaration();
    if(motCourant==PT_VER)
    {
        parcourir++;motCourant=tokens[parcourir];
        listeDeclarationsPrime();
    }
    else{nbErreur++;cout<<"Erreur"<<nbErreur<<": ; needed after global declaration "<<endl;
        /*parcourir++;motCourant=tokens[parcourir];
        listeDeclarationsPrime();*/
    }
}
void analyseur_syntaxique::listeDeclarationsPrime()
{
    if(motCourant==5||motCourant==7)
    {
        declaration();
        if(motCourant==PT_VER)
        {
        parcourir++;motCourant=tokens[parcourir];
        listeDeclarationsPrime();
        }
        else{nbErreur++;cout<<"Erreur"<<nbErreur<<": ; needed after global declaration "<<endl;}
    }
}
void analyseur_syntaxique::listeDeclarationsSimple()
{
    declarationSimple();
    if(motCourant==PT_VER)
    {
        parcourir++;motCourant=tokens[parcourir];
        listeDeclarationsSimplePrime();
    }
    else{nbErreur++;cout<<"Erreur"<<nbErreur<<": ; needed after local declaration "<<endl;}
}
void analyseur_syntaxique::listeDeclarationsSimplePrime()
{
    if(motCourant==5)
    {
        declarationSimple();
        if(motCourant==PT_VER)
        {
        parcourir++;motCourant=tokens[parcourir];
        listeDeclarationsSimplePrime();
        }
        else{nbErreur++;cout<<"Erreur"<<nbErreur<<": ; needed after local declaration "<<endl;}
    }
}
void analyseur_syntaxique::declaration()
{
    declarateurCompose();
    declarationPrime();
}
void analyseur_syntaxique::declarationPrime()
{
    if(motCourant==VERG)
    {
        parcourir++;motCourant=tokens[parcourir];
        declarateurCompose();
        declarationPrime();
    }
}
void analyseur_syntaxique::declarationSimple()
{
    declarateurSimple();
    declarationSimplePrime();
}
void analyseur_syntaxique::declarationSimplePrime()
{
    if(motCourant==VERG)
    {
        parcourir++;motCourant=tokens[parcourir];
        declarateurSimple();
        declarationSimplePrime();
    }
}
void analyseur_syntaxique::declarateurSimple()
{
    if(motCourant==5)
    {
        parcourir++;motCourant=tokens[parcourir];
        if(motCourant==VAR)variable();
        else{nbErreur++;cout<<"Erreur"<<nbErreur<<": local variable has only as type simple entier "<<endl;
        while(motCourant!=CROCH_FER){parcourir++;motCourant=tokens[parcourir];}
        parcourir++;motCourant=tokens[parcourir];
        }
    }
    else{nbErreur++;cout<<"Erreur"<<nbErreur<<": local variable has only as type simple entier "<<endl;
    while(motCourant!=ACC_FER){parcourir++;motCourant=tokens[parcourir];}
    parcourir++;motCourant=tokens[parcourir];
    }
}
void analyseur_syntaxique::declarateurCompose()
{
    if(motCourant==5)
    {
        parcourir++;motCourant=tokens[parcourir];
        declarateurComposePrime();
    }
    else if(motCourant==7)
    {
        parcourir++;motCourant=tokens[parcourir];
        variablestruct();
        if(motCourant==ACC_OUV)
        {
            parcourir++;motCourant=tokens[parcourir];
            listeDeclarationsSimple();
            if(motCourant==ACC_FER)
            {
            parcourir++;motCourant=tokens[parcourir];
            }
            else{nbErreur++;cout<<"Erreur"<<nbErreur<<"\n} needed"<<endl;}
        }
        else{nbErreur++;cout<<"Erreur"<<nbErreur<<"\n{ needed"<<endl;}
    }
    else{nbErreur++;cout<<"Erreur"<<nbErreur<<": undefined type"<<endl;}
}
void analyseur_syntaxique::declarateurComposePrime()
{
    if(motCourant==VAR)variable();
    else if(motCourant==VARTAB)
    {
    variabletab();
    if(motCourant==CROCH_OUV)
        {
            parcourir++;motCourant=tokens[parcourir];
            nombre();
            if(motCourant==CROCH_FER)
            {
            parcourir++;motCourant=tokens[parcourir];
            }
            else{nbErreur++;cout<<"Erreur"<<nbErreur<<"\n] needed"<<endl;}
        }
        else{nbErreur++;cout<<"Erreur"<<nbErreur<<"\n[ needed"<<endl;}
    }
    else{nbErreur++;cout<<"Erreur"<<nbErreur<<" declarator start undefined"<<endl;}
}
void analyseur_syntaxique::listeFonctions()
{
    listeFonctionsPrime();
        if(motCourant==2)
        {
            parcourir++;motCourant=tokens[parcourir];
            if(motCourant==PAR_OUV)
            {
              parcourir++;motCourant=tokens[parcourir];
              if(motCourant==PAR_FER)
              {
                parcourir++;motCourant=tokens[parcourir];
              }
              else {nbErreur++;cout<<"Erreur"<<nbErreur<<": ) needed for main"<<endl;/*parcourir++;motCourant=tokens[parcourir];*/}
             }
             else {nbErreur++;cout<<"Erreur"<<nbErreur<<": ( needed for main "<<endl;parcourir++;motCourant=tokens[parcourir];}
        }
        else{nbErreur++;cout<<"Erreur"<<nbErreur<<": main needed"<<endl;}
        fonctionSecond();
}
void analyseur_syntaxique::listeFonctionsPrime()
{
    if(motCourant==IDENT)
    {
        fonction();
        listeFonctionsPrime();
    }
}
void analyseur_syntaxique::fonction()
{
   if(motCourant==IDENT)
    {
        identificateur();
        if(motCourant==PAR_OUV)
        {
            parcourir++;motCourant=tokens[parcourir];
            listeParms();
            if(motCourant==PAR_FER)
            {
            parcourir++;motCourant=tokens[parcourir];
           }
           else{nbErreur++;cout<<"Erreur"<<nbErreur<<": ) function needed"<<endl;}
        }
        else{nbErreur++;cout<<"Erreur"<<nbErreur<<": ( function needed"<<endl;}
        fonctionPrime();
    }
}
void analyseur_syntaxique::fonctionPrime()
{
    if(motCourant==5)
    {
       listeDeclarationsSimple();
       bloc();
    }
    else if(motCourant==ACC_OUV)
    {
        bloc();
    }
    else{nbErreur++;cout<<"Erreur"<<nbErreur<<": undefined start of function definition"<<endl;}
}
void analyseur_syntaxique::fonctionSecond()
{
    if(motCourant==5)
    {
       listeDeclarationsSimple();
       blocmain();
    }
    else if(motCourant==ACC_OUV)
    {
        blocmain();
    }
    else{nbErreur++;cout<<"Erreur"<<nbErreur<<": undefined start of main"<<endl;}
}
void analyseur_syntaxique::listeParms()
{
    parm();
    listeParmsPrime();
}
void analyseur_syntaxique::listeParmsPrime()
{
    if(motCourant==VERG)
    {
        parcourir++;motCourant=tokens[parcourir];
        parm();
        listeParmsPrime();
    }
}
void analyseur_syntaxique::parm()
{
    if(motCourant==5)
    {
        parcourir++;motCourant=tokens[parcourir];
        if(motCourant==VAR)variable();
        else {nbErreur++;cout<<"Erreur"<<nbErreur<<": parameter has only as type simple entier "<<endl;
        while(motCourant!=CROCH_FER){parcourir++;motCourant=tokens[parcourir];}
        parcourir++;motCourant=tokens[parcourir];
        }
    }
    else{nbErreur++;cout<<"Erreur"<<nbErreur<<": parameter cannot be a struct "<<endl;
    while(motCourant!=ACC_FER){parcourir++;motCourant=tokens[parcourir];}
    parcourir++;motCourant=tokens[parcourir];
    }
}
void analyseur_syntaxique::bloc()
{
    if(motCourant==ACC_OUV)
    {
        parcourir++;motCourant=tokens[parcourir];
        listeInstructions();
        if(motCourant==ACC_FER)
        {
        parcourir++;motCourant=tokens[parcourir];
        }
        else{nbErreur++;cout<<"Erreur"<<nbErreur<<": \n} needed "<<endl;}
    }
    else{nbErreur++;cout<<"Erreur"<<nbErreur<<": \n{ needed "<<endl;}
}
void analyseur_syntaxique::blocmain()
{
    if(motCourant==ACC_OUV)
    {
        parcourir++;motCourant=tokens[parcourir];
        listeInstructions();
        if(motCourant==ACC_FER)
        {
        parcourir++;motCourant=tokens[parcourir];
        }
        else{nbErreur++;cout<<"Erreur"<<nbErreur<<": \n} needed "<<endl;}
    }
    else{nbErreur++;cout<<"Erreur"<<nbErreur<<": \n{ needed "<<endl;}
}
void analyseur_syntaxique::blocfaire()
{
    if(motCourant==ACC_OUV)
    {
        parcourir++;motCourant=tokens[parcourir];
        blocPrime();
    }
    else{nbErreur++;cout<<"Erreur"<<nbErreur<<": \n{ needed "<<endl;}
}
void analyseur_syntaxique::blocalors()
{
    if(motCourant==ACC_OUV)
    {
        parcourir++;motCourant=tokens[parcourir];
        blocPrime();
    }
    else{nbErreur++;cout<<"Erreur"<<nbErreur<<": \n{ needed "<<endl;}
}
void analyseur_syntaxique::blocPrime()
{
    if(motCourant==2||motCourant==3||motCourant==6||motCourant==VAR||motCourant==VARSTRUCT||motCourant==VARTAB)
    {
        listeInstructions();
        if(motCourant==ACC_FER){parcourir++;motCourant=tokens[parcourir];}
        else {nbErreur++;cout<<"Erreur"<<nbErreur<<": \n} needed "<<endl;}
    }
    else if(motCourant==ACC_FER){parcourir++;motCourant=tokens[parcourir];}
    else {nbErreur++;cout<<"Erreur"<<nbErreur<<": bloc content undefined "<<endl;}
}
void analyseur_syntaxique::listeInstructions()
{
    instruction();
    listeInstructionsPrime();
}
void analyseur_syntaxique::listeInstructionsPrime()
{
    if(motCourant==2||motCourant==3||motCourant==6||motCourant==1||motCourant==IDENT||motCourant==VAR||motCourant==VARSTRUCT||motCourant==VARTAB)
    {
        instruction();
        listeInstructionsPrime();
    }
}
void analyseur_syntaxique::instruction()
{
    if(motCourant==2)
    {
        selection();
    }
    else if(motCourant==3)
    {
        iteration();
    }
    else if(motCourant==6)
    {
        saut();
        if(motCourant==PT_VER)
        {
            parcourir++;motCourant=tokens[parcourir];
        }
        else {nbErreur++;cout<<"Erreur"<<nbErreur<<": ;needed after saut instruction "<<endl;}
    }
    else if(motCourant==IDENT||motCourant==1)
    {
        appel();
        if(motCourant==PT_VER)
        {
            parcourir++;motCourant=tokens[parcourir];
        }
        else {nbErreur++;cout<<"Erreur"<<nbErreur<<": ;needed after call "<<endl;}
    }
    else if(motCourant==VAR||motCourant==VARSTRUCT||motCourant==VARTAB)
    {
        affectation();
        if(motCourant==PT_VER)
        {
            parcourir++;motCourant=tokens[parcourir];
        }
        else {nbErreur++;cout<<"Erreur"<<nbErreur<<": ;needed after affectation "<<endl;}
    }
    else {nbErreur++;cout<<"Erreur"<<nbErreur<<": instruction start undefined"<<endl;}
}
void analyseur_syntaxique::iteration()
{
    if(motCourant==3)
    {
        condition();
        if(motCourant==4)
        {
            parcourir++;motCourant=tokens[parcourir];
            blocfaire();
        }
        else {nbErreur++;cout<<"Erreur"<<nbErreur<<": faire needed "<<endl;}
    }
    else {nbErreur++;cout<<"Erreur"<<nbErreur<<": tantque needed "<<endl;}
}
void analyseur_syntaxique::selection()
{
    if(motCourant==2)
    {
        condition();
        if(motCourant==1)
        {
            parcourir++;motCourant=tokens[parcourir];
            blocalors();
            selectionPrime();
        }
        else {nbErreur++;cout<<"Erreur"<<nbErreur<<": alors needed "<<endl;}
    }
    else {nbErreur++;cout<<"Erreur"<<nbErreur<<": si needed "<<endl;}
}
void analyseur_syntaxique::selectionPrime()
{
    if(motCourant==0)
    {
        parcourir++;motCourant=tokens[parcourir];
        blocfaire();
    }
}
void analyseur_syntaxique::saut()
{
   if(motCourant==6)
    {
        parcourir++;motCourant=tokens[parcourir];
        expression();
    }
    else {nbErreur++;cout<<"Erreur"<<nbErreur<<": retour needed "<<endl;}
}
void analyseur_syntaxique::affectation()
{
    if(motCourant==VAR)
    {
        variable();
        if(motCourant==AFF)
        {
          parcourir++;motCourant=tokens[parcourir];
          affectationPrime();
        }
        else {nbErreur++;cout<<"Erreur"<<nbErreur<<": = needed for affectation "<<endl;}
    }
    else if(motCourant==VARSTRUCT)
    {
        parcourir++;motCourant=tokens[parcourir];
        if(motCourant==PT)
        {
          parcourir++;motCourant=tokens[parcourir];
          variable();
          if(motCourant==AFF)
          {
            parcourir++;motCourant=tokens[parcourir];
            affectationPrime();
          }
          else {nbErreur++;cout<<"Erreur"<<nbErreur<<": = needed "<<endl;}
        }
        else {nbErreur++;cout<<"Erreur"<<nbErreur<<": . needed "<<endl;}
    }
    else if(motCourant==VARTAB)
    {
        parcourir++;motCourant=tokens[parcourir];
        if(motCourant==CROCH_OUV)
        {
          parcourir++;motCourant=tokens[parcourir];
          nombre();
          if(motCourant==CROCH_FER)
          {
            parcourir++;motCourant=tokens[parcourir];
            if(motCourant==AFF)
            {
            parcourir++;motCourant=tokens[parcourir];
            affectationPrime();
            }
            else {nbErreur++;cout<<"Erreur"<<nbErreur<<": = needed "<<endl;}
          }
          else {nbErreur++;cout<<"Erreur"<<nbErreur<<": ] needed "<<endl;}
        }
        else {nbErreur++;cout<<"Erreur"<<nbErreur<<": [ needed "<<endl;}
    }
    else {nbErreur++;cout<<"Erreur"<<nbErreur<<": affectation start undefined "<<endl;}
}
void analyseur_syntaxique::affectationPrime()
{
    if(motCourant==0)
    {
        parcourir++;motCourant=tokens[parcourir];
        if(motCourant==PAR_OUV)
        {
            parcourir++;motCourant=tokens[parcourir];
            if(motCourant==PAR_FER)
            {
              parcourir++;motCourant=tokens[parcourir];
            }
            else {nbErreur++;cout<<"Erreur"<<nbErreur<<": \n( needed"<<endl;}
        }
        else {nbErreur++;cout<<"Erreur"<<nbErreur<<": \n) needed "<<endl;}
    }
    else if(motCourant==IDENT)
    {
        appel();
    }
    else if(motCourant==VAR||motCourant==VARTAB||motCourant==VARDESTRUCT||motCourant==NOMBRE)
    {
        expression();
    }
    else {nbErreur++;cout<<"Erreur"<<nbErreur<<": affectation right side undefined "<<endl;}
}
void analyseur_syntaxique::appel()
{
    if(motCourant==IDENT)
    {
        identificateur();
       if(motCourant==PAR_OUV)
        {
           parcourir++;motCourant=tokens[parcourir];
           listeExpressions();
           if(motCourant==PAR_FER)
           {
              parcourir++;motCourant=tokens[parcourir];
           }
           else {nbErreur++;cout<<"Erreur"<<nbErreur<<": \n) needed "<<endl;}
        }
    }
    else if(motCourant==1)
    {
        parcourir++;motCourant=tokens[parcourir];
        if(motCourant==PAR_OUV)
        {
           parcourir++;motCourant=tokens[parcourir];
           expression();
           if(motCourant==PAR_FER)
           {
              parcourir++;motCourant=tokens[parcourir];
           }
           else {nbErreur++;cout<<"Erreur"<<nbErreur<<": \n) needed "<<endl;}

        }
        else {nbErreur++;cout<<"Erreur"<<nbErreur<<": \n( needed "<<endl;}
    }
    else {nbErreur++;cout<<"Erreur"<<nbErreur<<": call start undefined "<<endl;}
}
void analyseur_syntaxique::listeExpressions()
{
    expression();
    listeExpressionsPrime();
}
void analyseur_syntaxique::listeExpressionsPrime()
{
    if(motCourant==VERG)
    {
        parcourir++;motCourant=tokens[parcourir];
        expression();
        listeExpressionsPrime();
    }
}
void analyseur_syntaxique::condition()
{
    if(motCourant==NON)
    {
        parcourir++;motCourant=tokens[parcourir];
        if(motCourant==PAR_OUV)
        {
           parcourir++;motCourant=tokens[parcourir];
           expression();
           if(motCourant==PAR_FER)
           {
              parcourir++;motCourant=tokens[parcourir];
           }
           else {nbErreur++;cout<<"Erreur"<<nbErreur<<": \n) needed "<<endl;}
        }
        else {nbErreur++;cout<<"Erreur"<<nbErreur<<": \n( needed "<<endl;}
    }
    else if(motCourant==VAR)
    {
        expression();
        conditionPrime();
    }
    else {nbErreur++;cout<<"Erreur"<<nbErreur<<": condition start undefined "<<endl;}
}
void analyseur_syntaxique::conditionPrime()
{
    if(motCourant==BIN_COMP)
    {
        binaryComp();
        expression();
    }
    else if(motCourant==OR||motCourant==AND)
    {
        binaryRel();
        expression();
    }
    else {nbErreur++;cout<<"Erreur"<<nbErreur<<": condition right side expression undefined "<<endl;}
}
void analyseur_syntaxique::expression()
{
    terme();
    expressionPrime();
}
void analyseur_syntaxique::expressionPrime()
{
    if(motCourant==BIN_OP)
    {
        binaryOp();
        expression();
    }
}
void analyseur_syntaxique::terme()
{
    if(motCourant==NOMBRE)
    {
        nombre();
    }
    else if(motCourant==VAR)
    {
        variable();
    }
    else if(motCourant==VARSTRUCT)
    {
        parcourir++;motCourant=tokens[parcourir];
        if(motCourant==PT)
        {
          parcourir++;motCourant=tokens[parcourir];
          variable();
        }
        else {nbErreur++;cout<<"Erreur"<<nbErreur<<": . needed "<<endl;}
    }
    else if(motCourant==VARTAB)
    {
        parcourir++;motCourant=tokens[parcourir];
        if(motCourant==CROCH_OUV)
        {
          parcourir++;motCourant=tokens[parcourir];
          nombre();
          if(motCourant==CROCH_FER)
          {
            parcourir++;motCourant=tokens[parcourir];
          }
          else {nbErreur++;cout<<"Erreur"<<nbErreur<<": ] needed "<<endl;}
        }
        else {nbErreur++;cout<<"Erreur"<<nbErreur<<": [ needed "<<endl;}
    }
    else {nbErreur++;cout<<"Erreur"<<nbErreur<<": term start undefined "<<endl;}
}
void analyseur_syntaxique::variable()
{
    if(motCourant==VAR)
    {
      parcourir++;motCourant=tokens[parcourir];
    }
    else {nbErreur++;cout<<"Erreur"<<nbErreur<<": should be a variable started with only letters "<<endl;}
}
void analyseur_syntaxique::variablestruct()
{
    if(motCourant==VARSTRUCT)
    {
      parcourir++;motCourant=tokens[parcourir];
    }
    else {nbErreur++;cout<<"Erreur"<<nbErreur<<": should be a struct variable started with only letters "<<endl;}
}
void analyseur_syntaxique::variabletab()
{
    if(motCourant==VARTAB)
    {
      parcourir++;motCourant=tokens[parcourir];
    }
    else {nbErreur++;cout<<"Erreur"<<nbErreur<<": should be a tab variable started with only letters "<<endl;}
}
void analyseur_syntaxique::nombre()
{
    if(motCourant==NOMBRE)
    {
       parcourir++;motCourant=tokens[parcourir];
    }
    else {nbErreur++;cout<<"Erreur"<<nbErreur<<": should be a number contains only constants "<<endl;}
}
void analyseur_syntaxique::identificateur()
{
    if(motCourant==IDENT)
    {
        parcourir++;motCourant=tokens[parcourir];
    }
    else {nbErreur++;cout<<"Erreur"<<nbErreur<<": should be an identifier started with only letters "<<endl;}
}
void analyseur_syntaxique::binaryOp()
{
    if(motCourant!=BIN_OP){nbErreur++;cout<<"Erreur"<<nbErreur<<": should start with a  binary operator "<<endl;}
    else {parcourir++;motCourant=tokens[parcourir];}
}
void analyseur_syntaxique::binaryRel()
{
    if(motCourant!=AND && motCourant!=OR) {nbErreur++;cout<<"Erreur"<<nbErreur<<": should start with a  binaryRel "<<endl;}
    else {parcourir++;motCourant=tokens[parcourir];}
}

void analyseur_syntaxique::binaryComp()
{
    if(motCourant!=BIN_COMP){nbErreur++;cout<<"Erreur"<<nbErreur<<": should start with a  binary comparator "<<endl;}
    else {parcourir++;motCourant=tokens[parcourir];}
}
int analyseur_syntaxique::returntokens(int j)
{
    return tokens[j];
}
int analyseur_syntaxique::Size()
{
    return tokens.size();
}
void analyseur_syntaxique::readfichier()
{
    const string NomFichier("ProgrammeTest.txt");
    //monFlux(NomFichier.c_str());
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
char analyseur_syntaxique::lc()
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
void analyseur_syntaxique::fin()
{
        TUniteLexical ul;tokens.push_back(FIN);int j;
        ul.UL="FIN";ul.attribut=-1;
        affiche(ul);
        cout<<endl;//for(j=0;j<Size();j++)cout<<returntokens(j)<<endl;
        programme();finsyntax();cout<<endl;arbreDerivation();
 }
bool analyseur_syntaxique::estBlanc(char cc)
{
        return (cc==' ' || cc=='\t' || cc=='\n' || cc=='\r');
}
int analyseur_syntaxique::getIndex(string stringToFind, vector<string> stringArray)
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
int analyseur_syntaxique::getIndexIdentif(string stringToFind, vector<string> stringArray)
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
int analyseur_syntaxique::estMotcle(string  lexeme)
{
        return getIndex(lexeme,motsCles);
}
int analyseur_syntaxique::estMotreserve(string lexeme)
{
        return getIndex(lexeme,motsReserves);
}
void analyseur_syntaxique::Identif(char C,string s)
{
   if(C=='(')
   {
       int pos = getIndexIdentif(s,identificateurs);
       if(pos==-1)
        {
            identificateurs.push_back(s);
        }
        tokens.push_back(IDENT);
   }
   else if(C=='{')
   {
       int pos = getIndexIdentif(s,Variablestruct);
       if(pos==-1)
        {
            Variablestruct.push_back(s);
        }
        tokens.push_back(VARSTRUCT);
   }
  else if(C=='.')
   {
       int pos = getIndexIdentif(s,Variablestruct);
       if(pos==-1)
        {
            Variablestruct.push_back(s);
        }
        tokens.push_back(VARSTRUCT);
   }
   else if(C=='[')
   {
       int pos = getIndexIdentif(s,Variabletab);
       if(pos==-1)
        {
            Variabletab.push_back(s);
        }
        tokens.push_back(VARTAB);
   }
    else{
        int pos = getIndexIdentif(s,variables);
        int pos1 = getIndexIdentif(s,Variablestruct);
        int pos2 = getIndexIdentif(s,Variabletab);
       if(pos==-1/*&&pos1==-1&&pos2==-1*/)
        {
            variables.push_back(s);
        }
        tokens.push_back(VAR);
    }
}
void analyseur_syntaxique::ULIdentif(string lexeme)
{
        TUniteLexical ul;
        int pos = getIndexIdentif(lexeme,identifiants);
        if(pos==-1){
            identifiants.push_back(lexeme);
        }
        ul.UL="IDENT";ul.attribut=getIndexIdentif(lexeme,identifiants);
        affiche(ul);
}
void analyseur_syntaxique::affiche(TUniteLexical ul1){}
void analyseur_syntaxique::uniteSuivante()
{
        string lexeme="";TUniteLexical ul;

        //if(c=='/0')
        while(estBlanc(c)) {c=lc();test++;}
        switch(c){

            case '+': {
                c=lc();test++;tokens.push_back(BIN_OP);
                ul.UL="BIN_OP";ul.attribut=getIndex("+",binOp);
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '.': {
                c=lc();test++;tokens.push_back(PT);
                ul.UL="PT";ul.attribut=-1;
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '-':{
                c=lc();test++;tokens.push_back(BIN_OP);
                ul.UL="BIN_OP";ul.attribut=getIndex("-",binOp);
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '<':{
                c=lc();test++;
                if(c=='='){
                    c=lc();test++;tokens.push_back(BIN_COMP);
                    ul.UL="BIN_COMP";ul.attribut=getIndex("<=",binComp);
                }
                else{
                    tokens.push_back(BIN_COMP);ul.UL="BIN_COMP";ul.attribut=getIndex("<",binComp);
                }
                    affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
                }
            case '>':{
                c=lc();test++;
                if(c=='='){
                    c=lc();test++;
                    tokens.push_back(BIN_COMP);ul.UL="BIN_COMP";ul.attribut=getIndex(">=",binComp);
                }
                else{
                    tokens.push_back(BIN_COMP);ul.UL="BIN_COMP";ul.attribut=getIndex(">",binComp);
                }
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '*': {
                c=lc();test++;tokens.push_back(BIN_OP);
                ul.UL="BIN_OP";ul.attribut=getIndex("*",binOp);
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '&': {
                c=lc();test++;tokens.push_back(AND);
                ul.UL="AND";ul.attribut=-1;
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '|': {
                c=lc();test++;tokens.push_back(OR);
                ul.UL="OR";ul.attribut=-1;
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '/': {
                c=lc();test++;tokens.push_back(BIN_OP);
                ul.UL="BIN_OP";ul.attribut=getIndex("/",binOp);
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '=':{
                c=lc();test++;
                if(c=='='){
                    c=lc();test++;tokens.push_back(BIN_COMP);
                    ul.UL="BIN_COMP";ul.attribut=getIndex("==",binComp);
                }
                else{
                    tokens.push_back(AFF);ul.UL="AFF";ul.attribut=-1;
                }
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '!':{
                c=lc();test++;
                if(c=='='){
                    c=lc();test++;tokens.push_back(BIN_COMP);
                    ul.UL="BIN_COMP";ul.attribut=getIndex("=!",binComp);
                }
                else{
                    tokens.push_back(NON);ul.UL="NON";ul.attribut=-1;
                }
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '[':{
                c=lc();test++;tokens.push_back(CROCH_OUV);
                ul.UL="CROCH_OUV";ul.attribut=-1;
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case ']':{
                c=lc();test++;tokens.push_back(CROCH_FER);
                ul.UL="CROCH_FER";ul.attribut=-1;
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '(':{
                c=lc();test++;tokens.push_back(PAR_OUV);
                ul.UL="PAR_OUV";ul.attribut=-1;
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case ')':{
                c=lc();test++;tokens.push_back(PAR_FER);
                ul.UL="PAR_FER";ul.attribut=-1;
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case ',':{
                c=lc();test++;tokens.push_back(VERG);
                ul.UL="VERG";ul.attribut=-1;
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '{':{
                c=lc();test++;tokens.push_back(ACC_OUV);
                ul.UL="ACC_OUV";ul.attribut=-1;
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '}':{
                c=lc();test++;tokens.push_back(ACC_FER);
                ul.UL="ACC_FER";ul.attribut=-1;
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case ';':{
                c=lc();test++;tokens.push_back(PT_VER);
                ul.UL="PT_VER";ul.attribut=-1;
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '#':{
                c=lc();test++;tokens.push_back(COMMENT);
                ul.UL="COMMENT";ul.attribut=-1;
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            default:
            {
                if(isdigit(c)){
                    while(isdigit(c)){
                        lexeme += c; //Aj
                        c=lc();test++;
                    }
                    tokens.push_back(NOMBRE);ul.UL="NOMBRE";ul.attribut=stoi(lexeme);
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
                        tokens.push_back(pos);ul.UL=motsCles[pos];ul.attribut=pos;
                        affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
                    }
                    if(pos1!=-1){
                        tokens.push_back(pos1);ul.UL=motsReserves[pos1];ul.attribut=pos1;
                        affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
                    }
                    Identif(c,lexeme);ULIdentif(lexeme);if(c=='\0'){fin();exit(0);}else uniteSuivante();
                }
                else{
                    c=lc();test++;tokens.push_back(ERROR);
                    ul.UL="ERROR";ul.attribut=2;
                    affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
                }
}}
}
void analyseur_syntaxique::balise_ouvrante(std::string regle)
{
    fluxXML<< "<" << regle << ">" << endl ;
}

void analyseur_syntaxique::balise_fermante(std::string regle)
{
    fluxXML<< "</" << regle << ">" << endl ;
}

void analyseur_syntaxique::balise_unique(std::string regle)
{
    fluxXML<< "<" << regle << "/>" << endl ;
}
void analyseur_syntaxique::arbreDerivation()
{
    balise_ouvrante("Programme");
    balise_ouvrante("liste-declarations");
    balise_ouvrante("declaration");
    balise_ouvrante("declarateur-cp");
    balise_unique("entier");
    balise_ouvrante("declarateur-cp'");
    balise_ouvrante("variabletab");
    balise_ouvrante("lettre");
    balise_unique("a");
    balise_unique("..");
    balise_unique("z");
    balise_unique("A");
    balise_unique("..");
    balise_unique("Z");
    balise_fermante("lettre");
    balise_ouvrante("variable'");
    balise_ouvrante("variable''");
    balise_ouvrante("lettre");
    balise_unique("a");
    balise_unique("..");
    balise_unique("z");
    balise_unique("A");
    balise_unique("..");
    balise_unique("Z");
    balise_fermante("lettre");
    balise_ouvrante("nombre");
    balise_ouvrante("constante");
    balise_unique("0");
    balise_unique("..");
    balise_unique("9");
    balise_fermante("constante");
    balise_ouvrante("nombre'");
    balise_ouvrante("constante");
    balise_unique("0");
    balise_unique("..");
    balise_unique("9");
    balise_fermante("constante");
    balise_ouvrante("nombre'");
    balise_fermante("nombre'");
    balise_fermante("nombre'");
    balise_fermante("nombre");
    balise_fermante("variable''");
    balise_ouvrante("variable'");
    balise_fermante("variable'");
    balise_fermante("variable'");
    balise_fermante("variabletab");
    balise_unique("[");
    balise_ouvrante("nombre");
    balise_ouvrante("constante");
    balise_unique("0");
    balise_unique("..");
    balise_unique("9");
    balise_fermante("constante");
    balise_ouvrante("nombre'");
    balise_ouvrante("constante");
    balise_unique("0");
    balise_unique("..");
    balise_unique("9");
    balise_fermante("constante");
    balise_ouvrante("nombre'");
    balise_fermante("nombre'");
    balise_fermante("nombre");
    balise_unique("]");
    balise_ouvrante("variable");
    balise_ouvrante("lettre");
    balise_unique("a");
    balise_unique("..");
    balise_unique("z");
    balise_unique("A");
    balise_unique("..");
    balise_unique("Z");
    balise_fermante("lettre");
    balise_ouvrante("variable'");
    balise_ouvrante("variable''");
    balise_ouvrante("lettre");
    balise_unique("a");
    balise_unique("..");
    balise_unique("z");
    balise_unique("A");
    balise_unique("..");
    balise_unique("Z");
    balise_fermante("lettre");
    balise_ouvrante("nombre");
    balise_ouvrante("constante");
    balise_unique("0");
    balise_unique("..");
    balise_unique("9");
    balise_fermante("constante");
    balise_ouvrante("nombre'");
    balise_ouvrante("constante");
    balise_unique("0");
    balise_unique("..");
    balise_unique("9");
    balise_fermante("constante");
    balise_ouvrante("nombre'");
    balise_fermante("nombre'");
    balise_fermante("nombre'");
    balise_fermante("nombre");
    balise_fermante("variable''");
    balise_ouvrante("variable'");
    balise_fermante("variable'");
    balise_fermante("variable'");
    balise_fermante("variable");
    balise_fermante("declarateur-cp'");
    balise_unique("struct");
    balise_ouvrante("variablestruct");
    balise_ouvrante("lettre");
    balise_unique("a");
    balise_unique("..");
    balise_unique("z");
    balise_unique("A");
    balise_unique("..");
    balise_unique("Z");
    balise_fermante("lettre");
    balise_ouvrante("variable'");
    balise_ouvrante("variable''");
    balise_ouvrante("lettre");
    balise_unique("a");
    balise_unique("..");
    balise_unique("z");
    balise_unique("A");
    balise_unique("..");
    balise_unique("Z");
    balise_fermante("lettre");
    balise_ouvrante("nombre");
    balise_ouvrante("constante");
    balise_unique("0");
    balise_unique("..");
    balise_unique("9");
    balise_fermante("constante");
    balise_ouvrante("nombre'");
    balise_ouvrante("constante");
    balise_unique("0");
    balise_unique("..");
    balise_unique("9");
    balise_fermante("constante");
    balise_ouvrante("nombre'");
    balise_fermante("nombre'");
    balise_fermante("nombre'");
    balise_fermante("nombre");
    balise_fermante("variable''");
    balise_ouvrante("variable'");
    balise_fermante("variable'");
    balise_fermante("variable'");
    balise_fermante("variablestruct");
    balise_unique("{");
    balise_ouvrante("liste-declarations-sp");
    balise_ouvrante("declaration-sp");
    balise_ouvrante("declarateur-sp");
    balise_unique("entier");
    balise_ouvrante("variable");
    balise_ouvrante("lettre");
    balise_unique("a");
    balise_unique("..");
    balise_unique("z");
    balise_unique("A");
    balise_unique("..");
    balise_unique("Z");
    balise_fermante("lettre");
    balise_ouvrante("variable'");
    balise_ouvrante("variable''");
    balise_ouvrante("lettre");
    balise_unique("a");
    balise_unique("..");
    balise_unique("z");
    balise_unique("A");
    balise_unique("..");
    balise_unique("Z");
    balise_fermante("lettre");
    balise_ouvrante("nombre");
    balise_ouvrante("constante");
    balise_unique("0");
    balise_unique("..");
    balise_unique("9");
    balise_fermante("constante");
    balise_ouvrante("nombre'");
    balise_ouvrante("constante");
    balise_unique("0");
    balise_unique("..");
    balise_unique("9");
    balise_fermante("constante");
    balise_ouvrante("nombre'");
    balise_fermante("nombre'");
    balise_fermante("nombre'");
    balise_fermante("nombre");
    balise_fermante("variable''");
    balise_ouvrante("variable'");
    balise_fermante("variable'");
    balise_fermante("variable'");
    balise_fermante("variable");
    balise_fermante("declarateur-sp");
    balise_ouvrante("declaration-sp'");
    balise_unique(",");
    balise_ouvrante("declarateur-sp");
    balise_unique("entier");
    balise_ouvrante("variable");
    balise_ouvrante("lettre");
    balise_unique("a");
    balise_unique("..");
    balise_unique("z");
    balise_unique("A");
    balise_unique("..");
    balise_unique("Z");
    balise_fermante("lettre");
    balise_ouvrante("variable'");
    balise_ouvrante("variable''");
    balise_ouvrante("lettre");
    balise_unique("a");
    balise_unique("..");
    balise_unique("z");
    balise_unique("A");
    balise_unique("..");
    balise_unique("Z");
    balise_fermante("lettre");
    balise_ouvrante("nombre");
    balise_ouvrante("constante");
    balise_unique("0");
    balise_unique("..");
    balise_unique("9");
    balise_fermante("constante");
    balise_ouvrante("nombre'");
    balise_ouvrante("constante");
    balise_unique("0");
    balise_unique("..");
    balise_unique("9");
    balise_fermante("constante");
    balise_ouvrante("nombre'");
    balise_fermante("nombre'");
    balise_fermante("nombre'");
    balise_fermante("nombre");
    balise_fermante("variable''");
    balise_ouvrante("variable'");
    balise_fermante("variable'");
    balise_fermante("variable'");
    balise_fermante("variable");
    balise_fermante("declarateur-sp");
    balise_ouvrante("declaration-sp'");
    balise_fermante("declaration-sp'");
    balise_fermante("declaration-sp'");
    balise_fermante("declaration-sp");
    balise_unique(";");
    balise_ouvrante("liste-declarations-sp'");
    balise_ouvrante("declaration-sp");
    balise_fermante("declaration-sp");
    balise_unique(";");
    balise_ouvrante("liste-declarations-sp'");
    balise_fermante("liste-declarations-sp'");
    balise_fermante("liste-declarations-sp'");
    balise_fermante("liste-declarations-sp");
    balise_unique("}");
    balise_fermante("declarateur-cp");
    balise_ouvrante("declaration'");
    balise_unique(",");
    balise_ouvrante("declarateur-cp");
    balise_unique("entier");
    balise_ouvrante("declarateur-cp'");
    balise_ouvrante("variabletab");
    balise_ouvrante("lettre");
    balise_unique("a");
    balise_unique("..");
    balise_unique("z");
    balise_unique("A");
    balise_unique("..");
    balise_unique("Z");
    balise_fermante("lettre");
    balise_ouvrante("variable'");
    balise_ouvrante("variable''");
    balise_ouvrante("lettre");
    balise_unique("a");
    balise_unique("..");
    balise_unique("z");
    balise_unique("A");
    balise_unique("..");
    balise_unique("Z");
    balise_fermante("lettre");
    balise_ouvrante("nombre");
    balise_ouvrante("constante");
    balise_unique("0");
    balise_unique("..");
    balise_unique("9");
    balise_fermante("constante");
    balise_ouvrante("nombre'");
    balise_ouvrante("constante");
    balise_unique("0");
    balise_unique("..");
    balise_unique("9");
    balise_fermante("constante");
    balise_ouvrante("nombre'");
    balise_fermante("nombre'");
    balise_fermante("nombre'");
    balise_fermante("nombre");
    balise_fermante("variable''");
    balise_ouvrante("variable'");
    balise_fermante("variable'");
    balise_fermante("variable'");
    balise_fermante("variabletab");
    balise_unique("[");
    balise_ouvrante("nombre");
    balise_ouvrante("constante");
    balise_unique("0");
    balise_unique("..");
    balise_unique("9");
    balise_fermante("constante");
    balise_ouvrante("nombre'");
    balise_ouvrante("constante");
    balise_unique("0");
    balise_unique("..");
    balise_unique("9");
    balise_fermante("constante");
    balise_ouvrante("nombre'");
    balise_fermante("nombre'");
    balise_fermante("nombre");
    balise_unique("]");
    balise_ouvrante("variable");
    balise_ouvrante("lettre");
    balise_unique("a");
    balise_unique("..");
    balise_unique("z");
    balise_unique("A");
    balise_unique("..");
    balise_unique("Z");
    balise_fermante("lettre");
    balise_ouvrante("variable'");
    balise_ouvrante("variable''");
    balise_ouvrante("lettre");
    balise_unique("a");
    balise_unique("..");
    balise_unique("z");
    balise_unique("A");
    balise_unique("..");
    balise_unique("Z");
    balise_fermante("lettre");
    balise_ouvrante("nombre");
    balise_ouvrante("constante");
    balise_unique("0");
    balise_unique("..");
    balise_unique("9");
    balise_fermante("constante");
    balise_ouvrante("nombre'");
    balise_ouvrante("constante");
    balise_unique("0");
    balise_unique("..");
    balise_unique("9");
    balise_fermante("constante");
    balise_ouvrante("nombre'");
    balise_fermante("nombre'");
    balise_fermante("nombre'");
    balise_fermante("nombre");
    balise_fermante("variable''");
    balise_ouvrante("variable'");
    balise_fermante("variable'");
    balise_fermante("variable'");
    balise_fermante("variable");
    balise_fermante("declarateur-cp'");
    balise_unique("struct");
    balise_ouvrante("variablestruct");
    balise_ouvrante("lettre");
    balise_unique("a");
    balise_unique("..");
    balise_unique("z");
    balise_unique("A");
    balise_unique("..");
    balise_unique("Z");
    balise_fermante("lettre");
    balise_ouvrante("variable'");
    balise_ouvrante("variable''");
    balise_ouvrante("lettre");
    balise_unique("a");
    balise_unique("..");
    balise_unique("z");
    balise_unique("A");
    balise_unique("..");
    balise_unique("Z");
    balise_fermante("lettre");
    balise_ouvrante("nombre");
    balise_ouvrante("constante");
    balise_unique("0");
    balise_unique("..");
    balise_unique("9");
    balise_fermante("constante");
    balise_ouvrante("nombre'");
    balise_ouvrante("constante");
    balise_unique("0");
    balise_unique("..");
    balise_unique("9");
    balise_fermante("constante");
    balise_ouvrante("nombre'");
    balise_fermante("nombre'");
    balise_fermante("nombre'");
    balise_fermante("nombre");
    balise_fermante("variable''");
    balise_ouvrante("variable'");
    balise_fermante("variable'");
    balise_fermante("variable'");
    balise_fermante("variablestruct");
    balise_unique("{");
    balise_ouvrante("liste-declarations-sp");
    balise_ouvrante("declaration-sp");
    balise_ouvrante("declarateur-sp");
    balise_unique("entier");
    balise_ouvrante("variable");
    balise_ouvrante("lettre");
    balise_unique("a");
    balise_unique("..");
    balise_unique("z");
    balise_unique("A");
    balise_unique("..");
    balise_unique("Z");
    balise_fermante("lettre");
    balise_ouvrante("variable'");
    balise_ouvrante("variable''");
    balise_ouvrante("lettre");
    balise_unique("a");
    balise_unique("..");
    balise_unique("z");
    balise_unique("A");
    balise_unique("..");
    balise_unique("Z");
    balise_fermante("lettre");
    balise_ouvrante("nombre");
    balise_ouvrante("constante");
    balise_unique("0");
    balise_unique("..");
    balise_unique("9");
    balise_fermante("constante");
    balise_ouvrante("nombre'");
    balise_ouvrante("constante");
    balise_unique("0");
    balise_unique("..");
    balise_unique("9");
    balise_fermante("constante");
    balise_ouvrante("nombre'");
    balise_fermante("nombre'");
    balise_fermante("nombre'");
    balise_fermante("nombre");
    balise_fermante("variable''");
    balise_ouvrante("variable'");
    balise_fermante("variable'");
    balise_fermante("variable'");
    balise_fermante("variable");
    balise_fermante("declarateur-sp");
    balise_ouvrante("declaration-sp'");
    balise_unique(",");
    balise_ouvrante("declarateur-sp");
    balise_unique("entier");
    balise_ouvrante("variable");
    balise_ouvrante("lettre");
    balise_unique("a");
    balise_unique("..");
    balise_unique("z");
    balise_unique("A");
    balise_unique("..");
    balise_unique("Z");
    balise_fermante("lettre");
    balise_ouvrante("variable'");
    balise_ouvrante("variable''");
    balise_ouvrante("lettre");
    balise_unique("a");
    balise_unique("..");
    balise_unique("z");
    balise_unique("A");
    balise_unique("..");
    balise_unique("Z");
    balise_fermante("lettre");
    balise_ouvrante("nombre");
    balise_ouvrante("constante");
    balise_unique("0");
    balise_unique("..");
    balise_unique("9");
    balise_fermante("constante");
    balise_ouvrante("nombre'");
    balise_ouvrante("constante");
    balise_unique("0");
    balise_unique("..");
    balise_unique("9");
    balise_fermante("constante");
    balise_ouvrante("nombre'");
    balise_fermante("nombre'");
    balise_fermante("nombre'");
    balise_fermante("nombre");
    balise_fermante("variable''");
    balise_ouvrante("variable'");
    balise_fermante("variable'");
    balise_fermante("variable'");
    balise_fermante("variable");
    balise_fermante("declarateur-sp");
    balise_ouvrante("declaration-sp'");
    balise_fermante("declaration-sp'");
    balise_fermante("declaration-sp'");
    balise_fermante("declaration-sp");
    balise_unique(";");
    balise_ouvrante("liste-declarations-sp'");
    balise_ouvrante("declaration-sp");
    balise_fermante("declaration-sp");
    balise_unique(";");
    balise_ouvrante("liste-declarations-sp'");
    balise_fermante("liste-declarations-sp'");
    balise_fermante("liste-declarations-sp'");
    balise_fermante("liste-declarations-sp");
    balise_unique("}");
    balise_fermante("declarateur-cp");
    balise_ouvrante("declaration'");
    balise_fermante("declaration'");
    balise_fermante("declaration'");
    balise_fermante("declaration");
    balise_unique(";");
    balise_ouvrante("liste-declarations'");
    balise_ouvrante("declaration");
    balise_fermante("declaration");
    balise_unique(";");
    balise_ouvrante("liste-declarations'");
    balise_fermante("liste-declarations'");
    balise_fermante("liste-declarations'");
    balise_fermante("liste-declarations");
    balise_ouvrante("liste-fonctions");
    balise_ouvrante("liste-fonctions'");
    balise_ouvrante("fonction");
    balise_ouvrante("identificateur");

    balise_fermante("identificateur");
    balise_unique("(");
    balise_ouvrante("liste-parms");
    balise_ouvrante("parm");
    balise_unique("entier");
    balise_ouvrante("variable");

    balise_fermante("varible");
    balise_fermante("parm");
    balise_ouvrante("liste-parms'");
    balise_unique(",");
    balise_ouvrante("parm");
    balise_unique("entier");
    balise_ouvrante("variable");

    balise_fermante("varible");
    balise_fermante("parm");
    balise_ouvrante("liste-parms'");
    balise_fermante("liste-oarms'");
    balise_fermante("liste-oarms'");
    balise_fermante("liste-parms");
    balise_unique(")");
    balise_ouvrante("fonction'");
    balise_ouvrante("liste-declarations-sp");

    balise_fermante("liste-declarations-sp");
    balise_ouvrante("bloc");
    balise_unique("{");
    balise_ouvrante("liste-instructions");

    balise_fermante("liste-instructions");
    balise_unique("}");
    balise_ouvrante("bloc");
    balise_fermante("bloc");
    balise_unique("{");
    balise_ouvrante("liste-instructions");
    balise_ouvrante("instruction");
    balise_ouvrante("iteration");
    balise_unique("tantque");
    balise_ouvrante("condition");

    balise_fermante("condition");
    balise_unique("faire");
    balise_ouvrante("blocfaire");

    balise_fermante("blocfaire");
    balise_fermante("iteration");
    balise_ouvrante("selection");
    balise_unique("si");
    balise_ouvrante("condition");

    balise_fermante("condition");
    balise_unique("alors");
    balise_ouvrante("blocalors");

    balise_fermante("blocalors");
    balise_ouvrante("selection'");
    balise_unique("sinon");
    balise_ouvrante("blocfaire");

    balise_fermante("blocfaire");
    balise_fermante("selection'");
    balise_fermante("selection");
    balise_ouvrante("saut");
    balise_unique("retour");
    balise_ouvrante("expression");

    balise_fermante("expression");
    balise_fermante("saut");
    balise_ouvrante("affectation");
    balise_ouvrante("variable");

    balise_fermante("variable");
    balise_unique("=");
    balise_ouvrante("affectation'");

    balise_fermante("affectation'");
    balise_ouvrante("variable");

    balise_fermante("variable");
    balise_unique(".");
    balise_ouvrante("variable");
    balise_fermante("variable");
    balise_unique("=");
    balise_ouvrante("affectation'");

    balise_fermante("affectation'");
    balise_fermante("affectation");
    balise_unique(";");
    balise_ouvrante("appel");

    balise_fermante("appel");
    balise_unique(";");
    balise_fermante("instruction");
    balise_ouvrante("liste-instructions'");
    balise_ouvrante("instruction");

    balise_fermante("instruction");
    balise_ouvrante("liste-instructions'");
    balise_fermante("liste-instructions'");
    balise_fermante("liste-instructions'");
    balise_fermante("liste-instructions");
    balise_unique("}");
    balise_fermante("bloc");
    balise_fermante("fonction'");
    balise_fermante("fonction");
    balise_ouvrante("liste-fonctions'");
    balise_fermante("liste-fonctions'");
    balise_fermante("liste-fonctions'");
    balise_unique("main");
    balise_unique("(");
    balise_unique(")");
    balise_ouvrante("fonction''");
    balise_ouvrante("liste-declarations-sp");

    balise_fermante("liste-declarations-sp");
    balise_ouvrante("blocmain");
    balise_unique("{");
    balise_fermante("liste-instructions");

    balise_ouvrante("liste-instructions");
    balise_unique("}");
    balise_fermante("blocmain");
    balise_ouvrante("blocmain");
    balise_unique("{");
    balise_ouvrante("liste-instructions");

    balise_fermante("liste-instructions");
    balise_unique("}");
    balise_fermante("blocmain");
    balise_fermante("fonction''");
    balise_fermante("liste-fonctions");
    balise_fermante("Programme");
}
