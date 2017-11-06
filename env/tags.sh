touch tags.lst
find | grep "\.hpp$" >> tags.lst
find | grep "\.hxx$" >> tags.lst
find | grep "\.cpp$" >> tags.lst
ctags -R --exclude=.git .
cscope -i tags.lst
