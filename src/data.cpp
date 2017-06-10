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
QWidget* Data::parent=NULL;
Data::Data()
{
    bprog=bAB=bSEC=bdesc=aprog=aAB=aSEC=var=false;
}
void Data::activer(Traitement trai)
{
    switch(trai)
    {
    case AlB:
        if(bAB)
        {
            bAB=false;
            aAB=true;
        }
        regrouper();
        break;
    case Prog:
        if(bprog)
        {
            bprog=false;
            aprog=true;
        }
        regrouper();
        break;
    case eSEC:
        if(bSEC)
        {
            bSEC=false;
            aSEC=true;
        }
        regrouper();
        break;
    }
}
