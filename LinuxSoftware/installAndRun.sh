#!/bin/bash

# Function to print a progress message
print_message() {
    echo -e "\n===== $1 =====\n"
}

# Start of the installation
print_message "Starting Installation"

# Update the package list
print_message "Updating package list..."
sudo apt-get update

# Install necessary system libraries to run qt app 
print_message "Installing required system libraries..."
sudo apt-get install -y \
    libqt6core6 libqt6gui6 libqt6widgets6 \
    libstdc++6 libc6 \
    libegl1 libfontconfig1 \
    libx11-6 libxkbcommon0 libopengl0 \
    libpng16-16 libharfbuzz0b libfreetype6 libz1 \
    libicu66 libpcre2-16-0 libexpat1 libuuid1 libxcb1 libpcre3 \
    libdbus-1-3 libgraphite2-3 libsystemd0 libbsd0 librt1 liblzma5 liblz4-1 libgcrypt20 libgpg-error0

# Define the path to the application's build folder the folder where the install lies 
APP_BUILD_DIR="./#!/bin/bash

# Function to print a progress message
print_message() {
    echo -e "\n===== $1 =====\n"
}

# Start of the installation
print_message "Starting Installation"

# Update the package list
print_message "Updating package list..."
sudo apt-get update

# Install necessary system libraries
print_message "Installing required system libraries..."
sudo apt-get install -y \
    libqt6core6 libqt6gui6 libqt6widgets6 \
    libstdc++6 libc6 \
    libegl1 libfontconfig1 \
    libx11-6 libxkbcommon0 libopengl0 \
    libpng16-16 libharfbuzz0b libfreetype6 libz1 \
    libicu66 libpcre2-16-0 libexpat1 libuuid1 libxcb1 libpcre3 \
    libdbus-1-3 libgraphite2-3 libsystemd0 libbsd0 librt1 liblzma5 liblz4-1 libgcrypt20 libgpg-error0

# Define the path to the application's build folder
APP_BUILD_DIR="./run-build"
APP_BINARY="$APP_BUILD_DIR/appBreathTracker"

# Check if the build folder and binary exist
if [ ! -d "$APP_BUILD_DIR" ]; then
    echo "Error: Build directory $APP_BUILD_DIR does not exist!"
    exit 1
fi

if [ ! -f "$APP_BINARY" ]; then
    echo "Error: Application binary $APP_BINARY does not exist!"
    exit 1
fi

# Copy your application's binary to /usr/local/bin
print_message "Copying application binary to /usr/local/bin..."
sudo cp "$APP_BINARY" /usr/local/bin/appBreathTracker

# Make sure the system can find the Qt libraries
print_message "Running ldconfig to refresh shared library cache..."
sudo ldconfig

# Set executable permissions on the copied binary
print_message "Setting executable permissions..."
sudo chmod +x /usr/local/bin/appBreathTracker

# Finish installation
print_message "Installation complete! Running the application now..."

# Create and make the run.sh script executable
cat << 'EOF' > run.sh
#!/bin/bash
# Function to print a progress message
print_message() {
    echo -e "\n===== $1 =====\n"
}

# Start the application
print_message "Starting BreathTracker Application..."
/usr/local/bin/appBreathTracker
EOF

# Make run.sh executable
chmod +x run.sh

# Execute run.sh
./run.sh
"
APP_BINARY="$APP_BUILD_DIR/appBreathTracker"

# Check if the build folder and binary exist
if [ ! -d "$APP_BUILD_DIR" ]; then
    echo "Error: Build directory $APP_BUILD_DIR does not exist!"
    exit 1
fi

if [ ! -f "$APP_BINARY" ]; then
    echo "Error: Application binary $APP_BINARY does not exist!"
    exit 1
fi

# Copy your application's binary to /usr/local/bin, to make executable is within an environment where path variables are set 
print_message "Copying application binary to /usr/local/bin..."
sudo cp "$APP_BINARY" /usr/local/bin/appBreathTracker

# Make sure the system can find the Qt libraries
print_message "Running ldconfig to refresh shared library cache..."
sudo ldconfig

# Set executable permissions on the copied binary
print_message "Setting executable permissions..."
sudo chmod +x /usr/local/bin/appBreathTracker

# Finish installation
print_message "Installation complete! Running the application now..."

# Create and make the run.sh script executable
cat << 'EOF' > run.sh
#!/bin/bash
# Function to print a progress message
print_message() {
    echo -e "\n===== $1 =====\n"
}

# Start the application
print_message "Starting BreathTracker Application..."
/usr/local/bin/appBreathTracker
EOF

# Make run.sh executable
chmod +x run.sh

# Execute run.sh
./run.sh
