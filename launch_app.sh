#!/bin/bash

#grant executing permision
chmod +x launch_app.sh

# Check if exactly one argument is given
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <duration_in_seconds>"
    exit 1
fi

# Compile the C application
make

# Run the application in the background
echo "Running Application."
./main &
APP_PID=$!

# Wait for the specified duration
sleep $1

# Send SIGINT to the application
kill -SIGINT $APP_PID

# Wait for the application to exit
wait $APP_PID
echo "Application exited."