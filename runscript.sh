filename=config_space0.conf
numberofevents=10000

#abslength1[0] and abslength2[0] makes a pair
abslength1=(35 0.35)
abslength2=(35 0.35)
#same is for refrind
refrind1=(1.59 1.57)
refrind2=(1.57 1.59)

positions=(1 2 3 4 5 6 7 8 9 10) #offset = 1 because of the sipm size, along z axis

#echo ${refrind2[0]}

for i in ${positions[@]}
do
    for j in {0..1} #absorptionlength
    do
        for k in {0..1} #refraciveindex
        do
            sed -i -e "s/^numberofevents=.*$/numberofevents=$numberofevents/" \
                -e "s/^abslength1=.*$/abslength1=${abslength1[j]}/" \
                -e "s/^abslength2=.*$/abslength2=${abslength2[j]}/" \
                -e "s/^refrindex1=.*$/refrindex1=${refrind1[k]}/" \
                -e "s/^refrindex2=.*$/refrindex2=${refrind2[k]}/" \
                -e "s/^pgpositionz=.*$/pgpositionz=$i/" \
                $filename
            outfilename="eventdata_pos"$i"_abs1"${abslength1[j]}"_abs2"${abslength2[j]}"_refr1"${refrind1[k]}"_refr2"${refrind2[k]}".txt"
            echo "Processing $outfilename..."
            #cp config_space.conf $filename
            #./sipm -f config_space.conf -v | grep 'Number of photons in event' | awk '{print $6}' > $outfilename
        done
    done
done