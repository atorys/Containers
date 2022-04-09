#!/bin/bash
./ft_containers > ft_logs
./std_containers > std_logs
diff ft_logs std_logs > diff_logs
rm -rf ft_logs std_logs

if [ ! -s ./diff_logs ]
then
	echo "OK ✅ "
else
	echo "KO :( ❌ "
fi
