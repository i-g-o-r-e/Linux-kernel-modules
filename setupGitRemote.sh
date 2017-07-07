#!/bin/bash

# Run this script on your repo clone to setup ssh authentication for git.

echo "Setting git origin to git@github.com:i-g-o-r-e/Linux-kernel-modules.git"
git remote set-url origin git@github.com:i-g-o-r-e/Linux-kernel-modules.git

gitremote=`git config --get remote.origin.url`
echo "Your origin is now set to $gitremote"

