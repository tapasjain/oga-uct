echo ASAP
for domain in navigation navigation1 navigation2 navigation3 navigation4
do
	echo $domain
	cd RESULTS_$domain
	./run_asap.sh
	cd ../
done
