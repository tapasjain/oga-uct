echo OGA
for domain in sysadmin sysadmin1 sysadmin2 sysadmin3 sysadmin4 sysadmin5 
do
	echo $domain
	cd RESULTS_$domain
	./run_oga.sh
	cd ../
done
