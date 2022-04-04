#ifndef GENETICCODEQUERY_H
#define GENETICCODEQUERY_H

#include <QtCore>
#include "GeneticCodeData.h"

class  GeneticCodeQuery
{
public:
    /**
 * @brief GetTransList
 * source: http://www.ncbi.nlm.nih.gov/Taxonomy/Utils/wprintgc.cgi
 * http://www.bioinformatics.org/jambw/2/3/TranslationTables.html
 * @return
 */
static QList<GeneticCode> GetTransList();
static GeneticCode  recod(const QString& Tbn);
static GeneticCode  recod(int Tbn);
static QStringList GettbNames();
static QList<int>  GettbIds();
static QMap<QString,QStringList> GetRoles(int Tbn);
static QMap<QString,QStringList> GetRoles(const QString& Tbn);
    //GeneticCodeQuery();
  //  ~GeneticCodeQuery();
};



#endif // GENETICCODEQUERY_H
