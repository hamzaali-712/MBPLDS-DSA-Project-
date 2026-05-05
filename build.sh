#!/bin/bash
g++ -I src src/main.cpp src/core/User.cpp src/core/PasswordRecord.cpp src/engine/UserManager.cpp src/engine/HashUtils.cpp src/engine/PasswordEngine.cpp src/database/DatabaseManager.cpp src/ui/CLI.cpp -o mbplds
