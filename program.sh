time=0.0
read n m
#echo $n $m 
intersections=0
for i in `seq 1 $m`
do
    inters_time=`echo $n | ./input| ./code`
    t="$(echo "$inters_time"|awk '{print $2}')"
    time=`echo "$time + $t"| bc -l`
    e="$(echo "$inters_time"|awk '{print $1}')"
    intersections=`echo $e+$intersections|bc -l`
done
echo "$time/$m" | bc -l  
echo "$intersections/$m" | bc -l 
