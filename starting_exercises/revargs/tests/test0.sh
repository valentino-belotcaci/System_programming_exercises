#!/bin/bash

exec "$1" ciao ciao | sort
exit ${PIPESTATUS[0]}


