echo Vanilla
for domain in sailing sailing1 sailing2 sailing4
do
	echo $domain
	cd RESULTS_$domain
	./run_base.sh
	cd ../
done
