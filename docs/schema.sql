-- Starfield Data Index Schema

-- Sources tracks every archive or plugin file being indexed
CREATE TABLE IF NOT EXISTS sources (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    path VARCHAR(1024) NOT NULL,
    UNIQUE KEY (path)
);

-- Records tracks individual TLV records within plugins
CREATE TABLE IF NOT EXISTS records (
    source_id INT NOT NULL,
    offset BIGINT NOT NULL,
    formid INT NOT NULL,
    signature VARCHAR(8),
    size INT,
    PRIMARY KEY (source_id, offset),
    FOREIGN KEY (source_id) REFERENCES sources(id) ON DELETE CASCADE
);

-- EDIDs provide a fast lookup for record editor IDs
CREATE TABLE IF NOT EXISTS edids (
    id INT AUTO_INCREMENT PRIMARY KEY,
    source_id INT NOT NULL,
    offset BIGINT NOT NULL,
    edid VARCHAR(255) NOT NULL,
    FOREIGN KEY (source_id, offset) REFERENCES records(source_id, offset) ON DELETE CASCADE,
    INDEX (edid)
);

-- Assets tracks every file encountered in the Data folder and within BA2 archives
CREATE TABLE IF NOT EXISTS assets (
    id INT AUTO_INCREMENT PRIMARY KEY,
    source_id INT, -- NULL for loose files
    virtual_path VARCHAR(1024) NOT NULL,
    literal_path VARCHAR(1024) NOT NULL,
    internal_path VARCHAR(1024),
    size BIGINT,
    FOREIGN KEY (source_id) REFERENCES sources(id) ON DELETE CASCADE,
    INDEX (virtual_path)
);
