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
#include <map>
#include <fstream>
#include <QApplication>
void Data::traiter(Traitement trai)
{
    switch(trai)
    {
    case AlB:
        bAB=true;
        AB.clear();
        for(unsigned int i=0;i<codes.size();i++)
        {
            if((codes[i][6]=='1')&&(codes[i][7]=='1'))
            {
                std::string t=codes[i];
                t[8]=t[9]='0';
                AB.push_back(t);
            }
            else
                AB.push_back(codes[i]);
        }
        break;
    case Prog:
        bprog=true;
        prog.clear();
        for(unsigned int i=0;i<codes.size();i++)
        {
            prog.push_back(codes[i].substr(0,5));
        }
        break;
    case eSEC:
        bSEC=true;
        SEC.clear();
        for(unsigned int i=0;i<codes.size();i++)
        {
            SEC.push_back(codes[i].substr(6,2));
        }
        std::string a = "Coucou gamin";
    }
}
void Data::regrouper()
{
    if(aAB)
    {
        std::multimap<std::string,int> dic;
        for(unsigned int i=0;i<AB.size();i++)
        {
            dic.insert(make_pair(AB[i],i));
        }
        std::string last="";
        std::vector<std::string> nAB;
        std::vector<std::vector<double> > ndonnees;
        std::vector<double> t(donnees[0].size(),0.);
        for(std::map<std::string,int>::iterator it=dic.begin();it!=dic.end();it++)
        {
            if(it->first!=last&&last!="")
            {
                ndonnees.push_back(t);
                t = std::vector<double>(donnees[0].size(),0.);
                nAB.push_back(last);
            }
            for(unsigned int i=0;i<donnees[0].size();i++)
            {
                t[i]+=donnees[it->second][i];
            }
            last=it->first;
        }
        ndonnees.push_back(t);
        nAB.push_back(last);
        codes=nAB;
        AB=nAB;
        donnees=ndonnees;
    }
    if(aprog)
    {
        std::multimap<std::string,int> dic;
        for(unsigned int i=0;i<prog.size();i++)
        {
            dic.insert(make_pair(prog[i],i));
        }
        std::string last="";
        std::vector<std::string> nprog;
        std::vector<std::vector<double> > ndonnees;
        std::vector<double> t(donnees[0].size(),0.);
        for(std::map<std::string,int>::iterator it=dic.begin();it!=dic.end();it++)
        {
            if(it->first!=last&&last!="")
            {
                ndonnees.push_back(t);
                t = std::vector<double>(donnees[0].size(),0.);
                nprog.push_back(last);
            }
            for(unsigned int i=0;i<donnees[0].size();i++)
            {
                t[i]+=donnees[it->second][i];
            }
            last=it->first;
        }
        ndonnees.push_back(t);
        nprog.push_back(last);
        codes=nprog;
        prog=nprog;
        donnees=ndonnees;
    }
    if(aSEC)
    {
        std::multimap<std::string,int> dic;
        for(unsigned int i=0;i<SEC.size();i++)
        {
            dic.insert(make_pair(SEC[i],i));
        }
        std::string last="";
        std::vector<std::string> nSEC;
        std::vector<std::vector<double> > ndonnees;
        std::vector<double> t(donnees[0].size(),0.);
        for(std::map<std::string,int>::iterator it=dic.begin();it!=dic.end();it++)
        {
            if(it->first!=last&&last!="")
            {
                ndonnees.push_back(t);
                t = std::vector<double>(donnees[0].size(),0.);
                nSEC.push_back(last);
            }
            for(unsigned int i=0;i<donnees[0].size();i++)
            {
                t[i]+=donnees[it->second][i];
            }
            last=it->first;
        }
        ndonnees.push_back(t);
        nSEC.push_back(last);
        codes=nSEC;
        SEC=nSEC;
        donnees=ndonnees;
    }
}
Data Data::fusionner(Data& d)
{
    Data ret;
    if(!aSEC||!d.aSEC)
        return *this;
    std::ifstream input((QCoreApplication::applicationDirPath()+"/PrefSEC.txt").toLatin1(),std::ios::in);
    if(input.is_open())
    {
        std::vector<std::vector<int> > cols;
        int c=0;
        input>>c;
        for(int i=0;i<2;i++)
        {
            std::vector<int> temp;
            for(int i=0;i<c;i++)
            {
                int val=0;
                input>>val;
                temp.push_back(val);
            }
            cols.push_back(temp);
        }
        ret.titres.push_back("");
        for(unsigned int i=0;i<cols[0].size();i++)
            ret.titres.push_back(titres[cols[0][i]+1]);
        unsigned int a=0,b=0;
        while(a<codes.size()&&b<d.codes.size())
        {
            if(codes[a]==d.codes[b])
            {
                ret.codes.push_back(codes[a]);
                std::vector<double> tmp;
                for(unsigned int i=0;i<cols[0].size();i++)
                {
                    tmp.push_back(donnees[a][cols[0][i]]+d.donnees[b][cols[1][i]]);
                }
                ret.donnees.push_back(tmp);
                a++;
                b++;
            }
            else if(codes[a]<d.codes[b])
            {
                ret.codes.push_back(codes[a]);
                std::vector<double> tmp;
                for(unsigned int i=0;i<cols[0].size();i++)
                {
                    tmp.push_back(donnees[a][cols[0][i]]);
                }
                ret.donnees.push_back(tmp);
                a++;
            }
            else if(codes[a]>d.codes[b])
            {
                ret.codes.push_back(codes[b]);
                std::vector<double> tmp;
                for(unsigned int i=0;i<cols[0].size();i++)
                {
                    tmp.push_back(d.donnees[b][cols[1][i]]);
                }
                ret.donnees.push_back(tmp);
                b++;
            }
        }
        while(a<codes.size())
        {
            ret.codes.push_back(codes[a]);
            std::vector<double> tmp;
            for(unsigned int i=0;i<cols[0].size();i++)
            {
                tmp.push_back(donnees[a][cols[0][i]]);
            }
            ret.donnees.push_back(tmp);
            a++;
        }
        while(b<d.codes.size())
        {
            ret.codes.push_back(codes[b]);
            std::vector<double> tmp;
            for(unsigned int i=0;i<cols[0].size();i++)
            {
                tmp.push_back(d.donnees[b][cols[0][i]]);
            }
            ret.donnees.push_back(tmp);
            b++;
        }
        ret.aSEC=true;
        ret.SEC=ret.codes;
    }
    else
        return *this;
    return ret;
}
Data Data::verifier()
{
    Data ret;
    ret.titres=titres;
    ret.aAB=aAB;
    ret.bAB=bAB;
    ret.aprog=aprog;
    ret.bprog=bprog;
    ret.aSEC=aSEC;
    ret.bSEC=bSEC;
    ret.bdesc=bdesc;
    ret.var=var;
    if(var)
    {
        std::vector<std::vector<std::vector<int> > > col;
        std::ifstream input((QCoreApplication::applicationDirPath()+"/PrefDep.txt").toLatin1(),std::ios::in);
        if(input.is_open())
        {
            int c;
            input>>c;
            for(int i=0;i<c;i++)
            {
                std::vector<std::vector<int> > tmp;
                std::vector<int> temp;
                int d,e;
                input>>d>>e;
                for(int j=0;j<d;j++)
                {
                    int val;
                    input>>val;
                    temp.push_back(val);
                }
                tmp.push_back(temp);
                temp.clear();
                for(int j=0;j<e;j++)
                {
                    int val;
                    input>>val;
                    temp.push_back(val);
                }
                tmp.push_back(temp);
                col.push_back(tmp);
            }
            for(unsigned int i=0;i<donnees.size();i++)
            {
                bool ok=true;
                for(unsigned int j=0;j<col.size();j++)
                {
                    for(unsigned int k=0;k<col[j][0].size();k++)
                    {
                        bool ok2 =false;
                        for(unsigned int l=0;l<col[j][1].size();l++)
                        {
                            if(donnees[i][col[j][0][k]]>=-donnees[i][col[j][1][l]])
                            {
                                ok2=true;
                            }
                        }
                        if(!ok2)
                            ok=false;
                    }
                }
                if(!ok)
                {
                    ret.codes.push_back(codes[i]);
                    ret.donnees.push_back(donnees[i]);
                    if(bAB||aAB)
                        ret.AB.push_back(AB[i]);
                    if(bprog||aprog)
                        ret.prog.push_back(prog[i]);
                    if(bSEC||aSEC)
                        ret.SEC.push_back(SEC[i]);
                    if(bdesc)
                        ret.desc.push_back(desc[i]);
                }
            }
        }
        else
        {
            ret=*this;
        }

    }
    else
    {
        for(unsigned int i=0;i<donnees.size();i++)
        {
            for(unsigned int j=0;j<donnees[0].size();j++)
            {
                if(donnees[i][j]<0)
                {
                    ret.codes.push_back(codes[i]);
                    ret.donnees.push_back(donnees[i]);
                    if(bAB||aAB)
                        ret.AB.push_back(AB[i]);
                    if(bprog||aprog)
                        ret.prog.push_back(prog[i]);
                    if(bSEC||aSEC)
                        ret.SEC.push_back(SEC[i]);
                    if(bdesc)
                        ret.desc.push_back(desc[i]);
                    break;
                }
            }
        }
    }
    return ret;
}
Data Data::comparer(Data& d)
{
    Data ret;
    std::vector<int> cols;
    std::ifstream input((QCoreApplication::applicationDirPath()+"/PrefCmp.txt").toLatin1(),std::ios::in);
    if(input.is_open())
    {
    int c;
    input>>c;
    for(int i=0;i<c;i++)
    {
        int val;
        input>>val;
        cols.push_back(val);
    }
    if((aprog&&d.aprog)||(aAB&&d.aAB))
    {
        ret.bdesc=bdesc;
        ret.bprog=bprog;
        ret.aAB=aAB;
        ret.aprog=aprog;
        ret.bdesc=bdesc;
        ret.var=var;
        ret.titres.push_back("");
        for(unsigned int i=0;i<cols.size();i++)
        {
            ret.titres.push_back(titres[cols[i]+1]+" A");
            ret.titres.push_back(d.titres[cols[i]+1]+" B");
            ret.titres.push_back((QApplication::translate("Dialog", "Différence", 0)).toStdString());
        }
        unsigned int a=0,b=0;
        while(a<codes.size()&&b<d.codes.size())
        {
            if(codes[a]==d.codes[b])
            {
                bool ok=true;
                for(unsigned int i=0;i<cols.size();i++)
                {
                    if(donnees[a][cols[i]]!=d.donnees[b][cols[i]])
                        ok=false;
                }
                if(!ok)
                {
                    ret.codes.push_back(codes[a]);
                    std::vector<double> tmp;
                    for(unsigned int i=0;i<cols.size();i++)
                    {
                        tmp.push_back(donnees[a][cols[i]]);
                        tmp.push_back(d.donnees[b][cols[i]]);
                        tmp.push_back(donnees[a][cols[i]]-d.donnees[b][cols[i]]);
                    }
                    ret.donnees.push_back(tmp);
                    if(bdesc)
                    {
                        ret.desc.push_back(desc[a]);
                    }
                    if(bprog||aprog)
                    {
                        ret.prog.push_back(prog[a]);
                    }
                    if(bAB||aAB)
                    {
                        ret.AB.push_back(AB[a]);
                    }
                }
                a++;
                b++;
            }
            else if(codes[a]<d.codes[b])
            {
                ret.codes.push_back(codes[a]);
                std::vector<double> tmp;
                for(unsigned int i=0;i<cols.size();i++)
                {
                    tmp.push_back(donnees[a][cols[i]]);
                    tmp.push_back(0.);
                    tmp.push_back(donnees[a][cols[i]]);
                }
                ret.donnees.push_back(tmp);
                if(bprog||aprog)
                {
                    ret.desc.push_back(desc[a]);
                }
                if(bprog||aprog)
                {
                    ret.prog.push_back(prog[a]);
                }
                if(bAB||aAB)
                {
                    ret.AB.push_back(AB[a]);
                }
                a++;
            }
            else if(codes[a]>d.codes[b])
            {
                ret.codes.push_back(d.codes[b]);
                std::vector<double> tmp;
                for(unsigned int i=0;i<cols.size();i++)
                {
                    tmp.push_back(0.);
                    tmp.push_back(d.donnees[b][cols[i]]);
                    tmp.push_back(-d.donnees[b][cols[i]]);
                }
                ret.donnees.push_back(tmp);
                if(bdesc&&d.bdesc)
                {
                    ret.desc.push_back(d.desc[b]);
                }
                if(bdesc&&!d.bdesc)
                {
                    ret.desc.push_back("");
                }
                if((bprog&&d.bprog)||(aprog&&d.aprog))
                {
                    ret.prog.push_back(d.prog[b]);
                }
                if((bprog&&d.bprog)||(!(aprog&&d.aprog)))
                {
                    ret.prog.push_back("");
                }
                if((bAB&&d.bAB)||(aAB&&d.aAB))
                {
                    ret.AB.push_back(d.AB[b]);
                }
                if((bAB&&d.bAB)||(!(aAB&&d.aAB)))
                {
                    ret.AB.push_back("");
                }
                b++;
            }
        }
        while(a<codes.size())
        {
            ret.codes.push_back(codes[a]);
            std::vector<double> tmp;
            for(unsigned int i=0;i<cols.size();i++)
            {
                tmp.push_back(donnees[a][cols[i]]);
                tmp.push_back(0.);
                tmp.push_back(donnees[a][cols[i]]);
            }
            ret.donnees.push_back(tmp);
            if(bprog||aprog)
            {
                ret.desc.push_back(desc[a]);
            }
            if(bprog||aprog)
            {
                ret.prog.push_back(prog[a]);
            }
            if(bAB||aAB)
            {
                ret.prog.push_back(prog[a]);
            }
            a++;
        }
        while(b<d.codes.size())
        {
            ret.codes.push_back(d.codes[b]);
            std::vector<double> tmp;
            for(unsigned int i=0;i<cols.size();i++)
            {
                tmp.push_back(0.);
                tmp.push_back(d.donnees[b][cols[i]]);
                tmp.push_back(-d.donnees[b][cols[i]]);
            }
            ret.donnees.push_back(tmp);
            if(bdesc&&d.bdesc)
            {
                ret.desc.push_back(d.desc[b]);
            }
            if(bdesc&&!d.bdesc)
            {
                ret.desc.push_back("");
            }
            if((bprog&&d.bprog)||(aprog&&d.aprog))
            {
                ret.prog.push_back(d.prog[b]);
            }
            if((bprog&&d.bprog)||(!(aprog&&d.aprog)))
            {
                ret.prog.push_back("");
            }
            if((bAB&&d.bAB)||(aAB&&d.aAB))
            {
                ret.AB.push_back(d.AB[b]);
            }
            if((bAB&&d.bAB)||(!(aAB&&d.aAB)))
            {
                ret.AB.push_back("");
            }
            b++;
        }
        return ret;
    }
    else
    {
        return *this;
    }
    }
    else
    {
        return *this;
    }
}
