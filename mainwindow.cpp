#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ORFFinder.h"
#include <QDebug>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <QFileDialog>
#include <QScreen>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
  //  this->setStyleSheet("background-color: white");
//move(screen()->geometry().center() - frameGeometry().center());
ui->textBrowser_2->setText(transStrand(ui->textBrowser->toPlainText()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->tableWidget->setRowCount(0);
    ui->tableWidget_2->setRowCount(0);

qDebug()<< ui->comboBox_2->currentIndex();

 ORFFinder * mk=new ORFFinder();
 //std::reverse(s.begin(), s.end())
// QString sq=ui->textBrowser_2->toPlainText().simplified();
//qDebug()<<ui->textBrowser->toPlainText().simplified().length();
int orf_len=ui->comboBox->currentText().toInt();
int trans_tab=tab_no();                 //1;//ui->comboBox_2->currentIndex()+1;
if(ui->checkBox->isChecked())//   checkState(Qt::Unchecked))
 othe_start=true;
else
  othe_start=false;

 QVector<QStringList>  mm= mk->ForwordORFs(ui->textBrowser->toPlainText().simplified(),orf_len,trans_tab,othe_start);
// QVector<QStringList>  mm2= mk->ForwordORFs(sq);


 //qDebug() << list[4];
   ui->tableWidget->setRowCount(mm.size());
//qDebug()<< ui->tableWidget->columnCount();

for (int x=0; x< ui->tableWidget->rowCount();x++){
    QTableWidgetItem * it;

    for (int y=0; y< ui->tableWidget->columnCount();y++)
    {
       //  qDebug()<<y; //mm[x][1];
        it=new QTableWidgetItem;
        it->setTextAlignment(Qt::AlignCenter);
        if(y==0)
            it->setText("ORF-"+QString::number(x+1));
        if(y==1)
            it->setText("+") ;
        if(y==2)
            it->setText(mm[x][0]);
        if(y==3)
            it->setText(mm[x][1]);
        if(y==4)
            it->setText(mm[x][2]);
        if(y==5)
            it->setText(mm[x][3]);


        ui->tableWidget->setItem(x,y,it);
    }


}
//------------------------------
QVector<QStringList>  mm2= mk->ForwordORFs(ui->textBrowser_2->toPlainText().simplified(),orf_len,trans_tab,othe_start);
int len=ui->textBrowser_2->toPlainText().simplified().length()+1;
 ui->tableWidget_2->setRowCount(mm2.size());

 for (int x=0; x< ui->tableWidget_2->rowCount();x++){
     QTableWidgetItem * it;

     for (int y=0; y< ui->tableWidget_2->columnCount();y++)
     {
        //  qDebug()<<y; //mm[x][1];
         it=new QTableWidgetItem;
         it->setTextAlignment(Qt::AlignCenter);
         if(y==0)
             it->setText("ORF-"+QString::number(x+1));
         if(y==1)
             it->setText("-") ;
         if(y==2)
             it->setText(mm2[x][0]);
         if(y==3)
             it->setText(QString::number( len-(mm2[x][1]).toInt())  );
         if(y==4)
             it->setText(QString::number( len-(mm2[x][2]).toInt())  );//                                      mm2[x][2]);
         if(y==5)
             it->setText(mm2[x][3]);


         ui->tableWidget_2->setItem(x,y,it);
     }


 }

}


QString MainWindow::transStrand(const QString &seq)
{

    QString tmp;
     //  for (int i =0;i< seq.length() ;  i++)
     for (int i = seq.length() - 1; i >= 0; i--)
       {
           switch (seq[i].toLatin1())
           {
           case 'a':
           case 'A': tmp.append('T');
               break;
           case 't':
           case 'T': tmp.append('A');
               break;
           case 'c':
           case 'C': tmp.append('G');
               break;
           case 'g':
           case 'G': tmp.append('C');
               break;
           }
       }
    return tmp;
}



void MainWindow::on_pushButton_2_clicked()
{
    QString headerline;
    QString sequence;
    QString file2Name = QFileDialog::getOpenFileName(this,
                                                     tr("Open FASTA File"), "/home", tr("FASTA Files (*.fa *.FASTA)"));

    std::ifstream input(file2Name.toStdString());
    std::string line, name, content;
        while( std::getline( input, line ).good() ){
            if( line.empty() || line[0] == '>' ){ // Identifier marker
                if( !name.empty() ){ // Print out what we read from the last entry
                    std::cout << name << " : " << content << std::endl;
                    name.clear();
                }
                if( !line.empty() ){
                    name = line.substr(1);
                }
                content.clear();
            } else if( !name.empty() ){
                if( line.find(' ') != std::string::npos ){ // Invalid sequence--no spaces allowed
                    name.clear();
                    content.clear();
                } else {
                    content += line;
                }
            }
        }
      // if( !name.empty() ){ // Print out what we read from the last entry
           // std::cout << name << " : " << content << std::endl;
     //   }
QString seq=QString::fromUtf8(content.c_str());
ui->textBrowser->clear();
ui->textBrowser_2 ->clear();
//ui->tableWidget->clearContents();
/*for ( int i = 0; i < ui->tableWidget->rowCount(); ++i )
{
    ui->tableWidget->removeRow(i);
}*/
ui->tableWidget->setRowCount(0);
ui->tableWidget_2->setRowCount(0);

ui->textBrowser->setText(seq);
ui->textBrowser_2->setText(transStrand(ui->textBrowser->toPlainText()));

//qDebug()<<ui->comboBox->currentText().toUInt();
//qDebug()<<ui->comboBox_2->currentIndex();
}



int MainWindow::tab_no()
{
    int tb = 1;

    switch( ui->comboBox_2->currentIndex() )
    {
    case 0:
        tb = 1 ;
        break ;
    case 1:
        tb = 2 ;
        break ;
    case 2:
        tb = 3 ;
        break ;
    case 3:
        tb = 4 ;
        break ;
    case 4:
        tb = 5 ;
        break ;
    case 5:
        tb = 6 ;
        break ;
    case 6:
        tb = 9 ;
        break ;
    case 7:
        tb = 10 ;
        break ;
    case 8:
        tb = 11 ;
        break ;
    case 9:
        tb = 12 ;
        break ;
    case 10:
        tb = 13 ;
        break ;
    case 11:
        tb = 14 ;
        break ;
    case 12:
        tb = 15 ;
        break ;
    case 13:
        tb = 16 ;
        break ;
    case 14:
        tb = 21 ;
        break ;
    case 15:
        tb = 22 ;
        break ;
    case 16:
        tb = 23 ;
        break ;
    case 17:
        tb = 24 ;
        break ;
    case 18:
        tb = 25 ;
        break ;
    case 19:
        tb = 26 ;
        break ;
    case 20:
        tb = 27 ;
        break ;
    case 21:
        tb = 28 ;
        break ;
    case 22:
        tb = 29 ;
        break ;
    case 23:
        tb = 30 ;
        break ;
    case 24:
        tb = 31 ;
        break ;
    case 25:
        tb = 33 ;
        break ;
    }
    return tb;

}
