#! /bin/sh

if [[ ! -d $(pwd)/scripts  ]]; then
  echo "execute this command from root of the project"
  exit 1
fi

if [[ $# -lt 1 ]]; then
  echo "new_data_structure name_1 name_2 name_3 ..."
  exit 2
fi

for name_dt in $@
do
  if [[ ! -d src/$name_dt ]]; then
    echo "creating directory src/$name_dt"
    mkdir src/$name_dt
  fi
  
  if [[ ! -f src/$name_dt/$name_dt.h ]]; then
    echo "creating header file src/$name_dt/$name_dt.h"
    cp templates/data_st.h src/$name_dt/$name_dt.h
    sed -i "s/struct\ bst/struct\ $name_dt/g" src/$name_dt/$name_dt.h
    sed -i "s/bst/$name_dt/g" src/$name_dt/$name_dt.h
    sed -i "s/BST/${name_dt^^}/g" src/$name_dt/$name_dt.h
  fi

  if [[ ! -f src/$name_dt/$name_dt.c ]]; then
    echo "creating implementation file src/$name_dt/$name_dt.c"
    cp templates/data_st.c src/$name_dt/$name_dt.c
    sed -i "s/struct\ bst/struct\ $name_dt/g" src/$name_dt/$name_dt.c
    sed -i "s/bst/$name_dt/g" src/$name_dt/$name_dt.c
    sed -i "s/BST/${name_dt^^}/g" src/$name_dt/$name_dt.c
  fi
  
  echo "creating links for sources"
  cd src/$name_dt
  ln -f -s ../common/tree_operations.h tree_operations.h
  cd ../..

  if [[ ! -d tests/$name_dt ]]; then
    echo "creating directory tests/$name_dt"
    mkdir tests/$name_dt
  fi

  if [[ ! -f tests/$name_dt/test_$name_dt.c ]]; then
    echo "creating testing file for $name_dt"
    cp templates/test_data_st.c tests/$name_dt/test_$name_dt.c
    sed -i "s/bst/$name_dt/g" tests/$name_dt/test_$name_dt.c
    sed -i "s/BST/${name_dt^^}/g" tests/$name_dt/test_$name_dt.c
  fi

  if [[ ! -f test/$name_dt/Makefile ]]; then
    echo "creating Makefile for $name_dt"
    cp templates/Makefile tests/$name_dt/Makefile
    sed -i "s/bst/$name_dt/g" tests/$name_dt/Makefile
  fi

  echo "creating links for testing"
  cd tests/$name_dt
  ln -f -s ../../src/$name_dt/$name_dt.h $name_dt.h
  ln -f -s ../../src/$name_dt/$name_dt.c $name_dt.c
  ln -f -s ../../src/common/tree_operations.h tree_operations.h
  ln -f -s ../../src/common/tree_operations.c tree_operations.c
  cd ../..

done
