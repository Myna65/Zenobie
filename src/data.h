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

#ifndef DATA_H
#define DATA_H
#include <vector>
#include <string>
#include <QWidget>
enum Fichier
{
	TxtC,TxtL,In
};
enum Traitement
{
    AlB,Prog,eSEC
};
class Data
{
private:
	std::vector<std::string> titres;
	std::vector<std::string> codes;
	std::vector<std::string> prog;
	std::vector<std::string> AB;
	std::vector<std::string> SEC;
    std::vector<std::string> desc;
	std::vector<std::vector<double> > donnees;
	bool bprog,bAB,bSEC,bdesc;
    bool aprog,aAB,aSEC;
    bool var;
public:
    Data();
    void read(QString nom_fichier,Fichier type);
    void write(QString nom_fichier);
	void traiter(Traitement trai);
	void activer(Traitement trai);
	void regrouper();
    Data fusionner(Data& d);
    Data verifier();
    Data comparer(Data& d);
    static QWidget* parent;
};
#endif
