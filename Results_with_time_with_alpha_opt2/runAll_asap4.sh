echo ASAP
for domain in acadadvising acadadvising1 acadadvising2 acadadvising3
do
	echo $domain
	cd RESULTS_$domain
	./run_asap.sh
	cd ../
done
