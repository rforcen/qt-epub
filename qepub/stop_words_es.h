#pragma once

#include <QString>
#include <QStringList>
#include <QtAlgorithms>

class StopWords {
  QString __stop_words_es =
      R"(de,la,que,el,en,y,a,los,del,se,las,por,un,para,con,no,una,su,al,
es,lo,como,más,pero,sus,le,ya,o,fue,este,ha,sí,porque,esta,
son,entre,está,cuando,muy,sin,sobre,también,me,hasta,hay,donde,
quien,desde,todo,nos,durante,todos,uno,les,ni,contra,otros,
fueron,ese,eso,había,ante,ellos,e,esto,mí,antes,algunos,qué,
unos,yo,otro,otras,otra,él,tanto,esa,estos,mucho,quienes,nada,
muchos,cual,poco,ella,estar,estas,algunas,algo,nosotros,mi,mis,
tú,te,ti,tu,tus,ellas,nosotras,vosotros,vosotras,os,mío,mía,
míos,mías,tuyo,tuya,tuyos,tuyas,suyo,suya,suyos,suyas,nuestro,
nuestra,nuestros,nuestras,vuestro,vuestra,vuestros,vuestras,esos,
esas,estoy,estás,está,estamos,estáis,están,esté,estés,estemos,
estéis,estén,estaré,estarás,estará,estaremos,estaréis,estarán,
estaría,estarías,estaríamos,estaríais,estarían,estaba,estabas,
estábamos,estabais,estaban,estuve,estuviste,estuvo,estuvimos,
estuvisteis,estuvieron,estuviera,estuvieras,estuviéramos,estuvierais,
estuvieran,estuviese,estuvieses,estuviésemos,estuvieseis,estuviesen,
estando,estado,estada,estados,estadas,estad,he,has,ha,hemos,
habéis,han,haya,hayas,hayamos,hayáis,hayan,habré,habrás,habrá,
habremos,habréis,habrán,habría,habrías,habríamos,habríais,habrían,
había,habías,habíamos,habíais,habían,hube,hubiste,hubo,hubimos,
hubisteis,hubieron,hubiera,hubieras,hubiéramos,hubierais,hubieran,
hubiese,hubieses,hubiésemos,hubieseis,hubiesen,habiendo,habido,
habida,habidos,habidas,soy,eres,es,somos,sois,son,sea,seas,
seamos,seáis,sean,seré,serás,será,seremos,seréis,serán,sería,
serías,seríamos,seríais,serían,era,eras,éramos,erais,eran,fui,
fuiste,fue,fuimos,fuisteis,fueron,fuera,fueras,fuéramos,fuerais,
fueran,fuese,fueses,fuésemos,fueseis,fuesen,siendo,sido,tengo,
tienes,tiene,tenemos,tenéis,tienen,tenga,tengas,tengamos,tengáis,
tengan,tendré,tendrás,tendrá,tendremos,tendréis,tendrán,tendría,
tendrías,tendríamos,tendríais,tendrían,tenía,tenías,teníamos,teníais,
tenían,tuve,tuviste,tuvo,tuvimos,tuvisteis,tuvieron,tuviera,
tuvieras,tuviéramos,tuvierais,tuvieran,tuviese,tuvieses,tuviésemos,
tuvieseis,tuviesen,teniendo,tenido,tenida,tenidos,tenidas,tened,tal,

si,aunque,así,gran,solo,sólo,ser,hace,sino,hacia,todas,cada,tan,dentro,
menos,puede,tras,etc,aún,siempre,ello,ella,ellos,ellas,después,cabe)";

  QStringList stop_words;

 public:
  StopWords() {
    __stop_words_es.remove('\n');
    stop_words = __stop_words_es.split(",", QString::SkipEmptyParts);
    stop_words.sort();
  }

  bool operator[](QString word) {
    return word.length() > 1
               ? std::binary_search(stop_words.begin(), stop_words.end(), word)
               : true;
  }
};