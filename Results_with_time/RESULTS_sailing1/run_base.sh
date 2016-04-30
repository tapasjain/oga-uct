echo -n '' > BASE/baseNew.txt

for n in 30 60 100 150 200 300 400 500
do
	echo $n
	./../../mdp-engine-master/sailing/sailing_NEW  -f -a 0 -h 0 -s 0 -t 1000 50 random uct $n 50 0 > BASE/res$n
	
	echo $n $(grep -n "uct(random" BASE/res$n | awk '{print $2,$3,$5}') >> BASE/baseNew.txt	# Adding results to merged file too
done

cp BASE/baseNew.txt ALL/

