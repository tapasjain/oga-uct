for k in 5 7
do
	echo K=$k

	echo -n '' > K$k/k$k\New.txt

	for n in 30 60 100 150 200 300 400 500 600 700 850 1000
	do
		echo $n
		./../../OGA/race/race_NEW -f -a 0 -h 0 -s 0 -t 1000 ../../OGA/race/tracks/barto-big.track random uct $n 50 $k > K$k/res$n
		
		echo $n $(grep -n "uct(random" K$k/res$n | awk '{print $2,$3,$5}') >> K$k/k$k\New.txt	# Adding results to merged file too
	done

	cp K$k/k$k\New.txt ALL/ 
done

