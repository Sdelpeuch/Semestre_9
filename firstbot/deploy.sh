sshpass -p "raspberry" scp motors.py firstbot.py detection.py odometry.py pi@teamthree.local:~/firstbot
sshpass -p "raspberry" ssh -t pi@teamthree.local "cd firstbot && python3 firstbot.py $1 $2 $3"
if [ "$1" = "CO" ]
then
  sshpass -p "raspberry" scp pi@teamthree.local:firstbot/map.txt ./
  python3 map.py
fi