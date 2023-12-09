#!/bin/bash

 parent_folder="../"

 if [ -d "$parent_folder" ]; then 
    cd "$parent_folder"


    touch aditysona

    echo "folder is created"
 else
    echo "error"
 fi
