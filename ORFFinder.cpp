



#include "ORFFinder.h"

/*QVector<QPair<int,int>>*/ QVector<QStringList>  ORFFinder::ForwordORFs(const QString &seq, int min_length, int TransTable, bool Alternative_Starts)
{
   // qDebug()<< transStrand(seq);
    int min_length_bp=min_length;
    bool longest_orfs=true;
    int from, to;
    QString sig="";
    QMap<QString, QStringList> gamma=GeneticCodeQuery::GetRoles(TransTable);
    QVector<QPair<int,int>> ranges;
    QVector<QStringList> osama;
    QStringList allowable_starts ;
    allowable_starts.append(gamma.value("StartCodon"));
    if(Alternative_Starts)
        allowable_starts.append(gamma.value("StartAlteranative"));
    QStringList allowable_stops;
    allowable_stops.append(gamma.value("StopCodon"));
  //  qDebug()<<allowable_stops;

    QVector<QVector<int> > stops;
    QList<int> frm = QList<int>() << 1 << 2<<3<<-1 <<-2<<-3;
    for (int pos = 0;  pos < 3;  pos++) {

          stops.push_back(FindStops(seq,pos,seq.size(),allowable_stops));



    }

    // for each reading frame, calculate the orfs
   for (int frame = 0;  frame < 3;  frame++) {
// for (int frame = 0;frame <frm.count();frame++){

        if (stops[frame].empty()) {
            // no stops in this frame;
            from = frame;



            to = ((seq.size() - from) / 3) * 3 + from - 1;
            if (!allowable_starts.empty()) {
                from = FindFirstStart(seq, from, to, allowable_starts);
            }
            if (to - from + 1 >= min_length_bp) {
                ranges.push_back(qMakePair(from, to));

              //  qDebug()<<from << "---"<< to<<"-----"<<to-from <<" "<<frame+1;
                QStringList orf1 = { QString::number(frame+1), QString::number(from), QString::number(to),QString::number((to-from)+1) };
                osama.push_back(orf1);

                if (!longest_orfs && !allowable_starts.empty()) {
                    for (from += 3; from < to; from += 3) {
                        from = FindFirstStart(seq, from, to, allowable_starts);
                        if (to - from + 1 < min_length_bp)
                            break;
                        ranges.push_back(qMakePair(from, to));
                      //  qDebug()<<from << "---"<< to<<"-----"<<from-to <<" "<<frame+1;
                        QStringList orf1 = { QString::number(frame+1), QString::number(from), QString::number(to),QString::number((to-from)+1) };
                        osama.push_back(orf1);
                    }
                }
            }
            continue;
        }



        // deal specially with first ORF
        from = frame;
        to = stops[frame].front() ;//- 1;

        if (to - from + 1 >= min_length_bp) {
            if (!allowable_starts.empty()) {
                from = FindFirstStart(seq, from, to, allowable_starts);
            }
            if (from < to && to - from + 1 >= min_length_bp) {
                ranges.push_back(qMakePair(from, to+2));
// qDebug()<<from << "---"<< to<<"-----"<<from-to <<" "<<frame+1;
                QStringList orf1 = { QString::number(frame+1), QString::number(from), QString::number(to),QString::number((to-from)+1) };
                osama.push_back(orf1);
                if (!longest_orfs && !allowable_starts.empty()) {
                    for (from += 3; from < to; from += 3) {
                        from = FindFirstStart(seq, from, to, allowable_starts);
                        if (to - from + 1 < min_length_bp)
                            break;

                        ranges.push_back(qMakePair(from, to));
 //qDebug()<<from << "---"<< to<<"-----"<<from-to <<" "<<frame+1;
                        QStringList orf1 = { QString::number(frame+1), QString::number(from), QString::number(to),QString::number((to-from)+1) };
                        osama.push_back(orf1);
                    }
                }
            }
        }




        for (unsigned int i = 0;  i < stops[frame].size() - 1;  i++) {
            from = stops[frame][i] + 3;
            to = stops[frame][i + 1];// - 1;

            if (to - from + 1 >= min_length_bp) {
                if (!allowable_starts.empty()) {
                    from = FindFirstStart(seq, from, to, allowable_starts);
                    if (from >= to || to - from + 1 < min_length_bp) {
                        continue;
                    }
                }
                ranges.push_back(qMakePair(from, to));
 //qDebug()<<from << "---"<< to<<"-----"<<from-to <<" "<<frame+1;
                QStringList orf1 = { QString::number(frame+1), QString::number(from), QString::number(to),QString::number((to-from)+1) };
                osama.push_back(orf1);
                if (!longest_orfs && !allowable_starts.empty()) {
                    for (from += 3; from < to; from += 3) {
                        from = FindFirstStart(seq, from, to, allowable_starts);
                        if (to - from + 1 < min_length_bp)
                            break;

                        ranges.push_back(qMakePair(from, to));
                    //   qDebug()<<from << "---"<< to<<"-----"<<from-to <<" "<<frame+1;
                        QStringList orf1 = { QString::number(frame+1), QString::number(from), QString::number(to),QString::number((to-from)+1) };
                        osama.push_back(orf1);
                    }
                }
            }
        }




        // deal specially with last ORF
        from = stops[frame].back() + 3;

        to = ((seq.size() - from) / 3) * 3 + from;// - 1;

        if (to - from + 1 >= min_length_bp) {
            if (!allowable_starts.empty()) {
                from = FindFirstStart(seq, from, to, allowable_starts);
                if (from >= to || to - from + 1 < min_length_bp) {
                    continue;
                }
            }
            ranges.push_back(qMakePair(from, to));
 //qDebug()<<from << "---"<< to<<"-----"<<from-to <<" "<<frame+1;
            QStringList orf1 = { QString::number(frame+1), QString::number(from), QString::number(to),QString::number((to-from)+1) };
            osama.push_back(orf1);
            if (!longest_orfs && !allowable_starts.empty()) {
                for (from += 3; from < to; from += 3) {
                    from = FindFirstStart(seq, from, to, allowable_starts);
                    if (to - from + 1 < min_length_bp)
                        break;

                    ranges.push_back(qMakePair(from, to));
                  //  qDebug()<<from << "---"<< to<<"-----"<<from-to <<" "<<frame+1;
                    QStringList orf1 = { QString::number(frame+1), QString::number(from), QString::number(to),QString::number((to-from)+1) };
                    osama.push_back(orf1);
                }
            }
        }


    }


  //  return ranges;
   return osama;
}
/*
QVector<QPair<int, int> > ORFFinder::BackwordORFs(const QSequence& seq, int min_length, int TransTable, bool Alternative_Starts)
{
    QSequence _seq=( SequenceTools::GetComplement( SequenceTools::Reverse( seq)));

return ForwordORFs(_seq,min_length,TransTable,Alternative_Starts);
}
*/



int ORFFinder::FindFirstStart(const QString &_seq, int from, int to, const QStringList &allowable_starts)
{

    for(from;from<to;from+=3){
        QString tmp=_seq.mid(from,3);
        if(tmp.size()>2)
        {

            QStringList::const_iterator  it;
            for (it = allowable_starts.begin(); it != allowable_starts.end(); ++it)
            {
                if(tmp==*it)
                    return from+1;

            }
        }
    }
}

QVector<int> ORFFinder::FindStops(const QString &_seq, int from, int to, const QStringList &allowable_stops)
{
    QVector<int> tmpvec;

    for(from;from <to;from+=3)
    {
        QString tmp=_seq.mid(from,3);

        if(tmp.size()>2)
        {
            ;
            QStringList::const_iterator  it;
            for (it = allowable_stops.begin(); it != allowable_stops.end(); ++it)
            {
                if(tmp==*it)
                    tmpvec.push_back(from+3);
            }

        }

    }

    return tmpvec;
}

 QString ORFFinder::transStrand(const QString &seq)
 {

     QString tmp;
        for (int i =0;i< seq.length() ;  i++)
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
