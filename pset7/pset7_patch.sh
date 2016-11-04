#!/bin/bash

find -name *.php | xargs chmod 640

find -type d | xargs chmod 711

find -not -type d -and -not -name *.php | xargs chmod 644