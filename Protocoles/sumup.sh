#! /usr/local/bin/zsh
for f in `find . -name "*.txt"`; do; echo "-------------------------------------------"; cat $f; done;
