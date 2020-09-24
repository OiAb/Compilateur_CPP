#include "analyseur_semantique.h"
//#include "analyseur_lexical.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
analyseur_semantique::analyseur_semantique(string s)
{
    Str=s;int i;
    parcourir=0;nbErreur=0;Erreur=0;
    //ctor
}
void analyseur_semantique::RetourFonction()
{
    int i;
    for(int i=0;i<TableauLexemes.size();i++)
    {
        if(TableauLexemes[i]=="retour")
        {
            if(getTypeIdentif(TableauLexemes[i+1])!="entier")
            {Erreur++;cout<<"Erreur"<<Erreur<<": "<<TableauLexemes[i+1]<<" isn't an integer. It shouldn't be returned"<<endl;}
        }
    }
}
string analyseur_semantique::getTypeIdentif(string s)
{
        string type;
        int index =getIndex(s,identifiants);
        if(index!=-1){
        int index1 =getIndex(s,variables);
        int index2 =getIndex(s,identificateurs);
        int index3 =getIndex(s,Variablestruct);
        int index4 =getIndex(s,Variabletab);
        if(index1!=-1){type="entier";return type;}
        if(index2!=-1){type="identifiantFonction";return type;}
        if(index3!=-1){type="struct";return type;}
        if(index4!=-1){type="tableauEntier";return type;}
        }
        else{type="vide";return type;}
}
void analyseur_semantique::manipulerVariables()
{
    int i;
    for(int i=0;i<TableauLexemes.size();i++)
    {
        if(getTypeIdentif(TableauLexemes[i])=="tableauEntier")
        {
            if(TableauLexemes[i+1]!="["&&TableauLexemes[i-1]!="entier"&&TableauLexemes[i-1]!="struct"){Erreur++;cout<<"Erreur"<<Erreur<<": denied use of variable "<<TableauLexemes[i]<<", It has as type integers table"<<endl;}
        }
        else if(getTypeIdentif(TableauLexemes[i])=="struct")
        {
            if(TableauLexemes[i+1]!="."&&TableauLexemes[i+1]!="{"&&TableauLexemes[i-1]!="struct"&&TableauLexemes[i-1]!="entier"){Erreur++;cout<<"Erreur"<<Erreur<<": denied use of variable "<<TableauLexemes[i]<<", It has as type struct"<<endl;}
        }
        else if(getTypeIdentif(TableauLexemes[i])=="identifiantFonction")
        {
            if(TableauLexemes[i+1]!="("&&TableauLexemes[i-1]!="entier"&&TableauLexemes[i-1]!="struct"){Erreur++;cout<<"Erreur"<<Erreur<<": denied use of function identifier "<<TableauLexemes[i]<<", It isn't a variable"<<endl;}
        }
        else if(getTypeIdentif(TableauLexemes[i])=="entier")
        {
            if(TableauLexemes[i+1]=="["||TableauLexemes[i+1]=="."){Erreur++;cout<<"Erreur"<<Erreur<<": denied use of variable "<<TableauLexemes[i]<<", It has as type integer"<<endl;}
        }
}}
void analyseur_semantique::declareDeja()
{
    int i;
    for(int i=0;i<TableauLexemes.size();i++)
    {
        if(TableauLexemes[i]=="(")
        {
            int index=getIndexIdentif(TableauLexemes[i-1],Variablestruct);
            int index1=getIndexIdentif(TableauLexemes[i-1],Variabletab);
            nb1++;
            if(index1!=-1||index!=-1/*||(index!=-1&&nb1>1)*/){Erreur++;cout<<"Erreur"<<Erreur<<": "<<TableauLexemes[i+1]<<" is already declared"<<endl;}
       }
        if(TableauLexemes[i]=="struct")
        {
            int index=getIndexIdentif(TableauLexemes[i+1],Variablestruct);
            int index1=getIndexIdentif(TableauLexemes[i+1],Variabletab);
            int index2=getIndexIdentif(TableauLexemes[i+1],variables);
            nb1++;
            if(index1!=-1||index2!=-1/*||(index!=-1&&nb1>1)*/){Erreur++;cout<<"Erreur"<<Erreur<<": "<<TableauLexemes[i+1]<<" is already declared"<<endl;}
       }
        else if(TableauLexemes[i]=="entier")
        {
            int index=getIndexIdentif(TableauLexemes[i+1],Variablestruct);//cout<<index<<endl;
            int index1=getIndexIdentif(TableauLexemes[i+1],Variabletab);
            int index2=getIndexIdentif(TableauLexemes[i+1],variables);
            int index3=getIndexIdentif(TableauLexemes[i+1],identificateurs);
            if(index!=-1){Erreur++;cout<<"Erreur"<<Erreur<<": "<<TableauLexemes[i+1]<<" is already declared"<<endl;}
            if(index3!=-1){Erreur++;cout<<"Erreur"<<Erreur<<": "<<TableauLexemes[i+1]<<" is already declared as function identifier"<<endl;}
            /*if(getTypeIdentif(TableauLexemes[i+1])=="tableauEntier")
            {
            nb2++;
            if(index!=-1||index2!=-1/*||(index1!=-1&&nb2>1)){Erreur++;cout<<"Erreur"<<Erreur<<": "<<TableauLexemes[i+1]<<" is already declared"<<endl;}
            }
            else if(getTypeIdentif(TableauLexemes[i+1])=="entier")
            {
            nb++;
            if(index!=-1||index1!=-1/*||(index2!=-1&&nb>1)){Erreur++;cout<<"Erreur"<<Erreur<<": "<<TableauLexemes[i+1]<<" is already declared"<<endl;}
            }*/
        }
    }
    for(int i=0;i<TableauLexemes.size();i++)
    {
       if(TableauLexemes[i]=="entier") TableauEntier.push_back(i+1);
       if(TableauLexemes[i]=="struct") TableauStruct.push_back(i+1);
    }
    for(int i=0;i<TableauEntier.size();i++)
    {
       if(i!=TableauEntier.size()-1){if(TableauLexemes[TableauEntier[i]]==TableauLexemes[TableauEntier[i+1]])
        {Erreur++;cout<<"Erreur"<<Erreur<<": "<<TableauLexemes[TableauEntier[i]]<<" is already declared"<<endl;}}
    }
    for(int i=0;i<TableauStruct.size();i++)for(int i=0;i<TableauStruct.size();i++)
    {
       if(i!=TableauStruct.size()-1){if(TableauLexemes[TableauStruct[i]]==TableauLexemes[TableauStruct[i+1]])
        {Erreur++;cout<<"Erreur"<<Erreur<<": "<<TableauLexemes[TableauStruct[i]]<<" is already declared"<<endl;}}
    }
}
void analyseur_semantique::UtiliseNonDeclare()
{
    int i,j;int calcul=0;int stop=0;
    for(int i=0;i<TableauLexemes.size();i++)
    {
        if(TableauLexemes[i]=="entier")
        {
           stop++;
           for(int j=0;j<variables.size();j++)
           {
               if(TableauLexemes[i+1]==variables[j]){calcul++;VariableDeclare.push_back(variables[j]);}

           }
           for(int j=0;j<Variabletab.size();j++)
           {
               if(TableauLexemes[i+1]==Variabletab[j]){calcul++;VariableDeclare.push_back(Variabletab[j]);}

           }
        }
    }
    if(calcul!=(variables.size()+Variabletab.size()))
    {
        int s=variables.size()+Variabletab.size();
        Erreur++;cout<<"Erreur"<<Erreur<<": "<<variables[variables.size()-1]<<" is used without being declared"<<endl;
    }
}
void analyseur_semantique::finsyntax()
{
        declareDeja();manipulerVariables();UtiliseNonDeclare();RetourFonction();
        cout<<endl;
        if(Erreur==0){cout<<"Programme semantiquement correct."<<endl;}
        else {cout<<"Programme semantiquement incorrect avec "<<Erreur<<" erreur(s)."<<endl;}
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
        cout<<endl;/*
        cout<<"Tableau des lexemes: {";
        for(int i=0;i<TableauLexemes.size()-1;i++)cout<<TableauLexemes[i]<<", ";
        cout<<TableauLexemes[TableauLexemes.size()-1]<<"}";
        cout<<endl;*/

}
void analyseur_semantique::programme()
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
void analyseur_semantique::listeDeclarations()
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
void analyseur_semantique::listeDeclarationsPrime()
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
void analyseur_semantique::listeDeclarationsSimple()
{
    declarationSimple();
    if(motCourant==PT_VER)
    {
        parcourir++;motCourant=tokens[parcourir];
        listeDeclarationsSimplePrime();
    }
    else{nbErreur++;cout<<"Erreur"<<nbErreur<<": ; needed after local declaration "<<endl;}
}
void analyseur_semantique::listeDeclarationsSimplePrime()
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
void analyseur_semantique::declaration()
{
    declarateurCompose();
    declarationPrime();
}
void analyseur_semantique::declarationPrime()
{
    if(motCourant==VERG)
    {
        parcourir++;motCourant=tokens[parcourir];
        declarateurCompose();
        declarationPrime();
    }
}
void analyseur_semantique::declarationSimple()
{
    declarateurSimple();
    declarationSimplePrime();
}
void analyseur_semantique::declarationSimplePrime()
{
    if(motCourant==VERG)
    {
        parcourir++;motCourant=tokens[parcourir];
        declarateurSimple();
        declarationSimplePrime();
    }
}
void analyseur_semantique::declarateurSimple()
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
void analyseur_semantique::declarateurCompose()
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
void analyseur_semantique::declarateurComposePrime()
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
void analyseur_semantique::listeFonctions()
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
void analyseur_semantique::listeFonctionsPrime()
{
    if(motCourant==IDENT)
    {
        fonction();
        listeFonctionsPrime();
    }
}
void analyseur_semantique::fonction()
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
void analyseur_semantique::fonctionPrime()
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
void analyseur_semantique::fonctionSecond()
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
void analyseur_semantique::listeParms()
{
    parm();
    listeParmsPrime();
}
void analyseur_semantique::listeParmsPrime()
{
    if(motCourant==VERG)
    {
        parcourir++;motCourant=tokens[parcourir];
        parm();
        listeParmsPrime();
    }
}
void analyseur_semantique::parm()
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
void analyseur_semantique::bloc()
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
void analyseur_semantique::blocmain()
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
void analyseur_semantique::blocfaire()
{
    if(motCourant==ACC_OUV)
    {
        parcourir++;motCourant=tokens[parcourir];
        blocPrime();
    }
    else{nbErreur++;cout<<"Erreur"<<nbErreur<<": \n{ needed "<<endl;}
}
void analyseur_semantique::blocalors()
{
    if(motCourant==ACC_OUV)
    {
        parcourir++;motCourant=tokens[parcourir];
        blocPrime();
    }
    else{nbErreur++;cout<<"Erreur"<<nbErreur<<": \n{ needed "<<endl;}
}
void analyseur_semantique::blocPrime()
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
void analyseur_semantique::listeInstructions()
{
    instruction();
    listeInstructionsPrime();
}
void analyseur_semantique::listeInstructionsPrime()
{
    if(motCourant==2||motCourant==3||motCourant==6||motCourant==1||motCourant==IDENT||motCourant==VAR||motCourant==VARSTRUCT||motCourant==VARTAB)
    {
        instruction();
        listeInstructionsPrime();
    }
}
void analyseur_semantique::instruction()
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
void analyseur_semantique::iteration()
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
void analyseur_semantique::selection()
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
void analyseur_semantique::selectionPrime()
{
    if(motCourant==0)
    {
        parcourir++;motCourant=tokens[parcourir];
        blocfaire();
    }
}
void analyseur_semantique::saut()
{
   if(motCourant==6)
    {
        parcourir++;motCourant=tokens[parcourir];
        expression();
    }
    else {nbErreur++;cout<<"Erreur"<<nbErreur<<": retour needed "<<endl;}
}
void analyseur_semantique::affectation()
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
void analyseur_semantique::affectationPrime()
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
void analyseur_semantique::appel()
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
void analyseur_semantique::listeExpressions()
{
    expression();
    listeExpressionsPrime();
}
void analyseur_semantique::listeExpressionsPrime()
{
    if(motCourant==VERG)
    {
        parcourir++;motCourant=tokens[parcourir];
        expression();
        listeExpressionsPrime();
    }
}
void analyseur_semantique::condition()
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
void analyseur_semantique::conditionPrime()
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
void analyseur_semantique::expression()
{
    terme();
    expressionPrime();
}
void analyseur_semantique::expressionPrime()
{
    if(motCourant==BIN_OP)
    {
        binaryOp();
        expression();
    }
}
void analyseur_semantique::terme()
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
void analyseur_semantique::variable()
{
    if(motCourant==VAR)
    {
      parcourir++;motCourant=tokens[parcourir];
    }
    else {nbErreur++;cout<<"Erreur"<<nbErreur<<": should be a variable started with only letters "<<endl;}
}
void analyseur_semantique::variablestruct()
{
    if(motCourant==VARSTRUCT)
    {
      parcourir++;motCourant=tokens[parcourir];
    }
    else {nbErreur++;cout<<"Erreur"<<nbErreur<<": should be a struct variable started with only letters "<<endl;}
}
void analyseur_semantique::variabletab()
{
    if(motCourant==VARTAB)
    {
      parcourir++;motCourant=tokens[parcourir];
    }
    else {nbErreur++;cout<<"Erreur"<<nbErreur<<": should be a tab variable started with only letters "<<endl;}
}
void analyseur_semantique::nombre()
{
    if(motCourant==NOMBRE)
    {
       parcourir++;motCourant=tokens[parcourir];
    }
    else {nbErreur++;cout<<"Erreur"<<nbErreur<<": should be a number contains only constants "<<endl;}
}
void analyseur_semantique::identificateur()
{
    if(motCourant==IDENT)
    {
        parcourir++;motCourant=tokens[parcourir];
    }
    else {nbErreur++;cout<<"Erreur"<<nbErreur<<": should be an identifier started with only letters "<<endl;}
}
void analyseur_semantique::binaryOp()
{
    if(motCourant!=BIN_OP){nbErreur++;cout<<"Erreur"<<nbErreur<<": should start with a  binary operator "<<endl;}
    else {parcourir++;motCourant=tokens[parcourir];}
}
void analyseur_semantique::binaryRel()
{
    if(motCourant!=AND && motCourant!=OR) {nbErreur++;cout<<"Erreur"<<nbErreur<<": should start with a  binaryRel "<<endl;}
    else {parcourir++;motCourant=tokens[parcourir];}
}

void analyseur_semantique::binaryComp()
{
    if(motCourant!=BIN_COMP){nbErreur++;cout<<"Erreur"<<nbErreur<<": should start with a  binary comparator "<<endl;}
    else {parcourir++;motCourant=tokens[parcourir];}
}
int analyseur_semantique::returntokens(int j)
{
    return tokens[j];
}
int analyseur_semantique::Size()
{
    return tokens.size();
}
void analyseur_semantique::readfichier()
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
char analyseur_semantique::lc()
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
void analyseur_semantique::fin()
{
        TUniteLexical ul;tokens.push_back(FIN);int j;
        ul.UL="FIN";ul.attribut=-1;
        affiche(ul);
        cout<<endl;/*for(j=0;j<Size();j++)cout<<returntokens(j)<<endl;*/
        /*programme();*/finsyntax();
 }
bool analyseur_semantique::estBlanc(char cc)
{
        return (cc==' ' || cc=='\t' || cc=='\n' || cc=='\r');
}
int analyseur_semantique::getIndex(string stringToFind, vector<string> stringArray)
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
int analyseur_semantique::getIndexIdentif(string stringToFind, vector<string> stringArray)
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
int analyseur_semantique::estMotcle(string  lexeme)
{
        return getIndex(lexeme,motsCles);
}
int analyseur_semantique::estMotreserve(string lexeme)
{
        return getIndex(lexeme,motsReserves);
}
void analyseur_semantique::Identif(char C,string s)
{
   if(C=='(')
   {
       int pos = getIndexIdentif(s,identificateurs);
       int pos3 = getIndexIdentif(s,Variablestruct);
       int pos1 = getIndexIdentif(s,Variabletab);
       int pos2 = getIndexIdentif(s,variables);
       if(pos==-1&&pos1==-1&&pos2==-1&&pos3==-1)
        {
            identificateurs.push_back(s);
        }
        tokens.push_back(IDENT);
   }
   else if(C=='{')
   {
       int pos3 = getIndexIdentif(s,identificateurs);
       int pos = getIndexIdentif(s,Variablestruct);
       int pos1 = getIndexIdentif(s,Variabletab);
       int pos2 = getIndexIdentif(s,variables);
      if(pos==-1&&pos1==-1&&pos2==-1&&pos3==-1)
        {
            Variablestruct.push_back(s);
        }
        tokens.push_back(VARSTRUCT);
   }
  else if(C=='.')
   {
       int pos1 = getIndexIdentif(s,Variablestruct);
       int pos = getIndexIdentif(s,identificateurs);
       int pos3 = getIndexIdentif(s,Variabletab);
       int pos2 = getIndexIdentif(s,variables);
       if(pos==-1&&pos1==-1&&pos2==-1&&pos3==-1)
        {
            Variablestruct.push_back(s);
        }
        tokens.push_back(VARSTRUCT);
   }
   else if(C=='[')
   {
       int pos = getIndexIdentif(s,Variabletab);
       int pos2 = getIndexIdentif(s,variables);
       int pos1 = getIndexIdentif(s,Variablestruct);
       int pos3 = getIndexIdentif(s,identificateurs);
       if(pos==-1&&pos2==-1&&pos1==-1&&pos3==-1)
        {
            Variabletab.push_back(s);
        }
        tokens.push_back(VARTAB);
   }
    else{
        int pos = getIndexIdentif(s,variables);
        int pos1 = getIndexIdentif(s,Variablestruct);
        int pos2 = getIndexIdentif(s,Variabletab);
        int pos3 = getIndexIdentif(s,identificateurs);
       if(pos==-1&&pos1==-1&&pos2==-1&&pos3==-1)
        {
            variables.push_back(s);
        }
        tokens.push_back(VAR);
    }
}
void analyseur_semantique::ULIdentif(string lexeme)
{
        TUniteLexical ul;
        int pos = getIndexIdentif(lexeme,identifiants);
        if(pos==-1){
            identifiants.push_back(lexeme);
        }
        ul.UL="IDENT";ul.attribut=getIndexIdentif(lexeme,identifiants);
        affiche(ul);
}
void analyseur_semantique::affiche(TUniteLexical ul1){}
void analyseur_semantique::uniteSuivante()
{
        string lexeme="";TUniteLexical ul;

        //if(c=='/0')
        while(estBlanc(c)) {c=lc();test++;}
        switch(c){

            case '+': {
                c=lc();test++;tokens.push_back(BIN_OP);TableauLexemes.push_back("+");
                ul.UL="BIN_OP";ul.attribut=getIndex("+",binOp);
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '.': {
                c=lc();test++;tokens.push_back(PT);TableauLexemes.push_back(".");
                ul.UL="PT";ul.attribut=-1;
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '-':{
                c=lc();test++;tokens.push_back(BIN_OP);TableauLexemes.push_back("-");
                ul.UL="BIN_OP";ul.attribut=getIndex("-",binOp);
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '<':{
                c=lc();test++;
                if(c=='='){
                    c=lc();test++;tokens.push_back(BIN_COMP);
                    ul.UL="BIN_COMP";ul.attribut=getIndex("<=",binComp);TableauLexemes.push_back("<=");
                }
                else{
                    tokens.push_back(BIN_COMP);ul.UL="BIN_COMP";ul.attribut=getIndex("<",binComp);TableauLexemes.push_back("<");
                }
                    affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
                }
            case '>':{
                c=lc();test++;
                if(c=='='){
                    c=lc();test++;
                    tokens.push_back(BIN_COMP);ul.UL="BIN_COMP";ul.attribut=getIndex(">=",binComp);TableauLexemes.push_back(">=");
                }
                else{
                    tokens.push_back(BIN_COMP);ul.UL="BIN_COMP";ul.attribut=getIndex(">",binComp);TableauLexemes.push_back(">");
                }
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '*': {
                c=lc();test++;tokens.push_back(BIN_OP);TableauLexemes.push_back("*");
                ul.UL="BIN_OP";ul.attribut=getIndex("*",binOp);
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '&': {
                c=lc();test++;tokens.push_back(AND);TableauLexemes.push_back("&");
                ul.UL="AND";ul.attribut=-1;
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '|': {
                c=lc();test++;tokens.push_back(OR);TableauLexemes.push_back("|");
                ul.UL="OR";ul.attribut=-1;
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '/': {
                c=lc();test++;tokens.push_back(BIN_OP);TableauLexemes.push_back("/");
                ul.UL="BIN_OP";ul.attribut=getIndex("/",binOp);
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '=':{
                c=lc();test++;
                if(c=='='){
                    c=lc();test++;tokens.push_back(BIN_COMP);TableauLexemes.push_back("==");
                    ul.UL="BIN_COMP";ul.attribut=getIndex("==",binComp);
                }
                else{
                    tokens.push_back(AFF);ul.UL="AFF";ul.attribut=-1;TableauLexemes.push_back("=");
                }
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '!':{
                c=lc();test++;
                if(c=='='){
                    c=lc();test++;tokens.push_back(BIN_COMP);TableauLexemes.push_back("!=");
                    ul.UL="BIN_COMP";ul.attribut=getIndex("=!",binComp);
                }
                else{
                    tokens.push_back(NON);ul.UL="NON";ul.attribut=-1;TableauLexemes.push_back("!");
                }
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '[':{
                c=lc();test++;tokens.push_back(CROCH_OUV);TableauLexemes.push_back("[");
                ul.UL="CROCH_OUV";ul.attribut=-1;
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case ']':{
                c=lc();test++;tokens.push_back(CROCH_FER);TableauLexemes.push_back("]");
                ul.UL="CROCH_FER";ul.attribut=-1;
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '(':{
                c=lc();test++;tokens.push_back(PAR_OUV);TableauLexemes.push_back("(");
                ul.UL="PAR_OUV";ul.attribut=-1;
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case ')':{
                c=lc();test++;tokens.push_back(PAR_FER);TableauLexemes.push_back(")");
                ul.UL="PAR_FER";ul.attribut=-1;
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case ',':{
                c=lc();test++;tokens.push_back(VERG);TableauLexemes.push_back(",");
                ul.UL="VERG";ul.attribut=-1;
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '{':{
                c=lc();test++;tokens.push_back(ACC_OUV);TableauLexemes.push_back("{");
                ul.UL="ACC_OUV";ul.attribut=-1;
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '}':{
                c=lc();test++;tokens.push_back(ACC_FER);TableauLexemes.push_back("}");
                ul.UL="ACC_FER";ul.attribut=-1;
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case ';':{
                c=lc();test++;tokens.push_back(PT_VER);TableauLexemes.push_back(";");
                ul.UL="PT_VER";ul.attribut=-1;
                affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
            }
            case '#':{
                c=lc();test++;tokens.push_back(COMMENT);TableauLexemes.push_back("#");
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
                    tokens.push_back(NOMBRE);TableauLexemes.push_back(lexeme);ul.UL="NOMBRE";ul.attribut=stoi(lexeme);
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
                        tokens.push_back(pos);TableauLexemes.push_back(lexeme);ul.UL=motsCles[pos];ul.attribut=pos;
                        affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
                    }
                    if(pos1!=-1){
                        tokens.push_back(pos1);TableauLexemes.push_back(lexeme);ul.UL=motsReserves[pos1];ul.attribut=pos1;
                        affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
                    }
                    TableauLexemes.push_back(lexeme);Identif(c,lexeme);ULIdentif(lexeme);if(c=='\0'){fin();exit(0);}else uniteSuivante();
                }
                else{
                    c=lc();test++;tokens.push_back(ERROR);
                    ul.UL="ERROR";ul.attribut=2;
                    affiche(ul);if(c=='\0'){fin();exit(0);}else uniteSuivante();
                }
}}
}
