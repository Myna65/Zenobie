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

#include <fstream>
#include <iomanip>
#include <QWidget>
#include "data.h"
#include <sstream>
void Data::write(QString nom_fichier)
{
    std::vector<std::string>& princ=codes;
    if(aAB)
    {
        princ=AB;
    }
    if(aprog)
    {
        princ=prog;
    }
    std::ofstream output(nom_fichier.toLatin1(),std::ios::out|std::ios::trunc);
    output<<std::fixed<<std::setprecision(2)<<"<!DOCTYPE html>\n<html><body><table>";
    if(aAB)
        output<<"<tr><th>"<<QObject::tr("Allocations de base").toStdString()<<" </th>";
    else if(aprog)
        output<<"<tr><th>"<<QObject::tr("Programmes").toStdString()<<" </th>";
    else if(aSEC)
        output<<"<tr><th>"<<QObject::tr("Codes SEC").toStdString()<<" </th>";
    else
        output<<"<tr><th>"<<titres[0]<<" </th>";
    if(bAB)
    {
        output<<"<th>"<<QObject::tr("Allocations de base").toStdString()<<"</th>";
    }
    if(bprog)
    {
        output<<"<th>"<<QObject::tr("Programmes").toStdString()<<"</th>";
    }
    if(bdesc)
    {
        output<<"<th>"<<QObject::tr("Description").toStdString()<<"</th>";
    }
    for(unsigned int j=1,d=titres.size();j<d;j++)
    {
        output<<"<th>"<<titres[j]<<"</th>";
    }
    output<<"</tr>";
    for(unsigned int i=0,c=princ.size();i<c;i++)
    {
        output<<"<tr><td>"<<princ[i]<<" </td>";
        if(bAB)
        {
            output<<"<td>"<<AB[i]<<"</td>";
        }
        if(bprog)
        {
            output<<"<td>"<<prog[i]<<"</td>";
        }
        if(bdesc)
        {
            output<<"<td>"<<desc[i]<<"</td>";
        }
        std::ostringstream oss;
        oss<<std::fixed<<std::setprecision(2);
        for(int j=0,d=donnees[i].size();j<d;j++)
        {
            oss<<"<td>"<<donnees[i][j]<<"</td>";
        }
        std::string str=oss.str();
        while(str.find(".")!=std::string::npos)
        {
            str.replace(str.find("."),1,",");
        }
        output<<str;
        output<<"</tr>";
    }
    output<<"</table></body></html>";
}
