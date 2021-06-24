#!/bin/bash
sshpass -p "syncmaster" scp gudeh@logics-server-01.inf.ufrgs.br:/home/gudeh/DNNAIGReduction/results.csv .
mv results.csv results1.csv

for i in {2..5}
do
    sshpass -p "syncmaster" scp gudeh@logics-server-01.inf.ufrgs.br:/home/gudeh/$iDNNAIG/results.csv .
    mv results.csv results$i.csv
done

#sshpass -p "syncmaster" scp gudeh@logics-server-01.inf.ufrgs.br:/home/gudeh/2DNNAIG/results.csv .
#mv results.csv results2.csv
#
#sshpass -p "syncmaster" scp gudeh@logics-server-01.inf.ufrgs.br:/home/gudeh/3DNNAIG/results.csv .
#mv results.csv results3.csv
#
#sshpass -p "syncmaster" scp gudeh@logics-server-01.inf.ufrgs.br:/home/gudeh/4DNNAIG/results.csv .
#mv results.csv results4.csv
#
#sshpass -p "syncmaster" scp gudeh@logics-server-01.inf.ufrgs.br:/home/gudeh/5DNNAIG/results.csv .
#mv results.csv results5.csv
