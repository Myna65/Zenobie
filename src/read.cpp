//////////////////////////////////////////////////////////////////////
//Zenobie 2.4.0
//Copyright (C) 2011-2014 Meynaert Nathan
//
//This program is free software; you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation; either version 3 of the License.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////

#include "data.h"
#include <QApplication>
#include <QLocale>
#include <QMessageBox>
#include <fstream>
#include <ctype.h>
#include <cmath>
#include <sstream>
#include <map>
double lecdouble(std::string str)
{
    double ret=.0;
    int exp=0;
    for(unsigned int i=0,c=str.size();i<c;i++)
    {
        if(str[i]==' '||str[i]=='.')
            continue;
        if(isdigit(str[i]))
        {
            ret=(ret*10)+(str[i]-'0');
            exp--;
        }
        if(str[i]==',')
        {
            exp=0;
        }
        if(str[i]=='-')
        {
            ret=-ret;
        }
    }
    ret=ret*pow(10.,exp);
    return ret;
}
void Data::read(QString nom_fichier,Fichier type)
{
    switch(type)
    {
    case TxtL:
        var=true;
    case TxtC:
    {
        std::vector<std::string> file;
        std::ifstream input(nom_fichier.toLatin1(),std::ios::in);
        if(input.is_open())
        {
            while(!input.eof())
            {
                std::string temp;
                getline(input,temp);
                file.push_back(temp);
            }
        }
        else
        {
            //TODO: Traitement si pas fichier.
        }
        for(unsigned int i=5,c=file.size();i<c;i++)
        {
            if(file[i].size()<10)
                continue;
            if(file[i][0]!='|')
                continue;
            codes.push_back(file[i].substr(1,12));
            unsigned int pre=13;
            std::vector<double> temp;
            for(unsigned int j=14,d=file[i].size();j<d;j++)
            {
                if(file[i][j]=='|')
                {
                    temp.push_back(lecdouble(file[i].substr(pre+1,j-pre-1)));
                    pre=j;
                }
            }
            donnees.push_back(temp);
        }
        input.close();
        if(!var)
        {
            input.open((QCoreApplication::applicationDirPath()+"/CodesSpec.txt").toLatin1(),std::ios::in);
            int i=0;
            if(input.is_open())
            {
                while(!input.eof())
                {
                    std::string str;
                    getline(input,str);
                    if(str.size()>11)
                    {
                        codes[i]=str.substr(0,12);
                        i++;
                    }
                }
            }
        }
        int debut=1,taille=0;
        for(unsigned int i=1;i<file[3].size();i++)
        {
            if(file[3][i]=='|')
            {
                titres.push_back(file[3].substr(debut,taille));
                taille=0;
                debut=i+1;
            }
            else
                taille++;
        }
        break;
    }
    case In:
        std::ostringstream oss;
        oss<<"/ref";
        if(aAB)
            oss<<"AB";
        else if(aprog)
            oss<<"Prog";
        else if(aSEC)
        {
            oss<<"SEC";
            goto cont;
        }
        else
            return;
        if(var)
            oss<<"Var";
        else
            oss<<"Dis";
        cont:
        QString locale = QLocale::system().name().section('_', 0, 0);
        oss<<locale.toStdString()<<".txt";
        std::ifstream input(((QCoreApplication::applicationDirPath()+oss.str().c_str())).toLatin1(),std::ios::in);
        if(!input.is_open())
        {
            QMessageBox::warning(parent,QObject::tr("Attention"),QApplication::translate("Dialog", "Les fichiers contenant les descriptions n'ont pu être trouvé pour votre configuration et votre langue.\nLes fichiers seront donc chargés en français s'ils existent sinon aucun fichier ne sera chargé", 0),QMessageBox::Ok);
            oss.str("");
            oss<<"/ref";
            if(aAB)
                oss<<"AB";
            else if(aprog)
                oss<<"Prog";
            else if(aSEC)
            {
                oss<<"SEC";
                goto cont2;
            }
            else
                return;
            if(var)
                oss<<"Var";
            else
                oss<<"Dis";
            cont2:
            oss<<"fr.txt";
            input.open(((QCoreApplication::applicationDirPath()+oss.str().c_str())).toLatin1(),std::ios::in);
            if(!input.is_open())
            {
                return;
            }
        }
        std::map<std::string,std::string> dic;
        while(!input.eof())
        {
            std::string str;
            getline(input,str);
            if(str.size()>5)
            {
                unsigned int i=0;
                for(i=0;i<str.size();i++)
                {
                    if(!isdigit(str[i]))
                        break;
                }
                if(str.size()>i+1)
                    dic[str.substr(0,i)]=str.substr(i+1,std::string::npos);
                else
                    dic[str.substr(0,i)]="";
            }
        }
        for(unsigned int i=0;i<codes.size();i++)
        {
            if(dic.find(codes[i])!=dic.end())
                desc.push_back(dic[codes[i]]);
            else
                desc.push_back("");
                // TODO AB nonreconnue
        }
        bdesc=true;
        break;
    }
}
