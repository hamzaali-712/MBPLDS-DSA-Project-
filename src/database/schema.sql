CREATE DATABASE IF NOT EXISTS mbplds;
USE mbplds;

CREATE TABLE users (
    id INT PRIMARY KEY,
    username VARCHAR(50) UNIQUE NOT NULL,
    risk_level INT DEFAULT 0
);

CREATE TABLE passwords (
    log_id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT,
    hash VARCHAR(64) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE
);

CREATE TABLE leaked_passwords (
    hash VARCHAR(64) PRIMARY KEY
);

CREATE TABLE weak_passwords (
    word VARCHAR(50) PRIMARY KEY
);
