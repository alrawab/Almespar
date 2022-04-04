#ifndef ORFFINDER_H
#define ORFFINDER_H

#include <QtCore>
#include "GeneticCodeQuery.h"
class  ORFFinder
{
public:

/*static QVector<QPair<int,int>>*/  QVector<QStringList>  ForwordORFs(const QString& seq,int min_length=30,int TransTable=1,bool Alternative_Starts =false);
//static QVector<QPair<int,int>> BackwordORFs(const QSequence &seq,int min_length=100,int TransTable=1,bool Alternative_Starts =false);
private:
    static int FindFirstStart(const QString &_seq,int from,int to ,const QStringList &allowable_starts/*const QRegExp &allowable_starts */);
    static QVector<int> FindStops(const QString &_seq,int from,int to ,const QStringList &allowable_stops);
    static QString transStrand(const QString &_seq);
};

#endif // ORFFINDER_H
