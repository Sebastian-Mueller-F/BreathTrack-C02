#!/bin/bash
# Function to print a progress message
print_message() {
    echo -e "\n===== $1 =====\n"
}

# Start the application
print_message "Starting BreathTracker Application..."
/usr/local/bin/appBreathTracker
