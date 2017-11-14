echo "removing old stuff ..."
rm -rf cscope.out tags tags.lst

echo "creating new stuff ..."
find | egrep -i "\.(h|hpp)$" >> tags.lst
find | egrep -i "\.(c|cpp)$" >> tags.lst
find | egrep -i "\.(hxx)$" >> tags.lst
sort tags.lst > tags.lst.sorted
mv tags.lst.sorted tags.lst

echo "executing ctags ..."
ctags -L tags.lst
# ctags -R --exclude=.git .

echo "executing cscope ..."
cscope -i tags.lst

# run this script with following
# dos2unix tags.sh; chmod +x tags.sh; ./tags.sh
