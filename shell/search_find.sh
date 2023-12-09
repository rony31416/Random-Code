#!/bin/bash

  read -p "Enter a file path : " path
 if [ -d "$path" ]; then
    find "$path" -name "bsse13*" | sort
 else
    echo "Error ! " 
 fi
