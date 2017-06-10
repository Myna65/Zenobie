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

#include <QFileDialog>
#include <QDir>
#include "dialog.h"
#include "ui_dialog.h"
#include "data.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    Data::parent=this;
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(onClick()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(cSEC()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(cTout()));
    od=QApplication::translate("Dialog", "Ouvrir un fichier de cr\303\251dits", 0);
    ot=tr("Fichier texte(*.txt);;Tous les fichiers(*.*)");
    fd=tr("Enregister le tableau HTML");
    ft=tr("Fichier HTML(*.html *.htm);;Tous les fichiers(*.*)");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onClick()
{
    Fichier fi=TxtC;
    if(ui->radioButton_5->isChecked())
        fi=TxtL;
    if(ui->radioButton->isChecked())
        AB(fi);
    if(ui->radioButton_2->isChecked())
        tProg(fi);
}
void Dialog::cSEC()
{
    tSEC();
}
void Dialog::AB(Fichier fi)
{
    QString source = QFileDialog::getOpenFileName(this, od, QDir::homePath(), ot);
    if(source=="")
        return;
    Data a;
    a.read(source,fi);
    a.traiter(AlB);
    a.activer(AlB);
    a.traiter(Prog);
    a.read("",In);
    if(ui->groupBox->isChecked())
    {
        if(ui->radioButton_3->isChecked())
            a=a.verifier();
        if(ui->radioButton_6->isChecked())
        {
            QString source2 = QFileDialog::getOpenFileName(this, od, QDir::homePath(), ot);
            if(source2=="")
                return;
            Data b;
            b.read(source2,fi);
            b.traiter(AlB);
            b.activer(AlB);
            b.traiter(Prog);
            b.read("",In);
            a=a.comparer(b);
        }

    }
    QString dest = QFileDialog::getSaveFileName(this, fd, QDir::homePath() , ft);
    if(dest=="")
        return;
    a.write(dest);
}
void Dialog::tProg(Fichier fi)
{
    QString source = QFileDialog::getOpenFileName(this, od, QDir::homePath(), ot);
    if(source=="")
        return;
    Data a;
    a.read(source,fi);
    a.traiter(Prog);
    a.activer(Prog);
    a.read("",In);
    if(ui->groupBox->isChecked())
    {
        if(ui->radioButton_3->isChecked())
            a=a.verifier();
        if(ui->radioButton_6->isChecked())
        {
            QString source2 = QFileDialog::getOpenFileName(this, od, QDir::homePath(), ot);
            if(source2=="")
                return;
            Data b;
            b.read(source2,fi);
            b.traiter(Prog);
            b.traiter(Prog);
            b.read("",In);
            a=a.comparer(b);
        }

    }
    QString dest = QFileDialog::getSaveFileName(this, fd, QDir::homePath() , ft);
    if(dest=="")
        return;
    a.write(dest);
}
void Dialog::tSEC()
{
    QString source1 = QFileDialog::getOpenFileName(this, od, QDir::homePath(), ot);
    if(source1=="")
        return;
    QString source2 = QFileDialog::getOpenFileName(this, od, QDir::homePath(), ot);
    if(source2=="")
        return;
    QString dest = QFileDialog::getSaveFileName(this, fd, QDir::homePath() , ft);
    if(dest=="")
        return;
    Data a;
    Data b;
    a.read(source1,TxtC);
    a.traiter(eSEC);
    a.activer(eSEC);
    b.read(source2,TxtL);
    b.traiter(eSEC);
    b.activer(eSEC);
    a = a.fusionner(b);
    a.read("",In);
    a.write(dest);
}
void Dialog::cTout()
{
    QString source1 = QFileDialog::getOpenFileName(this, QApplication::translate("Dialog", "Ouvrir le fichier de crédits dissociés récent", 0), QDir::homePath(), ot);
    if(source1=="")
        return;
    QString source2 = QFileDialog::getOpenFileName(this, QApplication::translate("Dialog", "Ouvrir le fichier de crédits variables", 0), QDir::homePath(), ot);
    if(source2=="")
        return;
    QString source3 = QFileDialog::getOpenFileName(this, QApplication::translate("Dialog", "Ouvrir le fichier de crédits dissociés ancien", 0), QDir::homePath(), ot);
    if(source3=="")
        return;
    QString dest = QFileDialog::getExistingDirectory(this, QApplication::translate("Dialog", "Choisir le dossier d'enregistrement", 0), QDir::homePath() , QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    if(dest=="")
        return;
    Data a,b,c,d,e,f,g,h,i;
    a.read(source1,TxtC);
    f=b=a;
    a.traiter(AlB);
    a.activer(AlB);
    a.traiter(Prog);
    a.read("",In);
    b.traiter(Prog);
    b.activer(Prog);
    b.read("",In);
    f.traiter(eSEC);
    f.activer(eSEC);
    c.read(source2,TxtL);
    g=d=c;
    c.traiter(AlB);
    c.activer(AlB);
    c.traiter(Prog);
    c.read("",In);
    d.traiter(Prog);
    d.activer(Prog);
    d.read("",In);
    e.read(source3,TxtC);
    e.traiter(AlB);
    e.activer(AlB);
    e.traiter(Prog);
    e.read("",In);
    e=a.comparer(e);
    g.traiter(eSEC);
    g.activer(eSEC);
    f=f.fusionner(g);
    f.read("",In);
    g=a.verifier();
    h=b.verifier();
    i=d.verifier();
    a.write((dest+QObject::tr("/CDAB.html")));
    b.write((dest+QObject::tr("/CDPR.html")));
    c.write((dest+QObject::tr("/CVAB.html")));
    d.write((dest+QObject::tr("/CVPR.html")));
    e.write((dest+QObject::tr("/Comp.html")));
    f.write((dest+QObject::tr("/CSEC.html")));
    g.write((dest+QObject::tr("/ANCDAB.html")));
    h.write((dest+QObject::tr("/ANCDPR.html")));
    i.write((dest+QObject::tr("/ANCVPR.html")));
}
