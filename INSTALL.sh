#! /bin/bash

cp scripts/bash_installation.sh .
bash bash_installation.sh
rm bash_installation.sh
bash scripts/construct_default_conf.sh
