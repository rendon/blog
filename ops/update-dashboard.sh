#!/usr/bin/env bash
function update() {
	cd /home/rendon/workspace/algoristas/dashboard
	git pull origin master | grep 'Already up-to-date'
	if [ $? -eq 1 ]
	then
		node_modules/brunch/bin/brunch build
	fi
}

while true
do
	update
	sleep 5m
done
